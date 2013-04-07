#ifndef PLANEINIT 
#define PLANEINIT

#include "showpic.h"
#include "planetype.h"
#include "basetype.h"
#include "display.h"
#include "gameinit.h"

extern int screen_ceil_limit;
extern int screen_floor_limit;
extern int screen_left_limit;
extern int screen_right_limit;

#define NUMOFENEMYPLANES 3	// the number of type of enemy planes
struct airplane Plane_type_1;
struct airplane Plane_type_2;
struct airplane Plane_type_3;

struct bullet Bullet_type_1;
struct bullet Bullet_type_2;
struct bullet Bullet_type_3;

struct airplane Myplane_type_1;
struct airplane Myplane_type_2;
struct airplane Myplane_type_3;

struct airplane *enemy_plane_head;
struct airplane *enemy_plane_tail;
struct airplane *my_plane_head;
struct airplane *my_plane_tail;

struct bullet *enemy_bullet_head;
struct bullet *enemy_bullet_tail;
struct bullet *my_bullet_head;
struct bullet *my_bullet_tail;

struct wallpaper background1;
struct wallpaper background2;
struct wallpaper background3;

struct wallpaper *current_wall;
struct airplane *my_current_plane;

extern char *fbp;

int enemy_plane1_init()
{	
	char path[32] = "img/enemyplane1.bmp";

	Plane_type_1.width = 50;
	Plane_type_1.height = 55;

	Plane_type_1.type = 1;
	Plane_type_1.attack = 100;
	Plane_type_1.defense = 100;
	Plane_type_1.hor_speed = 2;
	Plane_type_1.ver_speed = 1;
	Plane_type_1.type_of_bullet = 1;
	Plane_type_1.current_pos.x = 0;
	Plane_type_1.current_pos.y = 0;
	Plane_type_1.reward = 30;
	Plane_type_1.loss = 10;
	Plane_type_1.MAXHP = 1000;
	Plane_type_1.MAXMP = 0;
	Plane_type_1.current_hp = 1000;
	Plane_type_1.current_mp = 0;
	Plane_type_1.recov_hp =  0;
	Plane_type_1.recov_mp = 0;
	Plane_type_1.next = NULL;
	Plane_type_1.prev = NULL;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));
	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	Plane_type_1.bmp.pixel = (char *) malloc (size);
	Plane_type_1.bmp.width = info_header.ciWidth;
	Plane_type_1.bmp.height = info_header.ciHeight;
	Plane_type_1.bmp.bitcount = info_header.ciBitCount;

	getBmpPixel (path, Plane_type_1.bmp.pixel);
	scale_pic (&Plane_type_1.bmp, Plane_type_1.width , Plane_type_1.height);

	return 0;
}

int enemy_plane2_init()
{	
	char path[32] = "img/enemyplane1.bmp";

	Plane_type_2.width = 50;
	Plane_type_2.height = 55;

	Plane_type_2.type = 2;
	Plane_type_2.attack = 100;
	Plane_type_2.defense = 100;
	Plane_type_2.hor_speed = 2;
	Plane_type_2.ver_speed = 1;
	Plane_type_2.type_of_bullet = 1;
	Plane_type_2.current_pos.x = 0;
	Plane_type_2.current_pos.y = 0;
	Plane_type_2.reward = 30;
	Plane_type_2.loss = 10;
	Plane_type_2.MAXHP = 1000;
	Plane_type_2.MAXMP = 0;
	Plane_type_2.current_hp = 1000;
	Plane_type_2.current_mp = 0;
	Plane_type_2.recov_hp =  0;
	Plane_type_2.recov_mp = 0;
	Plane_type_2.next = NULL;
	Plane_type_2.prev = NULL;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	Plane_type_2.bmp.pixel = (char *) malloc (size);
	Plane_type_2.bmp.width = info_header.ciWidth;
	Plane_type_2.bmp.height = info_header.ciHeight;
	Plane_type_2.bmp.bitcount = info_header.ciBitCount;
	getBmpPixel (path, Plane_type_2.bmp.pixel);

	scale_pic (&Plane_type_2.bmp, Plane_type_2.width , Plane_type_2.height);

	return 0;
}

