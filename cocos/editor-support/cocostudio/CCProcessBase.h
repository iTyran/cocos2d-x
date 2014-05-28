/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCPROCESSBASE_H__
#define __CCPROCESSBASE_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"

namespace cocostudio {


enum AnimationType
{
    SINGLE_FRAME = -4,          //! 动画只有一帧
    ANIMATION_NO_LOOP,          //! 动画不循环

    ANIMATION_TO_LOOP_FRONT,    //! 动画往前循环
    ANIMATION_TO_LOOP_BACK,     //! 动画往后循环

    ANIMATION_LOOP_FRONT,       //! 动画从前循环
    ANIMATION_LOOP_BACK,        //! 动画从后循环

    ANIMATION_MAX,

};

/**
 *  @js NA
 *  @lua NA
 */
class  ProcessBase : public cocos2d::Ref
{
public:
    ProcessBase(void);
    virtual ~ProcessBase(void);

    /**
     * 通过动画名称播放动画
     *
     * @param  durationTo   在两个动画改变-结束之前的那些帧.
     *         该参数意思是说切换到这个动画需要多少帧
     *
     *         -1 : 使用MovementData中得值，MovementData从从flash设计面板得到
     * @param  durationTween  在游戏中想要播放的帧
     *         如果_durationTween是80，动画在循环中将会播放80帧
     *
     *         -1 : 使用MovementData中得值，MovementData从从flash设计面板得到
     *
     * @param  loop 动画是否在循环
     *
     *         loop < 0 : 使用MovementData中得值，MovementData从从flash设计面板得到
     *         loop = 0 : 动画不在循环
     *         loop > 0 : 动画在循环
     *
     * @param  tweenEasing 缓动(Tween easing)是用来计算缓冲效果
     *
     *         TWEEN_EASING_MAX : 使用MovementData中得值，MovementData从从flash设计面板得到
     *         -1 : 淡出
     *         0  : 线性
     *         1  : 淡入
     *         2  : 淡入淡出
     *
     */
    virtual void play(int durationTo, int durationTween,  int loop, int tweenEasing);

    /**
     * 暂停进程
     */
    virtual void pause();
    /**
     * 恢复进程
     */
    virtual void resume();
    /**
     * 停止进程
     */
    virtual void stop();


    /**
     * 不应该调用这个函数，除非你知道你做了什么
     * 更新进程，包括当前进程，当前帧和子帧
     *
     * @param 自上次更新后的间隔
     */
    virtual void update(float dt);

    virtual int getCurrentFrameIndex();

    virtual void setProcessScale(float processScale) { _processScale = processScale; }
    virtual float getProcessScale() const { return _processScale; }

    virtual void setIsPause(bool pause) { _isPause = pause; }
    virtual bool isPause() const { return _isPause; }

    virtual void setIsComplete(bool complete) { _isComplete = complete; }
    virtual bool isComplete() const { return _isComplete; }

    virtual void setIsPlaying(bool playing) { _isPlaying = playing; }
    virtual bool isPlaying() const { return _isPlaying; }

    virtual float getCurrentPercent() const { return _currentPercent; }
    virtual int getRawDuration() const { return _rawDuration; }

protected:

    virtual void gotoFrame(int frameIndex);

    /**
     * Update(float dt)函数将会调用这个处理机(handler),你可以在这里处理你的逻辑
     */
    virtual void updateHandler() {};

protected:
    //! 缩放进程速度
    float _processScale;

    //! 设置和获取动画是否暂停
    bool _isPause;

    //! 设置和获取动画是否完成
    bool _isComplete;

    //! 设置和获取动画是否正在播放
    bool _isPlaying;

    //! 当前进程到达的百分比
    float _currentPercent;

    //! 原始长度
    int _rawDuration;

    //! 动画是否循环
    AnimationType _loopType;

    //! 缓动效果
    cocos2d::tweenfunc::TweenType _tweenEasing;

    //! 动画更新速度
    float _animationInternal;


protected:
    //! 在动画持续时间内将要播放的帧数
    int _durationTween;

    //! 当前进程的当前所处帧，这个帧是中间帧
    float _currentFrame;
    //! 在时间线中的帧的索引
    int _curFrameIndex;

    //! 当前进程需要运行到的下一帧
    int _nextFrameIndex;


    bool _isLoopBack;
};

}

#endif /*__CCPROCESSBASE_H__*/
