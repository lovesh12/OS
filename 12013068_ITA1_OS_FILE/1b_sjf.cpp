#include <bits/stdc++.h>

using namespace std;

struct process
{
    int id;
    int burst;
    int arrival;
    int waitTime;
    int startTime;

    process(int id, int burst, int arrival) : waitTime(-1), id(id), burst(burst), arrival(arrival){};

    bool operator>(const process &j) const
    {
        return burst > j.burst;
    }

    bool operator<(const process &j) const
    {
        return arrival < j.arrival;
    }
};

int main()
{
    cout << "Enter no. of processes: " << endl;
    int n;
    cin >> n;
    vector<process> processes;
    for (int i = 0; i < n; i++)
    {
        int burst, arrival;
        cout << "Enter Burst, Arrival Time for P" << (i + 1) << ": ";
        cin >> burst >> arrival;
        processes.push_back(process(i + 1, burst, arrival));
    }

    sort(processes.begin(), processes.end());

    priority_queue<process, vector<process>, greater<process>> queue;
    queue.push(processes[0]);

    vector<process> order;

    int lastCompTime = processes[0].arrival;
    int j = 1;

    while (!queue.empty())
    {
        process p = queue.top();
        queue.pop();
        lastCompTime += p.burst;
        order.push_back(p);

        while (j < n && processes[j].arrival <= lastCompTime)
            queue.push(processes[j++]);
    }

    int waitTime = 0;
    float avgWaitTime = 0;

    cout << endl
         << "Process\tWait Time\tStart Time" << endl;

    for (process p : order)
    {
        p.startTime = waitTime;
        p.waitTime = waitTime - p.arrival;
        avgWaitTime += p.waitTime;
        cout << p.id << "\t" << p.waitTime << "\t\t" << p.startTime << endl;
        waitTime += p.burst;
    }

    avgWaitTime /= n;
    cout << "Average Wait Time: " << avgWaitTime << endl;
}