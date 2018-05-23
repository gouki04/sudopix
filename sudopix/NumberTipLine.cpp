#include "StdAfx.h"
#include "NumberTipLine.h"
#include "game.h"
#include "Difficuty.h"

namespace SudoPix
{
	CNumberTip::CNumberTip( ENumberTipLineType _type /*= Horizontal*/ )
		: finished(false)
	{
		setType(_type);
		fnt = CGame::pResMgr()->GetFont("Number");
	}

	CNumberTip::~CNumberTip(void)
	{
	}

	void CNumberTip::render( float x, float y, float width, float height, int alpha /*= 255 */)
	{
		sprBG->RenderStretch(x, y, x + width, y + height);
		if (finished) return;

		float size = (float)DIFFICULTY.gridSize();
		fnt->SetColor(SETA(fnt->GetColor(), alpha));
		fnt->SetScale(DIFFICULTY.tipFontHeight() / fnt->GetHeight());
		if (type == Horizontal)
		{
			float right = x + width;
			for (unsigned i = 0; i < tip.size(); ++i)
				fnt->printfb(right - (i + 1) * size, y, size, size, HGETEXT_CENTER, "%d", tip[tip.size() - i - 1]);
		}
		else if (type == vertical)
		{
			float bottom = y + height;
			for (unsigned i = 0; i < tip.size(); ++i)
				fnt->printfb(x, bottom - (i + 1) * size, size, size, HGETEXT_CENTER, "%d", tip[tip.size() - i - 1]);
		}
	}

	void CNumberTip::setType( ENumberTipLineType _type )
	{
		type = _type;
		if (type == Horizontal)
			sprBG = CGame::pResMgr()->GetSprite("NumberTipH");
		else if (type == vertical)
			sprBG = CGame::pResMgr()->GetSprite("NumberTipV");
	}

	void CNumberTip::setNumberTip( const vector<unsigned>& _tip )
	{
		tip = _tip;
	}

	void CNumberTip::setColor( DWORD color )
	{
		sprBG->SetColor(color);
	}

}