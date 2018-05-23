#include "StdAfx.h"
#include "GameLoseScreen.h"
#include "Game.h"
#include "menuitem.h"
#include "resource.h"
#include "loadingscreen.h"
#include "GamePlayScreen.h"
#include "StartScreen.h"
#include "Sudopix.h"

namespace SudoPix
{
	GameLoseScreen::GameLoseScreen(void)
	{
		transitionOnTime = 1;
		transitionOffTime = 2;
	}


	GameLoseScreen::~GameLoseScreen(void)
	{
	}

	void GameLoseScreen::handleInput()
	{

	}

	bool GameLoseScreen::update( float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen )
	{
		int id = gui->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case LOSE_RETRY:
				CLoadingScreen::Load(true, new CGamePlayScreen(CSudopix::Retry));
				lastid = -1;
				break;
			case LOSE_BACKTOMENU:
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

	void GameLoseScreen::render()
	{
		int fade = getTransitionAlpha();
		bg->SetColor(ARGB(fade, fade, fade, fade));
		bg->Render(0.f, 0.f);
		gui->Render();

		Point viewport = CGame::ViewPort();
		titleFnt->SetColor(SETA(titleFnt->GetColor(), fade));
		titleFnt->Render(viewport.x / 2.f, 100 - 150 * (255 - fade) / 255.f, HGETEXT_CENTER, "You Lose");
	}

	void GameLoseScreen::loadContent()
	{
		hgeResourceManager* resMgr = CGame::pResMgr();
		bg = resMgr->GetSprite("GameBG");
		fnt = resMgr->GetFont("Button");
		titleFnt = resMgr->GetFont("Title");
		snd = resMgr->GetEffect("MenuSound");

		Point viewport = CGame::ViewPort();

		gui = new hgeGUI();
		float string_width = fnt->GetStringWidth("Retry", false);
		gui->AddCtrl(new hgeGUIMenuItem(LOSE_RETRY, fnt, snd, 10 + string_width / 2.f, viewport.y - 50, 0.0f, "Retry"));
		string_width = fnt->GetStringWidth("Back to Menu", false);
		gui->AddCtrl(new hgeGUIMenuItem(LOSE_BACKTOMENU, fnt, snd, viewport.x - 10 - string_width / 2.f, viewport.y - 50, 0.0f, "Back to Menu"));

		bg->SetTextureRect(0, 0, viewport.x, viewport.y);
	}

}