#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct process
{
    int id;
    int arrival;
    int burst;
    int remTime;
    int waitTime;

    process()
    {
        waitTime = 0;
    }

    int getTAT()
    {
        return waitTime + burst;
    }
};

int getNextSRTFProcess(vector<process> &jobs, int currentTick)
{
    int n = jobs.size();

    int minTimeRem = INT_MAX;
    int minShortestJob = -1;

    for (int i = 0; i < n; ++i)
    {
        if (jobs[i].arrival <= currentTick && jobs[i].remTime < minTimeRem && jobs[i].remTime > 0)
        {
            minTimeRem = jobs[i].remTime;
            minShortestJob = i;
        }
    }

    return minShortestJob;
}

int main()
{
    int n;
    cout << "Number of jobs: ";
    cin >> n;

    vector<process> processes(n);

    for (int i = 0; i < n; ++i)
    {
        cout << "Burst & Arrival Time for job " << (i + 1) << ": ";
        process p;
        p.id = i;
        cin >> p.burst >> p.arrival;

        p.remTime = p.burst;
        processes[i] = p;
    }

    sort(processes.begin(), processes.end(), [](const process &job1, const process &job2)
         { return job1.arrival < job2.arrival; });

    int currentTick = 0;
    int numCompleted = 0;

    vector<int> outputStr;
    vector<int> outputTime;

    outputStr.push_back(0);
    outputTime.push_back(processes[0].arrival);

    while (numCompleted != n)
    {
        int minShortestJobIdx = getNextSRTFProcess(processes, currentTick);
        if (minShortestJobIdx != -1 && outputStr.back() != minShortestJobIdx)
        {
            outputStr.push_back(minShortestJobIdx);
            outputTime.push_back(currentTick);
        }

        currentTick++;

        if (minShortestJobIdx == -1)
            continue;

        process &srtfJob = processes[minShortestJobIdx];
        srtfJob.remTime--;

        if (srtfJob.remTime == 0)
        {
            numCompleted++;

            srtfJob.waitTime = currentTick - srtfJob.burst - srtfJob.arrival;

            if (srtfJob.waitTime < 0)
                srtfJob.waitTime = 0;
        }
    }

    outputTime.push_back(currentTick);

    cout << endl
         << endl
         << "\t";

    for (int o : outputStr)
        cout << "P" << o + 1 << "\t";

    cout << endl
         << "    ";

    for (int t : outputTime)
        cout << t << "\t   ";

    cout << endl;

    double sumTAT = 0;

    for (auto p : processes)
    {
        cout << "\nID: " << p.id << " Wait Time: " << p.waitTime << " TAT: " << p.getTAT();

        sumTAT += p.getTAT();
    }

    cout << "\n\nAverage Turn Around Time: " << sumTAT / n;

    cout << "\nAverage Throughput: " << (double)n / currentTick;

    return 0;
}