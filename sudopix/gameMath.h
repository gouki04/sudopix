#pragma once

/* 将vlaue的值绑定在区间[min,max]内
 */
template <typename T>
T clamp(T &value, T min, T max)
{
    if (value < min) value = min;
    if (value > max) value = max;
    return value;
}

/* 获取一随机数
 * @param exclude true  : 随机数区间在[min, max)
 *                false : 随机数区间在[min, max]
 */
int random(int min, int max, bool exclude = true);

/* 获取一浮点随机数
 * @param decimalPlace 指定小数位，默认为1位小数位
 * @param exclude true  : 随机数区间在[min, max)
 *                false : 随机数区间在[min, max]
 */
float randomf(float min, float max, unsigned decimalPlace = 1, bool exclude = true);