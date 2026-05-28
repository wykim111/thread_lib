/*
timer_thread: 만료 감지 → work_pending 설정 → cond_signal
                                ↓
worker_thread: cond_wait로 대기 중 → 깨어남 → task 수행 → 다시 cond_wait
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static volatile int running = 1;
static int work_pending = 0;

void *timer_thread(void *arg)
{
    int interval = *(int *)arg;

    while (running) {
        sleep(interval);
        if (!running)
            break;

        pthread_mutex_lock(&mutex);
        work_pending = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *worker_thread(void *arg)
{
    (void)arg;

    while (running) {
        pthread_mutex_lock(&mutex);
        while (running && !work_pending)
            pthread_cond_wait(&cond, &mutex);

        if (!running) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        work_pending = 0;

        /* task 수행 */
        printf("worker_thread: task 수행\n");

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t timer_thread_id, worker_thread_id;
    int interval = 3;
    int run_sec = 30;

    if (argc > 1)
        interval = atoi(argv[1]);
    if (argc > 2)
        run_sec = atoi(argv[2]);

    pthread_create(&timer_thread_id, NULL, timer_thread, &interval);
    pthread_create(&worker_thread_id, NULL, worker_thread, NULL);

    sleep(run_sec);

    pthread_mutex_lock(&mutex);
    running = 0;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_join(timer_thread_id, NULL);
    pthread_join(worker_thread_id, NULL);

    return 0;
}
