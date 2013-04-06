#include "gameinit.h"
#include "display.h"


extern struct airplane *enemy_plane_head;
extern struct airplane *my_plane_head;
extern struct bullet *my_bullet_head;

extern struct wallpaper background1;



void show(struct airplane *p)
{
	printf("type: %d\n", p->type);
	draw_pic_at ( 40 , 50 , p->bmp.pixel, p->bmp.width, p->bmp.height);
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
//		show(p);
		p = p->next;
	}
}

int main()
{
	game_init();
//	_test_enemy_plane();
//	init_all_modules();
	
	scale_pic(&background1.wall, 1000, 568);
//	draw_pic_at ( 300, 400, my_plane_head->bmp.pixel, my_plane_head->bmp.width, my_plane_head->bmp.height);
	draw_pic_at ( 0 , 0 , background1.wall.pixel, background1.wall.width, background1.wall.height);
	fbd_exit();

	game_exit();

}



