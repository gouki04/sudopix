#pragma once

namespace SudoPix
{
    /* 时钟类
     */
	class CClock
	{
	public:
		CClock(void);
		~CClock(void);

        /* 更新和渲染 */
		void update(float dt);
		void render(float x, float y);

        /* 开始计时，统一为30分钟 */
		void start();

        /* 丢失时间，操作失误时会丢失一定时间，时间为0则Game Over */
		void loseTime(float _time);

	private:
		hgeFont* fnt;
		hgeSprite* bg;
		float curTime;
		int decCount;
		float perDecTime;
	};
}
