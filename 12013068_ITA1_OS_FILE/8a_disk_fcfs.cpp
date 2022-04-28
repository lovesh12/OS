#include <bits/stdc++.h>
using namespace std;

void FCFS(vector<int>& requests, int head) {
	int size = requests.size();
	
	int seek_count = 0;
	int distance, cur_track;

	for (int i = 0; i < size; i++) {
		cur_track = requests[i];
		
		distance = abs(cur_track - head);
		seek_count += distance;
		head = cur_track;
	}

	cout << "Total number of seek operations = "
		<< seek_count << endl;

	cout << "Seek Sequence is" << endl;

	for (int i = 0; i < size; i++) {
		cout << requests[i] << endl;
	}
}

/*
8
176 79 34 60 92 11 41 114
50
*/

int main() {
	int n;
	cout << "Enter no. of requests: ";
	cin >> n;
	
	vector<int> requests(n);
	
	for(int i = 0; i < n; ++i) {
		cin >> requests[i];
	}
	
	cout << "Enter head pointer: ";
	int head;
	cin >> head;

	FCFS(requests, head);

	return 0;
}
