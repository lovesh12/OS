#include <bits/stdc++.h>

using namespace std;

int buffer_size = 50;
vector<int> buffer;

struct semaphore
{
    int mutex;
    int full;
    int empty;

    semaphore()
    {
        full = 0;
        mutex = 1;
        empty = buffer_size;
    }
} s;

void wait(int &s)
{
    while (s <= 0)
        ;
    s--;
}

void signal(int &s)
{
    s++;
}

void producer()
{
    int loop = 50;
    do
    {
        wait(s.empty); // counting semaphore
        wait(s.mutex); // lock binary semaphore

        // place buffer
        buffer.push_back(1);
        cout << "Buffer size: " << buffer.size() << endl;

        signal(s.mutex);
        signal(s.full);

    } while (loop--);
}

void consumer()
{

    int loop = 10;
    {
        wait(s.full);
        wait(s.mutex);

        // remove from buffer
        buffer.pop_back();
        cout << "Buffer size: " << buffer.size() << endl;

        signal(s.mutex);
        signal(s.empty);
    }
    while (loop--)
        ;
}

int main()
{

    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}