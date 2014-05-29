/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCSCHEDULER_H__
#define __CCSCHEDULER_H__

#include <functional>
#include <mutex>
#include <set>

#include "base/CCRef.h"
#include "base/CCVector.h"
#include "2d/uthash.h"

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */

class Scheduler;

typedef std::function<void(float)> ccSchedulerFunc;
//
// Timer
//
/** @brief Light-weight timer */
//
class CC_DLL Timer : public Ref
{
protected:
    Timer();
public:
    /** 获得用秒计数的时间间隔 */
    inline float getInterval() const { return _interval; };
    /** 设置用秒计数的时间间隔 */
    inline void setInterval(float interval) { _interval = interval; };
    
    void setupTimerWithInterval(float seconds, unsigned int repeat, float delay);
    
    virtual void trigger() = 0;
    virtual void cancel() = 0;
    
    /** 触发计时器 */
    void update(float dt);
    
protected:
    
    Scheduler* _scheduler; // weak ref
    float _elapsed;
    bool _runForever;
    bool _useDelay;
    unsigned int _timesExecuted;
    unsigned int _repeat; //0 = once, 1 is 2 x executed
    float _delay;
    float _interval;
};


class CC_DLL TimerTargetSelector : public Timer
{
public:
    TimerTargetSelector();

    /** 通过参数：一个目标，一个选择器，一个间隔秒数，重复次数以及延迟的秒数来初始化计时器 */
    bool initWithSelector(Scheduler* scheduler, SEL_SCHEDULE selector, Ref* target, float seconds, unsigned int repeat, float delay);
    
    inline SEL_SCHEDULE getSelector() const { return _selector; };
    
    virtual void trigger() override;
    virtual void cancel() override;
    
protected:
    Ref* _target;
    SEL_SCHEDULE _selector;
};


class CC_DLL TimerTargetCallback : public Timer
{
public:
    TimerTargetCallback();
    
    /** 通过参数：一个目标，一个选择器，一个间隔秒数，重复次数以及延迟的秒数来初始化计时器. */
    bool initWithCallback(Scheduler* scheduler, const ccSchedulerFunc& callback, void *target, const std::string& key, float seconds, unsigned int repeat, float delay);
    
    /**
     * @js NA
     * @lua NA
     */
    inline const ccSchedulerFunc& getCallback() const { return _callback; };
    inline const std::string& getKey() const { return _key; };
    
    virtual void trigger() override;
    virtual void cancel() override;
    
protected:
    void* _target;
    ccSchedulerFunc _callback;
    std::string _key;
};

#if CC_ENABLE_SCRIPT_BINDING

class CC_DLL TimerScriptHandler : public Timer
{
public:
    bool initWithScriptHandler(int handler, float seconds);
    inline int getScriptHandler() const { return _scriptHandler; };
    
    virtual void trigger() override;
    virtual void cancel() override;
    
private:
    int _scriptHandler;
};

#endif

//
// Scheduler
//
struct _listEntry;
struct _hashSelectorEntry;
struct _hashUpdateEntry;

#if CC_ENABLE_SCRIPT_BINDING
class SchedulerScriptHandlerEntry;
#endif

/** @brief Scheduler负责触发已被调度的回调函数
你不应该在你的游戏逻辑中使用系统的计时器. 而是应该使用这个类.

有两种类型的回调函数 (selector(选择器) ):

- update 选择器会在每帧被调用. 你能够设定其优先级.
- custom 选择器会在每帧调用，或者在一个设定的时间间隔到来时调用

应该尽量避免使用'custom selectors'. 使用'update selector'更加快，且消耗的内存更少.

*/
class CC_DLL Scheduler : public Ref
{
public:
    // Priority level reserved for system services.
    static const int PRIORITY_SYSTEM;
    
    // Minimum priority level for user scheduling.
    static const int PRIORITY_NON_SYSTEM_MIN;
    /**
     * @js ctor
     */
    Scheduler();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Scheduler();

