#include "stdafx.h"
#include "Game.h"
#include "GameScreenMgr.h"
#include "StartScreen.h"
#include "InputMgr.h"

namespace SudoPix
{

    HGE *CGame::hge = 0;
    hgeResourceManager *CGame::resMgr = 0;
    bool CGame::isActive = true;
    Point CGame::viewPort = Point(0, 0);
    bool CGame::resetDelta = false;

    CGame::CGame(void)
    {
        hge = hgeCreate(HGE_VERSION);
        resetDelta = false;
    }

    CGame::~CGame(void)
    {
        hge->Release();
    }

    void CGame::go()
    {
        if(initialize())
        {
            hge->System_Log("-------- Game start --------");
            GSMgr.loadContent();
            GSMgr.addScreen(new CStartScreen);
            srand((unsigned)time(0));
            hge->System_Start();

            // 注：不用System_SetState来设置退出函数，而是在这里手动调用
            // 因为退出游戏有2种方式：
            // 1:强制退出（ALT+F4或者按X），这时程序会到这里也会到System设置的ExitFunc中
            // 2:通过update返回true退出，此时程序会到这里但不会到System设置的ExitFunc中
            // 所以不用System_SetState来设置退出函数，那样正常退出就释放不了资源
            exitFunc();
        }
        else
        {	
            throw (std::string)hge->System_GetErrorMessage();
        }

        hge->System_Shutdown();
    }

    bool CGame::initialize()
    {
        const char *INI_FILE_NAME = "config.ini";
        const char *LOG_FILE_NAME = "Game.log";
        const char *WINDOW_TITLE  = "sudopix";
        const char *RESOURCE_FILE = "core.hgeres";
        const int DEFAULT_WIDTH = 800;
        const int DEFAULT_HEIGHT = 600;

        hge->System_SetState(HGE_FRAMEFUNC, &frameFunc);
        hge->System_SetState(HGE_RENDERFUNC, &renderFunc);
        hge->System_SetState(HGE_FOCUSLOSTFUNC, &focusLostFunc);
        hge->System_SetState(HGE_FOCUSGAINFUNC, &focusGainFunc);
        //hge->System_SetState(HGE_EXITFUNC, &exitFunc);
        hge->System_SetState(HGE_INIFILE, INI_FILE_NAME);   
        hge->System_SetState(HGE_SCREENWIDTH, hge->Ini_GetInt("basic", "width", DEFAULT_WIDTH));
        hge->System_SetState(HGE_SCREENHEIGHT, hge->Ini_GetInt("basic", "height", DEFAULT_HEIGHT));
        hge->System_SetState(HGE_LOGFILE, LOG_FILE_NAME);
        hge->System_SetState(HGE_TITLE, hge->Ini_GetString("basic", "title", WINDOW_TITLE));
        hge->System_SetState(HGE_WINDOWED, true);
        hge->System_SetState(HGE_USESOUND, false);
        hge->System_SetState(HGE_FPS, 60);

        resMgr = new hgeResourceManager(hge->Ini_GetString("basic", "resScript", RESOURCE_FILE));
        viewPort.x = static_cast<float>(hge->System_GetState(HGE_SCREENWIDTH));
        viewPort.y = static_cast<float>(hge->System_GetState(HGE_SCREENHEIGHT));

        return hge->System_Initiate();
    }

	bool CGame::frameFunc()
	{
		InputMgr.update();
		return GSMgr.update(hge->Timer_GetDelta());
    }

    bool CGame::renderFunc()
    {
        hge->Gfx_BeginScene();
        GSMgr.render();
        hge->Gfx_EndScene();
        return false;
    }

	bool CGame::exitFunc()
	{
		GSMgr.unloadContent();
		GSMgr.cleanup();
		hge->System_Log("-------- Game exit --------");
		return true;
	}

}