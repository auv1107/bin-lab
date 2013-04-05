all: test

test:  game.c gameinit.h gamerun.h clean.h basetype.h buildpics.h display.h drawpic.h generate.h initplane.h kbhit.h planetype.h showpic.h updatepos.h
	gcc g -o test game.c gameinit.h gamerun.h clean.h basetype.h buildpics.h display.h drawpic.h generate.h initplane.h kbhit.h planetype.h showpic.h updatepos.h -lm

clean: 
	rm -rf test
