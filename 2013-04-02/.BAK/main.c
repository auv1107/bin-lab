#include "basetype.h"
#include "drawpic.h"

int main()
{
	struct color cl;
	cl.blue = 0;
	cl.green = 0;
	cl.red = 0;
	cl.alpha = 0;

	char *fbp = fbd_init();

	struct point centre;
	centre.x = 400;
	centre.y = 200;

	Set_color(cl);
	Draw_circle(fbp, centre, 300);
	
	int i, j;

	for(i = 0; i < 200; i++)
		for(j = 0; j < 400; j++)
			draw_point(fbp, i, j);

	for(i = 300; i < 310; i++)
		draw_line(fbp, 0, i, 1366, i);

	draw_rectangle(fbp, 0, 0, 1365, 761);

	fbd_exit(fbp);

	exit(0);
}