int enemy_plane3_init()
{	
	char path[32] = "img/enemyplane1.bmp";

	Plane_type_3.width = 50;
	Plane_type_3.height = 55;

	Plane_type_3.type = 3;
	Plane_type_3.attack = 100;
	Plane_type_3.defense = 100;
	Plane_type_3.hor_speed = 2;
	Plane_type_3.ver_speed = 1;
	Plane_type_3.type_of_bullet = 1;
	Plane_type_3.current_pos.x = 0;
	Plane_type_3.current_pos.y = 0;
	Plane_type_3.reward = 30;
	Plane_type_3.loss = 10;
	Plane_type_3.MAXHP = 1000;
	Plane_type_3.MAXMP = 0;
	Plane_type_3.current_hp = 1000;
	Plane_type_3.current_mp = 0;
	Plane_type_3.recov_hp =  0;
	Plane_type_3.recov_mp = 0;
	Plane_type_3.next = NULL;
	Plane_type_3.prev = NULL;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	Plane_type_3.bmp.pixel = (char *) malloc (size);
	Plane_type_3.bmp.width = info_header.ciWidth;
	Plane_type_3.bmp.height = info_header.ciHeight;
	Plane_type_3.bmp.bitcount = info_header.ciBitCount;
	getBmpPixel (path, Plane_type_3.bmp.pixel);

	scale_pic (&Plane_type_3.bmp, Plane_type_3.width , Plane_type_3.height);

	return 0;
}

int my_plane1_init()
{	
	char path[32] = "img/myplane1.bmp";

	Myplane_type_1.width = 50;
	Myplane_type_1.height = 55;

	Myplane_type_1.type = 1;
	Myplane_type_1.attack = 100;
	Myplane_type_1.defense = 100;
	Myplane_type_1.hor_speed = 30;
	Myplane_type_1.ver_speed = 30;
	Myplane_type_1.type_of_bullet = 1;
	Myplane_type_1.current_pos.x = 0;
	Myplane_type_1.current_pos.y = 0;
	Myplane_type_1.reward = 30;
	Myplane_type_1.loss = 10;
	Myplane_type_1.MAXHP = 1000;
	Myplane_type_1.MAXMP = 0;
	Myplane_type_1.current_hp = 1000;
	Myplane_type_1.current_mp = 0;
	Myplane_type_1.recov_hp =  0;
	Myplane_type_1.recov_mp = 0;
	Myplane_type_1.next = NULL;
	Myplane_type_1.prev = NULL;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	Myplane_type_1.bmp.pixel = (char *) malloc (size);
	Myplane_type_1.bmp.width = info_header.ciWidth;
	Myplane_type_1.bmp.height = info_header.ciHeight;
	Myplane_type_1.bmp.bitcount = info_header.ciBitCount;
	getBmpPixel (path, Myplane_type_1.bmp.pixel);

	scale_pic (&Myplane_type_1.bmp, Myplane_type_1.width , Myplane_type_1.height);

	return 0;
}

int my_plane2_init()
{	
	char path[32] = "img/myplane1.bmp";

	Myplane_type_2.width = 50;
	Myplane_type_2.height = 55;

	Myplane_type_2.type = 2;
	Myplane_type_2.attack = 100;
	Myplane_type_2.defense = 100;
	Myplane_type_2.hor_speed = 10;
	Myplane_type_2.ver_speed = 10;
	Myplane_type_2.type_of_bullet = 1;
	Myplane_type_2.current_pos.x = 0;
	Myplane_type_2.current_pos.y = 0;
	Myplane_type_2.reward = 30;
	Myplane_type_2.loss = 10;
	Myplane_type_2.MAXHP = 1000;
	Myplane_type_2.MAXMP = 0;
	Myplane_type_2.current_hp = 1000;
	Myplane_type_2.current_mp = 0;
	Myplane_type_2.recov_hp =  0;
	Myplane_type_2.recov_mp = 0;
	Myplane_type_2.next = NULL;
	Myplane_type_2.prev = NULL;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));
	
	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	Myplane_type_2.bmp.pixel = (char *) malloc (size);
	Myplane_type_2.bmp.width = info_header.ciWidth;
	Myplane_type_2.bmp.height = info_header.ciHeight;
	Myplane_type_2.bmp.bitcount = info_header.ciBitCount;
	getBmpPixel (path, Myplane_type_2.bmp.pixel);

	scale_pic (&Myplane_type_2.bmp, Myplane_type_2.width , Myplane_type_2.height);

	return 0;
}

