#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

#include <pthread.h> 

typedef struct {
    char            timer_id[64];
    void            (*callback)(void *);
    void            *param;
    int             interval;
    int             running;
    int             work_pending;
    pthread_t       timer_tid;
    pthread_t       worker_tid;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
} timer_handler_t;

// 시작 — 포인터 반환
timer_handler_t *timer_handler_start(const char *timer_id,
                                      void (*callback)(void *),
                                      void *param,
                                      int interval);

// 종료 — 포인터 받기
int timer_handler_stop(timer_handler_t *handler);

#endif /* TIMER_HANDLER_H */