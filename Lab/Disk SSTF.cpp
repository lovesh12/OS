#include <bits/stdc++.h>
using namespace std;

int getMINSeekTimeRequest(vector<int> &requests, vector<bool> &allocated, int head)
{
	int n = requests.size();

	int min = -1;
	int minIdx = -1;
	bool found = false;

	for (int i = 0; i < n; ++i)
	{
		if (!found)
		{
			if (!allocated[i])
			{
				found = true;
				min = abs(requests[i] - head);
				minIdx = i;
			}
		}
		else if (!allocated[i] && abs(requests[i] - head) < min)
		{
			min = abs(requests[i] - head);
			minIdx = i;
		}
	}

	return minIdx;
}

void SSTF(vector<int> &requests, int head)
{
	int size = requests.size();

	vector<bool> allocated(size, false);

	int seek_count = 0;
	int distance, cur_track;

	vector<int> seekSequence;

	int idx = getMINSeekTimeRequest(requests, allocated, head);

	while (idx != -1)
	{
		allocated[idx] = true;

		cur_track = requests[idx];
		distance = abs(cur_track - head);
		head = cur_track;

		seekSequence.push_back(requests[idx]);

		idx = getMINSeekTimeRequest(requests, allocated, head);
	}

	cout << "Total number of seek operations = "
		 << seek_count << endl;

	cout << "Seek Sequence is" << endl;

	for (int i = 0; i < size; i++)
	{
		cout << seekSequence[i] << endl;
	}
}

/*
8
176 79 34 60 92 11 41 114
50
*/

int main()
{
	int n;
	cout << "Enter no. of requests: ";
	cin >> n;

	vector<int> requests(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> requests[i];
	}

	cout << "Enter head pointer: ";
	int head;
	cin >> head;

	SSTF(requests, head);

	return 0;
}
