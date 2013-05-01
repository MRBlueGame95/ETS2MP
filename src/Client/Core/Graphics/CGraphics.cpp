/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CGraphics.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>,
 *
 ***************************************************************/
#include <Includes.h>

IDirect3DDevice9 * CGraphics::m_sDevice = 0;
CChat * CGraphics::m_sChat = 0;

sUnknown * model = NULL;
ID3DXFont * pTestFont = NULL;
extern DWORD VAR_GamePtr;

void CGraphics::Initialize(IDirect3DDevice9 * pDevice)
{
	m_sDevice = pDevice;

	if(m_sDevice)
	{
		D3DXCreateFont(m_sDevice, 15, 0, NULL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pTestFont);

		m_sChat = new CChat(m_sDevice);
	}
}

void _declspec(naked) *sub_486550()
{
	_asm
	{
		mov eax, 0x486550
		jmp eax
	}
}

void _declspec(naked) *sub_67F8F0()
{
	_asm
	{
		mov eax, 0x67F8F0
		jmp eax
	}
}

void _declspec(naked) *sub_4844A0()
{
	_asm
	{
		mov eax, 0x4844A0
		jmp eax
	}
}

// Create Player Driver(?)
void _declspec(naked) * sub_475B10()
{
	_asm
	{
		mov eax, 0x475B10
		jmp eax
	}
}

class Test // 0xA57E9C
{
public:
	int sub_61CA40(int,int,int);
};

int _declspec(naked) Test::sub_61CA40(int,int,int)
{
	_asm {
		mov eax, 0x61CA40
		call eax
	}
}

class CSomething
{
public: 
	int sub_61CA40(int*,const char**,signed int);
};

int _declspec(naked) CSomething::sub_61CA40(int*,const char**,signed int)
{
	_asm
	{
		mov eax, 0x61CA40
		jmp eax
	}
}

