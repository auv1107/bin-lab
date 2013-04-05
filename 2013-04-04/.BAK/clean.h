#ifndef CLEAN
#define CLEAN


#include "initplane.h"


extern struct airplane* enemy_plane_head;
extern struct airplane* my_plane_head;

extern struct bullet* enemy_bullet_head;
extern struct bullet* my_bullet_head;


void clean_enemy_planes()
{
	struct airplane* p = enemy_plane_head->next;
	struct airplane* tmp = NULL;
	while (p != NULL)
	{
		if (p->current_hp <= 0)
		{
			p->prev->next = p->next;
			if (p->next != NULL)
			{
				p->next->prev = p->prev;
			}
			tmp = p;
			p = p->next;
			free(tmp);
			continue;
		}
		p = p->next;
	}
}

void clean_all_bullets()
{
	struct bullet* p = enemy_bullet_head->next;
	struct bullet* tmp = NULL;
	while (p != NULL)
	{
		if (p->exist = 0)
		{
			p->prev->next = p->next;
			if (p->next != NULL)
			{
				p->next->prev = p->prev;
			}
			tmp = p;
			p = p->next;
			free(tmp);
			continue;
		}
		p = p->next;
	}

	p = my_bullet_head->next;
	tmp = NULL;

	while (p != NULL)
	{
		if (p->exist = 0)
		{
			p->prev->next = p->next;
			if (p->next != NULL)
			{
				p->next->prev = p->prev;
			}
			tmp = p;
			p = p->next;
			free(tmp);
			continue;
		}
		p = p->next;
	}

}

void clean_all_for_exit()
{
	struct airplane* p = enemy_plane_head;
	struct airplane* tmp = NULL;
	while (p != NULL)
	{
		tmp = p;
		p = p->next;
		free(tmp);
	}
	
	struct bullet* q = enemy_bullet_head;
	struct bullet* t = NULL;
	while (q != NULL)
	{
		t = q;
		q = q->next;
		free(t);
	}

	q = my_bullet_head;
	tmp = NULL;
	while (q != NULL)
	{
		t = q;
		q = q->next;
		free(t);
	}
}

void clean_all_zombies()
{
	clean_enemy_planes();
	clean_all_bullets();
}





#endif
