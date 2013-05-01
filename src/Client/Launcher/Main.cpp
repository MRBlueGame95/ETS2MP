/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Launcher
 * Licence     : See LICENSE in the top level directory
 * File		   : Main.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <StdInc.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdLine)
{
	// Install anty debugger
	SharedUtils::Protection::InstallAntyDebugger();

	// Predefine all varibles
	char szGamePath[MAX_PATH] = { 0 };
	char szGameFullPath[MAX_PATH] = { 0 };
	char szParams[] = "-rdevice dx9";

	// Get current client core library file name
#ifdef DEBUG
	char * szLibraryPath = "Client_d.dll";
#else
	char * szLibraryPath = "Client.dll";
#endif

	// Grab game path from registry
	if(!SharedUtils::Registry::Read(HKEY_LOCAL_MACHINE, "Software\\SCS Software\\Euro Truck Simulator 2", "InstallDir", szGamePath, MAX_PATH))
	{
		// If we cannot find it - display an error
		// and close launcher
		// TODO: Custom game path selector
		MessageBox(NULL,"Cannot find game path in registry!", "Fatal Error", MB_ICONERROR);		
		return 0;
	}

	// Format game paths
	sprintf(szGamePath,"%s\\bin\\win_x86",szGamePath);
	sprintf(szGameFullPath, "%s\\eurotrucks2.exe", szGamePath);

	// Predefine startup and process infos
	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

	// Create game process
	if(!CreateProcess(szGameFullPath,szParams,NULL,NULL,true,CREATE_SUSPENDED,NULL,szGamePath,&siStartupInfo,
		&piProcessInfo))
	{
		// If we cannot start process print an error
		// and close launcher
		// TODO: Try UAC Creating process if failed
		MessageBox(NULL,"Cannot create process!","Fatal Error",MB_ICONERROR);
		return 0;
	}

	// Inject library into process
	SharedUtils::Injecting::eState injectState = SharedUtils::Injecting::LibraryIntoProcess(SharedUtils::GetAbsolutePath(szLibraryPath),piProcessInfo.hProcess);

	if(injectState == SharedUtils::Injecting::FAILED)
	{
		// If we cannot inject library into process print an error
		// and close launcher
		MessageBox(NULL,"Cannot inject mod library into process!","Fatal Error",MB_ICONERROR);
		return 0;
	}

	// Resume game main thread
	ResumeThread(piProcessInfo.hThread);

	// Return 1
	return 1;
}