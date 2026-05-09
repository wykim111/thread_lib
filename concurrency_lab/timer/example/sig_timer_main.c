#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int cnt = 0;

void timer_handler(int sig) {
    printf("timer expired!\n");
    ++cnt;

    printf("[timer handler] cnt : %d\n", cnt);

    //random 문자열 생성 후 출력
    char *random_str = (char *)malloc(100);
    for (int i = 0; i < 100; i++) {
        random_str[i] = rand() % 26 + 'a';
    }
    random_str[100] = '\0';
    printf("random string: %s\n", random_str);
    
    if (cnt == 200) {
        printf("timer expired 200 times\n");
        exit(0);
    }
    
    free(random_str);

}

int main() {
    struct sigaction sa;
    struct sigevent sev;
    struct itimerspec its;
    timer_t timerid;

    // 1. signal handler 등록
    sa.sa_handler = timer_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGRTMIN, &sa, NULL);

    // 2. 타이머 생성
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    timer_create(CLOCK_REALTIME, &sev, &timerid);

    // 3. 타이머 시작 (5초 주기)
    its.it_value.tv_sec = 5;      // 첫 만료
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 3;   // 이후 주기
    its.it_interval.tv_nsec = 0;
    timer_settime(timerid, 0, &its, NULL);

    // 4. 대기
    while(1) pause();

    return 0;
}