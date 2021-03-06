#pragma once

#include "commonType.h"
#include "hge.h"
#include "IGameScreen.h"

class hgeFont;
class hgeSprite;
class hgeGUI;

namespace SudoPix
{
    // 开始游戏画面
    class CStartScreen : public IGameScreen
    {
	public:
		CStartScreen(void);
		virtual ~CStartScreen(void);

		virtual void handleInput();
		virtual bool update(float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen);
		virtual void render();
		virtual void loadContent();
		virtual const char *Name() { return "Start Screen"; }

	private:
		hgeFont *fnt;
		hgeFont* titleFnt;
		hgeSprite* bg;
		hgeGUI* gui;
		HEFFECT snd;
		int lastid;
    };
}
