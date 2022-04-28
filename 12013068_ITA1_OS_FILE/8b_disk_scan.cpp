#include <bits/stdc++.h>
using namespace std;

void SCAN(vector<int>& requests, int diskSize, int head, int direction) {
	int size = requests.size();
	
	vector<int> left, right;
	
	if (direction == 0) left.push_back(0);
    else if (direction == 1) right.push_back(diskSize - 1);
 
    for (int i = 0; i < size; i++) {
        if (requests[i] < head) left.push_back(requests[i]);
        if (requests[i] > head) right.push_back(requests[i]);
    }
 
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
		
	int seek_count = 0;
	int distance, cur_track;
	
	vector<int> seekSequence;
	
	int run = 2;
	while (run--) {
		if (direction == 0) {
			for (int i = left.size() - 1; i >= 0; i--) {
				cur_track = left[i];

				seekSequence.push_back(cur_track);
				distance = abs(cur_track - head);
				seek_count += distance;
				head = cur_track;
			}
			
			direction = 1;
		}
		else if (direction == 1) {
			for (int i = 0; i < right.size(); i++) {
				cur_track = right[i];
			
				seekSequence.push_back(cur_track);
				distance = abs(cur_track - head);
				seek_count += distance;
				head = cur_track;
			}
			
			direction = 0;
		}
	}
	
	cout << "Total number of seek operations = "
		<< seek_count << endl;

	cout << "Seek Sequence is" << endl;

	for (int i = 0; i < seekSequence.size(); i++) {
		cout << seekSequence[i] << endl;
	}
}

/*
200
8
176 79 34 60 92 11 41 114
50
51
*/

int main() {
	int diskSize;
	cout << "Enter disk size: ";
	cin >> diskSize;
	
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
	
	cout << "Enter previous pointer: ";
	int prev;
	cin >> prev;
	
	int direction = 0;
	
	if(head < prev) direction = 0;
	else direction = 1;
	
	SCAN(requests, diskSize, head, direction);

	return 0;
}
