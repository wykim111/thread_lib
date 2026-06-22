#include <stdio.h>
#include <unistd.h>

#include "../timer_thread_pair.h"

static void on_tick(void *param)
{
    const char *name = param;
    printf("[%s] timer fired\n", name);
}

int main(void)
{
    timer_thread_pair_t *a;
    timer_thread_pair_t *b;

    a = timer_thread_pair_start("A", on_tick, "timer-A", 1);
    b = timer_thread_pair_start("B", on_tick, "timer-B", 10);
    
    if (a == NULL || b == NULL) {
        fprintf(stderr, "timer_thread_pair_start failed\n");
        return 1;
    }

    sleep(10);

    timer_thread_pair_stop(a);
    sleep(5);
    timer_thread_pair_stop(b);

    return 0;
}
