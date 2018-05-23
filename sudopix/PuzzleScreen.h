#pragma once
#include "IGameScreen.h"

namespace SudoPix
{
    class CPuzzleScreen : public IGameScreen
    {
    public:
        CPuzzleScreen(void);
        virtual ~CPuzzleScreen(void);

        virtual void handleInput();
        virtual bool update(float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen);
        virtual void render();
        virtual void loadContent();
        virtual const char *Name() { return "Puzzle Screen"; }

    private:
        hgeSprite* bg;
        hgeFont* fnt;
    };
}