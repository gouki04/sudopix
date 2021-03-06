#pragma once

namespace SudoPix
{
	/* 难度类（单例）
	 * 游戏在不同难度下有不同的表现，此类抽象出不同难度下的参数
	 * 使外部有一个通用的接口
	 */
    class CDifficuty
    {
	private:
		CDifficuty(void);
		CDifficuty(const CDifficuty&);
		//CDifficuty& operator=(const CDifficuty&);

    public:
        enum EDifficuty
        {
            Easy = 0,	// 简单
            Normal,		// 普通
            Hard		// 困难
        };

    public:
		static CDifficuty& instance();
		~CDifficuty(void);

		/* 设置\获取难度 */
		void setDifficuty(EDifficuty _difficuty) { difficuty = _difficuty; }
		EDifficuty getDifficuty() const { return difficuty; }

		/* 获取行数 */
		int rowCount() const;

		/* 获取列数 */
		int colCount() const;

		/* 获取格子的大小（宽高相同）*/
		int gridSize() const;

        /* 获取提示数字的个数 */
		int tipCount() const;

        /* 获取提示数字的字高 */
		int tipFontHeight() const;

        /* 获取难度对应字符串 */
		std::string name() const;

        /* 获取点击错误损失的时间 */
		float loseTime() const;

	private:
		EDifficuty difficuty;
	};

#define DIFFICULTY CDifficuty::instance()
}