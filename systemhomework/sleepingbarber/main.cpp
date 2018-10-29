#include <iostream>
#include <pthread.h>
#include "semutils.cpp"
#include <unistd.h>
#define N 3

using namespace std;

sem_t barberready;  // 理发师是否空闲. 0空闲 1忙碌
sem_t personready; // 顾客准备好 0未准备好 1准备好了
int setsnum = N;   // 椅子数目
sem_t setmutex;    // 椅子的锁,1代表可操作椅子数目


int personnum = 0;

void* barber(void* arg); // consumer
void* person(void* arg); // producer

int main() {
	semsetup(&barberready, 0);
	semsetup(&personready, 0);
	semsetup(&setmutex, 1);
	
	int TESTNUM=5;	
    pthread_t threads[TESTNUM];
    for(int i = 0; i < TESTNUM; i++) {
        if(i==0) {
            int status = pthread_create(&threads[i], NULL, barber, (void*)NULL);
            if(status != 0) {
               printf("error");
               exit(0);
            }
        }
        else {
            int status = pthread_create(&threads[i], NULL, person, (void*)NULL);
            if(status != 0) {
                printf("error");
                exit(0);
            }
        }
    }
	usleep(5000);
    return 0;
}

/*
 * consumer
 */

void* barber(void* arg) {
	while(true){
		down(&personready);
		cout << "理发师理发ing" << endl;
		down(&setmutex);		
		setsnum += 1;
		up(&barberready);
		cout << "理发师理发结束" << endl;
		up(&setmutex);	
	}
}


/*
 * producer
 */
void* person(void* arg) {
	while(true){
		down(&setmutex);
		if (setsnum > 0) {
			setsnum -= 1;
			cout << personnum++ << "号顾客进来了" << endl;
			up(&personready);
			up(&setmutex);
			down(&barberready);
		} else {
			cout << personnum++ <<"号顾客走掉了" <<endl;
			up(&setmutex);	
		}	
	}
}


