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

#ifndef __cocos2d_libs__CCCustomEventListener__
#define __cocos2d_libs__CCCustomEventListener__

#include "base/CCEventListener.h"

NS_CC_BEGIN

class EventCustom;

/**
 *  用法:
 *        auto dispatcher = Director::getInstance()->getEventDispatcher();
 *     添加一个监听器:
 *
 *        auto callback = [](EventCustom* event){ do_some_thing(); };
 *        auto listener = EventListenerCustom::create(callback);
 *        dispatcher->addEventListenerWithSceneGraphPriority(listener, one_node);
 *
 *     派发一个自定义事件:
 *
 *        EventCustom event("your_event_type");
 *        dispatcher->dispatchEvent(&event);
 *
 *     移除一个监听器
 *
 *        dispatcher->removeEventListener(listener);
 */
class EventListenerCustom : public EventListener
{
public:
    /** 指定事件类型和回调函数创建一个事件监听器.
     *  @param eventType 事件类型.
     *  @param callback 特定的事件被触发时执行该回调函数.
     */
    static EventListenerCustom* create(const std::string& eventName, const std::function<void(EventCustom*)>& callback);
    
    /// 重写
    virtual bool checkAvailable() override;
    virtual EventListenerCustom* clone() override;
    
CC_CONSTRUCTOR_ACCESS:
    /** 构造函数 */
    EventListenerCustom();
    
    /** 指定事件类型和回调函数初始化事件监听器 */
    bool init(const ListenerID& listenerId, const std::function<void(EventCustom*)>& callback);
    
protected:
    std::function<void(EventCustom*)> _onCustomEvent;
    
    friend class LuaEventListenerCustom;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCCustomEventListener__) */
