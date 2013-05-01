/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CWindowProcess.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

class CWindowProcess
{
private:
	static bool				m_bInstalled;
	static	WNDPROC			m_wWndProc;
	static LRESULT APIENTRY	WindowProcess_Hook( HWND, UINT, WPARAM, LPARAM );
public:
	static void Install(HWND hWnd);
};