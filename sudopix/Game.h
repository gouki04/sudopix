#pragma once

#include "commonType.h"
#include <hgevector.h>

class HGE;
class hgeResourceManager;

namespace SudoPix
{

    class CGame
    {
    public:
        CGame(void);
		~CGame(void);

		bool initialize();
		static bool frameFunc();
		static bool renderFunc();
		static bool focusLostFunc() { isActive = false; return false; }
		static bool focusGainFunc() { isActive = true; return false; }
		static bool exitFunc();

		void go();

		static HGE *pHGE() { return hge; }
		static hgeResourceManager *pResMgr() { return resMgr; }
		static bool IsActive() { return isActive; }
		static const Point& ViewPort() { return viewPort; }

        static void resetTimerDelta() { resetDelta = true; }

    public:
        static HGE *hge;
        static hgeResourceManager *resMgr;
        static bool isActive;
        static Point viewPort;
        static bool resetDelta;
    };

}