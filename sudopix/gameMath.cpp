#include "stdafx.h"
#include "gameMath.h"

int random(int min, int max, bool exclude /*= true*/)
{
    if (exclude)
        return rand() % (max - min + 1) + min;
    else
        return rand() % (max - min) + min;
}

float randomf(float min, float max, unsigned decimalPlace /*= 1*/, bool exclude /*= true*/)
{
    unsigned times = 1;
    for(;decimalPlace > 0; --decimalPlace)
        times *= 10;

    if(exclude)
        return (float)(rand() % (int)((max - min) * times + 1) + min * times) / times;
    else
        return (float)(rand() % (int)((max - min) * times) + min * times) / times;
}