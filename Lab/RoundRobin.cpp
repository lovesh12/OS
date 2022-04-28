#include <bits/stdc++.h>

using namespace std;

struct process
{
    int id;
    int burst;
    int arrival;
    int waitTime;
    int startTime;
    int remTime;
    int firstResponse;

    process(int id, int burst, int arrival) : waitTime(-1), id(id), burst(burst), remTime(burst), arrival(arrival){};

    int getTAT()
    {
        return waitTime + burst;
    }
};

bool cmp(process *a, process *b)
{
    return a->arrival < b->arrival;
}

int main()
{

    int quantum;
    cin >> quantum;

    cout << "Enter no. of processes: " << endl;
    int n;
    cin >> n;
    vector<process *> processes;
    for (int i = 0; i < n; i++)
    {
        int burst, arrival;
        cout << "Enter Burst, Arrival Time for P" << (i + 1) << ": ";
        cin >> burst >> arrival;
        process *p = new process(i + 1, burst, arrival);
        processes.push_back(p);
    }

    sort(processes.begin(), processes.end(), cmp);

    vector<int> order;
    vector<int> times;

    queue<process *> queue;
    queue.push(processes[0]);
    int timeCompl = processes[0]->arrival;
    int j = 1;

    cout << endl;

    while (!queue.empty() || j < n)
    {
        if (queue.empty() && j < n) //queue empty and process not arrived
        {
            timeCompl = processes[j]->arrival;
            continue;
        }

        bool finished = false;
        process *p = queue.front();
        queue.pop();
        order.push_back(p->id);
        times.push_back(timeCompl);

        if (p->burst == p->remTime)
            p->firstResponse = timeCompl;

        if (p->remTime > quantum)
        {
            p->remTime -= quantum;
            timeCompl += quantum;
        }
        else
        {
            timeCompl += p->remTime;
            p->remTime = 0;
            p->waitTime = timeCompl - p->arrival - p->burst;
            if (p->waitTime < 0)
                p->waitTime = 0;
            finished = true;
        }

        while (j < n && processes[j]->arrival <= timeCompl)
        {
            queue.push(processes[j]);
            j++;
        }

        if (!finished)
        {
            queue.push(p);
        }
    }

    times.push_back(timeCompl);

    cout << endl
         << "\t    ";

    for (int p : order)
        cout << "P" << p << "\t   ";

    cout << endl
         << "\t";

    for (int t : times)
        cout << t << "\t";

    cout << endl;
    double sumTAT = 0;

    for (process *p : processes)
    {
        cout << "\nID: " << p->id << " Wait Time: " << p->waitTime << " TAT: " << p->getTAT() << " First Response: " << p->firstResponse;

        sumTAT += p->getTAT();
    }

    cout << "\n\nAverage Turn Around Time: " << sumTAT / n;
    cout << "\nAverage Throughput: " << (double)n / timeCompl;
    cout << "\nContext Switches: " << order.size() - 1;
}