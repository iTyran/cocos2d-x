/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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

#ifndef __CCREF_H__
#define __CCREF_H__

#include "base/CCPlatformMacros.h"
#include "base/ccConfig.h"

#define CC_USE_MEM_LEAK_DETECTION 0

NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

class Ref;

/** 如何克隆一个Ref对象的接口定义 */
class CC_DLL Clonable
{
public:
    /** 返回Ref对象的一份拷贝 */
    virtual Clonable* clone() const = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Clonable() {};

    /** 返回Ref对象的一份拷贝.
     * @deprecated 使用 clone() 替代
     */
    CC_DEPRECATED_ATTRIBUTE Ref* copy() const
    {
        // 使用 "clone" 替代
        CC_ASSERT(false);
        return nullptr;
    }
};

class CC_DLL Ref
{
public:
    /**
     * 保留所有权.
     *
     * 该方法会增加Ref对象的引用计数.
     *
     * @see release, autorelease
     * @js NA
     */
    void retain();

    /**
     * 立即释放所有权.
     *
     * 该方法会减少Ref对象的引用计数.
     *
     * 如果引用计数被减少到0,该Ref对象将被销毁.
     *
     * @see retain, autorelease
     * @js NA
     */
    void release();

    /**
     * 自动释放所有权在不久的将来.
     *
     * 结束当前pool池时,减少Ref对象的引用计数
     *
     * 如果引用计数被减少到0,该Ref对象将被销毁.
     *
     * @returns 返回Ref对象自己.
     *
     * @see AutoreleasePool, retain, release
     * @js NA
     * @lua NA
     */
    Ref* autorelease();

    /**
     *返回Ref对象当前的引用计数.
     *
     * @returns 返回Ref对象的引用计数.
     * @js NA
     */
    unsigned int getReferenceCount() const;

protected:
    /**
     * 构造函数
     *
     * 构造完成后,Ref对象的引用计数为1.
     * @js NA
     */
    Ref();

public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Ref();

protected:
    ///引用计数
    unsigned int _referenceCount;

    friend class AutoreleasePool;

#if CC_ENABLE_SCRIPT_BINDING
public:
    /// 对象 id, 脚本支持需要 public _ID
    unsigned int        _ID;
    /// Lua 引用 id
    int                 _luaID;
#endif

    // 内存泄漏诊断数据 (仅包括 CC_USE_MEM_LEAK_DETECTION被定义且值不为0)
#if CC_USE_MEM_LEAK_DETECTION
public:
    static void printLeaks();
#endif
};

class Node;

typedef void (Ref::*SEL_CallFunc)();
typedef void (Ref::*SEL_CallFuncN)(Node*);
typedef void (Ref::*SEL_CallFuncND)(Node*, void*);
typedef void (Ref::*SEL_CallFuncO)(Ref*);
typedef void (Ref::*SEL_MenuHandler)(Ref*);
typedef void (Ref::*SEL_SCHEDULE)(float);

#define callfunc_selector(_SELECTOR) static_cast<cocos2d::SEL_CallFunc>(&_SELECTOR)
#define callfuncN_selector(_SELECTOR) static_cast<cocos2d::SEL_CallFuncN>(&_SELECTOR)
#define callfuncND_selector(_SELECTOR) static_cast<cocos2d::SEL_CallFuncND>(&_SELECTOR)
#define callfuncO_selector(_SELECTOR) static_cast<cocos2d::SEL_CallFuncO>(&_SELECTOR)
#define menu_selector(_SELECTOR) static_cast<cocos2d::SEL_MenuHandler>(&_SELECTOR)
#define schedule_selector(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)

// end of base_nodes group
/// @}

NS_CC_END

#endif // __CCREF_H__
