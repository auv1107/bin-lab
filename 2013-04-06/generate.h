#ifndef GENERATE
#define GENERATE _

#include "initplane.h"
#include "time.h"

extern struct airplane *enemy_plane_tail;
extern struct bullet *enemy_bullet_tail;
extern struct bullet *my_bullet_tail;
extern struct airplane *my_plane_head;
extern struct airplane *enemy_plane_head;

extern int Period;   // the period of screen refreshing     unit: us
extern int Rate;

void generate_enemy_plane()
{
	static int times = 0;
	
	if(times == Rate)
	{
		struct airplane *plane;
		plane = (struct airplane*) malloc (sizeof(struct airplane) );
		plane->type = time((void*) NULL) % NUMOFENEMYPLANES + 1;
		init_enemyplane_data(plane);

		plane->current_pos.x = rand() % 1366;
		plane->current_pos.y = 0;
		enemy_plane_tail->next = plane;
		plane->prev = enemy_plane_tail;
		enemy_plane_tail = plane;

		times = 0;
	}

	times++;
}

void generate_my_bullet()
{
	static int times = 0;
	if(times == Rate/10)
	{
		struct airplane *p = my_plane_head;
		while(p != NULL)
		{
			struct bullet *blt;
			blt = ( struct bullet *) malloc ( sizeof(struct bullet) );
			blt->type = p->type_of_bullet;
			init_bullet_data(blt);
			blt->current_pos.x = p->current_pos.x;
			blt->current_pos.y = p->current_pos.y - blt->bmp.height ;
			blt->angel = -90;

			my_bullet_tail->next = blt;
			blt->prev = my_bullet_tail;
			my_bullet_tail = blt;

			p = p->next;
		}
		times = 0;
		return;
	}
	times ++;
}

void generate_enemy_bullet()
{
	static int times = 0;
	if(times == Rate/2)
	{
		struct airplane *p = enemy_plane_head->next;
		while (p != NULL)
		{
			struct bullet *blt;
			blt = (struct bullet*) malloc (sizeof (struct bullet) );
			blt->type = 1;
			init_bullet_data(blt);   // TODO  
			blt->current_pos.x = p->current_pos.x;
			blt->current_pos.y = p->current_pos.y + blt->bmp.height;

			enemy_bullet_tail->next = blt;
			blt->prev = enemy_bullet_tail;
			enemy_bullet_tail = blt;

			p = p->next;
		}
		times = 0;
	}
	times ++;
}



void generate_all_things()
{
	generate_enemy_bullet();
	generate_my_bullet();
	generate_enemy_plane();
}







#endif
