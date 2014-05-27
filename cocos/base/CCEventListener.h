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

#ifndef __CCEVENTLISTENER_H__
#define __CCEVENTLISTENER_H__

#include "base/CCPlatformMacros.h"
#include "base/CCRef.h"

#include <functional>
#include <string>
#include <memory>
#include <set>

NS_CC_BEGIN

class Event;
class Node;

/**
 *  事件监听器( event listener)的基类.
 *  如果你需要使用不同的回调自定义监听时，你需要继承这个类
 *  例如你可以参考 AccelerationEventListener, KeyboardEventListener or TouchEventListener, CustomEventListener.
 */
class EventListener : public Ref
{
public:
    enum class Type
    {
        UNKNOWN,
        TOUCH_ONE_BY_ONE,
        TOUCH_ALL_AT_ONCE,
        KEYBOARD,
        MOUSE,
        ACCELERATION,
        FOCUS,
        CUSTOM
    };

    typedef std::string ListenerID;

protected:
    /** 构造函数 */
    EventListener();

    /**使用 事件类型和回调函数 初始化事件 */
    bool init(Type t, const ListenerID& listenerID, const std::function<void(Event*)>& callback);
public:
    /** 析构函数 */
    virtual ~EventListener();

    /** 检查监听器(listener)是否可用. */
    virtual bool checkAvailable() = 0;

    /** 克隆监听器(listener)，它的子类必须重写此. */
    virtual EventListener* clone() = 0;

    /** 启用或禁用监听器(listener)
     *  @note 仅当监听器"启用"(`enabled`)状态才能接收到事件.
     *        当一个监听器初始化后，它默认是启用的.
     *        当一个监听器处于启用状态且没被暂停，它可以收到事件.
     *        暂停状态时总是false的，当它是一个固定优先级的侦听器.
     */
    inline void setEnabled(bool enabled) { _isEnabled = enabled; };

    /** 检查监听器是否可用 */
    inline bool isEnabled() const { return _isEnabled; };

protected:

    /** 设置监听器的暂停状态
     *  暂停状态仅被用于场景图像优先级监听器.
     *  `EventDispatcher::resumeAllEventListenersForTarget(node)` 将会设置暂停状态为 `true`,
     *  然而 `EventDispatcher::pauseAllEventListenersForTarget(node)` 将会设置暂停状态为 `false`.
     *  @note 1) 固定优先级的监听器不会有暂停.  如果个一个固定优先级的监听器不想接收事件,调用
     *           `setEnabled(false)` 代替.
     *        2) 在节点(`Node`)的 onEnter 和 onExit 方法中, 和暂停状态的监听器  关联的节点将会自动更新.
     */
    inline void setPaused(bool paused) { _paused = paused; };

    /** 检查监听器是否被暂停 */
    inline bool isPaused() const { return _paused; };

    /** 标记监听器已经被加入到事件派发器(EventDispatcher) */
    inline void setRegistered(bool registered) { _isRegistered = registered; };

    /** 检查监听器是否被注册到事件派发器(EventDispatcher) */
    inline bool isRegistered() const { return _isRegistered; };

    /**获取监听器(listener)的类型
     *  @note 它不同于`EventType`, 例如. TouchEvent有两种事件监听器 - EventListenerOneByOne, EventListenerAllAtOnce
     */
    inline Type getType() const { return _type; };

    /** 获取监听器的ID 
     *  当事件派发,监听器ID是用于查找符合事件类型的监听器的关键字.
     */
    inline const ListenerID& getListenerID() const { return _listenerID; };

    /** 为监听器设置固定优先级
     *  @note 此方法仅用于 `fixed priority listeners`, 它需要传人一个非零(non-zero)值.
     *  0 被保留用于场景图像监听器的优先级
     */
    inline void setFixedPriority(int fixedPriority) { _fixedPriority = fixedPriority; };

    /** 获取监听器的优先级
     *  @return 如果是场景图像监听器则返回0,其他固定优先级的监听器返回非零(non-zero)值
     */
    inline int getFixedPriority() const { return _fixedPriority; };

    /**设置和监听器关联的节点 */
    inline void setAssociatedNode(Node* node) { _node = node; };

    /** 获取和监听器关联的节点
     *  @return 如果是固定优先级的监听器则返回空指针(nullptr),否则返回非空指针(non-nullptr)
     */
    inline Node* getAssociatedNode() const { return _node; };

    ///////////////
    // Properties
    //////////////
    std::function<void(Event*)> _onEvent;   /// 事件回调函数

    Type _type;                             /// Event listener 事件监听器的类型
    ListenerID _listenerID;                 /// Event listener 事件监听器的ID
    bool _isRegistered;                     /// 监听器(listener)是否被加入到派发器(dispatcher) .

    int   _fixedPriority;   // 数值越高，优先级越高. 0 是场景图像的基础优先级.
    Node* _node;            // 事件监听器关联的节点
    bool _paused;           // 监听器是否暂停
    bool _isEnabled;        // 监听器是否启用
    friend class EventDispatcher;
};

NS_CC_END

#endif // __CCEVENTLISTENER_H__
