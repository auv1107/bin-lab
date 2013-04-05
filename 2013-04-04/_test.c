#include "gameinit.h"
#include "display.h"


extern struct airplane *enemy_plane_head;
extern struct airplane *my_plane_head;
extern struct bullet *my_bullet_head;



void show(struct bullet *p)
{
	printf("type: %d\n", p->type);
	draw_pic_at ( 40 , 50 , p->pixel, p->width, p->height);
}


void _test_enemy_plane()
{
	struct airplane *p = my_plane_head;
	while (p != NULL)
	{
		show(p);
		p = p->next;
	}
}

void _test_my_bullet()
{
	struct bullet *p = my_bullet_head;
	while (p != NULL)
	{
		show(p);
		p = p->next;
	}
}

int main()
{
	game_init();
	_test_enemy_plane();
	game_exit();

}



