#include "StdAfx.h"
#include "Grid.h"
#include "game.h"
#include "Difficuty.h"

namespace SudoPix
{

    CGrid::CGrid( EGridState _state /*= None*/ ) 
        : gridState(_state), curState(None), sprGrid(0), timer(-1.f)
    {
        sprGrid = CGame::pResMgr()->GetSprite("GridNone");
		fnt = CGame::pResMgr()->GetFont("LittleNumber");
    }

    CGrid::~CGrid(void)
    {
    }

    void CGrid::render( float x, float y, float width, float height, int alpha /*= 255*/ )
    {
        switch (curState)
        {
        case None:
			sprGrid = CGame::pResMgr()->GetSprite("GridNone");
            break;
        case Fill:
            sprGrid = CGame::pResMgr()->GetSprite("GridFill");
            break;
        case Cross:
            sprGrid = CGame::pResMgr()->GetSprite("GridCross");
            break;
        default:
			sprGrid = CGame::pResMgr()->GetSprite("GridNone");
			break;
        }
		sprGrid->SetColor(SETA(sprGrid->GetColor(), alpha));
		sprGrid->RenderStretch(x, y, x + width, y + height);

		if (timer != -1.f)
		{
			fnt->SetScale(height / 2.f / fnt->GetHeight());
			fnt->printf(x + width / 2.f, y + timer * height / 2.f, HGETEXT_LEFT, "-%d", (int)(DIFFICULTY.loseTime() / 60.f));
		}
    }

    bool CGrid::setState( EGridState _state )
    {
		if (_state == None) 
		{
			curState = None;
			return true;
		}
		else if (_state == Cross)
		{
			if (curState == Cross)
				curState = None;
			else if (curState == None)
				curState = Cross;
			return true;
		}
		else if (_state == Fill && curState == None)
		{
			if (checkState(Fill))
			{
				curState = Fill;
				return true;
			}
			else
			{
				curState = Cross;
				timer = 1.f;
				return false;
			}
		}
		return true;
    }

    bool CGrid::checkState( EGridState _state )
    {
        return _state == gridState;
    }

    void CGrid::update( float dt )
    {
        if (timer == -1.f) return;
		timer -= dt;
		if (timer <= 0.f)
			timer = -1.f;
    }

	bool CGrid::isFinished() const
	{
		if (gridState == Cross) 
			return true;
		if (gridState == Fill && curState == Fill) 
			return true;
		return false;
	}

}