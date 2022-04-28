#include <bits/stdc++.h>

using namespace std;

class BankersAlgo
{
private:
    int m, n;
    bool checkSafety(vector<bool> &);
    bool needLessThanWork(vector<int> &, vector<int> &);
    bool requestLessThanNeed(vector<int> &, vector<int> &);
    bool requestLessThanAvailable(vector<int> &, vector<int> &);

public:
    vector<int> available;
    vector<vector<int>> maxx;
    vector<vector<int>> allocation;
    vector<vector<int>> need;
    BankersAlgo();
    void takeInput();
    void printCurrentState();
    pair<bool, vector<int>> safetyAlgo(vector<int> &, vector<vector<int>> &, vector<vector<int>> &);
    pair<bool, vector<int>> requestResource(int, vector<int>);
};

BankersAlgo::BankersAlgo()
{
    takeInput();
}

void BankersAlgo::takeInput()
{
    cout << "Enter no. of processes: ";
    cin >> n;
    cout << "Enter no. of resource types: ";
    cin >> m;

    available.resize(m);
    maxx.resize(n, vector<int>(m));
    allocation.resize(n, vector<int>(m));
    need.resize(n, vector<int>(m));

    cout << "Enter Allocation matrix" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];
    }

    cout << "Enter Max matrix" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cin >> maxx[i][j];
    }

    cout << "Enter resources available: ";
    for (int i = 0; i < m; i++)
        cin >> available[i];

    // calculating NEED matrix = MAX - ALLOCATION
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            need[i][j] = maxx[i][j] - allocation[i][j];
    }
}

void BankersAlgo::printCurrentState()
{
    cout << "\n\n\tAllocation\tMax\t\tNeed\t\tAvailable\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "\t";
        for (int j = 0; j < m; j++)
            cout << "R" << j + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t";
        for (int j = 0; j < m; j++)
            cout << allocation[i][j] << "  ";
        cout << "\t";
        for (int j = 0; j < m; j++)
            cout << maxx[i][j] << "  ";
        cout << "\t";
        for (int j = 0; j < m; j++)
            cout << need[i][j] << "  ";
        cout << "\t";
        if (i == 0)
        {
            for (int j = 0; j < m; j++)
                cout << available[j] << " ";
            cout << "\t";
        }
        cout << "\n";
    }
}

bool BankersAlgo::needLessThanWork(vector<int> &need, vector<int> &work)
{
    bool needLessThanWork = true;
    for (int j = 0; j < m; j++)
        if (need[j] > work[j])
            needLessThanWork = false;

    return needLessThanWork;
}

bool BankersAlgo::checkSafety(vector<bool> &finish)
{
    bool safe = true;
    for (bool b : finish)
        if (!b)
            return false;
    return safe;
}

pair<bool, vector<int>> BankersAlgo::safetyAlgo(vector<int> &available, vector<vector<int>> &allocation, vector<vector<int>> &need)
{
    vector<int> work = available;
    vector<bool> finish(n);

    vector<int> safeOrder;

    bool change = true;
    while (change)
    {
        change = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i] && needLessThanWork(need[i], work))
            {
                for (int j = 0; j < m; j++)
                    work[j] += allocation[i][j];

                finish[i] = true;
                change = true;
                safeOrder.push_back(i);
            }
        }
    }

    bool isSafe = checkSafety(finish);
    return {isSafe, safeOrder};
}

bool BankersAlgo::requestLessThanNeed(vector<int> &request, vector<int> &need)
{
    for (int i = 0; i < m; i++)
        if (request[i] > need[i])
            return false;

    return true;
}

bool BankersAlgo::requestLessThanAvailable(vector<int> &request, vector<int> &available)
{
    for (int i = 0; i < m; i++)
        if (request[i] > available[i])
            return false;

    return true;
}

int main()
{
    BankersAlgo ba;
    ba.printCurrentState();
    pair<bool, vector<int>> safety = ba.safetyAlgo(ba.available, ba.allocation, ba.need);
    if (safety.first)
    {
        cout << "\n\nThe system is in a safe state" << endl;
        cout << "Safe sequence" << endl;
        for (int p : safety.second)
            cout << "P" << p + 1 << " ";
    }
    else
        cout << "\n\nThe system is not in safe state" << endl;
}