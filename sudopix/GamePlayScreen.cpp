#include "StdAfx.h"
#include "GamePlayScreen.h"
#include "game.h"
#include "gamescreenmgr.h"
#include "StartScreen.h"
#include "sudopix.h"
#include "loadingscreen.h"

namespace SudoPix
{

	CGamePlayScreen::CGamePlayScreen(const CSudopix::EStartMode mode /*= CSudopix::Random*/)
	{
		transitionOnTime = 2;
		transitionOffTime = 2;
		sudopix = new CSudopix;
		sudopix->generate(mode);
	}

    CGamePlayScreen::~CGamePlayScreen(void)
    {
    }

	void CGamePlayScreen::handleInput()
	{
		if (CGame::pHGE()->Input_GetKeyState(HGEK_ESCAPE))
		{
			ScreenList screens;
			screens.push_back(new CStartScreen);
			CLoadingScreen::Load(false, screens);
		}
		if (transitionPosition <= 0)
			sudopix->handleInput();
	}

    bool CGamePlayScreen::update( float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen )
    {
		if (transitionPosition <= 0)
	        sudopix->update(dt);
        return IGameScreen::update(dt, _otherScreenHasFocus, coveredByOtherScreen);
    }

	void CGamePlayScreen::render()
	{
		int fade = getTransitionAlpha();
		bg->SetColor(ARGB(fade, fade, fade, fade));
		bg->Render(0.f, 0.f);

		Point viewport = CGame::ViewPort();
		sudopix->render((viewport.x - 480) / 2.f + 180, (viewport.y - 480) / 2.f + 180, fade);
	}

    void CGamePlayScreen::loadContent()
    {
        hgeResourceManager* resMgr = CGame::pResMgr();
        bg = resMgr->GetSprite("GameBG");

        Point viewport = CGame::ViewPort();
        bg->SetTextureRect(0, 0, viewport.x, viewport.y);
    }
}