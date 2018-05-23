#include "stdafx.h"
#include "Game.h"
#include "gameMath.h"
#include "StartScreen.h"
#include "menuitem.h"
#include "gamescreenmgr.h"
#include "gameplayscreen.h"
#include "loadingscreen.h"
#include "puzzlescreen.h"
#include "resource.h"
#include "difficuty.h"

namespace SudoPix
{
    CStartScreen::CStartScreen(void)
    {
        transitionOnTime = 1;
        transitionOffTime = 1;
    }

    CStartScreen::~CStartScreen(void)
    {

    }

    void CStartScreen::handleInput()
    {
    }

    bool CStartScreen::update( float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen )
    {
        int id=gui->Update(dt);
        if(id == -1)
        {
            Point viewport = CGame::ViewPort();
            ScreenList screens;
            switch(lastid)
            {
            case MENU_START:
                gui->DelCtrl(MENU_START);
                gui->DelCtrl(MENU_OPTION);
                gui->DelCtrl(MENU_EXIT);
                gui->AddCtrl(new hgeGUIMenuItem(MENU_EASY, fnt, snd, viewport.x / 2.f, 200, 0.0f, "Easy"));
                gui->AddCtrl(new hgeGUIMenuItem(MENU_NORMAL, fnt, snd, viewport.x / 2.f, 240, 0.1f, "Normal"));
                gui->AddCtrl(new hgeGUIMenuItem(MENU_HARD, fnt, snd, viewport.x / 2.f, 280, 0.2f, "Hard"));
                gui->AddCtrl(new hgeGUIMenuItem(MENU_BACK, fnt, snd, viewport.x / 2.f, 320, 0.2f, "Back"));
                gui->SetFocus(MENU_EASY);
                gui->Enter();
                lastid = -1;
                break;
            case MENU_EASY:
                DIFFICULTY.setDifficuty(CDifficuty::Easy);
                CLoadingScreen::Load(true, new CGamePlayScreen);
                lastid = -1;
                break;
            case MENU_NORMAL:
                DIFFICULTY.setDifficuty(CDifficuty::Normal);
                CLoadingScreen::Load(true, new CGamePlayScreen);
                lastid = -1;
                break;
            case MENU_HARD:
                DIFFICULTY.setDifficuty(CDifficuty::Hard);
                CLoadingScreen::Load(true, new CGamePlayScreen);
                lastid = -1;
                break;
            case MENU_BACK:
                gui->DelCtrl(MENU_EASY);
                gui->DelCtrl(MENU_NORMAL);
                gui->DelCtrl(MENU_HARD);
                gui->DelCtrl(MENU_BACK);
                gui->AddCtrl(new hgeGUIMenuItem(MENU_START, fnt, snd, viewport.x / 2.f, 200, 0.0f, "Start Game"));
                //gui->AddCtrl(new hgeGUIMenuItem(MENU_OPTION, fnt, snd, viewport.x / 2.f, 240, 0.1f, "Option"));
                gui->AddCtrl(new hgeGUIMenuItem(MENU_EXIT, fnt, snd, viewport.x / 2.f, 240, 0.2f, "Exit"));
                gui->SetFocus(MENU_START);
                gui->Enter();
                lastid = -1;
                break;
            case MENU_OPTION:
                gui->SetFocus(MENU_START);
                gui->Enter();
                lastid = -1;
                break;
            case MENU_EXIT: 
                GSMgr.setExiting(true); 
                lastid = -1;
                break;
            }
        }
        else if(id) 
        { 
            lastid = id;
            gui->Leave(); 
        }

        return IGameScreen::update(dt, _otherScreenHasFocus, coveredByOtherScreen);
    }

    void CStartScreen::render()
    {
        int fade = getTransitionAlpha();
        bg->SetColor(ARGB(fade, fade, fade, fade));
        bg->Render(0.f, 0.f);
        gui->Render();

        Point viewport = CGame::ViewPort();
        titleFnt->SetColor(SETA(titleFnt->GetColor(), fade));
        titleFnt->Render(viewport.x / 2.f, 10 - 150 * (255 - fade) / 255.f, HGETEXT_CENTER, "SUDOPIX");
		//fnt->Render(viewport.x - 10, viewport.y - fnt->GetHeight(), HGETEXT_RIGHT, "Proudced by gouki at 2011");
    }

    void CStartScreen::loadContent()
    {
		hgeResourceManager* resMgr = CGame::pResMgr();
		bg = resMgr->GetSprite("GameBG");
		fnt = resMgr->GetFont("Button");
		titleFnt = resMgr->GetFont("Title");
		snd = resMgr->GetEffect("MenuSound");

		Point viewport = CGame::ViewPort();

		gui = new hgeGUI();
		gui->AddCtrl(new hgeGUIMenuItem(MENU_START, fnt, snd, viewport.x / 2.f, 200, 0.0f, "Start Game"));
		//gui->AddCtrl(new hgeGUIMenuItem(MENU_OPTION, fnt, snd, viewport.x / 2.f, 240, 0.1f, "Option"));
		gui->AddCtrl(new hgeGUIMenuItem(MENU_EXIT, fnt, snd, viewport.x / 2.f, 240, 0.2f, "Exit"));

		bg->SetTextureRect(0, 0, viewport.x, viewport.y);
    }
}