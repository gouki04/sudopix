#include "StdAfx.h"
#include "Sudopix.h"
#include "grid.h"
#include "game.h"
#include "difficuty.h"
#include "NumberTipLine.h"
#include "InputMgr.h"
#include "Clock.h"
#include "GameScreenMgr.h"
#include "gamemath.h"
#include "loadingscreen.h"
#include "GameWinScreen.h"

#define SALF_DELETE(T) if (T) { delete T; T = 0; }
//#define TEST

namespace SudoPix
{
	int CSudopix::puzzle_num = 0;
	CSudopix::CSudopix(void) : clock(0)
	{
		bg = CGame::pResMgr()->GetSprite("White");
		highlight_grid = CGame::pResMgr()->GetSprite("GridHighlight");
	}

	CSudopix::~CSudopix(void)
	{
		cleanup();
	}

	void CSudopix::generate( const EStartMode& mode /*= Random*/ )
	{
		cleanup();
		clock = new CClock;
		clock->start();

		stringstream ss;
		switch (mode)
		{
		case Continue:
			++puzzle_num;
			if (puzzle_num > 5) puzzle_num = 1;
			break;
		case Retry:
			break;
		case Random:
			puzzle_num = random(1, 5);
			break;
		}

#ifdef _DEBUG
		puzzle_num = 1;
#endif
		ss << puzzle_num;
		load(ss.str());
		init_tip_number();
	}

	void CSudopix::cleanup()
	{
		for (unsigned i = 0; i < grids.size(); ++i)
			for (unsigned j = 0; j < grids[i].size(); ++j)
				SALF_DELETE(grids[i][j]);
		grids.clear();

		for (unsigned i = 0; i < leftTips.size(); ++i)
			SALF_DELETE(leftTips[i]);
		leftTips.clear();

		for (unsigned i = 0; i < topTips.size(); ++i)
			SALF_DELETE(topTips[i]);
		topTips.clear();

		SALF_DELETE(clock);
	}

	void CSudopix::render( float x, float y, int alpha /*= 255*/)
	{
		clock->render(x / 2.f, y / 2.f/*, alpha*/);

		leftTop.x = x;
		leftTop.y = y;

		unsigned row = DIFFICULTY.rowCount();
		unsigned col = DIFFICULTY.colCount();
		float size = (float)DIFFICULTY.gridSize();
		HGE* hge = CGame::pHGE();

		unsigned highlight_row, highlight_col;
		Point p = GSMgr.getCursorPos();
		highlight_row = (int)floor((p.y - leftTop.y) / size);
		highlight_col = (int)floor((p.x - leftTop.x) / size);

		bg->SetColor(ARGB(alpha, 255, 255, 255));
		bg->RenderStretch(x, y, x + col * size, y + row * size);

		DWORD highlight_line = ARGB(alpha, 0, 0, 0);
		DWORD normal_line = ARGB(alpha, 136, 136, 136);
		for (unsigned i = 0; i <= row; ++i)
		{
			if (i % 5)
				hge->Gfx_RenderLine(x, y + i * size, x + col * size, y + i * size, normal_line);
			else
				hge->Gfx_RenderLine(x, y + i * size, x + col * size, y + i * size, highlight_line);
		}

		for (unsigned j = 0; j <= col; ++j)
		{
			if (j % 5)
				hge->Gfx_RenderLine(x + j * size, y, x + j * size, y + row * size, normal_line);
			else
				hge->Gfx_RenderLine(x + j * size, y, x + j * size, y + row * size, highlight_line);
		}

		for (unsigned i = 0; i < grids.size(); ++i)
		{
			for (unsigned j = 0; j < grids[i].size(); ++j)
			{
				grids[i][j]->render(x + j * size, y + i * size, size, size, alpha);
			}
		}

		DWORD tipLine_color1 = ARGB(alpha, 0, 255, 0);
		DWORD tipLine_color2 = ARGB(alpha, 0, 221, 112);
		int tipCount = DIFFICULTY.tipCount();
		for (unsigned i = 0; i < leftTips.size(); ++i)
		{
			if (i % 2)
				leftTips[i]->setColor(tipLine_color1);
			else
				leftTips[i]->setColor(tipLine_color2);
			leftTips[i]->render(x - tipCount * size, y + i * size, tipCount * size, size);
		}
		for (unsigned i = 0; i < topTips.size(); ++i)
		{
			if (i % 2)
				topTips[i]->setColor(tipLine_color1);
			else
				topTips[i]->setColor(tipLine_color2);
			topTips[i]->render(x + i * size, y - tipCount * size, size, tipCount * size);
		}

		DWORD highlighTip_color = ARGB(alpha, 102, 102, 51);
		if (highlight_row >= 0 && highlight_row < row && highlight_col >= 0 && highlight_col < col)
		{
			highlight_grid->RenderStretch(x + highlight_col * size - 1, y + highlight_row * size - 1, x + highlight_col * size + size + 1, y + highlight_row * size + size + 1);
			leftTips[highlight_row]->setColor(highlighTip_color);
			leftTips[highlight_row]->render(x - tipCount * size, y + highlight_row * size, tipCount * size, size);
			topTips[highlight_col]->setColor(highlighTip_color);
			topTips[highlight_col]->render(x + highlight_col * size, y - tipCount * size, size, tipCount * size);
		}
	}

