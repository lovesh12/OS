#include <bits/stdc++.h>

using namespace std;

struct process
{
    int id;
    int burst;
    int arrival;
    int waitTime;
    int startTime;

    process(int id, int burst, int arrival) : waitTime(-1), startTime(-1), id(id), burst(burst), arrival(arrival){};

    bool operator<(const process &j) const
    {
        return arrival < j.arrival;
    }
    int getTAT()
    {
        return waitTime + burst;
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

    int waitTime = 0;
    float avgWaitTime = 0;

    cout << endl
         << "Process\tWait Time\tStart Time\tTAT" << endl;

    for (process p : processes)
    {
        p.startTime = waitTime;
        p.waitTime = waitTime - p.arrival;
        avgWaitTime += p.waitTime;
        cout << p.id << "\t" << p.waitTime << "\t\t" << p.startTime << "\t\t" << p.getTAT() << endl;
        waitTime += p.burst;
    }

    avgWaitTime /= n;
    cout << "Average Wait Time: " << avgWaitTime << endl;
}