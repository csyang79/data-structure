#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <list>

using namespace std;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notEmpty = PTHREAD_COND_INITIALIZER;
const int MAX_BUFF_SIZE = 5;

list<int> buffer;
int item = 0;
int total = 0;

void *producer(void *arg) {
	int cnt = atoi((char*)arg);
	printf("%d\n", cnt);
	sleep(3);
	while (cnt > 0) {
		pthread_mutex_lock(&mtx);
		while (buffer.size() == MAX_BUFF_SIZE)
			pthread_cond_wait(&notFull, &mtx);
		buffer.push_back(++item);
		printf("item %d created\n", item);
		if (buffer.size() == 1)
			pthread_cond_signal(&notEmpty);
		--cnt;
		pthread_mutex_unlock(&mtx);
	}
}

void *consumer(void *arg) {
	while (1) {
		pthread_mutex_lock(&mtx);
		while (buffer.size() == 0)
			pthread_cond_wait(&notEmpty, &mtx);
		printf("item %d consumed\n", buffer.front());
		buffer.pop_front();
		if (--total == 0)
			exit(0);
		if (buffer.size() == MAX_BUFF_SIZE - 1)
			pthread_cond_broadcast(&notFull);
		
		pthread_mutex_unlock(&mtx);
	}
}

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "%s <producer count+> <consumer>\n", argv[0]);
		exit(0);
	}
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_t tid;
	for (int i = 1; i < argc - 1; ++i) {
		pthread_create(&tid, &attr, producer, argv[i]);
		// total 无需加锁，此时consumer并未运行
//		pthread_mutex_lock(&mtx);
		total += atoi(argv[i]);
//		pthread_mutex_unlock(&mtx);
	}
	for (int i = 0; i < atoi(argv[argc - 1]); ++i) {
		pthread_create(&tid, &attr, consumer, NULL);
	}
	pthread_exit(NULL);
}
