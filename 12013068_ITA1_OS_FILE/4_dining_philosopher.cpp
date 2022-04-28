#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

std::mutex mutex;
std::mutex S[N];

void test(int phnum) {
	if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		// state that eating
		state[phnum] = EATING;

		std::this_thread::sleep_for (std::chrono::seconds(2));

		printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
		printf("Philosopher %d is Eating\n", phnum + 1);

		// has no effect
		// during takefork
		// used to wake up hungry philosophers
		// during putfork
		S[phnum].unlock();
	}
}

// take up chopsticks
void take_fork(int phnum) {
	mutex.lock();

	// state that hungry
	state[phnum] = HUNGRY;

	printf("Philosopher %d is Hungry\n", phnum + 1);

	// eat if neighbours are not eating
	test(phnum);

	mutex.unlock();

	// if unable to eat wait to be signalled
	S[phnum].lock();

	std::this_thread::sleep_for (std::chrono::seconds(1));
}

// put down chopsticks
void put_fork(int phnum) {
	mutex.lock();

	// state that thinking
	state[phnum] = THINKING;

	printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
	printf("Philosopher %d is thinking\n", phnum + 1);

	test(LEFT);
	test(RIGHT);

	mutex.unlock();
}

void* philosopher(void* num) {
	while (1) {
		int* i = (int*)num;

		std::this_thread::sleep_for (std::chrono::seconds(1));

		take_fork(*i);

		std::this_thread::sleep_for (std::chrono::seconds(0));

		put_fork(*i);
	}
}

int main() {
	int i;
	std::thread thread_id[N];

	for (i = 0; i < N; i++) {
		thread_id[i] = std::thread(philosopher, &phil[i]);
		printf("Philosopher %d is thinking\n", i + 1);
	}

	for (i = 0; i < N; i++) {
		thread_id[i].join();
	}
}

