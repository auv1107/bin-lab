all: test

test: main.c basetype.h drawpic.h
	gcc -o test main.c basetype.h drawpic.h -lm

clean: test
	rm -rf test
