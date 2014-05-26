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

#ifndef __cocos2d_libs__CCCustomEvent__
#define __cocos2d_libs__CCCustomEvent__

#include "base/CCEvent.h"

NS_CC_BEGIN

class EventCustom : public Event
{
public:
    /** 构造函数 */
    EventCustom(const std::string& eventName);
    
    /** 设置用户数据 */
    inline void setUserData(void* data) { _userData = data; };
    
    /** 获取用户数据 */
    inline void* getUserData() const { return _userData; };
    
    /** 获取事件名称 */
    inline const std::string& getEventName() const { return _eventName; };
protected:
    void* _userData;       ///< 用户数据
    std::string _eventName;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCCustomEvent__) */
