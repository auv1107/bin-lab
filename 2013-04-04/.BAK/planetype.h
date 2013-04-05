#ifndef PLANETYPE
#define PLANETYPE

#include "basetype.h"

typedef struct airplane			// 飞机模型
{
	int type;		// 飞机类型
	int attack;		// 攻击力
	int defense;	// 防御力
	int hor_speed;		// 移动速度
	int ver_speed;
	int type_of_bullet;		// 子弹类型

	struct point current_pos;		// 当前位置
	int width;				// 飞机宽度
	int height;				// 分级高度
	char *pixel;			// 图像

	int reward;		// 击杀奖励
	int loss;		// 过线损失

	int MAXHP;		// 最大HP
	int MAXMP;		// 最大MP

	int current_hp;			// 当强HP
	int current_mp;			// 当前MP

	int recov_hp;		// HP 回复速度
	int recov_mp;		// MP 回复速度

		
	struct airplane *next;
	struct airplane *prev;

} Airplane;


typedef struct bullet		// 子弹模型
{
	int type;		// 子弹类型
	int attack;		// 攻击力
	int speed;		// 速度

	struct point current_pos;	// 当前坐标
	int width;		// 宽度
	int height;		// 高度
	char *pixel;

	int angel;		// 飞行角度（0，180）
	int exist;

	struct bullet *next;
	struct bullet *prev;

} Bullet;





#endif
