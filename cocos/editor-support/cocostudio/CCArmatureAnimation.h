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


#ifndef __CCANIMATION_H__
#define __CCANIMATION_H__

#include "cocostudio/CCProcessBase.h"
#include "cocostudio/CCTween.h"
#include <queue>

namespace cocostudio {


enum MovementEventType
{
    START,
    COMPLETE,
    LOOP_COMPLETE
};


class Armature;
class Bone;

typedef void (cocos2d::Ref::*SEL_MovementEventCallFunc)(Armature *, MovementEventType, const std::string&);
typedef void (cocos2d::Ref::*SEL_FrameEventCallFunc)(Bone *, const std::string&, int, int);

#define movementEvent_selector(_SELECTOR) (cocostudio::SEL_MovementEventCallFunc)(&_SELECTOR)
#define frameEvent_selector(_SELECTOR) (cocostudio::SEL_FrameEventCallFunc)(&_SELECTOR)

struct FrameEvent
{
    Bone *bone;
    std::string frameEventName;
    int originFrameIndex;
    int currentFrameIndex;
};

struct MovementEvent
{
    Armature *armature;
    MovementEventType movementType;
    std::string movementID;
};

class  ArmatureAnimation : public ProcessBase
{
public:
    /**
     * 通过Armature创建ArmatureAnimation
     * @param armature 创建的ArmatureAnimation
     */
    static ArmatureAnimation *create(Armature *armature);
public:
	/**
     * @js ctor
     */
    ArmatureAnimation();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ArmatureAnimation(void);

    /**
     * 通过Armature来初始化ArmatureAnimation
     * @param armature The Armature ArmatureAnimation will bind to
     */
    virtual bool init(Armature *armature);

    /**
     * 缩放动作速度
     * 不推荐使用该方法,请使用setSpeedScale
     * @param animationScale 缩放值
     */
    CC_DEPRECATED_ATTRIBUTE virtual void setAnimationScale(float animationScale);
    CC_DEPRECATED_ATTRIBUTE virtual float getAnimationScale() const;

    /**
     * 缩放动画播放速度
     * @param animationScale 缩放值
     */
    virtual void setSpeedScale(float speedScale);
    virtual float getSpeedScale() const;

    //! 设置动画更新速度
    CC_DEPRECATED_ATTRIBUTE virtual void setAnimationInternal(float animationInternal) {}

    using ProcessBase::play;
    /**
     * 播放指定名称的动画
     *
     * @param  animationName  想要播放的动画名称
     * @param  durationTo 两个动画之间的切换帧数量
     *         
     *
     *         -1 : 使用MovementData中的值
     * @param  loop   是否循环播放
     *
     *         loop < 0 : 使用MovementData中的值
     *         loop = 0 : 不循环
     *         loop > 0 : 循环指定次数
     */
    virtual void play(const std::string& animationName, int durationTo = -1,  int loop = -1);

    /**
     * 播放指定索引的动作，其他参数的意思同play函数相同
     * @deprecated, 请使用playByIndex
     * @param  animationIndex  想要播放的动画索引
     */
    CC_DEPRECATED_ATTRIBUTE virtual void playByIndex(int animationIndex,  int durationTo = -1, int loop = -1);
    virtual void playWithIndex(int animationIndex,  int durationTo = -1, int loop = -1);

    virtual void playWithNames(const std::vector<std::string>& movementNames, int durationTo = -1, bool loop = true);
    virtual void playWithIndexes(const std::vector<int>& movementIndexes, int durationTo = -1, bool loop = true);

    /**
     * 跳转到指定的帧并播放
     * 你需要先切换到你想要播放的movement，然后再调用该函数
     * 
     * example : playByIndex(0);
     *           gotoAndPlay(0);
     *           playByIndex(1);
     *           gotoAndPlay(0);
     *           gotoAndPlay(15);
     */
    virtual void gotoAndPlay(int frameIndex);

    /**
     * 跳转到指定帧，并暂停当前动作
     */
    virtual void gotoAndPause(int frameIndex);

    /**
     * 暂停处理
     */
    virtual void pause();
    /**
     * 恢复处理
     */
    virtual void resume();
    /**
     * 停止处理
     */
    virtual void stop();


