#pragma once

namespace SudoPix
{
    /* Screen状态 */
    enum EScreenState
    {
        TransitionOn = 0, // 出场中
        Active,           // 活动中
        TransitionOff,    // 离开中
        Hidden            // 不可见
    };

    /* Screen接口 */
    class IGameScreen
    {
    public:
        IGameScreen() 
            : isPopup(false), 
            transitionPosition(1.f), 
            transitionOnTime(0.f), 
            transitionOffTime(0.f), 
            screenState(TransitionOn),
            isExiting(false)
        { }

        virtual ~IGameScreen() {}

    public:
        /* 处理输入 */
        virtual void handleInput() { }
        
        /* 更新状态
         * @param dt 距离上次更新的时间差
         * @param _otherScreenHasFocus 是否有其他Screen已经获得焦点
         * @param coveredByOtherScreen 是否有其他Screen盖上上面
         */
        virtual bool update(float dt, bool _otherScreenHasFocus, bool coveredByOtherScreen);

        /* 渲染 */
        virtual void render() = 0;

        /* 加载资源 */
        virtual void loadContent() { }
        
        /* 释放资源 */
        virtual void unloadContent() { }
        
        /* 退出当前Screen */
        virtual void ExitScreen();

        /* 获取Screen的名称 */
        virtual const char *Name() { return ""; }

        /* 判断Screen是否为popup（弹出Screen会盖在其他Screen上面 */
        bool IsPopup() { return isPopup; }

        /* 获取Screen的状态 */
        EScreenState ScreenState() { return screenState; }
        
        /* 判断当前是否在退出中 */
        bool IsExiting() { return isExiting; }
        
        /* 判断当前是否在活动中 */
        bool IsActive() { return !otherScreenHasFocus && (screenState == TransitionOn || screenState == Active); }
        
        /* 根据当前的Transition值计算alpha */
        int getTransitionAlpha() { return 255 - (int)(transitionPosition * 255); }

        /* 设定Screen是否要退出 */
        void SetExiting(bool exiting) { isExiting = exiting; }

    private:
        /* 更新Transition */
        bool UpdateTransition(float dt, float time, int direction);

    protected:
        float transitionPosition; 
        float transitionOnTime;
        float transitionOffTime;
        bool isPopup;
        EScreenState screenState;
        bool isExiting;
        bool otherScreenHasFocus;
    };
}