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
    int queueId;

    process(int id, int burst, int arrival, int queueId) : waitTime(-1), id(id), burst(burst), remTime(burst), arrival(arrival), queueId(queueId){};

    int getTAT()
    {
        return waitTime + burst;
    }

    bool operator<(const process &j) const
    {
        return arrival < j.arrival;
    }
};

class MLQ
{
private:
    void startRR();
    void startFCFS();

public:
    int priorityRR;
    int priorityFCFS;
    int quantum;
    int nProcess;
    vector<process> processes;
};

int main()
{

    MLQ mlq;

    cout << "Enter priority of RR Queue: ";
    cin >> mlq.priorityRR;

    cout << "Enter priority of FCFS Queue: ";
    cin >> mlq.priorityFCFS;

    cout << "Enter time quantum of RR Queue: ";
    cin >> mlq.quantum;

    cout << "Enter no. of processes: " << endl;
    cin >> mlq.nProcess;

    int n = mlq.nProcess;

    for (int i = 0; i < n; i++)
    {
        int burst, arrival, queueId;
        cout << "Enter Burst, Arrival Time, Queue for P" << (i + 1) << ": ";
        cin >> burst >> arrival >> queueId;
        process p(i + 1, burst, arrival, queueId);
        mlq.processes.push_back(p);
    }

    sort(mlq.processes.begin(), mlq.processes.end());

    class Compare
    {
    public:
        bool operator()(const process &p1, const process &p2)
        {
            int pr1 = queueId == 0 ? mlq.priorityRR : mlq.priorityFCFS;
            int pr2 = queueId == 0 ? mlq.priorityRR : mlq.priorityFCFS;

            if (pr1 == pr2)
                return p1.arrival > p2.arrival;
            return pr1 > pr2;
        }
    };

    priority_queue<process, vector<process>, Compare> queue;
    queue.push(mlq.processes[0]);

    vector<process> order;

    int lastCompTime = mlq.processes[0].arrival;
    int j = 1;

    while (!queue.empty())
    {
        process p = queue.top();
        queue.pop();
        lastCompTime += p.burst;
        order.push_back(p);

        while (j < n && mlq.processes[j].arrival <= lastCompTime)
            queue.push(mlq.processes[j++]);
    }

    int waitTime = 0;
    float avgWaitTime = 0;
    float avgTAT = 0;

    cout << endl
         << "Process\tWait Time\tStart Time" << endl;

    for (process p : order)
    {
        p.startTime = waitTime;
        p.waitTime = waitTime - p.arrival;
        avgWaitTime += p.waitTime;
        cout << p.id << "\t" << p.waitTime << "\t\t" << p.startTime << endl;
        waitTime += p.burst;
        avgTAT += p.getTAT();
    }

    avgWaitTime /= n;
    avgTAT /= n;
    cout << "Average Wait Time: " << avgWaitTime << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;
}