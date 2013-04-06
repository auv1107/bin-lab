all: test

test:  game.c gameinit.h gamerun.h clean.h basetype.h buildpics.h display.h drawpic.h generate.h initplane.h kbhit.h planetype.h showpic.h updatepos.h packetfunction.h 
	gcc -g -o test game.c gameinit.h gamerun.h clean.h basetype.h buildpics.h display.h drawpic.h generate.h initplane.h kbhit.h planetype.h showpic.h updatepos.h packetfunction.h -lm

clean: 
	rm -rf test

i: _test.c
	gcc -g -o a.out _test.c -lm
