#include <bits/stdc++.h>
#include <thread>

using namespace std;

int N = 5;

vector<int> chopstick(N, 1);

void lock(int &s)
{
    while (s == 0)
        ;
    s = 0;
}

void unlock(int &s)
{
    s = 1;
}

void philosopher(int i)
{
    while (true)
    {
        lock(chopstick[i]);
        lock(chopstick[(i + 1) % 5]);

        this_thread::sleep_for(1000ms);

        cout
            << "\nPhilosopher Eating: " << i + 1 << " with chopstick " << i + 1 << " and " << ((i + 1) % 5) + 1;

        this_thread::sleep_for(1000ms);

        unlock(chopstick[i]);
        unlock(chopstick[(i + 1) % 5]);

        cout
            << "\nPhilosopher: " << i + 1 << " puts down chopsticks " << i + 1 << " and " << ((i + 1) % 5) + 1;

        this_thread::sleep_for(1000ms);

        cout << "\nPhilosopher Thinking: " << i + 1;
    }
}

int main()
{
    thread t1(philosopher, 0);
    thread t2(philosopher, 1);
    thread t3(philosopher, 2);
    thread t4(philosopher, 3);
    thread t5(philosopher, 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    return 0;
}