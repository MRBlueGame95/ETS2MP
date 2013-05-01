/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CClient.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

CClient * CClient::m_sInstance = 0;

CClient::CClient()
	: m_bControls(true)
{	
	// Setup the instance
	m_sInstance = this;

	// Initialize game offsets
	if(!CGameOffsets::Initialize())
	{
		MessageBox(NULL,"Cannot detect game version! Mod currently supports "MOD_SUPPORTED_VERSIONS" please try update or downgrade your game.","Fatal Error",MB_ICONERROR);
		ExitProcess(0);
		return;
	}

	// Initialize game patches
	if(!CGamePatches::Initialize())
	{
		MessageBox(NULL, "Cannot install game patches! Please try again!", "Fatal Error", MB_ICONERROR);
		ExitProcess(0);
		return;
	}

	// Initialize game hooks
	if(!CGameHooks::Initialize())
	{
		MessageBox(NULL, "Cannot install game hooks! Please try again!", "Fatal Error", MB_ICONERROR);
		ExitProcess(0);
		return;
	}

	// Install DirectX3D9Hook
	if(!CDirect3D9Hook::Install())
	{
		MessageBox(NULL, "Cannot install Direct3D 9 hook! Please try again!", "Fatal Error", MB_ICONERROR);
		ExitProcess(0);
		return;
	}

	// Install Direct input hook
	CDirectInput8Hook::Install();
}

CClient::~CClient()
{

}


bool bNetworkState = false;
void CClient::pulse()
{
	if(bNetworkState)
	{
		CNetwork::GetInstance().pulse();
	}
}

void CClient::loadGame()
{
	new CNetwork();
	bNetworkState = true;

	char szAddress[64], *res;
	strcpy(szAddress,"127.0.0.1");
	FILE * fFile = fopen(SharedUtils::GetAbsolutePath("server.conf"),"r+");
	if(fFile)
	{
		res = fgets(szAddress,64,fFile);
		if(res==NULL)
		{
			strcpy(szAddress,"127.0.0.1");
		}
	}
	fclose(fFile);

	CChat::GetInstance().output(0xFFFF8000,"Connecting to %s:%d..", szAddress, 8365);
	CNetwork::GetInstance().connect(szAddress, 8365);

}