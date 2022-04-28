#include <bits/stdc++.h>

using namespace std;

class BankersAlgo
{
private:
    bool checkSafety(vector<bool> &);
    bool needLessThanWork(vector<int> &, vector<int> &);
    bool requestLessThanNeed(vector<int> &, vector<int> &);
    bool requestLessThanAvailable(vector<int> &, vector<int> &);

public:
    int m, n;
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

pair<bool, vector<int>> BankersAlgo::safetyAlgo(vector<int> &pavailable, vector<vector<int>> &pallocation, vector<vector<int>> &pneed)
{
    vector<int> work = pavailable;
    vector<bool> finish(n);

    vector<int> safeOrder;

    bool change = true;
    while (change)
    {
        change = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i] && needLessThanWork(pneed[i], work))
            {
                for (int j = 0; j < m; j++)
                    work[j] += pallocation[i][j];

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
        {
            cout << endl
                 << request[i] << " " << need[i] << endl;
            return false;
        }

    return true;
}

bool BankersAlgo::requestLessThanAvailable(vector<int> &request, vector<int> &available)
{
    for (int i = 0; i < m; i++)
        if (request[i] > available[i])
            return false;

    return true;
}

// Resource - Request Algorithm
pair<bool, vector<int>> BankersAlgo::requestResource(int process, vector<int> request)
{
    process--;
    if (requestLessThanNeed(request, need[process]))
    {
        if (requestLessThanAvailable(request, available))
        {
            vector<int> tempAvailable = available;
            vector<vector<int>> tempAllocation = allocation;
            vector<vector<int>> tempNeed = need;

            for (int i = 0; i < m; i++)
                tempAvailable[i] -= request[i];

            for (int i = 0; i < m; i++)
                tempAllocation[process][i] += request[i];

            for (int i = 0; i < m; i++)
                tempNeed[process][i] -= request[i];

            pair<bool, vector<int>> safety = safetyAlgo(tempAvailable, tempAllocation, tempNeed);
            if (safety.first) // safe
            {
                available = tempAvailable;
                allocation = tempAllocation;
                need = tempNeed;
                cout << "After Resource Allocation\n";
                printCurrentState();
            }
            return safety;
        }
        else
        {
            cout << "Process need to wait";
            return {false, {}};
        }
    }
    else
    {
        cout << "Process requesting more than maximum claim";
        return {false, {}};
    }
}

int main()
{
    BankersAlgo ba;
    ba.printCurrentState();
    pair<bool, vector<int>> safety = ba.safetyAlgo(ba.available, ba.allocation, ba.need);
    cout << "\nBefore requesting resource";
    if (safety.first)
    {
        cout << "\n\nThe system is in a safe state"
             << endl;
        cout << "Safe sequence" << endl;
        for (int p : safety.second)
            cout << "P" << p + 1 << " ";
        cout << "\n\n";
    }
    else
        cout << "\n\nThe system is not in safe state" << endl;

    if (safety.first)
    {
        int rId;
        vector<int> request(ba.m);
        cout << "Enter resource ID: ";
        cin >> rId;
        cout << "Enter instances of each resource requested: ";
        for (int i = 0; i < ba.m; i++)
            cin >> request[i];
        pair<bool, vector<int>> req = ba.requestResource(rId, request);
        if (req.first)
        {
            cout << "\n\nResource request is safe" << endl;
            cout << "Safe sequence" << endl;
            for (int p : req.second)
                cout << "P" << p + 1 << " ";
        }
        else
            cout << "\n\nResource request is not safe" << endl;
    }
}