#ifndef TIMER_THREAD_PAIR_H
#define TIMER_THREAD_PAIR_H

#include <pthread.h>

typedef struct {
    char            *timer_id;
    void            (*callback)(void *);
    void            *param;
    int             interval;
    int             running;
    int             work_pending;
    pthread_t       timer_tid;
    pthread_t       worker_tid;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
} timer_thread_pair_t;

timer_thread_pair_t *timer_thread_pair_start(const char *timer_id,
                                              void (*callback)(void *),
                                              void *param,
                                              int interval);

int timer_thread_pair_stop(timer_thread_pair_t *handler);

#endif /* TIMER_THREAD_PAIR_H */
