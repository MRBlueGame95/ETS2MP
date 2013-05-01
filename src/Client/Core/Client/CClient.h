/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CClient.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

class CClient
{
private:
	static CClient * m_sInstance;

	bool m_bControls;
public:
	CClient();
	~CClient();
	 
	void pulse();

	void loadGame();

	inline void setControls(bool bControls) { m_bControls = bControls; }
	inline bool getControls() { return m_bControls; }

	static CClient& GetInstance() { return *m_sInstance; }

};