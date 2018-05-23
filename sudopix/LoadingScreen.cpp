#include "StdAfx.h"
#include "LoadingScreen.h"
#include "GameScreenMgr.h"
#include "game.h"

namespace SudoPix
{
    CLoadingScreen::CLoadingScreen( bool _loadingIsSlow, ScreenList _screensToLoad )
    {
        loadingIsSlow = _loadingIsSlow;
        screensToLoad = _screensToLoad;
        otherScreensAreGone = false;
        transitionOnTime = 1;
        transitionOffTime = 1;
    }

    CLoadingScreen::~CLoadingScreen(void)
    {

    }

    bool CLoadingScreen::update( float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen )
    {
        if(IGameScreen::update(dt, _otherScreenHasFocus, coveredByOtherScreen))
            return true;

        if (otherScreensAreGone)
        {
            ScreenList::iterator iter = screensToLoad.begin();
            for (; iter != screensToLoad.end(); ++iter)
                GSMgr.addScreen((*iter));
            GSMgr.removeScreen(this);
            //CGame::resetTimerDelta();
            return true;
        }

        return false;
    }

    void CLoadingScreen::render()
    {
        if (screenState == Active && GSMgr.getScreens().size() == 1)
            otherScreensAreGone = true;

        if (loadingIsSlow)
        {
            Point viewPort = CGame::ViewPort();
            const char *text = "loading...";
            float x = viewPort.x - fnt->GetStringWidth(text) - 30;
            float y = viewPort.y - fnt->GetHeight() - 15;

            fnt->SetColor(ARGB(getTransitionAlpha(), 255, 255, 255));
            fnt->Render(x, y, HGETEXT_LEFT, text);
        }
    }

    void CLoadingScreen::Load( bool _loadingIsSlow, ScreenList _screensToLoad )
    {
        ScreenList screensToRemove = GSMgr.getScreens();
        IGameScreen *screen;
        while (screensToRemove.size() > 0)
        {
            screen = screensToRemove.back();
            screensToRemove.pop_back();
            screen->ExitScreen();
        }

        GSMgr.addScreen(new CLoadingScreen(_loadingIsSlow, _screensToLoad));
    }

    void CLoadingScreen::Load( bool _loadingIsSlow, IGameScreen* _screenToLoad )
    {
        ScreenList screensToRemove = GSMgr.getScreens();
        IGameScreen *screen;
        while (screensToRemove.size() > 0)
        {
            screen = screensToRemove.back();
            screensToRemove.pop_back();
            screen->ExitScreen();
        }

        ScreenList screensToLoad;
        screensToLoad.push_back(_screenToLoad);
        GSMgr.addScreen(new CLoadingScreen(_loadingIsSlow, screensToLoad));
    }

    void CLoadingScreen::loadContent()
    {
        fnt = CGame::pResMgr()->GetFont("Text");
    }
}