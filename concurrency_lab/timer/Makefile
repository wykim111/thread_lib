CC      = gcc
CFLAGS  = -Wall -Wextra -pthread
LDFLAGS = -pthread

LIB     = libtimer_handler.a
EXAMPLE = example/timer_handler_demo

.PHONY: all clean

all: $(LIB) $(EXAMPLE)

$(LIB): timer_handler.o
	ar rcs $@ $^

$(EXAMPLE): example/timer_handler_demo.o $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

timer_handler.o: timer_handler.c timer_handler.h
	$(CC) $(CFLAGS) -c -o $@ timer_handler.c

example/timer_handler_demo.o: example/timer_handler_demo.c timer_handler.h
	$(CC) $(CFLAGS) -c -o $@ example/timer_handler_demo.c

clean:
	rm -f $(LIB) timer_handler.o example/timer_handler_demo.o $(EXAMPLE)