int my_plane3_init()
{	
	char path[32] = "img/myplane1.bmp";

	Myplane_type_3.width = 50;
	Myplane_type_3.height = 55;

	Myplane_type_3.type = 3;
	Myplane_type_3.attack = 100;
	Myplane_type_3.defense = 100;
	Myplane_type_3.hor_speed = 10;
	Myplane_type_3.ver_speed = 10;
	Myplane_type_3.type_of_bullet = 1;
	Myplane_type_3.current_pos.x = 0;
	Myplane_type_3.current_pos.y = 0;
	Myplane_type_3.reward = 30;
	Myplane_type_3.loss = 10;
	Myplane_type_3.MAXHP = 1000;
	Myplane_type_3.MAXMP = 0;
	Myplane_type_3.current_hp = 1000;
	Myplane_type_3.current_mp = 0;
	Myplane_type_3.recov_hp =  0;
	Myplane_type_3.recov_mp = 0;
	Myplane_type_3.next = NULL;
	Myplane_type_3.prev = NULL;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	Myplane_type_3.bmp.pixel = (char *) malloc (size);
	Myplane_type_3.bmp.width = info_header.ciWidth;
	Myplane_type_3.bmp.height = info_header.ciHeight;
	Myplane_type_3.bmp.bitcount = info_header.ciBitCount;
	getBmpPixel (path, Myplane_type_3.bmp.pixel);

	scale_pic (&Myplane_type_3.bmp, Myplane_type_3.width , Myplane_type_3.height);
	
	return 0;
}

int init_plane()
{
	enemy_plane1_init();
	enemy_plane2_init();
	enemy_plane3_init();

	my_plane1_init();
	my_plane2_init();
	my_plane3_init();

	return 0;
}



int bullet1_init()
{
	char path[32] = "img/bullet1.bmp";
	
	Bullet_type_1.width = 10;
	Bullet_type_1.height = 10;
	Bullet_type_1.type = 1;
	Bullet_type_1.attack = 100;
	Bullet_type_1.speed = 10;
	Bullet_type_1.current_pos.x = 0;
	Bullet_type_1.current_pos.y = 0;
	Bullet_type_1.angel = 90;
	Bullet_type_1.exist = 1;
	Bullet_type_1.next = NULL;
	Bullet_type_1.prev = NULL;
	
	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	Bullet_type_1.bmp.pixel = (char *) malloc (size);
	Bullet_type_1.bmp.width = info_header.ciWidth;
	Bullet_type_1.bmp.height = info_header.ciHeight;
	Bullet_type_1.bmp.bitcount = info_header.ciBitCount;

	getBmpPixel (path, Bullet_type_1.bmp.pixel);
	scale_pic (&Bullet_type_1.bmp, Bullet_type_1.width , Bullet_type_1.height);
	
	return 0;
}

int bullet2_init()
{
	char path[32] = "img/bullet1.bmp";
	
	Bullet_type_2.width = 50;
	Bullet_type_2.height = 55;
	Bullet_type_2.type = 2;
	Bullet_type_2.attack = 100;
	Bullet_type_2.speed = 1;
	Bullet_type_2.current_pos.x = 0;
	Bullet_type_2.current_pos.y = 0;
	Bullet_type_2.angel = 90;
	Bullet_type_2.exist = 1;
	Bullet_type_2.next = NULL;
	Bullet_type_2.prev = NULL;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	Bullet_type_2.bmp.pixel = (char *) malloc (size);
	Bullet_type_2.bmp.width = info_header.ciWidth;
	Bullet_type_2.bmp.height = info_header.ciHeight;
	Bullet_type_2.bmp.bitcount = info_header.ciBitCount;

	getBmpPixel (path, Bullet_type_2.bmp.pixel);
	scale_pic (&Bullet_type_2.bmp, Bullet_type_2.width , Bullet_type_2.height);

	return 0;
}

