#pragma once
#include "commonType.h"
#include <vector>
using std::vector;

namespace SudoPix
{
	class CGrid;
	typedef vector<CGrid*> GridLine;
	typedef vector<GridLine> GridMatirx;

	class CNumberTip;
	typedef vector<CNumberTip*> NumberTipVec;

	class CClock;

	class CSudopix
	{
	public:
		enum EStartMode
		{
			Continue = 1,
			Retry,
			Random
		};

	public:
		CSudopix(void);
		~CSudopix(void);

		void generate(const EStartMode& mode = Random);
		void render(float x, float y, int alpha = 255);
		void update(float dt);
		void handleInput();
		void cleanup();

		void load(const string &name);
		void find_next(ifstream &fs) const;
		void CSudopix::init_tip_number();

	private:
		bool checkRow(int _row) const;
		bool checkCol(int _col) const;
		bool checkFinish() const;

	private:
		GridMatirx grids;			// 格的集合（N*N）
		NumberTipVec topTips;		// 上边的数字提示栏
		NumberTipVec leftTips;		// 左边的数字提示栏
		CClock* clock;				// 左上角的时钟
		Point leftTop;				// 格的左上角坐标
		hgeSprite* bg;				// 背景Sprite
		hgeSprite* highlight_grid;	// 高亮格的Sprite
		static int puzzle_num;		// 当前的题号
	};

}