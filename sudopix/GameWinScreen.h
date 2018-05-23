#pragma once
#include "IGameScreen.h"

namespace SudoPix
{
	class GameWinScreen : public IGameScreen
	{
	public:
		GameWinScreen(void);
		~GameWinScreen(void);

		virtual void handleInput();
		virtual bool update(float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen);
		virtual void render();
		virtual void loadContent();
		virtual const char *Name() { return "GameWin Screen"; }

	private:
		hgeFont *fnt;
		hgeFont* titleFnt;
		hgeSprite* bg;
		hgeGUI* gui;
		HEFFECT snd;
		int lastid;
	};
}
