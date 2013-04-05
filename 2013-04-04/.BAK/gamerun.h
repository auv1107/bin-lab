#include "generate.h"
#include "buildpics.h"
#include "updatepos.h"
#include "clean.h"

extern Period;

void game_run()
{
	for( ; ; )
	{
		generate_all_things();
		build_all_things();
		update_all_things();
		clean_all_zombies();

		usleep(Period);
	}
}
