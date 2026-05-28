#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

/* interval: 초 단위 주기 */

int timer_handler_start(const char *timer_id,
                        void (*callback)(void *),
                        void *param,
                        int interval);

int timer_handler_stop(const char *timer_id);

#endif /* TIMER_HANDLER_H */
