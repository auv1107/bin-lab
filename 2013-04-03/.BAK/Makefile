all: test

test: _main.c basetype.h showpic.h drawpic.h kbhit.h
	gcc -o test _main.c showpic.h basetype.h basetype.h kbhit.h -lm

clean:
	rm -rf test
