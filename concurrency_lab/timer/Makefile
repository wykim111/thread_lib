CC      = gcc
CFLAGS  = -Wall -Wextra -pthread
LDFLAGS = -pthread

LIB     = libtimer_thread_pair.a
EXAMPLE = example/timer_thread_pair_demo

.PHONY: all clean

all: $(LIB) $(EXAMPLE)

$(LIB): timer_thread_pair.o
	ar rcs $@ $^

$(EXAMPLE): example/timer_thread_pair_demo.o $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

timer_thread_pair.o: timer_thread_pair.c timer_thread_pair.h
	$(CC) $(CFLAGS) -c -o $@ timer_thread_pair.c

example/timer_thread_pair_demo.o: example/timer_thread_pair_demo.c timer_thread_pair.h
	$(CC) $(CFLAGS) -c -o $@ example/timer_thread_pair_demo.c

clean:
	rm -f $(LIB) timer_thread_pair.o example/timer_thread_pair_demo.o $(EXAMPLE)
