// /*
// ** Haaf's Game Engine 1.8
// ** Copyright (C) 2003-2007, Relish Games
// ** hge.relishgames.com
// **
// ** sudopix
// */

#include "stdafx.h"
#include "Game.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        SudoPix::CGame game;
		game.go();
	}
	catch (std::string& e)
	{
		MessageBox(NULL, e.c_str(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
	catch (...)
	{
		MessageBox(NULL, "Something Wrong", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}
    return 0;
}