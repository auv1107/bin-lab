#ifndef GAMERUN
#define GAMERUN _


#include "generate.h"
#include "buildpics.h"
#include "updatepos.h"
#include "clean.h"
#include <pthread.h>

extern Period;

void game_run()
{
	int i;
	for( ;   ;  )   //  here should be    for ( ; ; )
	{
		generate_all_things();
		build_all_things();
		update_all_things();
		clean_all_zombies();

		usleep(Period);
	}
}







#endif