    inline float getTimeScale() { return _timeScale; }
	
	/** 改变所有被调度的回调函数的时间.
    你可以使用这个属性来创建一个'慢镜头'或者'快进'的效果.
    默认值是1.0. 使用低于1.0的值来创建一个'慢镜头'的效果.
    要创建一个'快进'的效果, 使用大于1.0的值.
    @since v0.8
    @warning 它将影响每一个被调度的选择器(selector) / 动作(action).
    */
    inline void setTimeScale(float timeScale) { _timeScale = timeScale; }

	/** 'update' 调度器.
     你永远不应该调用这个方法,除非你知道自己在做什么.
     * @js NA
     * @lua NA
     */
    void update(float dt);

    /////////////////////////////////////
    
    // schedule
    
	/** 被调度的方法会在每一个时间间隔'interval'指定的秒数到来时调用.
     如果被调度的方式处于暂停状态，那么只有在它恢复之后才能被调用.
     如果时间间隔'interval'是0, 它会在每帧被调用, 如果是这样, 推荐使用'scheduleUpdate'函数代替.
     如果回调函数'callback'已经被调度,那么函数只会更新参数interval,不会再次重复调度.
     repeat 让动作重复执行repeat + 1次, 如果想让动作持续执行可以使用kRepeatForever
     delay 表示函数被调用之前等待的时间值
     @param key 标识回调的key
     @since v3.0
     */
    void schedule(const ccSchedulerFunc& callback, void *target, float interval, unsigned int repeat, float delay, bool paused, const std::string& key);

	/** 通过参数kRepeatForever和0时延调用scheduleCallback函数
     @since v3.0
     */
    void schedule(const ccSchedulerFunc& callback, void *target, float interval, bool paused, const std::string& key);
    
    
	/** 已被调度的方法将在每个时间间隔'interval'设定的秒数到来时调用.
     如果被调度的方法是暂停状态, 那么直到它被恢复才能被调用.
     如果时间间隔'interval'是0,它会在每帧调用,但是这种情况推荐使用'scheduleUpdate'替换.
     若果selector已经被调度,那么只有参数interval会被更新,并不会再次重新调度
     repeat 让动作重复执行 repeat + 1 次, 如果想让动作持续不停的执行，使用kRepeatForever
     delay 表示函数被调用之前等待的时间量
     
     @since v3.0, 参数repeat和delay在版本1.1加入
     */
    void schedule(SEL_SCHEDULE selector, Ref *target, float interval, unsigned int repeat, float delay, bool paused);
    
    /** 通过参数kRepeatForever和0时延调用scheduleSelector */
    void schedule(SEL_SCHEDULE selector, Ref *target, float interval, bool paused);
    
	/** 通过给定的优先级在目标上调用'update' 选择器(selector).
     'update' selector 会在每帧被调用.
     优先级越低，越容易被调用.
     @since v3.0
     @lua NA
     */
    template <class T>
    void scheduleUpdate(T *target, int priority, bool paused)
    {
        this->schedulePerFrame([target](float dt){
            target->update(dt);
        }, target, priority, paused);
    }

#if CC_ENABLE_SCRIPT_BINDING
    // schedule for script bindings
	/** 已被调度的脚本回调函数会在每个时间间隔'interval'指定的秒数到来时调用.
     如果脚本回调被设置为暂停,那么在它被恢复之前是不会被调用的.
     如果'interval'等于0, 它会在每帧被调用.
     返回调度脚本条目的ID, 这个ID可以在函数unscheduleScriptFunc()中使用.
     */
    unsigned int scheduleScriptFunc(unsigned int handler, float interval, bool paused);
#endif
    /////////////////////////////////////
    
    // unschedule

	/** 在给定的key和target上撤销对回调函数的调度.
     如果你想撤销调度'callbackPerFrame', 使用unscheduleUpdate函数.
     @since v3.0
     */
    void unschedule(const std::string& key, void *target);

