#include <pthread.h>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <unistd.h>

using namespace std;

const int MAX_BUFF_SIZE = 5;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t full = PTHREAD_COND_INITIALIZER;
static pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
list<int> buff;
int item = 0;
int total = 0;
void *producer(void *arg) {
	// 注意参数传入方式，传的是void *，若是&int，则用*(int*)arg;
	// int cnt = atoi((char*)arg); 
	int cnt = *(int*)arg;
	while (cnt > 0) {
		pthread_mutex_lock(&mtx);
		while (buff.size() == MAX_BUFF_SIZE)
			pthread_cond_wait(&full, &mtx);
		buff.push_back(++item);
		printf("item %d created\n", item);
		if (buff.size() == 1)
			pthread_cond_signal(&empty);
		--cnt;
		pthread_mutex_unlock(&mtx);
	}
	printf("producer exit\n");
}

void *consumer(void *arg) {
	while (1) {
		pthread_mutex_lock(&mtx);
		while (buff.size() == 0)
			pthread_cond_wait(&empty, &mtx);
		printf("item %d consumed\n", buff.front());
		buff.pop_front();
		printf("[log] thread = %ld, total = %d\n", (long)pthread_self(), total);
		// exit为进程退出函数，某线程调用则所有进程都退出
		if (--total <= 0)
			exit(0);
		// producer并非执行相同的任务，使用signal可能由于cnt为0阻塞
		if (buff.size() == MAX_BUFF_SIZE - 1)
			pthread_cond_broadcast(&full);
		pthread_mutex_unlock(&mtx);
	}
	printf("consumer exit\n");
}


int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "usage %s <item produced+> <number of consumer>\n", argv[0]);
	}
	pthread_t tid1, tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	for (int i = 1; i < argc - 1; ++i) {
		// 若使用int t = atoi(argv[i])则bug，main线程会多次在同一地址创建int，到传入producer线程时可能要取的值已经被覆盖（每个线程都需要同一个地址的值）
		// 使用sleep(1)貌似可解决问题
		int t = atoi(argv[i]);
		pthread_create(&tid1, &attr, producer, &t);
		// pthread_create(&tid1, &attr, producer, argv[i]);
		pthread_mutex_lock(&mtx);
		total += atoi(argv[i]);
		pthread_mutex_unlock(&mtx);
		sleep(1);
	}
	for (int i = 0; i < atoi(argv[argc - 1]); ++i) {
		pthread_create(&tid2, &attr, consumer, NULL);
	}

	pthread_exit(NULL);
}
