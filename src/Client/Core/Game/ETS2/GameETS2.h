//=======================================================
//	
//	ETS2MP Client Core - GameETS2.h
//  Authors : RootKiller
//
//=======================================================
#pragma once

class VecPrism3d
{
public:
	float x; // 00-04
	float y; // 04-08
	float z; // 08-0C
};

struct GameETS2_VTable // sizeof(GameETS2VTable) = 0x234
{
	DWORD scalar_destructor;	// 000-004 (Destructor)
	MEMPAD(pad_0,0x230);		// 004-234		
};

class PhysicsEngineETS2
{
public:
	// TODO
	DWORD dwPhysicsVTable; // 00-04
};

class NavigationDataETS2
{
public:
	// TODO
};

class GameETS2
{
public:
	GameETS2_VTable * vtable;		// 000-004	
	MEMPAD(pad1, 0x2FC);			// 004-300
	PhysicsEngineETS2 * physics;	// 300-304
	MEMPAD(pad2, 0x55C);			// 304-860
	NavigationDataETS2 * navidata;	// 860-864
	MEMPAD(pad3, 0x18);				// 864-87C
	EconomyETS2 * economy;			// 87C-880
};