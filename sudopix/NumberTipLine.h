#pragma once
#include <vector>
using std::vector;

class hgeFont;
class hgeSprite;
namespace SudoPix
{
	class CNumberTip
	{
	public:
		enum ENumberTipLineType
		{
			Horizontal = 0,
			vertical
		};

	public:
		CNumberTip(ENumberTipLineType _type = Horizontal);
		~CNumberTip(void);

		void render(float x, float y, float width, float height, int alpha = 255);
		void setType(ENumberTipLineType _type);
		void setNumberTip(const vector<unsigned>& _tip);
		void setColor(DWORD color);

		void setFinish() { finished = true; }
		bool isFinish() const { return finished; }

	private:
		ENumberTipLineType type;
		vector<unsigned> tip;
		hgeSprite* sprBG;
		hgeFont* fnt;
		bool finished;
	};

}