#include "StdAfx.h"
#include "Clock.h"
#include "Game.h"
#include "loadingscreen.h"
#include "GameLoseScreen.h"

namespace SudoPix
{
	CClock::CClock(void) : curTime(0), decCount(0)
	{
		fnt = CGame::pResMgr()->GetFont("ClockNumber");
		bg = CGame::pResMgr()->GetSprite("Clock");
	}

	CClock::~CClock(void)
	{
	}

	void CClock::update( float dt )
	{
		curTime -= dt;

		// 如果还没减少完时间，则减去响应时间
		if (decCount)
		{
			curTime -= perDecTime;
			if (curTime < 0) 
			{
				curTime = 0;
				CLoadingScreen::Load(false, new GameLoseScreen);
			}
			--decCount;
		}
	}

	void CClock::render( float x, float y )
	{
		bg->Render(x, y);

		int seconds = (int)curTime;
		int minute = seconds / 60;
		int second = seconds % 60;
		stringstream ss;
		ss << setw(2) << setfill('0') << minute << ':' << setw(2) << setfill('0') << second;
		fnt->SetScale(44 / fnt->GetHeight());
		fnt->printfb(x - 40, y - 18, 79, 44, HGETEXT_CENTER, ss.str().c_str());
	}

	void CClock::start()
	{
		curTime = 30 * 60.f;
	}

	void CClock::loseTime( float _time )
	{
		// 如果当前正在减时间，则将还没减少的时间添加到_time中
		// 这样保证每次减少时间所需要的时间一致，而且重复减少时间次数越多
		// 时间减少得就越快
		if (decCount > 0)
		{
			_time += decCount * perDecTime;
		}

		// 分50次来减少，每次减少perDecTime
		decCount = 50;
		perDecTime = _time / (float)decCount;
	}

}