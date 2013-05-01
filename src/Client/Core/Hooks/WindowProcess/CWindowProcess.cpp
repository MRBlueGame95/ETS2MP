/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CWindowProcess.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

bool CWindowProcess::m_bInstalled = false;
WNDPROC CWindowProcess::m_wWndProc = NULL;

void CWindowProcess::Install(HWND hWnd)
{
	if(!m_bInstalled)
	{
		m_wWndProc = SubclassWindow(hWnd, WindowProcess_Hook);

		m_bInstalled = true;

		SetWindowText(hWnd, PROJECT_STRING);
	}
}

LRESULT APIENTRY CWindowProcess::WindowProcess_Hook( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( GetForegroundWindow() == hWnd )
	{
		if( CGraphics::InputHandler( uMsg, (DWORD)wParam ) )
			return 0;
	}

	return CallWindowProc( m_wWndProc, hWnd, uMsg, wParam, lParam );
}