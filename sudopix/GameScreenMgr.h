#pragma once

#include "commonType.h"

class IGameScreen;
class hgeSprite;

namespace SudoPix
{

    // 游戏界面管理器（单例）
    class CGameScreenMgr
    {
    private:
        CGameScreenMgr();
        CGameScreenMgr(const CGameScreenMgr &gameMgr);
        CGameScreenMgr& operator=(const CGameScreenMgr &gameMgr);

    public:
        ~CGameScreenMgr();
        static CGameScreenMgr& Instance();

        // 更新与绘制函数
        bool update(float dt);
        void render();

        // 管理游戏界面的函数
        void addScreen(IGameScreen *gameScreen);
        void removeScreen(IGameScreen *gameScreen);
        void removeScreen();
        ScreenList &getScreens() { return gameScreens; }

        void loadContent();
        void unloadContent();

        void cleanup();
        void setExiting(bool exiting) { isExiting = exiting; }

        void fadeBackToBlack(int alpha);

		const Point& getCursorPos() const;

    private:
        ScreenList gameScreens; // 当前游戏界面列表
        hgeSprite *blank;
        hgeSprite *cursor;
        Point cursorPos;
        IGameScreen *curRemovedScreen;
        bool isExiting;
    };

    #define GSMgr CGameScreenMgr::Instance()
}

