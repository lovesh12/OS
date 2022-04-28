#include <bits/stdc++.h>

using namespace std;

class Graph
{
    int V;
    list<int> *adj;
    bool isCyclicUtil(int v, vector<bool>, vector<bool>);

public:
    Graph(int V);
    void addEdge(int s, int d);
    bool isCyclic();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int s, int d)
{
    adj[s].push_back(d);
}

bool Graph::isCyclicUtil(int v, vector<bool> visited, vector<bool> stackk)
{
    if (visited[v] == false)
    {
        visited[v] = true;
        stackk[v] = true;

        for (int i : adj[v])
        {
            if (!visited[i] && isCyclicUtil(i, visited, stackk))
                return true;
            else if (stackk[i])
                return true;
        }
    }
    stackk[v] = false;
    return false;
}

bool Graph::isCyclic()
{

    vector<bool> visited(V);
    vector<bool> stackk(V);

    for (int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, stackk))
            return true;

    return false;
}

int main()
{
    int nR, nP;
    cout << "Enter no. of resources, processes: ";
    cin >> nR >> nP;

    int n = nR + nP;

    // Adjacency Matrix
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    cout << "Enter IDs of resource allocated to each processes 1 to " << nP << " (0 for none): ";
    for (int i = 0; i < nP; i++)
    {
        int allocatedResource;
        cin >> allocatedResource;
        if (allocatedResource > 0)
        {
            adjMatrix[nP + allocatedResource - 1][i] = 1;
        }
    }

    cout << "Enter IDs of resource requested by each process 1 to " << nP << " (0 for none): ";
    for (int i = 0; i < nP; i++)
    {
        int requestedResource;
        cin >> requestedResource;
        if (requestedResource > 0)
        {
            adjMatrix[i][nP + requestedResource - 1] = 1;
        }
    }

    cout << endl
         << "\n\n\n\t";
    for (int i = 0; i < nP; i++)
        cout << "P" << i + 1 << "\t";
    for (int i = 0; i < nR; i++)
        cout << "R" << i + 1 << "\t";

    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == 0)
            {
                if (i < nP)
                    cout << "P" << i + 1 << "\t";
                else
                    cout << "R" << i + 1 - nP << "\t";
            }
            cout << adjMatrix[i][j] << "\t";
        }
        cout << endl;
    }

    Graph g(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (adjMatrix[i][j] == 1)
                g.addEdge(i, j);
    }

    bool isCycle = g.isCyclic();
    if (isCycle)
        cout << "Deadlock detected";
    else
        cout << "No Deadlock detected";
}