#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../timer_handler.h"

static void on_tick(void *param)
{
    const char *name = param;
    printf("[%s] timer fired\n", name);
}

int main(void)
{
    if (timer_handler_start("A", on_tick, "timer-A", 2) != 0) {
        fprintf(stderr, "start A failed\n");
        return 1;
    }
    if (timer_handler_start("B", on_tick, "timer-B", 3) != 0) {
        fprintf(stderr, "start B failed\n");
        return 1;
    }

    sleep(10);

    timer_handler_stop("A");
    sleep(5);
    timer_handler_stop("B");

    return 0;
}
