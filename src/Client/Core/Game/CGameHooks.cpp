/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CGameHooks.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>,
 *			     Aliqe		<kiklus95@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

//#define DEBUG_LOGGER

extern CClient * g_pClient;

DWORD HOOKPOS_MainLoop = 0x5D2900;
DWORD RETURN_MainLoop = 0x5D290A;

DWORD HOOKPOS_CTrafficGenerator__Generate = 0x6E7FE0;

DWORD HOOKPOS_CPedestriansGenerator__Generate = 0x6E7FE0;

DWORD HOOKPOS_CParkedCarGenerator__Generate = 0x50FB00;

DWORD HOOKPOS_Logger = 0x5F00A1;
DWORD RETURN_Logger = 0x5F00AB;

DWORD HOOKPOS_CVars__Store = 0x5BC461;
DWORD RETURN_CVars__Store = 0x5BC466;

DWORD mem_vsnprintf = 0x80D2B8;
DWORD mem_operatorNew = 0x80ABFF;

char * szLogBuffer;
HWND hDlg = NULL;

void _declspec(naked) HOOK_CVars__Store()
{
	_asm
	{
		pushad
	}

	CGameVars::StoreCustomVars();

	_asm
	{
		popad
		pop esi
		pop ebx
		mov esp, ebp
		pop ebp
		jmp RETURN_CVars__Store
	}
}

void _declspec(naked) HOOK_MainLoop()
{
	_asm
	{
		pushad
	}

	if(g_pClient)
		g_pClient->pulse();

	hDlg = *(HWND *)0xA4094C;
	_asm 
	{
		popad
		sub esp, 1Ch
		cmp hDlg, 0
		jmp RETURN_MainLoop
	}
}

void _declspec(naked) HOOK_CPedestriansGenerator__Generate()
{
	_asm
	{
		mov eax, 0
		retn
	}
}

void _declspec(naked) HOOK_CTrafficGenerator__Generate ()
{
	_asm
	{
		retn
	}
}

void _declspec(naked) HOOK_CParkedCarGenerator__Generate ()
{
	_asm
	{
		retn 4
	}
}

void _declspec(naked) HOOK_Logger()
{
	_asm
	{
		call mem_vsnprintf
		add esp, 10h
		mov szLogBuffer, esi
		pushad
	}

	if(szLogBuffer && strlen(szLogBuffer) > 0)
	{
		CLogger::Printf("%s",szLogBuffer);
	}

	_asm
	{
		popad
		test eax, eax
		jmp RETURN_Logger
	}
}

// TEST START
DWORD HOOKPOS_Test = 0x682EE0;
DWORD RETURN_Test = 0x682EE6;
void _declspec(naked) HOOK_Test()
{
	_asm
	{
		pushad
	}

	CLogger::Debugf("Create truck or camera constructor");

	_asm
	{
		popad
		push esi
		push 0D8h
		jmp RETURN_Test
	}
}

DWORD HOOKPOS_Test_2 = 0x4364E0;
DWORD RETURN_Test_2 = 0x4364E5;
DWORD dwHandler_2 = NULL;
void _declspec(naked) HOOK_Test_2()
{
	_asm
	{
		pushad
	}

	CLogger::Debugf("Test 2");

	dwHandler_2 = *(DWORD*)0xA0EBEC;
	_asm
	{
		popad
		mov eax, dwHandler_2
		jmp RETURN_Test_2
	}
}

