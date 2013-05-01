/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : StdInc.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

#include <RakPeerInterface.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <StringCompressor.h>

#include <Windows.h>
#include <WindowsX.h>

#include <time.h>

#include <Version.h>
#include <Logger\CLogger.h>
#include <Common.h>
#include <Libraries\CLibrary.h>
#include <Utils\SharedUtils.h>
#include <Memory\Memory.h>
#include <detours.h>
#include <Network/CPacketManager.h>

#include <Main.h>

// Network
#include <Network/CNetwork.h>

// Game
#include <Game/ETS2/CConsole.h>
#include <Game/ETS2/CameraETS2.h>
#include <Game/ETS2/TruckETS2.h>
#include <Game/ETS2/EconomyETS2.h>
#include <Game/ETS2/GameETS2.h>

#include <Game/Archive/CSCSArchive.h>

#include <Game/CGameVars.h>
#include <Game/CGamePatches.h>
#include <Game/CGameHooks.h>
#include <Game/CGameOffsets.h>

// Hooks
// DirectInput
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <XInput.h>

#include <Hooks/DirectInput/IDirectInput8Proxy.h>
#include <Hooks/DirectInput/IDirectInputDevice8Proxy.h>
#include <Hooks/DirectInput/CDirectInput8Hook.h>

#include <Hooks/WindowProcess/CWindowProcess.h>

// Graphics
#include <d3d9.h>
#include <d3dx9.h>
#include <Graphics/Hook/CDirect3D9Hook.h>
#include <Graphics/Hook/Proxy/IDirect3D9Proxy.h>
#include <Graphics/Hook/Proxy/IDirect3DDevice9Proxy.h>
#include <Graphics/Hook/Proxy/IDirect3D9ProxyEx.h>
#include <Graphics/Hook/Proxy/IDirect3DDevice9ProxyEx.h>

#include <Graphics/CChat.h>
#include <Graphics/CGraphics.h>

// Client
#include <Client/CClient.h>