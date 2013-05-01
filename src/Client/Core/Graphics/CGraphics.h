/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CGraphics.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>,
 *
 ***************************************************************/
#pragma once

class CGraphics
{
private:
	static IDirect3DDevice9 * m_sDevice;
	static CChat			* m_sChat;
public:
	static void Initialize(IDirect3DDevice9 * pDevice);

	static void Render();

	static void OnLost();

	static void OnReset();

	static bool	InputHandler(unsigned int uMsg, DWORD dwChar);

};