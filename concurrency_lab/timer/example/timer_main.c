/*
timer_thread: 만료 감지 → cond_signal
                                ↓
worker_thread: cond_wait로 대기 중 → 깨어남 → task 수행 → 다시 cond_wait
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// 뮤텍스, cond 초기화
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;



void *timer_thread(void *arg) {
    
    return NULL;
}

void *worker_thread(void *arg) {

        int flag = 1;

        while (flag) {
        // cond_wait로 대기 중 → 깨어남 → task 수행 → 다시 cond_wait
            pthread_mutex_lock(&mutex);
            pthread_cond_wait(&cond, &mutex);
            pthread_mutex_unlock(&mutex);
        }

        //task 수행
        pthread_cond_signal(&cond); // timer_thread에게 신호 보내기

    return NULL;
}

int main(int argc, char *argv[]) {
    
    pthread_t timer_thread_id, worker_thread_id;

    
    
    return 0;
}

