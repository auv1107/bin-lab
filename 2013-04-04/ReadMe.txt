there's still a problem, when reading pixel of bmps


the problem may be caused by malloc,  I malloc some memory in a jubu function,  after i quit , these memories will disappear. so the seg fault generated.

the for in gamerun.c, if i < 26, it broken.  but for 25, it was all right.

25 is the number to generate my first bullet.  when it called to be showed, seg fault.

try to draw the pics after reading pixel from bmps. in file initplane.h

