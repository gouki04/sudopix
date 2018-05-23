#include "StdAfx.h"
#include "InputMgr.h"
#include "Game.h"

namespace SudoPix
{
	CInputMgr::CInputMgr(void)
	{
	}

	CInputMgr::~CInputMgr(void)
	{
	}

	CInputMgr& CInputMgr::instance()
	{
		static CInputMgr instance;
		return instance;
	}

	void CInputMgr::update()
	{
		prevState = curState;
		CGame::pHGE()->Input_GetEvent(&curState);
	}

	bool CInputMgr::isKeyPressed( short key )
	{
		return curState.type == INPUT_KEYDOWN && curState.key == key;
	}

	bool CInputMgr::isKeyTriggered( short key )
	{
		return curState.type == INPUT_KEYDOWN && curState.key == key &&
			prevState.type != INPUT_KEYDOWN;
	}

	bool CInputMgr::isMouseButtonLeftDown( Point& p )
	{
		if (curState.type == INPUT_MBUTTONDOWN && curState.key == HGEK_LBUTTON &&
			prevState.type != INPUT_MBUTTONDOWN)
		{
			p.x = curState.x;
			p.y = curState.y;
			return true;
		}
		return false;
	}

	bool CInputMgr::isMouseButtonRightDown( Point& p )
	{
		if (curState.type == INPUT_MBUTTONDOWN && curState.key == HGEK_RBUTTON &&
			prevState.type != INPUT_MBUTTONDOWN)
		{
			p.x = curState.x;
			p.y = curState.y;
			return true;
		}
		return false;
	}

	bool CInputMgr::isMouseButtonMove( Point& p )
	{
		if (curState.type == INPUT_MOUSEMOVE)
		{
			p.x = curState.x;
			p.y = curState.y;
			return true;
		}
		return false;
	}

	bool CInputMgr::isMouseButtonDrag( Point& p )
	{
		if (curState.type == INPUT_MOUSEMOVE)
		{
			p.x = curState.x;
			p.y = curState.y;
			return true;
		}
		return false;
	}

}