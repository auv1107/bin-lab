#ifndef BUILDPICS
#define BUILDPICS

#include "planetype.h"
#include "drawpic.h"
#include "display.h"

extern struct airplane *enemy_plane_head;
extern struct airplane *my_plane_head;

extern struct bullet *enemy_bullet_head;
extern struct bullet *my_bullet_head;

extern struct wallpaper background1;
extern struct wallpaper background2;
extern struct wallpaper background3;

extern struct wallpaper *current_wall;

extern char *fbp;

int background_build(struct wallpaper *background)
{
	//  optimize the way to show a wallpaper
	draw_pic_at (background->current_pos.x, background->current_pos.y, background->wall.pixel, background->wall.width, background->wall.height);

	return 0;
}

void build_background()
{
	background_build(current_wall);
/*
	switch(type)
	{
		case 1: background_build (&background1); break;
		case 2: background_build (&background2); break;
		case 3: background_build (&background3); break;
		default: background_build (&background1); break;
	}
*/
}

void plane_build(struct airplane *p)
{
	draw_pic_at(p->current_pos.x, p->current_pos.y, p->bmp.pixel, p->bmp.width, p->bmp.height);
}

void build_enemy_plane()
{
	struct airplane *p = enemy_plane_head->next;

	while(p != NULL)
	{
		plane_build(p);
		p = p->next;
	}
}

void build_my_plane()
{
	struct airplane *p = my_plane_head;

	while(p != NULL)
	{
		plane_build(p);
		p = p->next;
	}
}

void bullet_build(struct bullet *p)
{
	draw_pic_at(p->current_pos.x, p->current_pos.y, p->bmp.pixel, p->bmp.width, p->bmp.height);
}

void build_enemy_bullet()
{
	struct bullet *p = enemy_bullet_head->next;
	while(p != NULL)
	{
		bullet_build(p);
		p = p->next;
	}
}

void build_my_bullet()
{
	struct bullet *p = my_bullet_head->next;
	while(p != NULL)
	{
		bullet_build(p);
		p = p->next;
	}
}


void build_all_things()
{
	build_background();
	build_enemy_plane();
	build_enemy_bullet();
	build_my_plane();
	build_my_bullet();
}










#endif 