int bullet3_init()
{
	char path[32] = "img/bullet1.bmp";
	
	Bullet_type_3.width = 50;
	Bullet_type_3.height = 55;
	Bullet_type_3.type = 3;
	Bullet_type_3.attack = 100;
	Bullet_type_3.speed = 1;
	Bullet_type_3.current_pos.x = 0;
	Bullet_type_3.current_pos.y = 0;
	Bullet_type_3.angel = 90;
	Bullet_type_3.exist = 1;
	Bullet_type_3.next = NULL;
	Bullet_type_3.prev = NULL;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	Bullet_type_3.bmp.pixel = (char *) malloc (size);
	Bullet_type_3.bmp.width = info_header.ciWidth;
	Bullet_type_3.bmp.height = info_header.ciHeight;
	Bullet_type_3.bmp.bitcount = info_header.ciBitCount;

	getBmpPixel (path, Bullet_type_3.bmp.pixel);
	scale_pic (&Bullet_type_3.bmp, Bullet_type_3.width , Bullet_type_3.height);
	
	return 0;
}

int init_bullet()
{
	bullet1_init();
	bullet2_init();
	bullet3_init();
	
	return 0;
}

int background1_init()
{
	char path[32] = "img/background1.bmp";
	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	background1.wall.pixel = (char *) malloc (size);
	background1.wall.width = info_header.ciWidth;
	background1.wall.height = info_header.ciHeight;
	background1.wall.bitcount = info_header.ciBitCount;

	getBmpPixel (path, background1.wall.pixel);
	scale_pic (&background1.wall , screen_right_limit - screen_left_limit,  (screen_floor_limit - screen_ceil_limit) * 3);

	background1.speed = 6;
	background1.current_pos.x = 0;
	background1.current_pos.y = 2 * (screen_floor_limit - screen_ceil_limit);

	return 0;
}

int background2_init()
{
	char path[32] = "img/background1.bmp";
	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	background2.wall.pixel = (char *) malloc (size);
	background2.wall.width = info_header.ciWidth;
	background2.wall.height = info_header.ciHeight;
	background2.wall.bitcount = info_header.ciBitCount;

	getBmpPixel (path, background2.wall.pixel);
	background2.speed = 6;
	background2.current_pos.x = 0;
	background2.current_pos.y = 0;

	return 0;
}

int background3_init()
{
	char path[32] = "img/background1.bmp";
	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(BITMAPINFOHEADER));

	ReadBitmapInfoHeader(path, &info_header);
	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	background3.wall.pixel = (char *) malloc (size);
	background3.wall.width = info_header.ciWidth;
	background3.wall.height = info_header.ciHeight;
	background3.wall.bitcount = info_header.ciBitCount;

	getBmpPixel (path, background3.wall.pixel);
	background3.speed = 6;
	background3.current_pos.x = 0;
	background3.current_pos.y = 0;

	return 0;
}

int init_background()
{
	background1_init();
	background2_init();
	background3_init();

	return 0;
}

void copy_plane_data(struct airplane* dest, struct airplane* src)
{
	dest->width = src->width;
	dest->height = src->height;

	dest->bmp.pixel = src->bmp.pixel;
	dest->bmp.width = src->bmp.width;
	dest->bmp.height = src->bmp.height;
	dest->bmp.bitcount = src->bmp.bitcount;
	dest->type = src->type;
	dest->attack = src->attack;
	dest->defense = src->defense;
	dest->hor_speed = src->hor_speed;
	dest->ver_speed = src->ver_speed;
	dest->type_of_bullet = src->type_of_bullet;
	dest->current_pos.x = vinfo.xres / 2;
	dest->current_pos.y = vinfo.yres - 10 - src->bmp.height;
	dest->reward = src->reward;
	dest->loss = src->loss;
	dest->MAXHP = src->MAXHP;
	dest->MAXMP = src->MAXMP;
	dest->current_hp = src->current_hp;
	dest->current_mp = src->current_mp;
	dest->recov_hp =  src->recov_hp;
	dest->recov_mp = src->recov_mp;
	dest->next = src->next;
	dest->prev = src->prev;
	
}

