
CC = cc
CFLAGS = -I ../include -std=c11 -O2

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard ../include/libcx/*.h)

OUT = libcx.so
AOUT = libcx.a

default: $(OUT) $(AOUT)

$(OUT): $(OBJS) $(AOUT) $(HEADERS)
	$(CC) $(OBJS) -shared -o $(OUT)

$(AOUT): $(OBJS)
	ar rcs $(AOUT) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $(?)

clean:
	@rm -f $(OBJS) $(OUT) $(AOUT)