DWORD HOOKPOS_TrailerCreate = 0x70C2B0;
DWORD RETURN_TrailerCreate = 0x70C2B7;
void _declspec(naked) HOOK_TrailerCreate()
{
	_asm
	{
		pushad
	}

	CLogger::Debugf("Create Trailer");

	_asm
	{
		popad
		push 58h ; sizeof ETS2Trailer structure
		call mem_operatorNew
		jmp RETURN_TrailerCreate
	}
}
/*
  sub_453DF0(v1);
  sub_583C70(&off_98CF1C); // environment 
  sub_583C70(&off_98AB98); // rain
  sub_583C70(&off_98AB48); // snow
  sub_453F10();
  sub_583C70(&off_98C7E8); // game physics vehicle
  sub_583C70(&off_98C74C); // game trailer actor
  sub_583C70(&off_98A8F4); // game trailer traffic
  sub_453FF0();
  sub_583C70(&off_98A7A8); // debug camera et
  sub_583C70(&off_98D6E4); // showroom camera
  sub_583C70(&off_98D588); // game actor
  sub_583C70(&off_98A740); // game actor glass (LOL?)
  sub_583C70(&off_98C790); // visual interior
  sub_583C70(&off_98C6F0); // gas station hud
  sub_583C70(&off_98D1B0); // traffic
  sub_583C70(&off_98D144); // sound player
  sub_583C70(&off_98D864); // screen ctrl

  //

  sub_583C70(&off_98CF3C); // save container
  sub_583C70(&off_97CF30); // voice data
  sub_583C70(&off_97CF48); // voice table
  sub_583C70(&off_97CF60); // voices overs
  sub_583C70(&off_98AB00); // showroom vehicle
  sub_583C70(&off_98AACC); // showroom data
  sub_583C70(&off_98AAB4); // game material data
  sub_583C70(&off_98C8D4); // game tr light item
  sub_583C70(&off_98AA7C); // parked car
  sub_583C70(&off_97CF00); // billboard message
  sub_583C70(&off_98A9F4); // garage door
  sub_583C70(&off_98A9D0); // brand hookup
  sub_583C70(&off_98CAC4); // scene desc
  sub_583C70(&off_98A9A0); // desktop sdecs selector
  sub_583C70(&off_98C3F8); // tollgate
  sub_583C70(&off_98A964); // speed camera
  sub_583C70(&off_98C8BC); // truck dealer stortiment
  sub_583C70(&off_98CB0C); // showroom state

  //

  sub_583C70(&off_98D96C); // economy
  sub_583C70(&off_98D668); // job offsers
  sub_583C70(&off_98C80C); // job info
  sub_583C70(&off_98D650); // company
  sub_583C70(&off_98D954); // special job sequence status
  sub_583C70(&off_98CF54); // special job offer
  sub_583C70(&off_98CF6C); // special job sequence
  sub_583C70(&off_98D08C); // driver
  sub_583C70(&off_98CED4); // driver ai
  sub_583C70(&off_98CBA4); // driver player
  sub_583C70(&off_98CC28); // delivery log entry
  sub_583C70(&off_98CC40); // delivery log
  sub_583C70(&off_98CCD8); // transport data
  sub_583C70(&off_98CCF0); // game progress
  sub_583C70(&off_98CFE4); // economy data
  sub_583C70(&off_98CFFC); // driver names
  sub_583C70(&off_98CF84); // economy event
  sub_583C70(&off_98CF9C); // economy event queue
  sub_583C70(&off_98C824); // company pernament
  sub_583C70(&off_98D5DC); // player
  sub_583C70(&off_98D5F8); // player job
  sub_583C70(&off_98CE08); // bank
  sub_583C70(&off_98A8A8); // bank loan
  sub_583C70(&off_98A874); // bank data
  sub_583C70(&off_98A85C); // feat visitor data
  sub_583C70(&off_98CDB0); // garage
  sub_583C70(&off_98CC74); // profit log entry
  sub_583C70(&off_98CC8C); // profit log
  sub_583C70(&off_98D434); // mail text
  sub_583C70(&off_98D44C); // mail data
  sub_583C70(&off_98D464); // mail definition
  sub_583C70(&off_98D47C); // mail send params
  sub_583C70(&off_98D494); // mail ctrl
  sub_583C70(&off_98CE64); // police data
  sub_583C70(&off_98CE7C); // police ctrl
  sub_583C70(&off_98A814); // feat description
  sub_583C70(&off_98A82C); // feat data
  sub_583C70(&off_98A844); // feat visitor data
  sub_583C70(&off_98D114); // user profile
  sub_583C70(&off_98A7C8); // special event data
  sub_583C70(&off_98CD08); // registry


*/
DWORD HOOKPOS_TrailerCreate_2 = 0x486550;//Trailer VTABLE 98C750
DWORD RETURN_TrailerCreate_2 = 0x486556;
void _declspec(naked) HOOK_TrailerCreate_2()
{
	_asm
	{
		pushad
	}

	CLogger::Debugf("Trailer Create 2");

	_asm
	{
		popad
		push esi
		push 3F0h
		jmp RETURN_TrailerCreate_2
	}
}

