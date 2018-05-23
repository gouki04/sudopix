#pragma once

#include "commonType.h"
#include "hge.h"
#include "IGameScreen.h"
#include "Sudopix.h"

class hgeFont;
class hgeSprite;
class hgeGUI;

namespace SudoPix
{
    class CSudopix;

    /* SudoPix游戏画面 */
    class CGamePlayScreen : public IGameScreen
    {
    public:
        CGamePlayScreen(const CSudopix::EStartMode mode = CSudopix::Random);
        virtual ~CGamePlayScreen(void);

        virtual void handleInput();
        virtual bool update(float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen);
        virtual void render();
        virtual void loadContent();
        virtual const char *Name() { return "GamePlay Screen"; }

    private:
        hgeFont *fnt;
        hgeSprite* bg;
        hgeGUI* gui;
        HEFFECT snd;
        int lastid;
        CSudopix* sudopix;
    };
}
