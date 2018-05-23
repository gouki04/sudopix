#pragma once

class hgeSprite;
class hgeAnimation;

namespace SudoPix
{
    class CGrid
    {
    public:
        enum EGridState
        {
            Fill = 0,
            Cross,
            None
        };

	public:
		CGrid(EGridState _state = None);
		~CGrid(void);

		void update(float dt);
		void render(float x, float y, float width, float height, int alpha = 255);
		bool setState(EGridState _state);
		bool checkState(EGridState _state);
		bool isFinished() const;

	private:
		EGridState curState;
		EGridState gridState;
		hgeSprite* sprGrid;
		hgeFont* fnt;
		float timer;
	};

}