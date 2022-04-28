#include <iostream>
#include <mutex>
#include <thread>

std::mutex read_wrt;
std::mutex read;
std::mutex output;

int readersCount = 0;

int counter = 0;

long rand_time()
{
    return 1000L + (rand() % 1000);
}

void critical_write()
{
    counter++;
}

void writer_task()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(rand_time()));

    do
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand_time()));

        read_wrt.lock();
        critical_write();
        read_wrt.unlock();
    } while (true);
}

void critical_read()
{
    int counterVal = counter;

    output.lock();
    printf("Counter: %d\n", counterVal);
    output.unlock();
}

void read_task()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(rand_time()));

    do
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand_time()));

        read.lock();
        readersCount++;

        if (readersCount == 1)
            read_wrt.lock();

        read.unlock();

        critical_read();

        read.lock();
        readersCount--;

        if (readersCount == 0)
            read_wrt.unlock();
        read.unlock();
    } while (true);
}

int main()
{
    srand(time(0));

    std::thread readers[10], writers[5];

    for (int i = 0; i < 10; i++)
    {
        readers[i] = std::thread(read_task);
    }

    for (int i = 0; i < 5; i++)
    {
        writers[i] = std::thread(writer_task);
    }

    for (int i = 0; i < 10; i++)
    {
        readers[i].join();
    }
    for (int i = 0; i < 5; i++)
    {
        writers[i].join();
    }

    return 0;
}