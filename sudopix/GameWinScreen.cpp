#include "StdAfx.h"
#include "GameWinScreen.h"
#include "Game.h"
#include "menuitem.h"
#include "resource.h"
#include "loadingscreen.h"
#include "StartScreen.h"
#include "GamePlayScreen.h"
#include "Sudopix.h"

namespace SudoPix
{
	GameWinScreen::GameWinScreen(void)
	{
		transitionOnTime = 1;
		transitionOffTime = 2;
	}


	GameWinScreen::~GameWinScreen(void)
	{
	}

	void GameWinScreen::handleInput()
	{

	}

	bool GameWinScreen::update( float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen )
	{
		int id = gui->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case WIN_CONTINUE:
				CLoadingScreen::Load(true, new CGamePlayScreen(CSudopix::Continue));
				lastid = -1;
				break;
			case WIN_BACKTOMENU:
				CLoadingScreen::Load(true, new CStartScreen);
				lastid = -1;
				break;
			}
		}
		else if(id) 
		{ 
			lastid = id;
			gui->Leave(); 
		}
		return IGameScreen::update(dt, _otherScreenHasFocus, coveredByOtherScreen);
	}

	void GameWinScreen::render()
	{
		int fade = getTransitionAlpha();
		bg->SetColor(ARGB(fade, fade, fade, fade));
		bg->Render(0.f, 0.f);
		gui->Render();

		Point viewport = CGame::ViewPort();
		titleFnt->SetColor(SETA(titleFnt->GetColor(), fade));
		titleFnt->Render(viewport.x / 2.f, 100 - 150 * (255 - fade) / 255.f, HGETEXT_CENTER, "You Win");
	}

	void GameWinScreen::loadContent()
	{
		hgeResourceManager* resMgr = CGame::pResMgr();
		bg = resMgr->GetSprite("GameBG");
		fnt = resMgr->GetFont("Button");
		titleFnt = resMgr->GetFont("Title");
		snd = resMgr->GetEffect("MenuSound");

		Point viewport = CGame::ViewPort();

		gui = new hgeGUI();
		float string_width = fnt->GetStringWidth("Continue", false);
		gui->AddCtrl(new hgeGUIMenuItem(WIN_CONTINUE, fnt, snd, 10 + string_width / 2.f, viewport.y - 50, 0.0f, "Continue"));
		string_width = fnt->GetStringWidth("Back to Menu", false);
		gui->AddCtrl(new hgeGUIMenuItem(WIN_BACKTOMENU, fnt, snd, viewport.x - 10 - string_width / 2.f, viewport.y - 50, 0.0f, "Back to Menu"));

		bg->SetTextureRect(0, 0, viewport.x, viewport.y);
	}

}