void copy_bullet_data(struct bullet* dest, struct bullet* src)
{
	dest->width = src->width;
	dest->height = src->height;

	dest->bmp.pixel = src->bmp.pixel;
	dest->bmp.width = src->bmp.width;
	dest->bmp.height = src->bmp.height;
	dest->bmp.bitcount = src->bmp.bitcount;
	dest->type = src->type;
	dest->attack = src->attack;
	dest->speed = src->speed;
	dest->angel = src->angel;
	dest->exist = src->exist;
	dest->next = src->next;
	dest->prev = src->prev;
}

void init_myplane_data(struct airplane* dest)
{
	switch(dest->type)
	{
		case 1: copy_plane_data(dest, &Myplane_type_1 ); break;
		case 2: copy_plane_data(dest, &Myplane_type_2 ); break;
		case 3: copy_plane_data(dest, &Myplane_type_3 ); break;
		default: dest->type = 1; copy_plane_data (dest, &Myplane_type_1) ;
	}
}

void init_bullet_data(struct bullet* dest)
{
	switch(dest->type)
	{
		case 1: copy_bullet_data(dest, &Bullet_type_1); break;
		case 2: copy_bullet_data(dest, &Bullet_type_1); break;
		case 3: copy_bullet_data(dest, &Bullet_type_1); break;
		default: dest->type = 1; copy_bullet_data(dest, &Bullet_type_1); break;
	}
}

void init_enemyplane_data(struct airplane* dest)
{
	switch(dest->type)
	{
		case 1: copy_plane_data(dest, &Plane_type_1); break;
		case 2: copy_plane_data(dest, &Plane_type_2); break;
		case 3: copy_plane_data(dest, &Plane_type_3); break;
		default: dest->type = 1; copy_plane_data(dest, &Plane_type_1); break;
	}
}

void init_all_headpoints()
{
//		initial all head point
	enemy_plane_head = (struct airplane*) malloc (sizeof (struct airplane) );
	bzero(enemy_plane_head, sizeof(enemy_plane_head));
	enemy_plane_head->next = NULL;
	enemy_plane_head->prev = NULL;
	enemy_plane_tail = enemy_plane_head;

	my_plane_head = (struct airplane*) malloc (sizeof (struct airplane) );
	bzero(my_plane_head, sizeof(my_plane_head));
	//  here will be some difference with enemy planes,  cause i have only one plane in a single play
	my_plane_head->type = 1;
	init_myplane_data(my_plane_head);
	my_plane_head->next = NULL;
	my_plane_head->prev = NULL;
	my_plane_tail = my_plane_head;

	enemy_bullet_head = (struct bullet*) malloc (sizeof (struct bullet) );
	bzero(enemy_bullet_head, sizeof(enemy_bullet_head ) );
	enemy_bullet_head->next = NULL;
	enemy_bullet_head->prev = NULL;
	enemy_bullet_tail = enemy_bullet_head;

	my_bullet_head = (struct bullet*) malloc (sizeof (struct bullet) );
	bzero(my_bullet_head, sizeof(my_bullet_head) );
	my_bullet_head->next = NULL;
	my_bullet_head->prev = NULL;
	my_bullet_tail = my_bullet_head;
}

void set_default_wall_and_plane()
{
//  set current_wall, my_current_plane  
	current_wall = &background1;
	my_current_plane = my_plane_head;
}

int init_all_modules()
{
	init_plane();
	init_bullet();
	init_background();
	
	init_all_headpoints();
	set_default_wall_and_plane();

	return 0;
}

#endif
