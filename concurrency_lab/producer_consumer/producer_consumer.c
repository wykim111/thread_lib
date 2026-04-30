#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_SIZE 5

int queue[MAX_SIZE];
int head = 0, tail = 0, size = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_full = PTHREAD_COND_INITIALIZER;   // 가득 찼을 때
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER;  // 비었을 때

void* producer(void* arg) {
    int data = 0;
    while (1) {
        pthread_mutex_lock(&mutex);

        // 꽉 차면 대기
        while (size == MAX_SIZE) {
            printf("producer: queue full — waiting\n");
            pthread_cond_wait(&cond_full, &mutex);
        }

        // push
        queue[tail] = data;
        tail = (tail + 1) % MAX_SIZE;
        size++;

        printf("producer: push %d (size=%d)\n", data++, size);

        pthread_cond_signal(&cond_empty);  // consumer 깨움
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);

        // 비었으면 대기(블로킹)
        while(size == 0){
            printf("consumer: queue empty — waiting\n");
            pthread_cond_wait(&cond_empty, &mutex);
        }

        // pop
        int data = queue[head];
        head = (head + 1) % MAX_SIZE;
        size--;
        printf("consumer: pop %d (size=%d)\n", data, size);

        pthread_cond_signal(&cond_full);  // producer 깨움
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t producer_t, consumer_t;

    pthread_create(&producer_t, NULL, producer, NULL);
    pthread_create(&consumer_t, NULL, consumer, NULL);

    pthread_join(producer_t, NULL);
    pthread_join(consumer_t, NULL);

    return 0;
}