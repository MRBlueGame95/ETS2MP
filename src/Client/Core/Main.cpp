/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : Main.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>,
 *			     Aliqe		<kiklus95@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

CClient * g_pClient = NULL;

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			// Disable thread library calls
			DisableThreadLibraryCalls(hModule);

			// Initialize Logger
			char szLogPath[MAX_PATH];
			time_t t = time(NULL);
			struct tm * p_time = localtime(&t);

			CreateDirectory(SharedUtils::GetAbsolutePath("Logs\\"),NULL);

			sprintf(szLogPath,"%sclient_%02d_%02d_%04d.log",SharedUtils::GetAbsolutePath("Logs\\"),p_time->tm_mday,(p_time->tm_mon+1),(1900+p_time->tm_year));
			CLogger::Init(szLogPath);

#ifdef DEBUG
			// Initialize debug stuffs
			AllocConsole();
			freopen("CONOUT$", "w", stdout);
			freopen("CONIN$", "r", stdin);

			CLogger::Debugf("Console started!");
#endif

			// Create an client instance
			g_pClient = new CClient();

			if(!g_pClient)
			{
				MessageBox(NULL, "Critical error with initializing client core instance, try again. If still this message occurs please try reinstal mod.", "Critical Error", MB_ICONERROR | MB_TOPMOST);
				ExitProcess(0);
				return TRUE;
			}
		} break;
	case DLL_PROCESS_DETACH:
		{
			if(g_pClient)
			{
				delete g_pClient;
				g_pClient = NULL;
			}
		} break;
	}
	return TRUE;
}