#include "stdafx.h"
#include "Game.h"
#include "GameScreenMgr.h"

namespace SudoPix
{

    CGameScreenMgr::CGameScreenMgr()
        : blank(0), cursor(0), curRemovedScreen(0), isExiting(false)
    {

    }

    CGameScreenMgr::~CGameScreenMgr()
    {

    }

    CGameScreenMgr& CGameScreenMgr::Instance()
    {
        static CGameScreenMgr gameScreenMgr;
        return gameScreenMgr;
    }

    bool CGameScreenMgr::update( float dt )
    {
        CGame::pHGE()->Input_GetMousePos(&cursorPos.x, &cursorPos.y);

        bool otherScreenHasFocus = !CGame::IsActive();
        bool coverdByOtherScreen = false;

        // 在进行界面的update时，不能直接对gameScreens进行遍历操作，由于在update过程中
        // 可能出现screen已经transitionoff，并调用removeScreen来去掉自己的情况。
        // 而在removeScreen中会将该screen delete掉。从而造成外部迭代器指向出问题。
        ScreenList screenToUpdate = gameScreens;
        IGameScreen *screen;

        // 从后往前遍历所有screen
        while (screenToUpdate.size() > 0)
        {
            screen = screenToUpdate.back();
            screenToUpdate.pop_back();

            // 如果screen的update过程中已经要求remove自己了，则直接跳过本screen
            if(screen->update(dt, otherScreenHasFocus, coverdByOtherScreen))
                continue;

            if (screen->ScreenState() == TransitionOn || screen->ScreenState() == Active)
            {
                // 如果这是第一个active的screen，则给它一次处理输入的机会
                if (!otherScreenHasFocus)
                {
                    screen->handleInput();
                    otherScreenHasFocus = true;
                }

                if(!screen->IsPopup())
                    coverdByOtherScreen = true;
            }
        }

        return isExiting;
    }

    void CGameScreenMgr::render()
    {
        IGameScreen *screen;
        ScreenList::iterator iter = gameScreens.begin();
        for (; iter != gameScreens.end(); ++iter)
        {
            screen = (*iter);
            if(screen->ScreenState() == Hidden)
                continue;
            screen->render();
        }
        cursor->Render(cursorPos.x, cursorPos.y);
    }

    void CGameScreenMgr::addScreen( IGameScreen *gameScreen )
    {
        CGame::pHGE()->System_Log("[%d->%d]Adding Screen ----- %s", gameScreens.size(), gameScreens.size() + 1, gameScreen->Name());
        gameScreen->SetExiting(false);
        gameScreen->loadContent();
        gameScreens.push_back(gameScreen);
    }

    void CGameScreenMgr::removeScreen()
    {
        if(!gameScreens.empty())  
        {
            gameScreens.back()->unloadContent();
            gameScreens.pop_back();
        }
    }

    void CGameScreenMgr::removeScreen( IGameScreen *gameScreen )
    {
		CGame::pHGE()->System_Log("[%d->%d]Removing Screen --- %s", gameScreens.size(), gameScreens.size() - 1, gameScreen->Name());
		gameScreen->unloadContent();
		gameScreens.remove(gameScreen);
		curRemovedScreen = gameScreen;
		delete gameScreen;
	}

	void CGameScreenMgr::fadeBackToBlack( int alpha )
	{
		Point viewPort = CGame::ViewPort();
		blank->SetColor(ARGB(alpha, 0, 0, 0));
		blank->RenderStretch(0, 0, viewPort.x, viewPort.y);
	}

    void CGameScreenMgr::loadContent()
    {   
        blank = CGame::pResMgr()->GetSprite("Blank");
        cursor = CGame::pResMgr()->GetSprite("Cursor");

        if (!blank) CGame::pHGE()->System_Log("[Error]Resource Sprite Blank not found!");
        if (!cursor) CGame::pHGE()->System_Log("[Error]Resource Sprite Cursor not found!");
    }

    void CGameScreenMgr::unloadContent()
    {

    }

    void CGameScreenMgr::cleanup()
    {
        ScreenList screensToRemove = gameScreens;
        IGameScreen *screen;
        while (screensToRemove.size() > 0)
        {
            screen = screensToRemove.back();
            screensToRemove.pop_back();
            removeScreen(screen); // 这里不用ExitScreen，由于此时程序已要求退出，没时间transitionoff了
        }
    }

	const Point& CGameScreenMgr::getCursorPos() const
	{
		return cursorPos;
	}

}