    /**
     * 获取movement的数量
     */
    ssize_t getMovementCount() const;

    void update(float dt);

    /**
     * 获取当前movement的id
     * @return 当前movement的名称
     */
    std::string getCurrentMovementID() const;

    /**
     * 设置armature的movment时间处理回调函数
     * 断开当前事件，调用setMovementEventCallFunc(nullptr, nullptr);
     */
    CC_DEPRECATED_ATTRIBUTE void setMovementEventCallFunc(cocos2d::Ref *target, SEL_MovementEventCallFunc callFunc);

    /**
     * 设置armature的frame时间处理回调函数
     * setFrameEventCallFunc(nullptr, nullptr);
     */
    CC_DEPRECATED_ATTRIBUTE void setFrameEventCallFunc(cocos2d::Ref *target, SEL_FrameEventCallFunc callFunc);
    
    void setMovementEventCallFunc(std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> listener);
    void setFrameEventCallFunc(std::function<void(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)> listener);

    virtual void setAnimationData(AnimationData *data) 
    {
        if (_animationData != data)
        {
            CC_SAFE_RETAIN(data);
            CC_SAFE_RELEASE(_animationData);
            _animationData = data; 
        }
    }
    virtual AnimationData *getAnimationData() const { return _animationData; }


    /** 
     * 返回用户赋值对象
     * 
     * 类似userData,但是保存的是一个对象
     *
     * @return 用户赋值对象
     * @js NA
     * @lua NA
     */
    virtual Ref* getUserObject() { return _userObject; }
    /** 
    * @js NA
    * @lua NA
    */
    virtual const Ref* getUserObject() const { return _userObject; }

    /**
     * 设置用户赋值对象
     *
     * 类似UserData,但是保持的是一个对象。
     * UserObject会在该函数中retain一次，并且释放上一个UserObject
     *
     * @param userObject    A user assigned Object
     */
    virtual void setUserObject(Ref *userObject);
protected:

    /**
     * Update(float dt) 会调用该函数，可以添加自己需要的一些功能
     * @js NA
     * @lua NA
     */
    void updateHandler();

    /**
     * 更新当前关键帧，并且处理会自动的停止或暂停
     * @js NA
     * @lua NA
     */
    void updateFrameData(float currentPercent);

    /**
     * 发生一次frame事件
     * @js NA
     * @lua NA
     */
    void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex);

    /**
     * 发生一次movement事件
     */
    void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);

    void updateMovementList();

    bool isIgnoreFrameEvent() const { return _ignoreFrameEvent; }

    friend class Tween;
protected:
    //! AnimationData保存动画使用的所有的Movement数据
    AnimationData *_animationData;

    //! 缩放动画速度
    float _speedScale;

    MovementData *_movementData;				//! MovementData保存动画所有的MovementFrameDatas

    Armature *_armature;						//! armature的弱引用

    std::string _movementID;				//! 当前movement的名称

    int _toIndex;								//! 当前帧在MovementData->m_pMovFrameDataArr中的索引

    cocos2d::Vector<Tween*> _tweenList;

    bool _ignoreFrameEvent;
    
    std::queue<FrameEvent*> _frameEventQueue;
    std::queue<MovementEvent*> _movementEventQueue;

    std::vector<std::string> _movementList;
    
    bool _onMovementList;
    bool _movementListLoop;
    unsigned int _movementIndex;
    int _movementListDurationTo;

    cocos2d::Ref *_userObject;
protected:
    /**
     * MovementEvent回调函数
     * @param Armature* 骨骼动画
     * @param MovementEventType, 事件类型, 比如：START,COMPLETE
     * @param const char*, Movement Id, Movement名称
     */
    SEL_MovementEventCallFunc _movementEventCallFunc;

    /**
     * FrameEvent回调函数
     * @param Bone*, 骨骼
     * @param const char*, 帧事件的名称
     * @param int, 原始Frame索引
     * @param int, 当前frame的索引，动画可能被延迟
     */
    SEL_FrameEventCallFunc _frameEventCallFunc;


    cocos2d::Ref *_movementEventTarget;
    cocos2d::Ref *_frameEventTarget;
    
    
    std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> _movementEventListener;
    std::function<void(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)> _frameEventListener;
};

}

#endif /*__CCANIMATION_H__*/
