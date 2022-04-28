#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<bool> flag1, flag2;
atomic<int> turn;

int counter = 0;

void process1()
{
    int loop = 10;
    do
    {
        flag1 = true;
        turn = 2;

        while (flag2 && turn == 2)
            ;
        counter++;
        cout << "Process 1: " << counter << endl;
        flag1 = false;
    } while (loop--);
}

void process2()
{
    int loop = 10;
    do
    {
        flag2 = true;
        turn = 1;
        while (flag1 && turn == 1)
            ;
        // Critical Section
        counter++;
        cout << "Process 2: " << counter << endl;
        flag2 = false;
    } while (loop--);
}

int main()
{
    thread t1(process1);
    thread t2(process2);

    t1.join();
    t2.join();

    return 0;
}