	/** 在给定目标上撤销调度selector.
     如果你想撤销调度 "update", 使用unscheudleUpdate函数.
     @since v3.0
     */
    void unschedule(SEL_SCHEDULE selector, Ref *target);
    
	/** 在给定的目标上撤销update selector调度
     @since v0.99.3
     */
    void unscheduleUpdate(void *target);
    
	/** 撤销给定目标上的所有selector调度.
     包括"update" selector.
     @since v0.99.3
     @js  unscheduleCallbackForTarget
     @lua NA
     */
    void unscheduleAllForTarget(void *target);
    
	/** 撤销所有目标上的所有selector(选择器).
     你永远不应该调用这个方法,除非你知道自己在做什么.
     @since v0.99.3
     */
    void unscheduleAll(void);
    
	/** 以最低的优先级撤销所有目标上的所有selector的调度.
     调用这个函数时你应当只使用kPriorityNonSystemMin或者更高一点的优先级.
     @since v2.0.0
     */
    void unscheduleAllWithMinPriority(int minPriority);
    
#if CC_ENABLE_SCRIPT_BINDING
    /** 取消对一个脚本条目的调度. */
    void unscheduleScriptEntry(unsigned int scheduleScriptEntryID);
#endif
    
    /////////////////////////////////////
    
    // isScheduled
    
	 /** 检查一个关联到'key'和'target'的回调是否被调度.
     @since v3.0.0
     */
    bool isScheduled(const std::string& key, void *target);
    
	 /** 检查给定目标上的一个selector(选择器)是否被调度.
     @since v3.0
     */
    bool isScheduled(SEL_SCHEDULE selector, Ref *target);
    
    /////////////////////////////////////
    
	 /** 暂停目标.
     在给定目标上的所有被调度的selector/update不会被即时执行，直到这个目标被恢复
     如果目标不存在,什么事情都不做.
     @since v0.99.3
     */
    void pauseTarget(void *target);

	 /** 恢复目标.
     目标'target' 会被恢复, 这样所有调度的selector/update将会重新记时执行.
     如果目标不存在,什么事情都不做.
     @since v0.99.3
     */
    void resumeTarget(void *target);


	/** 返回目标是否被暂停
    @since v1.0.0
    * In js: var isTargetPaused(var jsObject)
    * @lua NA 
    */
    bool isTargetPaused(void *target);

	/** 在所有的目标上暂停所有的selector(选择器).
       你永远不应该调用这个方法,除非你知道自己在做什么.
     @since v2.0.0
      */
    std::set<void*> pauseAllTargets();

	/** 以最低的优先级在所有的目标上暂停所有的selector(选择器).
      你只应该用kPriorityNonSystemMin或者更高的优先级来调用此函数.
      @since v2.0.0
      */
    std::set<void*> pauseAllTargetsWithMinPriority(int minPriority);

	/** 在一个目标集合中恢复selector.
     这个函数可以用来取消对pauseAllSelectors的调用.
     @since v2.0.0
      */
    void resumeTargets(const std::set<void*>& targetsToResume);

	 /** 在cocos2d线程中调用方法. 当你需要在另外一个线程中调用一个cocos2d函数时有用.
     这个方法是线程安全的.
     @since v3.0
     */
    void performFunctionInCocosThread( const std::function<void()> &function);
    
    /////////////////////////////////////
    
    // Deprecated methods:
    