    void CSudopix::update( float dt )
    {
		clock->update(dt);
#ifdef _DEBUG
		if (CGame::pHGE()->Input_GetKeyState(HGEK_A))
		{
			for (unsigned i = 0; i < grids.size(); ++i)
			{
				for (unsigned j = 0; j < grids[i].size(); ++j)
				{
					grids[i][j]->setState(CGrid::Fill);
				}
			}
		}
		else if (CGame::pHGE()->Input_GetKeyState(HGEK_1))
		{
			if (DIFFICULTY.getDifficuty() != CDifficuty::Easy)
			{
				DIFFICULTY.setDifficuty(CDifficuty::Easy);
				generate();
			}
		}
		else if (CGame::pHGE()->Input_GetKeyState(HGEK_2))
		{
			if (DIFFICULTY.getDifficuty() != CDifficuty::Normal)
			{
				DIFFICULTY.setDifficuty(CDifficuty::Normal);
				generate();
            }
        }
        else if (CGame::pHGE()->Input_GetKeyState(HGEK_3))
        {
            if (DIFFICULTY.getDifficuty() != CDifficuty::Hard)
            {
                DIFFICULTY.setDifficuty(CDifficuty::Hard);
                generate();
            }
        }
#endif
        for (unsigned i = 0; i < grids.size(); ++i)
        {
            for (unsigned j = 0; j < grids[i].size(); ++j)
            {
                grids[i][j]->update(dt);
            }
        }
	}

	void CSudopix::load( const string &name )
	{
		// 打开文件流fs
		string file_name = CGame::pHGE()->Ini_GetString("basic", "question_file", "");
		ifstream fs(file_name.c_str());
		if (!fs)
			throw "Cann't open file \"" + file_name + "\"";

		// 获取难度和行列数
		string difficulty = DIFFICULTY.name();
		int row = DIFFICULTY.rowCount();
		int col = DIFFICULTY.colCount();

		grids.resize(row);
		for (int i = 0; i < row; ++i)
			grids[i].resize(col);

		string s;
		string tmp;
		while (!fs.eof())
		{
			fs >> s;
			if (s == difficulty)	// 查找对应难度数据块
			{
				fs >> s;
				while(!fs.eof())
				{
					fs >> s;
					if (s == name)	// 查找对应题号的数据块
					{
						fs >> s;
						// 开始读取谜题数据
						for (int i = 0; i < row; ++i)
						{
							fs >> s;
							for (int j = 0; j < col; ++j)
							{
								// '0'代表填充，'-'代表不填充
								grids[i][j] = new CGrid(s[j] == '0' ? CGrid::Fill : CGrid::Cross);
							}
						}

						fs.close();
						return;
					}
					else
						find_next(fs);	// 查找下个数据块
				}
			}
			else
				find_next(fs);	// 查找下个数据块
		}

		throw "Load Question Error!\nQuery for non-exist question \"" + difficulty + "." + name + "\"";
	}

