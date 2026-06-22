#include "timer_thread_pair.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void sleep_interval(timer_thread_pair_t *handler)
{
    for (int i = 0; i < handler->interval; i++) {
        if (!handler->running)
            return;
        sleep(1);
    }
}

static void *timer_thread(void *arg)
{
    timer_thread_pair_t *handler = arg;

    while (handler->running) {
        sleep_interval(handler);
        if (!handler->running)
            break;

        pthread_mutex_lock(&handler->mutex);
        if (!handler->running) {
            pthread_mutex_unlock(&handler->mutex);
            break;
        }
        handler->work_pending = 1;
        pthread_cond_signal(&handler->cond);
        pthread_mutex_unlock(&handler->mutex);
    }

    return NULL;
}

static void *worker_thread(void *arg)
{
    timer_thread_pair_t *handler = arg;

    pthread_mutex_lock(&handler->mutex);
    while (handler->running) {
        while (handler->running && !handler->work_pending)
            pthread_cond_wait(&handler->cond, &handler->mutex);

        if (!handler->running)
            break;

        handler->work_pending = 0;

        void (*callback)(void *) = handler->callback;
        void *param = handler->param;

        pthread_mutex_unlock(&handler->mutex);
        callback(param);
        pthread_mutex_lock(&handler->mutex);
    }
    pthread_mutex_unlock(&handler->mutex);

    return NULL;
}

timer_thread_pair_t *timer_thread_pair_start(const char *timer_id,
                                              void (*callback)(void *),
                                              void *param,
                                              int interval)
{
    if (timer_id == NULL || callback == NULL || interval <= 0)
        return NULL;

    timer_thread_pair_t *handler = malloc(sizeof(*handler));
    if (handler == NULL)
        return NULL;

    handler->timer_id = strdup(timer_id);
    if (handler->timer_id == NULL) {
        free(handler);
        return NULL;
    }

    handler->callback = callback;
    handler->param = param;
    handler->interval = interval;
    handler->running = 1;
    handler->work_pending = 0;

    if (pthread_mutex_init(&handler->mutex, NULL) != 0) {
        free(handler->timer_id);
        free(handler);
        return NULL;
    }

    if (pthread_cond_init(&handler->cond, NULL) != 0) {
        pthread_mutex_destroy(&handler->mutex);
        free(handler->timer_id);
        free(handler);
        return NULL;
    }

    if (pthread_create(&handler->timer_tid, NULL, timer_thread, handler) != 0) {
        pthread_cond_destroy(&handler->cond);
        pthread_mutex_destroy(&handler->mutex);
        free(handler->timer_id);
        free(handler);
        return NULL;
    }

    if (pthread_create(&handler->worker_tid, NULL, worker_thread, handler) != 0) {
        pthread_mutex_lock(&handler->mutex);
        handler->running = 0;
        pthread_cond_broadcast(&handler->cond);
        pthread_mutex_unlock(&handler->mutex);
        pthread_join(handler->timer_tid, NULL);

        pthread_cond_destroy(&handler->cond);
        pthread_mutex_destroy(&handler->mutex);
        free(handler->timer_id);
        free(handler);
        return NULL;
    }

    return handler;
}

int timer_thread_pair_stop(timer_thread_pair_t *handler)
{
    if (handler == NULL)
        return -1;

    pthread_mutex_lock(&handler->mutex);
    handler->running = 0;
    pthread_cond_broadcast(&handler->cond);
    pthread_mutex_unlock(&handler->mutex);

    pthread_join(handler->timer_tid, NULL);
    pthread_join(handler->worker_tid, NULL);

    pthread_mutex_destroy(&handler->mutex);
    pthread_cond_destroy(&handler->cond);
    free(handler->timer_id);
    free(handler);

    return 0;
}
