#include "initplane.h"
#include "display.h"

extern struct airplane *my_plane_head;
extern struct airplane Myplane_type_1;

void printplane(struct airplane *dest)
{
	printf("type: %d\n", dest->type);
	printf("attack: %d\n", dest->attack);
	printf("defanse: %d\n", dest->defense);
	printf("ver_speed: %d\n", dest->ver_speed);
	printf("type of bullet: %d\n", dest->type_of_bullet);
	printf("pos: %d\n", dest->current_pos.x);
	printf("dest->next: %d\n", dest->next);
	printf("dest->pixel[0]: %s\n", dest->pixel);
}


void goairplane(struct airplane *head)
{
	struct airplane* p = head;
	while (p != NULL)
	{
		printplane(p);
		p = p->next;
	}
}

int main()
{
	init_all_modules();
//	printplane(&Myplane_type_1);
	draw_pic_at( 10 , 20 , Myplane_type_1.pixel, Myplane_type_1.width, Myplane_type_1.height);
//	goairplane(my_plane_head);
}
