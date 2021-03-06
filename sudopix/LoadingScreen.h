#pragma once
#include "IGameScreen.h"
#include "commonType.h"

namespace SudoPix
{
    /* Loading界面
     * 同时负责界面的载入
     */
    class CLoadingScreen : public IGameScreen
    {
    public:
        virtual ~CLoadingScreen(void);
        virtual bool update(float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen);
        virtual void render();
        virtual void loadContent();
        virtual const char *Name() { return "Loading Screen"; }

        /* 载入界面
         * @param _loadingIsSlow 载入比较慢时会显示载入界面，否则不显示
         * @param _screensToLoad 需要载入的一列界面
         * @ramark 此函数不仅加载新的界面，同时也将旧的界面去掉，
         *         如果不想去掉旧的界面，使用ScreenMgr的AddScreen方法
         */
        static void Load(bool _loadingIsSlow, ScreenList _screensToLoad);
        
        /* 加载单个界面 */
        static void Load(bool _loadingIsSlow, IGameScreen* _screenToLoad);

    private:
        CLoadingScreen(bool _loadingIsSlow, ScreenList _screensToLoad);

        bool loadingIsSlow;
        bool otherScreensAreGone;
        ScreenList screensToLoad;

        hgeFont *fnt;
    };
}