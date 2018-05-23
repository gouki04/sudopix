#include "stdafx.h"
#include "IGameScreen.h"
#include "GameScreenMgr.h"
#include "Game.h"
#include "gameMath.h"

namespace SudoPix
{
    bool IGameScreen::update( float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen )
    {
        this->otherScreenHasFocus = _otherScreenHasFocus;

        if (isExiting)
        {
            screenState = TransitionOff;
            if (!UpdateTransition(dt, transitionOffTime, 1))
            {
                GSMgr.removeScreen(this);
                return true;
            }
        }
        else if (coveredByOtherScreen)
        {
            if(UpdateTransition(dt, transitionOffTime, 1))
                screenState = TransitionOff;
            else
                screenState = Hidden;
        }
        else
        {
            if(UpdateTransition(dt, transitionOnTime, -1))
                screenState = TransitionOn;
            else
                screenState = Active;
        }
        return false;
    }

    bool IGameScreen::UpdateTransition( float dt, float time, int direction )
    {
        float transitionDelta;

        if(time == 0.f)
            transitionDelta = 1;
        else
            transitionDelta = dt / time;

        transitionPosition += transitionDelta * direction;

        if((direction < 0 && transitionPosition <= 0) || (direction > 0 && transitionPosition >= 1))
        {
            clamp(transitionPosition, 0.f, 1.f);
            return false;
        }

        return true;
    }

    void IGameScreen::ExitScreen()
    {
        if(transitionOffTime == 0.f)
            GSMgr.removeScreen(this);
        else
            isExiting = true;
    }
}