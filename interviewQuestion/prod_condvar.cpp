#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <list>
#include <pthread.h>

using namespace std;

const int MAX_SIZE = 3;

list<int> nums;
int avail = 1;
int total;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
	int cnt = atoi((char*)arg);
	for (int i = 0; i < cnt; ++i) {
		pthread_mutex_lock(&mtx);
		while (nums.size() == MAX_SIZE)
			pthread_cond_wait(&full, &mtx);	
		nums.push_back(avail);
		
		if (nums.size() == 1)
			pthread_cond_signal(&empty);
		printf("[log] avail = %d\n", avail);
		++avail;
		sleep(1);
		pthread_mutex_unlock(&mtx);
	//	sleep(1);
	}
}

void *consumer(void *arg) {
	int numConsumed = 0;
	for (;;) {
		pthread_mutex_lock(&mtx);
		while (nums.size() == 0)
			pthread_cond_wait(&empty, &mtx);
		printf("%d consumed\n", nums.front());
		if (nums.front() == total) {
			nums.pop_front();
			break;
		}
		nums.pop_front();
		
		if (nums.size() == MAX_SIZE - 1)
			pthread_cond_signal(&full);
		pthread_mutex_unlock(&mtx);
		
	}
	
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <num>\n", argv[0]);
		exit(0);
	}
	pthread_t tid1, tid2;
	total = atoi(argv[1]);
	pthread_create(&tid1, nullptr, producer, argv[1]);
	pthread_create(&tid2, nullptr, consumer, nullptr);
	pthread_join(tid1, nullptr);
	pthread_join(tid2, nullptr);
}
