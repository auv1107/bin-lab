#ifndef UPDATEPOS
#define UPDATEPOS

#include "planetype.h"
#include "kbhit.h"
#include "clean.h"
#include "gameinit.h"

extern struct wallpaper *current_wall;
extern struct fb_var_screeninfo vinfo;
extern struct fb_fix_screeninfo finfo;

extern struct airplane *enemy_plane_head;
extern struct airplane *my_plane_head;
extern struct bullet *enemy_bullet_head;
extern struct bullet *my_bullet_head;
extern struct airplane *my_current_plane;


#define PI 3.1415
#define RADIAN 3.1415*1.0/180

extern int screen_left_limit;
extern int screen_right_limit;
extern int screen_ceil_limit;
extern int screen_floor_limit;

void update_wallpaper()
{
	current_wall->current_pos.y += current_wall->speed;
	if (current_wall->current_pos.y >= screen_floor_limit )
		current_wall->current_pos.y = screen_ceil_limit ;
	//TODO  optimize the way to reset pos
}

void enemy_plane_update(struct airplane *p)
{
// TODO  optimize the way to choose a direction
	p->current_pos.y += p->ver_speed;

	int dir = time( (void*)NULL ) % 2;
	if( dir == 0 )
	{
		//  plane fly to left side
		p->current_pos.x -= p->hor_speed;
		if (p->current_pos.x <= screen_left_limit)
			p->current_pos.x += 2 * p->hor_speed;
	}
	else
	{
		// 	right
		p->current_pos.x += p->hor_speed;
		if (p->current_pos.y >=  screen_right_limit)
			p->current_pos.y -= 2 * p->hor_speed;
	}
}

void update_enemy_plane()
{
	struct airplane *p = enemy_plane_head->next;
	while(p != NULL)
	{
		enemy_plane_update(p);
		p = p->next;
	}
}

void bullet_update(struct bullet *p)
{
// TODO update position of each one bullet
	int x_offset = (int) ( p->speed * cos(p->angel * RADIAN) );
	int y_offset = (int) ( p->speed * sin(p->angel * RADIAN) );
	
	p->current_pos.x += x_offset;
	p->current_pos.y += y_offset;

	if(p->current_pos.x < screen_left_limit ||
			p->current_pos.x > screen_right_limit ||
			p->current_pos.y < screen_ceil_limit ||
			p->current_pos.y > screen_floor_limit )
	{
		p->exist = 0;
	}
	
}

void update_bullet()
{
	struct bullet *p = enemy_bullet_head->next;
	while(p != NULL)
	{
		bullet_update(p);
		p = p->next;
	}
	
	p = my_bullet_head->next;
	while(p != NULL)
	{
		bullet_update(p);
		p = p->next;
	}
}


void update_my_plane(int press)
{
	switch(press)
	{
		case K_UP: 
			{
				my_current_plane->current_pos.y -= my_current_plane->ver_speed;
				if (my_current_plane->current_pos.y < screen_ceil_limit )
					my_current_plane->current_pos.y = screen_ceil_limit;
				break;
			}
		case K_DOWN:
			{
				my_current_plane->current_pos.y += my_current_plane->ver_speed;
				if (my_current_plane->current_pos.y > screen_floor_limit - my_current_plane->bmp.height / 2)
					my_current_plane->current_pos.y = screen_floor_limit - my_current_plane->bmp.height / 2;
				break;
			}
		case K_LEFT:
			{
				my_current_plane->current_pos.x -= my_current_plane->hor_speed;
				if (my_current_plane->current_pos.x < screen_left_limit )
					my_current_plane->current_pos.x = screen_left_limit ;
				break;
			}
		case K_RIGHT:
			{
				my_current_plane->current_pos.x += my_current_plane->hor_speed;
				if (my_current_plane->current_pos.x > screen_right_limit - my_current_plane->bmp.width / 2)
					my_current_plane->current_pos.x = screen_right_limit - my_current_plane->bmp.width / 2;
				break;
			}
		case 'q':
			{
				clean_all_for_exit();
				game_exit();
				exit(0);
			}
	}
}




void update_all_things()
{
	update_wallpaper();
	update_enemy_plane();
	update_bullet();

	int press = getudlr();
	update_my_plane(press);
}





















#endif
