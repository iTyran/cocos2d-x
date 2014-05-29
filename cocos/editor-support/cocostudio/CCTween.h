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


#ifndef __CCTWEEN_H__
#define __CCTWEEN_H__

#include "cocostudio/CCProcessBase.h"
#include "2d/CCTweenFunction.h"

namespace cocostudio {

class Bone;
class ArmatureAnimation;
using cocos2d::tweenfunc::TweenType;

/**
 *  @js NA
 *  @lua NA
 */
class  Tween : public ProcessBase
{
public:
    /**
     * 用骨骼创建
     * @param bone 骨骼
     */
    static Tween *create(Bone *bone);
public:
    Tween(void);
    virtual ~Tween(void);

    /**
     * 用骨骼初始化
     * @param bone 骨骼
     */
    virtual bool init(Bone *bone);

    using ProcessBase::play;
    /**
     * 启动进程
     *
     * @param  movementBoneData 包含所有FrameData
     * @param  durationTo 动画需要的帧数
     * @param  durationTween  真正持续的帧数
     *
     * @param  loop   是否循环动画
     *
     *         loop < 0 : 从 MovementData 中获取
     *         loop = 0 : 不循环
     *         loop > 0 : 循环次数
     *
     * @param  tweenEasing  用来计算消失效果
     *
     *         TWEEN_EASING_MAX : 从 MovementData 中获取
     *         -1 : 淡出
     *         0  : 线性
     *         1  : 淡入
     *         2  : 淡入淡出
     *
     */
    virtual void play(MovementBoneData *movementBoneData, int durationTo, int durationTween,  int loop, int tweenEasing);

    inline void setAnimation(ArmatureAnimation *animation) { _animation = animation; }
    inline ArmatureAnimation *getAnimation() const { return _animation; }

    virtual void gotoAndPlay(int frameIndex);
    virtual void gotoAndPause(int frameIndex);

    virtual void setMovementBoneData(MovementBoneData *data) { _movementBoneData = data; }
    virtual const MovementBoneData *getMovementBoneData() const { return _movementBoneData; }
protected:

    /**
     * 触发Update的调用
     */
    virtual void updateHandler();

    /**
     * 计算到达的帧，有事件就派发
     */
    virtual float updateFrameData(float currentPercent);

    /**
     * 计算from和to直接的值
     */
    virtual void setBetween(FrameData *from, FrameData *to, bool limit = true);

    /**
     * 根据百分比计算tween效果
     */
    virtual FrameData *tweenNodeTo(float percent, FrameData *node = nullptr);

    /**
     * 根据百分比计算颜色
     */
    virtual void tweenColorTo(float percent, FrameData *node);

    /**
     * 更新关键帧
     */
    virtual void arriveKeyFrame(FrameData *keyFrameData);
protected:
    //! MovementBoneData的弱引用
    MovementBoneData *_movementBoneData;

    FrameData *_tweenData;          //! 弱引用 tweenData
    FrameData *_from;               //! 用来计算中间值
    FrameData *_to;                 //! 用来计算中间值
    FrameData *_between;            //! 中间值


    Bone *_bone;                    //! 弱引用 Bone

    TweenType _frameTweenEasing;  //! 使用哪个特效

    int _betweenDuration;           //! 当前关键帧持续时间
    int _totalDuration;


    int _fromIndex;				    //! 当前帧的index值
    int _toIndex;                   //! 当前帧的index值

    ArmatureAnimation *_animation;

    bool _passLastFrame;            //! 是否当前帧的index大于上一帧的index
};

}

#endif /*__CCTWEEN_H__*/
