#include "gameinit.h"
	#include "initplane.h"
	#include "planetype.h"
	#include "basetype.h"
#include "gamerun.h"
	#include "generate.h"
	#include "buildpics.h"
	#include "updatepos.h"
		#include "kbhit.h"
	
int main()
{
	game_init();
	game_run();
	
	clean_all_for_exit();
}
