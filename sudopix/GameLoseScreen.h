#pragma once
#include "IGameScreen.h"

namespace SudoPix
{
	class GameLoseScreen : public IGameScreen
	{
	public:
		GameLoseScreen(void);
		~GameLoseScreen(void);

		virtual void handleInput();
		virtual bool update(float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen);
		virtual void render();
		virtual void loadContent();
		virtual const char *Name() { return "GameLose Screen"; }

	private:
		hgeFont *fnt;
		hgeFont* titleFnt;
		hgeSprite* bg;
		hgeGUI* gui;
		HEFFECT snd;
		int lastid;
	};

}