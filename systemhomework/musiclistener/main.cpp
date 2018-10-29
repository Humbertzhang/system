#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#include "semutils.cpp"

using namespace std;

int THREADSLEEP=1;

int items1 = 0;
int items2 = 0;
int items3 = 0;
sem_t sems; // 保证每次只借出一个
sem_t sem0;	
sem_t sem1;
sem_t sem2;

void* boss(void* arg); 
void* listener0(void* arg); 
void* listener1(void* arg); 
void* listener2(void* arg); 

int main() {
	semsetup(&sems, 1);
	semsetup(&sem0, 1);
	semsetup(&sem1, 1);
	semsetup(&sem2, 1);

	// 一个老板，3名音乐爱好者	
	int TESTNUM=4;	
    pthread_t threads[TESTNUM];
    for(int i = 0; i < TESTNUM; i++) {
        if(i==0) {
            int status = pthread_create(&threads[i], NULL, boss, (void*)NULL);
        }
        else if(i==1){
            int status = pthread_create(&threads[i], NULL, listener0, (void*)NULL);
        }
        else if(i==2){
            int status = pthread_create(&threads[i], NULL, listener1, (void*)NULL);
        }
        else if(i==3){
            int status = pthread_create(&threads[i], NULL, listener2, (void*)NULL);
        }
    }
	usleep(100000000);
    return 0;
}


void* boss(void* arg) {
	// 使用微秒来产生随机数.
	while(true){
		usleep(THREADSLEEP);

		down(&sems);

		timeval tv;
		gettimeofday(&tv, NULL);
		int random = tv.tv_usec%3;
		if(random == 0) {
			up(&sem0);
			printf("老板借出了物品0\n");
		} else if(random == 1) {
			up(&sem1);
			printf("老板借出了物品1\n");
		} else if(random == 2) {
			up(&sem2);
			printf("老板借出了物品2\n");
		}
	}
}


void* listener0(void* arg) {
	while(true){
		usleep(THREADSLEEP);
		down(&sem0);
		printf("listener0正在欣赏音乐\n");
		up(&sems);
	}
}


void* listener1(void* arg) {
	while(true){
		usleep(THREADSLEEP);
		down(&sem1);
		printf("listener1正在欣赏音乐\n");
		up(&sems);
	}
}

void* listener2(void* arg) {
	while(true){
		usleep(THREADSLEEP);
		down(&sem2);
		printf("listener2正在欣赏音乐\n");
		up(&sems);
	}
}
