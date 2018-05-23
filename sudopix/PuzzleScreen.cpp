#include "StdAfx.h"
#include "PuzzleScreen.h"
#include "game.h"

namespace SudoPix
{
    CPuzzleScreen::CPuzzleScreen(void)
    {
        transitionOnTime = 1;
        transitionOffTime = 1;
    }

    CPuzzleScreen::~CPuzzleScreen(void)
    {
    }

    void CPuzzleScreen::handleInput()
    {
        
    }

    bool CPuzzleScreen::update( float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen )
    {
        return IGameScreen::update(dt, _otherScreenHasFocus, coveredByOtherScreen);
    }

    void CPuzzleScreen::render()
    {
        int fade = getTransitionAlpha();
        bg->SetColor(ARGB(fade, fade, fade, fade));
        bg->Render(0, 0);
        fnt->Render(10, 10, HGETEXT_LEFT, "Select Your Puzzle!");
    }

    void CPuzzleScreen::loadContent()
    {
        hgeResourceManager* resMgr = CGame::pResMgr();
        bg = resMgr->GetSprite("GameBG");
        fnt = resMgr->GetFont("Text");

        Point viewport = CGame::ViewPort();
        bg->SetTextureRect(0, 0, viewport.x, viewport.y);
    }
}