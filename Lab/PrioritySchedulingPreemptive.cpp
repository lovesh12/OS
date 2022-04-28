#include <bits/stdc++.h>

using namespace std;

struct process
{
    int id;
    int burst;
    int remTime;
    int arrival;
    int waitTime;
    int startTime;
    int priority;

    process(int id, int priority, int burst, int arrival) : waitTime(-1), id(id), remTime(burst), priority(priority), burst(burst), arrival(arrival){};

    int getTAT()
    {
        return waitTime + burst;
    }
};

bool cmp(const process *a, const process *b)
{
    if (a->arrival == b->arrival)
        return a->priority < b->priority;
    return a->arrival < b->arrival;
}

class processPtrMinPQueue
{
public:
    bool operator()(process *a, process *b)
    {
        if (a->priority == b->priority)
            return a->arrival > b->arrival;
        return a->priority > b->priority;
    }
};

int main()
{
    cout << "Enter no. of processes: " << endl;
    int n;
    cin >> n;
    vector<process *> processes;
    for (int i = 0; i < n; i++)
    {
        int burst, arrival, priority;
        cout << "Enter Burst, Arrival Time for P" << (i + 1) << ": ";
        cin >> priority >> burst >> arrival;
        process *p = new process(i + 1, priority, burst, arrival);
        processes.push_back(p);
    }

    sort(processes.begin(), processes.end(), cmp);

    priority_queue<process *, vector<process *>, processPtrMinPQueue> queue;
    queue.push(processes[0]);

    vector<int> order;
    vector<int> orderTime;
    order.push_back(processes[0]->id);
    orderTime.push_back(processes[0]->arrival);

    int lastCompTime = processes[0]->arrival;
    int j = 1;

    while (!queue.empty())
    {
        process *p = queue.top();

        if (order.back() != p->id)
        {
            order.push_back(p->id);
            orderTime.push_back(lastCompTime);
        }

        queue.pop();

        while (p->remTime > 0)
        {
            lastCompTime++;
            p->remTime--;

            while (j < n && processes[j]->arrival <= lastCompTime)
                queue.push(processes[j++]);

            if (p->remTime <= 0)
            {
                p->remTime = 0;
                p->waitTime = lastCompTime - p->burst - p->arrival;
                if (p->waitTime < 0)
                    p->waitTime = 0;
            }
            else if (!queue.empty() && queue.top()->priority < p->priority)
            {
                queue.push(p);
                break;
            }
        }

        if (queue.empty() && j < n) // no process arrived
            lastCompTime = processes[j]->arrival;
    }

    orderTime.push_back(lastCompTime);

    cout << endl
         << endl
         << "\t";

    for (int o : order)
        cout << "P" << o << "\t";

    cout << endl
         << "    ";

    for (int t : orderTime)
        cout << t << "\t   ";

    cout << endl;

    double sumTAT = 0;

    for (process *p : processes)
    {
        cout << "\nID: " << p->id << " Wait Time: " << p->waitTime << " TAT: " << p->getTAT();

        sumTAT += p->getTAT();
    }

    cout << "\n\nAverage Turn Around Time: " << sumTAT / n;

    cout << "\nAverage Throughput: " << (double)n / lastCompTime;
}