DWORD HOOKPOS_GameActorCreate = 0x442CA0;
DWORD RETURN_GameActorCreate = 0x442CA5;
void _declspec(naked) HOOK_GameActorCreate()
{
	_asm
	{
		pushad
	}

	CLogger::Debugf("GameActorCreate");

	_asm
	{
		popad
		push 3B0h
		jmp RETURN_GameActorCreate
	}
}

//int __usercall sub_445FB0<eax>(int a1<edx>, int a2<ecx>, int a3<esi>)
DWORD HOOKPOS_Test_3 = 0x445FB0;
DWORD RETURN_Test_3 = (HOOKPOS_Test_3 + 0x5);
void _cdecl sub_445FB0(int a1, int a2, int a3)
{
	CLogger::Debugf("sub_445FB0(0x%p, 0x%p, 0x%p); // CREATE TRUCK (4)?", a1,a2,a3);
}

void _declspec(naked) HOOK_Test_3()
{
	_asm
	{
		pushad

		push esi
		push ecx
		push edx
		call sub_445FB0
		add esp, 0Ch
		popad

		mov eax, 0xA0EBEC
		mov eax, [eax]
		jmp RETURN_Test_3
	}
}

// void *__thiscall sub_505B20(void *this, char a2)
DWORD HOOKPOS_Test_4 = 0x505B20;
DWORD RETURN_Test_4 = (HOOKPOS_Test_4 + 0x9);
void _cdecl sub_505B20(int _ecx, int a2)
{
	CLogger::Debugf("sub_505B20(0x%p, %d); // CREATE TRUCK (3)?",_ecx, a2);
}

void _declspec(naked) HOOK_Test_4()
{
	_asm
	{
		pushad
		push [esp+8h]
		push ecx
		call sub_505B20
		add esp, 8h
		popad

		push esi
		mov esi, ecx
		mov edi, 0x9AE840; can cause crash
		mov dword ptr [esi], edi
		jmp RETURN_Test_4
	}
}


// sub_505AF0(int a1)
DWORD HOOKPOS_Test_5 = 0x505AF0;
DWORD RETURN_Test_5 = (HOOKPOS_Test_5 + 0x5);

void _cdecl sub_505AF0(int a1)
{
	CLogger::Debugf("sub_505AF0(0x%p); // CREATE TRUCK (2)?", a1);
}

void _declspec(naked) HOOK_Test_5()
{
	_asm
	{
		pushad
		push [esp+4h]
		call sub_505AF0
		add esp, 4h
		popad

		push 0D0h 
		call mem_operatorNew
		jmp RETURN_Test_5
	}
}

//int __stdcall sub_41BAB0(int a1)
DWORD HOOKPOS_Test_6 = 0x41BAB0;
DWORD RETURN_Test_6 = (HOOKPOS_Test_6 + 0x9);
void _cdecl sub_41BAB0(int a1)
{
	CLogger::Debugf("sub_41BAB0(0x%p); // CREATE TRUCK?", a1);
}

void _declspec(naked) HOOK_Test_6()
{
	_asm
	{
		pushad
		push [esp+4Ch]
		call sub_41BAB0
		add esp, 4h
		popad

		sub esp, 38h
		mov esi, 0xA57E9C
		mov ecx, [esi]
		jmp RETURN_Test_6
	}
}

DWORD HOOKPOS_Test_7 = 0x454280;
DWORD RETURN_Test_7 = (HOOKPOS_Test_7 + 0x5);
void _cdecl sub_454280(int _this)
{
	CLogger::Debugf("sub_454280(0x%p)", _this);
}

void _declspec(naked) HOOK_Test_7()
{
	_asm
	{
		pushad
		push eax
		call sub_454280
		add esp, 4h
		popad

		push 0EF58h
		jmp RETURN_Test_7
	}
}

DWORD HOOKPOS_Test_8 = 0x004F76D0;
DWORD RETURN_Test_8 = (HOOKPOS_Test_8 + 0x5);
void _cdecl sub_4F76D0(int a1)
{
	CLogger::Debugf("sub_4F76D0(0x%p)", a1);
}

void _declspec(naked) HOOK_Test_8()//truck_config_hdl
{
	_asm
	{
		pushad
		push [esp+4h]
		call sub_4F76D0
		add esp, 4h
		popad

		push 140h
		jmp RETURN_Test_8
	}
}

