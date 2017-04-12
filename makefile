all: kk

kk: kk.c
	gcc kk.c -std=c11 -Ofast -lm -o kk

clean:
	rm -f kk