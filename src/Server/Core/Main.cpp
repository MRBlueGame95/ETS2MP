/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Server Core
 * Licence     : See LICENSE in the top level directory
 * File		   : Main.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

int main(int argc, char ** argv)
{
	printf("[startup] Euro Truck Simulator 2 Multiplayer server starting... (Port: 8365, Max connections: 100)\n");
	new CNetwork(100, 8365);
	printf("[startup] Network started, listening at port 8365 (Max connections 100)!\n");

	while(true)
	{
		CNetwork::GetInstance().pulse();

		Sleep(5);
	}
	return 1;
}