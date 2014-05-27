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


#ifndef __CCEVENT_H__
#define __CCEVENT_H__

#include <string>
#include <stdint.h>

#include "base/CCRef.h"
#include "base/CCPlatformMacros.h"

NS_CC_BEGIN

class Node;

/**
 *   Base class of all kinds of events.
 */
class Event : public Ref
{
public:
    enum class Type
    {
        TOUCH,
        KEYBOARD,
        ACCELERATION,
        MOUSE,
        FOCUS,
        CUSTOM
    };
    
protected:
    /** 构造函数 */
    Event(Type type);
public:
    /** 析构函数 */
    virtual ~Event();

    /** 获取事件类型 */
	inline Type getType() const { return _type; };
    
    /** 停止当前事件传播 */
    inline void stopPropagation() { _isStopped = true; };
    
    /** 检查指定事件是否已经停止 */
    inline bool isStopped() const { return _isStopped; };
    
    /** @brief  获取事件的当前目标
     *  @return 返回与指定事件相关的目标
     *  @note   只有当事件侦听器与节点相关联时可用
     *          当侦听器与一个固定优先级相关联时返回0 
     */
    inline Node* getCurrentTarget() { return _currentTarget; };
    
protected:
    /** 设置当前目标 */
    inline void setCurrentTarget(Node* target) { _currentTarget = target; };
    
	Type _type;     ///< 事件类型
    
    bool _isStopped;       ///< 事件是否已经停止.
    Node* _currentTarget;  ///< 当前目标
    
    friend class EventDispatcher;
};

NS_CC_END


#endif // __CCEVENT_H__