int gWeather = 0;
bool bDebug = false;
void CGraphics::Render()
{
	if(!m_sDevice)
		return;	

	if(GetAsyncKeyState(VK_F1))
	{
		bDebug = !bDebug;
	}

	if(GetAsyncKeyState(VK_F2))
	{
		CConsole::Write("TEST");
	}

	if(GetAsyncKeyState(VK_F12))
	{
		// 0x9ECAF0 (Camera VTable)
		// 0x9A2528 - Trailer VTable
		// 0x97D240 - Physical Trailer VTable
		// 0x97D70C - Vehicle Shared VTable
		// 0xA56BD0 - Local truck?
		// 45E360  5F1060
		// 0x445FB0 - Create
		void * pTrailer = sub_486550();

		DWORD dwTrailer = (DWORD)pTrailer;
		DWORD dwPlaceable = *(DWORD*)(dwTrailer+236);
		float _x = *(float*)(dwPlaceable+40);
		float _y = *(float*)(dwPlaceable+44); 
		float _z = *(float*)(dwPlaceable+48); 

		CLogger::Debugf("Creating trailer (0x%p (%f,%f,%f))", pTrailer, _x,_y,_z);
	}

	if(GetAsyncKeyState(VK_F11))
	{
		void * pCoreVehicle = sub_67F8F0();
		CLogger::Debugf("CoreVehicle -> 0x%p (%f,%f,%f)", pCoreVehicle, 
			*(float*)((DWORD)pCoreVehicle + 40),
			*(float*)((DWORD)pCoreVehicle + 44),
			*(float*)((DWORD)pCoreVehicle + 48));
	}
	
	if(GetAsyncKeyState(VK_NUMPAD1))
	{
		// 0x4845A0
		// 0x98C7E8 - Game Vehicle VTable
		// 0xA40968 (Vehicles array?)
		void *pGameVehicle = sub_4844A0();
		CLogger::Debugf("GameVehicle -> 0x%p", pGameVehicle);
	}
	
	if(GetAsyncKeyState(VK_NUMPAD2))
	{
		void *pDriver = sub_475B10();
		CLogger::Debugf("Driver -> 0x%p", pDriver);
	}

	if(GetAsyncKeyState(VK_NUMPAD4))
	{
		// It should be second economy pointer
		DWORD dwUnknownBase = *(DWORD*)0xA6B83C;
		if(dwUnknownBase)
		{
			CLogger::Debugf("Unknown base value:\t0x%p", dwUnknownBase);

			// Unknown pointer (base + 112)
			DWORD v27 = *(DWORD*) ( dwUnknownBase + 112 );
			if(v27)
			{
				int v10 = 0;
				int v31 = 0;
				do
				{
					// Should be money
					// float v30 = 0.0;
					//v30 = *(float *)(*(_DWORD *)(v5 + 384) + 4 * v10) + v30;
					float v30 = 0.0f;
					
					v30 = *(float*)(*(DWORD*)(v27 + 384) + 4 * v10) + v30;
					v31 = v10 + 1;

					//v11 = floor(v30 * 100.0 + 0.5);
					float v11 = floor(v30 * 100.0f + 0.5f);
	
					// 
					CLogger::Debugf("v11 = %f", v11); // (Money?)

					v10 = v31;
				} while ( (unsigned int)v31 < *(DWORD *)(v27 + 388) );
			}
		}
	}

	if(GetAsyncKeyState(VK_NUMPAD5))
	{
		DWORD mem_operatorNew = 0x80ABFF;

		CLogger::Debugf("Pre-Allocator ..");
		sUnknown * pVehicle =  NULL;
		_asm
		{
			push 380h
			call mem_operatorNew
			add esp, 4h
			mov pVehicle, eax
		}
		CLogger::Debugf("Truck memory allocated 0x%p", pVehicle);

		if(pVehicle)
		{
			DWORD FUNC_Unknown_1 = 0x456270;
			_asm
			{
				mov eax, pVehicle
				call FUNC_Unknown_1
				mov esi, eax
			}
			CLogger::Debugf("Vehicle 0x%p");

			DWORD dwTest = *(DWORD*)0xA6B838;

			sUnknown * pDynamicActor = NULL;
			DWORD FUNC_CreateDynamicActor = 0x5E41B0;
			DWORD UnknownOffset = *(DWORD*)(dwTest + 772);
			_asm
			{
				mov edi, UnknownOffset
				call FUNC_CreateDynamicActor
				mov pDynamicActor, eax
			}

			CLogger::Debugf("Dynamic actor for parked veh > 0x%p", pDynamicActor);

			/* Call something from vtable
			DWORD dwFunc =  *(DWORD*)(pVehicle+628);
			_asm
			{
				push 1
				call dwFunc
			//	add esp, 4h
			}*/

			// Set vehicle physics actor
			*(sUnknown**)(pVehicle + 628) = pDynamicActor;
		}
		
	}

	if(GetAsyncKeyState(VK_NUMPAD6))
	{
		CSomething *pSomething = *(CSomething**)0xA57E9C;
		if(pSomething)
		{
			int * unk = NULL;
			const char * szUnk = "/def/vehicle/truck";
			pSomething->sub_61CA40(unk,&szUnk,1);

			CLogger::Debugf("Truck 0x%p", unk);
		}
	}
	
	if(GetAsyncKeyState(VK_NUMPAD7))
	{
		// Its game not profile
		GameETS2 *pProfile = *(GameETS2**)CGameOffsets::VAR_GamePtr;
		DWORD dwUnknown = *(DWORD*)(pProfile + 2032); //It's can be WorldManager (I'm not sure!)
		if(!dwUnknown)
			CLogger::Debugf("dwUnknown is null");
		else
		{
			CLogger::Debugf("PreChangeWeather 0x%p", dwUnknown);
			DWORD FUNC_ChangeWeather = 0x00466830;
			int Myretn = 0;
			char a3 = (char)true;// instant or interpolated
			_asm
			{
				push a3
				mov esi, dwUnknown
				mov eax, gWeather
				call FUNC_ChangeWeather
				mov Myretn, eax
			}
			CLogger::Debugf("ChangeWeather (retn = %d)", Myretn);
			
			gWeather++;
			if(gWeather > 1)
				gWeather = 0;
		}
	}
		
	if(GetAsyncKeyState(VK_NUMPAD8))
	{
		int v10, v11, v47;
		DWORD dwTrailer = 0;

		// Create unit for game_trailer_actor
		_asm
		{
			mov edx, v10
			mov ecx, v11
			mov esi, v47
			mov eax, 0x446050
			call eax
			mov eax, dwTrailer
		}

		if( dwTrailer )
		{
			*(BYTE *)(dwTrailer + 8) |= 0x40u;
			++*(DWORD*)(dwTrailer + 4);
		}

		// I think it's register v47 into pool but i'm not sure
		_asm
		{
			push v47
			mov eax, 0x4105D0
			call eax
			add esp, 4h
		}
		
		// Create plate for trailer
		GameETS2 *pProfile = *(GameETS2**)CGameOffsets::VAR_GamePtr;
		DWORD dwPlateManager = *(DWORD*)(pProfile + 748);
		DWORD dwPlate = 0;

		char * szNumberPlate  = "TEST";
		_asm
		{
			push 0
			push 1
			push szNumberPlate
			push dwPlateManager
			mov eax, 0x6A6EF0
			call eax
			add esp, 10h
			mov dwPlate, eax
		}

		// Attach plate to trailer
		DWORD dwTrailerVTable = *(DWORD*)(dwTrailer + 0);
		_asm
		{
			push dwPlate
			push 14 ; unk
			push 0 ; unk(Its probably model)
			mov ecx, dwTrailer
			mov eax, [dwTrailerVTable + 48]
			call eax
			add esp, 0Ch
		}

		// Maybe setup(?)
		_asm
		{
			mov ecx, dwTrailer
			mov eax, [dwTrailerVTable + 260]
			call eax
		}		
	}
	
	if(m_sChat)
		m_sChat->onRender();


	if(pTestFont)
	{
		char szLocalProfileData[256] = { 0 };
		sprintf( szLocalProfileData, "No profile data presented");
		GameETS2 *pProfile = *(GameETS2**)CGameOffsets::VAR_GamePtr;
		DWORD dwUnk = 0;
		DWORD dwSomething = 0;
		if(pProfile)
		{
			EconomyETS2 * pEconomy = pProfile->economy;
			if(pEconomy)
			{
				float x=0,y=0,z=0,u=0,u2=0,u3=0,u4=0;				
				DWORD dwTrailer = 0;

				if(pEconomy->truck)
				{
					DWORD truck = (DWORD)pEconomy->truck;
					CLogger::Debugf("Truck 0x%p",pEconomy->truck);
					if(truck)
					{
						x = *(float*)(truck + 140);
						CLogger::Debugf("%f",x);
						y = *(float*)(truck + 144);
						CLogger::Debugf("%f",y);
						z = *(float*)(truck + 148);
						CLogger::Debugf("%f",z);
						u = *(float*)(truck + 152);
						CLogger::Debugf("%f",u);
						u2 = *(float*)(truck + 156);
						CLogger::Debugf("%f",u2);
						u3 = *(float*)(truck + 160);
						CLogger::Debugf("%f",u3);
						u4 = *(float*)(truck + 164);
						CLogger::Debugf("%f",u4);
						dwTrailer = *(DWORD*)(truck + 64);
						CLogger::Debugf("0x%p",dwTrailer);
					}
				}

				sprintf( szLocalProfileData, "X %f, Y %f, Z %f, Trailer 0x%p (%f,%f,%f,%f)", x, y,z, dwTrailer, u, u2, u3, u4 );
			} else {
				sprintf( szLocalProfileData, "No economy data presented");
			}
		}

		//7D0F70- create phiscics engine?
		char szDebug[1024] = { 0 }; 
		sprintf(szDebug, "DEBUG VIEW\n \
			(BYTE) 0xA42D88 = %d // km/h(0) or mph(1)\n \
			(FLOAT) 0xA0D864 = %f // Velocity MP\n \
			(DWORD) 0xA6B848 = 0x%p // Core Traffic Pointer\n \
			(DWORD) 0xA57E9C = 0x%p // Idk what but needs to be tested\n\n \
			_______________________________________________________________\n\
			%s", 
			 *(BYTE*)0xA42D88,
			 *(float*)0xA0D864,
			 *(DWORD*)0xA6B848,
			 *(DWORD*)0xA57E9C,
			szLocalProfileData);

#ifdef DEBUG
   	    RECT rct = { 0 };
		SetRect(&rct, 11, 201, 0, 0);
		pTestFont->DrawText(NULL,szDebug,-1,&rct,DT_NOCLIP,D3DCOLOR_ARGB(180,0,0,0));
		SetRect(&rct, 10, 200, 0, 0);
		pTestFont->DrawText(NULL,szDebug,-1,&rct,DT_NOCLIP,D3DCOLOR_ARGB(180,255,255,255));
#endif
	}
}

void CGraphics::OnLost()
{
	if(!m_sDevice)
		return;

	if(m_sChat)
		m_sChat->onLost();

	if(pTestFont)
		pTestFont->OnLostDevice();
}

void CGraphics::OnReset()
{
	if(!m_sDevice)
		return;

	if(m_sChat)
		m_sChat->onReset();

	if(pTestFont)
		pTestFont->OnResetDevice();
}

bool CGraphics::InputHandler(unsigned int uMsg, DWORD dwChar)
{
	if(m_sChat->inputHandler(uMsg, dwChar))
		return true;

	return false;
}