DWORD HOOKPOS_Test_9 = 0x4402C0;
DWORD RETURN_Test_9 = (HOOKPOS_Test_9 + 0x6);
void _cdecl sub_4402C0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	CLogger::Debugf("sub_4402C0(%d, %d, %d, %d, %d, %d, %d, %d)",
		a1, a2, a3, a4, a5, a6, a7, a8);
}

void _declspec(naked) HOOK_Test_9()
{
	_asm
	{
		pushad
		push [esp+58h]
		push [esp+54h]
		push [esp+50h]
		push [esp+4Ch]
		push [esp+48h]
		;mov ebx, xmm0
		;push ebx
		push 0 ;xmm0 (We doesn't have any 128bit varaible type)
		push ecx
		push edx
		call sub_4402C0
		add esp, [4h * 8]
		popad

		push ebp
		mov ebp, esp
		and esp, 0FFFFFFF8h
		jmp RETURN_Test_9
	}
}

DWORD HOOKPOS_Test_10 = 0x67F9E0;
DWORD RETURN_Test_10 = (HOOKPOS_Test_10 + 8);

void _cdecl sub_67F9E0(int ecx, int ebp)
{
	CLogger::Debugf("sub_67F9E0(0x%p,0x%p)",ecx,ebp);
}

void _declspec(naked) HOOK_Test_10()
{
	_asm
	{
		pushad
		push ebp
		push ecx
		call sub_67F9E0
		add esp, [2 * 4h]
		popad

		push esi
		push edi
		mov edi,ecx
		movzx eax, byte ptr [edi+8]
		jmp RETURN_Test_10
	}
}

DWORD HOOKPOS_Test_11 = 0x440980;
DWORD RETURN_Test_11 = (HOOKPOS_Test_11 + 5);
void _cdecl sub_440980(int eax, int ecx, int a3, int a4)
{
	CLogger::Debugf("sub_440980(0x%p,0x%p,%d,%d)",eax,ecx,a3,a4);
}

void _declspec(naked) HOOK_Test_11()
{
	_asm
	{
		pushad
		push [esp+14h]
		push [esp+10h]
		push ebx
		push eax
		call sub_440980
		add esp, [4 * 4h]
		popad

		push ebx
		mov ebx, [esp+4h]
		jmp RETURN_Test_11
	}
}

DWORD HOOKPOS_Test_12 = 0x6389D0;
DWORD RETURN_Test_12 = (HOOKPOS_Test_12+6);

void _cdecl sub_6389D0(void *p_this)
{
	CLogger::Debugf("sub_6389D0(0x%p)", p_this);
}

void HOOK_Test_12()
{
	_asm
	{
		pushad
		push ecx
		call sub_6389D0
		add esp, 4h
		popad

		sub     esp, 12Ch
		jmp		RETURN_Test_12
	}
}

DWORD HOOKPOS_Test_13 = 0x4105D0;
DWORD RETURN_Test_13 = (HOOKPOS_Test_13 + 5);
DWORD loc_415610 = 0x415610;

void _cdecl sub_4105D0(int a1)
{
	CLogger::Debugf("%s (%d)", __FUNCSIG__, a1);
}

void _declspec(naked) HOOK_Test_13()
{
	_asm
	{
		pushad
		push [esp+8h]
		call sub_4105D0
		add esp, 4h
		popad

		push ebx
		mov ebx, [esp+4h]
		jmp RETURN_Test_13
	}
}

DWORD HOOKPOS_Test_14 = 0x63A8F0;
DWORD RETURN_Test_14 = (HOOKPOS_Test_14 + 6);

void _cdecl sub_63A8F0(char a1)
{
	CLogger::Debugf("sub_63A8F0(0x%p)",a1);
}

void _declspec(naked) HOOK_Test_14()
{
	_asm
	{
		pushad
		push [esp+40h]
		call sub_63A8F0
		add esp, 4h
		popad

		push    ebp
		mov     ebp, esp
		and     esp, 0FFFFFFF8h
		jmp RETURN_Test_14
	}
}

DWORD HOOKPOS_Test_15 = 0x593FE0;
DWORD RETURN_Test_15 = (HOOKPOS_Test_15 + 6);

void _cdecl sub_593FE0(int a1, int a2, unsigned int a3)
{
	CLogger::Debugf("sub_593FE0(0x%p, 0x%p, %d)", a1, a2, a3);
}

void _declspec(naked) HOOK_Test_15()
{
	_asm
	{
		pushad
		push [esp+60h]
		push [esp+5Ch]
		push eax
		call sub_593FE0
		add esp, [ 3 * 4h ]
		popad

		push    ebp
		mov     ebp, esp
		and     esp, 0FFFFFFC0h
		jmp RETURN_Test_15
	}
}


DWORD HOOKPOS_Test_16 = 0x506000;
DWORD RETURN_Test_16 = (HOOKPOS_Test_16 + 6);

void _cdecl sub_506000(int a1, int a2)
{
	CLogger::Debugf("sub_506000(0x%p, 0x%p)", a1, a2);
}

void _declspec(naked) HOOK_Test_16()
{
	_asm
	{
		pushad
		push [esp+13Ch]
		push [esp+138h]
		call sub_506000
		add esp, [ 2 * 4h ]
		popad

		sub esp, 0FCh		
		jmp RETURN_Test_16
	}
}

DWORD HOOKPOS_WeatherChange = 0x00466830;
DWORD RETURN_WeatherChange = (HOOKPOS_WeatherChange + 5);
void _cdecl WeatherChange(int eax, int esi, char a3)
{
	CLogger::Debugf("WeatherChange(0x%p, 0x%p, %d/%c)", eax, esi, a3, a3);
}

void _declspec(naked) HOOK_WeatherChange()
{
	_asm
	{
		pushad
		push [esp+4h]
		push esi
		push eax
		call WeatherChange
		add esp, 0Ch
		popad

		cmp     [esp+4h], 0
		jmp RETURN_WeatherChange
	}
}

DWORD HOOKPOS_Test_17 = 0x4833F0;
DWORD RETURN_Test_17 = (HOOKPOS_Test_17 + 6);

void _cdecl sub_4833F0(int a1, int a2, int a3, int a4, int a5, char a6, int a7, int a8)
{
	CLogger::Debugf("sub_4833F0(%d,%d,%d,%d,%d,%d,%d,%d)",
		a1,a2,a3,a4,a5,a6,a7,a8 );
}

void _declspec(naked) HOOK_Test_17()
{
	_asm
	{
		pushad
		push [esp+0CCh]
		push [esp+0C8h]
		push [esp+0C4h]
		push [esp+0C0h]
		push [esp+0BCh]
		push [esp+0B8h]
		push [esp+0B4h]
		push [esp+0B0h]
		call sub_4833F0
		add esp, [ 4h * 8h ]
		popad

		sub esp, 8Ch
		jmp RETURN_Test_17
	}
}

DWORD HOOKPOS_LoadGameCall = 0x42CE43;
DWORD RETURN_LoadGameCall = 0x42CE4A;

void _cdecl MyLoadGame()
{
	g_pClient->loadGame();
}

BYTE bCheck = 0;
void _declspec(naked) HOOK_LoadGameCall()
{
	_asm
	{
		pushad
		call MyLoadGame

	}
	bCheck = *(BYTE*) 0xA10D2D;

	_asm
	{
		popad
		cmp bCheck, 0
		jmp RETURN_LoadGameCall
	}
}

DWORD HOOKPOS_SaveGame = 0x433160;

void _declspec(naked) HOOK_SaveGame()
{
	_asm
	{
		mov al, 1
		retn 
	}
}

bool CGameHooks::Initialize()
{
#ifdef NO_131_COMPILATION
	// 0x6A6EF0 - CreateLicencePlate (BASE + 748 - manager)
	// 0xA6B880 - console(?)
	// 0x593760 - LoadUIScript

#ifdef DEBUG
	
	// CreateTrailer(?)
	//Memory::JumpHook(HOOKPOS_Test_17, (DWORD)HOOK_Test_17);

	//Memory::JumpHook(HOOKPOS_WeatherChange, (DWORD)HOOK_WeatherChange);
	Memory::JumpHook(HOOKPOS_Test_16, (DWORD)HOOK_Test_16);
	//Memory::JumpHook(HOOKPOS_Test_15, (DWORD)HOOK_Test_15);
	//Memory::JumpHook(HOOKPOS_Test_14, (DWORD)HOOK_Test_14);
	//Memory::JumpHook(HOOKPOS_Test_13,(DWORD)HOOK_Test_13);
	//Memory::JumpHook(HOOKPOS_Test, (DWORD)HOOK_Test);
	//Memory::JumpHook(HOOKPOS_Test_2, (DWORD)HOOK_Test_2);
	//Memory::JumpHook(HOOKPOS_Test_3, (DWORD)HOOK_Test_3);
	//Memory::JumpHook(HOOKPOS_Test_4, (DWORD)HOOK_Test_4);
	//Memory::JumpHook(HOOKPOS_Test_5, (DWORD)HOOK_Test_5);
	//Memory::JumpHook(HOOKPOS_Test_6, (DWORD)HOOK_Test_6);
	//Memory::JumpHook(HOOKPOS_TrailerCreate, (DWORD)HOOK_TrailerCreate);
	//Memory::JumpHook(HOOKPOS_TrailerCreate_2, (DWORD)HOOK_TrailerCreate_2);//VALID
	//Memory::JumpHook(HOOKPOS_GameActorCreate, (DWORD)HOOK_GameActorCreate);//VALID
	//0x443100 (Maybe put actor in vehicle)
	//.rdata:0098A8F4 - traffic trailer vtable
	// Traffic Constructor
	//Memory::JumpHook(HOOKPOS_Test_7, (DWORD)HOOK_Test_7);
	// truck_config_hdl (Allocator) 004F76D0
	//Memory::JumpHook(HOOKPOS_Test_8, (DWORD)HOOK_Test_8);
	//Memory::JumpHook(HOOKPOS_Test_9, (DWORD)HOOK_Test_9);
	//Memory::JumpHook(HOOKPOS_Test_10,(DWORD)HOOK_Test_10);
	//Memory::JumpHook(HOOKPOS_Test_11,(DWORD)HOOK_Test_11);
	//Memory::JumpHook(HOOKPOS_Test_12,(DWORD)HOOK_Test_12);
#endif

#ifdef DEBUG_LOGGER
	// Logger hook
	Memory::JumpHook(HOOKPOS_Logger, (DWORD)HOOK_Logger);
#endif

	// 440980- we need to check it

	// Always start new Game
	// TODO: Fix this (Works good but after select city game get crashed)
	//Memory::JumpHook(0x42DFC8,0x42E1C9);
	// NOTE: We need to reverse more stuffs and control spawn by server 

	// Disable save game
	// NOTE: We can't do this because it's cause crash - i think we need to block this func in menu
	//Memory::JumpHook(HOOKPOS_SaveGame, (DWORD)HOOK_SaveGame);
	/*Memory::NopHook(0x412EE0+0x6A,5);
	Memory::NopHook(0x415F20+0x79,5);
	Memory::NopHook(0x42C560+0x43,5);
	Memory::NopHook(0x433120+0x12,5);
	Memory::NopHook(0x439660+0x4A,5);
	Memory::NopHook(0x444CC0+0xC8,5);
	Memory::NopHook(0x48DFA0+0x9E,5);
	Memory::NopHook(0x4C25B0+0x151,5);
	Memory::NopHook(0x4EC4B0+0xAD,5);*/

	// Disable profile selection
	// TODO

	// Load game hook
	Memory::JumpHook(HOOKPOS_LoadGameCall, (DWORD)HOOK_LoadGameCall);

	// Main loop hook
	Memory::JumpHook(HOOKPOS_MainLoop,(DWORD)HOOK_MainLoop);
	
	// Generate traffic hook
	Memory::JumpHook(HOOKPOS_CTrafficGenerator__Generate, (DWORD)HOOK_CTrafficGenerator__Generate);

	// Generate pedestrians hook
	Memory::JumpHook(HOOKPOS_CPedestriansGenerator__Generate, (DWORD)HOOK_CPedestriansGenerator__Generate);

	// Generate parked cars hook
	Memory::JumpHook(HOOKPOS_CParkedCarGenerator__Generate, (DWORD)HOOK_CParkedCarGenerator__Generate);

	// Vars hook
	Memory::JumpHook(HOOKPOS_CVars__Store, (DWORD)HOOK_CVars__Store);
#endif
	return true;
}