	/** 被调度的方法将在每个时间间隔'interval'指定的秒数到来时调用.
     如果脚本回调被设置为暂停,那么在它被恢复之前是不会被调用的.
     如果时间间隔'interval'是0,它会在每帧调用,但是这种情况推荐使用'scheduleUpdate'替换..
     若果selector已经被调度,那么只有参数interval会被更新,并不会再次重新调度.
     repeat 让动作重复执行repeat + 1次, 如果想让动作持续执行可以使用kRepeatForever
     delay 表示函数被调用之前等待的时间量
     @deprecated 请使用'Scheduler::schedule'代替此方法.
     @since v0.99.3, 参数repeat和delay在版本v1.1中加入
     */
    CC_DEPRECATED_ATTRIBUTE void scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, unsigned int repeat, float delay, bool paused)
    {
        schedule(selector, target, interval, repeat, delay, paused);
    };
    
	/** 通过参数kRepeatForever和0延时调用scheduleSelector
     *  @deprecated 请使用'Scheduler::schedule'代替此方法.
     */
    CC_DEPRECATED_ATTRIBUTE void scheduleSelector(SEL_SCHEDULE selector, Ref *target, float interval, bool paused)
    {
        schedule(selector, target, interval, paused);
    };
    
	/** 在指定的目标上以指定的优先级调度'update' selector.
     'update' selector会在每帧调用.
     优先级越低，越容易被调度.
     @deprecated 请使用'Scheduler::scheduleUpdate'代替此方法.
     @since v0.99.3
     */
    template <class T>
    CC_DEPRECATED_ATTRIBUTE void scheduleUpdateForTarget(T* target, int priority, bool paused) { scheduleUpdate(target, priority, paused); };
    
	 /** 在给定目标上取消调度selector.
     如果你想取消调度 "update", 使用 unscheudleUpdateForTarget.
     @deprecated 请使用'Scheduler::unschedule'代替此方法.
     @since v0.99.3
     */
    CC_DEPRECATED_ATTRIBUTE void unscheduleSelector(SEL_SCHEDULE selector, Ref *target) { unschedule(selector, target); };
    
	 /** 检查在一个selector(选择器)是否在给定的target上被调度.
     @deprecated 请使用'Scheduler::isScheduled'代替此方法.
     @since v0.99.3
     */
    CC_DEPRECATED_ATTRIBUTE bool isScheduledForTarget(Ref *target, SEL_SCHEDULE selector) { return isScheduled(selector, target); };
    
	 /** 在指定的目标上取消调度update选择器
     @deprecated 请使用'Scheduler::unscheduleUpdate'代替此方法.
     @since v0.99.3
     */
    CC_DEPRECATED_ATTRIBUTE void unscheduleUpdateForTarget(Ref *target) { return unscheduleUpdate(target); };
    
protected:
    
	 /** 在给定的目标上以给定的优先级调度'callback'函数.
     'callback' selector(选择器)会在每帧调用.
     优先级越低,越容易被调用.
     @note 这个方法只在内部使用.
     @since v3.0
     */
    void schedulePerFrame(const ccSchedulerFunc& callback, void *target, int priority, bool paused);
    
    void removeHashElement(struct _hashSelectorEntry *element);
    void removeUpdateFromHash(struct _listEntry *entry);

    // update specific

    void priorityIn(struct _listEntry **list, const ccSchedulerFunc& callback, void *target, int priority, bool paused);
    void appendIn(struct _listEntry **list, const ccSchedulerFunc& callback, void *target, bool paused);


    float _timeScale;

    //
    // "updates with priority" stuff
    //
    struct _listEntry *_updatesNegList;        // list of priority < 0
    struct _listEntry *_updates0List;            // list priority == 0
    struct _listEntry *_updatesPosList;        // list priority > 0
    struct _hashUpdateEntry *_hashForUpdates; // hash used to fetch quickly the list entries for pause,delete,etc

    // Used for "selectors with interval"
    struct _hashSelectorEntry *_hashForTimers;
    struct _hashSelectorEntry *_currentTarget;
    bool _currentTargetSalvaged;
    // If true unschedule will not remove anything from a hash. Elements will only be marked for deletion.
    bool _updateHashLocked;
    
#if CC_ENABLE_SCRIPT_BINDING
    Vector<SchedulerScriptHandlerEntry*> _scriptHandlerEntries;
#endif
    
    // Used for "perform Function"
    std::vector<std::function<void()>> _functionsToPerform;
    std::mutex _performMutex;
};

// end of global group
/// @}

NS_CC_END

#endif // __CCSCHEDULER_H__
