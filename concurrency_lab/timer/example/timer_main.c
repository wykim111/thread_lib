#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/types.h>ßßßßß
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// 뮤텍스, cond 초기화
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

