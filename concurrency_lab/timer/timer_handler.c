#include "timer_handler.h"

// timer_thread, worker_thread 는 내부 함수 (static)
static void *timer_thread(void *arg) { ... }
static void *worker_thread(void *arg) { ... }

timer_handler_t *timer_handler_start(...) {
    // 1. malloc
    // 2. 필드 초기화
    // 3. mutex, cond 초기화
    // 4. 쓰레드 생성
    // 5. return handler
}

int timer_handler_stop(timer_handler_t *handler) {
    // 1. running = 0
    // 2. broadcast
    // 3. join
    // 4. free
    // 5. return 0
}