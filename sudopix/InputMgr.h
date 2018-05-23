#pragma once
#include "commonType.h"

namespace SudoPix
{
	class CInputMgr
	{
	private:
		CInputMgr(void);
		CInputMgr(const CInputMgr&);
		CInputMgr& operator=(const CInputMgr&);

	public:
		static CInputMgr& instance();
		~CInputMgr(void);

		void update();
		bool isKeyPressed(short key);
		bool isKeyTriggered(short key);

		bool isMouseButtonLeftDown(Point& p);
		bool isMouseButtonRightDown(Point& p);
		bool isMouseButtonMove(Point& p);
		bool isMouseButtonDrag(Point& p);

	private:
		hgeInputEvent prevState;
		hgeInputEvent curState;
	};

#define InputMgr CInputMgr::instance()
}
