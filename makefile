all: kk

kk: kk.c
	gcc kk.c heap.h -std=c11 -Ofast -lm -o kk

clean:
	rm -f kk