	void CSudopix::find_next( ifstream &fs ) const
	{
		string s;
		int brace_count = 0;

		while (!fs.eof())
		{
			fs >> s;
			if (s == "{")
				++brace_count;
			else if (s == "}")
			{
				--brace_count;
				if (brace_count == 0)
				{
					return;
				}
			}
		}
	}

	void CSudopix::init_tip_number()
	{
		leftTips.resize(DIFFICULTY.rowCount());
		topTips.resize(DIFFICULTY.colCount());

		vector<unsigned> row, col;
		for (unsigned i = 0; i < grids.size(); ++i)
		{
			unsigned count = 0;
			bool start = false;
			row.clear();
			for (unsigned j = 0; j < grids[i].size(); ++j)
			{
				if (grids[i][j]->checkState(CGrid::Fill))
				{
					start = true;
					++count;
				}
				else
				{
					if (start)
					{
						row.push_back(count);
						count = 0;
						start = false;
					}
				}
			}
			if (grids[i][grids[i].size() - 1]->checkState(CGrid::Fill))
			{
				row.push_back(count);
			}
			leftTips[i] = new CNumberTip(CNumberTip::Horizontal);
			leftTips[i]->setNumberTip(row);
		}

		for (unsigned j = 0; j < grids[0].size(); ++j)
		{
			unsigned count = 0;
			bool start = false;
			col.clear();
			for (unsigned i = 0; i < grids.size(); ++i)
			{
				if (grids[i][j]->checkState(CGrid::Fill))
				{
					start = true;
					++count;
				}
				else
				{
					if (start)
					{
						col.push_back(count);
						count = 0;
						start = false;
					}
				}
			}
			if (grids[grids.size() - 1][j]->checkState(CGrid::Fill))
			{
				col.push_back(count);
			}
			topTips[j] = new CNumberTip(CNumberTip::vertical);
			topTips[j]->setNumberTip(col);
		}
	}

	void CSudopix::handleInput()
	{
		int size = DIFFICULTY.gridSize();
		Point p;
		if (InputMgr.isMouseButtonLeftDown(p))
		{
			int row = (int)floor((p.y - leftTop.y) / size);
			int col = (int)floor((p.x - leftTop.x) / size);

			if (row < 0 || row >= DIFFICULTY.rowCount() || col < 0 || col >= DIFFICULTY.colCount()) return;
			bool result = grids[row][col]->setState(CGrid::Fill);
			if (result)
			{
#ifndef _DEBUG
				if (checkRow(row)) leftTips[row]->setFinish();
				if (checkCol(col)) topTips[col]->setFinish();
				if (checkFinish()) CLoadingScreen::Load(false, new GameWinScreen);
#endif
			}
			else
			{
				clock->loseTime(DIFFICULTY.loseTime());
			}
		}
		else if (InputMgr.isMouseButtonRightDown(p))
		{
			int row = (int)floor((p.y - leftTop.y) / size);
			int col = (int)floor((p.x - leftTop.x) / size);

			if (row < 0 || row >= DIFFICULTY.rowCount() || col < 0 || col >= DIFFICULTY.colCount()) return;
			grids[row][col]->setState(CGrid::Cross);
		}
	}

	bool CSudopix::checkRow( int _row ) const
	{
		unsigned rows = DIFFICULTY.rowCount();
		for (unsigned i = 0; i < rows; ++i)
			if (!grids[_row][i]->isFinished())
				return false;
		return true;
	}

	bool CSudopix::checkCol( int _col ) const
	{
		unsigned cols = DIFFICULTY.colCount();
		for (unsigned j = 0; j < cols; ++j)
			if (!grids[j][_col]->isFinished())
				return false;
		return true;
	}

	bool CSudopix::checkFinish() const
	{
		for (unsigned i = 0; i < leftTips.size(); ++i)
		{
			if (!leftTips[i]->isFinish()) return false;
		}

		for (unsigned i = 0; i < topTips.size(); ++i)
		{
			if (!topTips[i]->isFinish()) return false;
		}
		return true;
	}

}