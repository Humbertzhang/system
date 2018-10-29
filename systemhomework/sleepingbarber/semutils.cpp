//
// Created by zhangke on 18-10-29.
//
#include <semaphore.h>


int semsetup(sem_t *sem, int value) {
    return sem_init(sem, 0, value);
}

int down(sem_t *sem) {
    return sem_wait(sem);
}

int up(sem_t *sem) {
    return sem_post(sem);
}
