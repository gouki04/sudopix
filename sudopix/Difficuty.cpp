#include "StdAfx.h"
#include "Difficuty.h"

namespace SudoPix
{
    CDifficuty::CDifficuty(void)
    {
    }

    CDifficuty::~CDifficuty(void)
    {
    }

    int CDifficuty::rowCount() const
    {
        switch (difficuty)
        {
		case EDifficuty::Easy:   return 5;
        case EDifficuty::Normal: return 10;
        case EDifficuty::Hard:   return 15;
        default:     return 5;
        }
    }

    int CDifficuty::colCount() const
    {
        switch (difficuty)
        {
        case EDifficuty::Easy:   return 5;
        case EDifficuty::Normal: return 10;
        case EDifficuty::Hard:   return 15;
        default:     return 5;
        }
    }

	int CDifficuty::gridSize() const
	{
		switch (difficuty)
		{
		case EDifficuty::Easy:   return 60;
		case EDifficuty::Normal: return 30;
		case EDifficuty::Hard:   return 20;
		default:     return 60;
		}
	}

	CDifficuty& CDifficuty::instance()
	{
		static CDifficuty instance;
		return instance;
	}

	int CDifficuty::tipCount() const
	{
		switch (difficuty)
		{
		case EDifficuty::Easy:   return 3;
		case EDifficuty::Normal: return 5;
		case EDifficuty::Hard:   return 8;
		default:     return 8;
		}
	}

	std::string CDifficuty::name() const
	{
		switch (difficuty)
		{
		case EDifficuty::Easy:   return "Easy";
		case EDifficuty::Normal: return "Normal";
		case EDifficuty::Hard:   return "Hard";
		default:     return "Easy";
		}
	}

	int CDifficuty::tipFontHeight() const
	{
		switch (difficuty)
		{
		case EDifficuty::Easy:   return 60;
		case EDifficuty::Normal: return 30;
		case EDifficuty::Hard:   return 20;
		default:     return 60;
		}
	}

	float CDifficuty::loseTime() const
	{
		switch (difficuty)
		{
		case EDifficuty::Easy:   return 5 * 60.f;
		case EDifficuty::Normal: return 3 * 60.f;
		case EDifficuty::Hard:   return 1 * 60.f;
		default:     return 5 * 60.f;
		}
	}

}