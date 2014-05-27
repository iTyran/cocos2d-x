/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __SCRIPT_SUPPORT_H__
#define __SCRIPT_SUPPORT_H__

#include "base/ccConfig.h"
#if CC_ENABLE_SCRIPT_BINDING

#include "2d/platform/CCCommon.h"
#include "base/CCTouch.h"
#include "base/CCEventTouch.h"
#include "base/CCEventKeyboard.h"
#include <map>
#include <string>
#include <list>

typedef struct lua_State lua_State;

NS_CC_BEGIN

class TimerScriptHandler;
class Layer;
class MenuItem;
class CallFunc;
class Acceleration;

enum ccScriptType {
    kScriptTypeNone = 0,
    kScriptTypeLua,
    kScriptTypeJavascript
};

class ScriptHandlerEntry : public Ref
{
public:
    static ScriptHandlerEntry* create(int handler);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ScriptHandlerEntry();
    
    int getHandler(void) {
        return _handler;
    }
    
    int getEntryId(void) {
        return _entryId;
    }
    
protected:
    ScriptHandlerEntry(int handler)
    : _handler(handler)
    {
        static int newEntryId = 0;
        newEntryId++;
        _entryId = newEntryId;
    }
    
    int _handler;
    int _entryId;
};

/**
 * @addtogroup script_support
 * @{
 */

class SchedulerScriptHandlerEntry : public ScriptHandlerEntry
{
public:
    // nHandler 由tolua_ref_function()函数返回，在LuaCocos2d.cpp中调用
    /**
     * @js NA
     * @lua NA
     */
    static SchedulerScriptHandlerEntry* create(int handler, float interval, bool paused);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SchedulerScriptHandlerEntry();
    /**
     * @js NA
     * @lua NA
     */
    TimerScriptHandler* getTimer(void) {
        return _timer;
    }
    /**
     * @js NA
     * @lua NA
     */
    bool isPaused(void) {
        return _paused;
    }
    /**
     * @js NA
     * @lua NA
     */
    void markedForDeletion(void) {
        _markedForDeletion = true;
    }
    /**
     * @js NA
     * @lua NA
     */
    bool isMarkedForDeletion(void) {
        return _markedForDeletion;
    }
    
private:
    SchedulerScriptHandlerEntry(int handler)
    : ScriptHandlerEntry(handler)
    , _timer(nullptr)
    , _paused(false)
    , _markedForDeletion(false)
    {
    }
    bool init(float interval, bool paused);
    
    TimerScriptHandler*   _timer;
    bool                _paused;
    bool                _markedForDeletion;
};



class TouchScriptHandlerEntry : public ScriptHandlerEntry
{
public:
    /**
     * @js NA
     * @lua NA
     */
    static TouchScriptHandlerEntry* create(int handler, bool isMultiTouches, int priority, bool swallowsTouches);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TouchScriptHandlerEntry();
    /**
     * @js NA
     * @lua NA
     */
    bool isMultiTouches(void) {
        return _isMultiTouches;
    }
    /**
     * @js NA
     * @lua NA
     */
    int getPriority(void) {
        return _priority;
    }
    /**
     * @js NA
     * @lua NA
     */
    bool getSwallowsTouches(void) {
        return _swallowsTouches;
    }
    
private:
    TouchScriptHandlerEntry(int handler)
    : ScriptHandlerEntry(handler)
    , _isMultiTouches(false)
    , _priority(0)
    , _swallowsTouches(false)
    {
    }
    bool init(bool isMultiTouches, int priority, bool swallowsTouches);
    
    bool    _isMultiTouches;
    int     _priority;
    bool    _swallowsTouches;
};

enum ScriptEventType
{
    kNodeEvent = 0,
    kMenuClickedEvent,
    kCallFuncEvent,
    kScheduleEvent,
    kTouchEvent,
    kTouchesEvent,
    kKeypadEvent,
    kAccelerometerEvent,
    kControlEvent,
    kCommonEvent,
    kComponentEvent
};

struct BasicScriptData
{
    // nativeobject:为lua获得句柄(handler)或者为js获得js对象(jsobject)
    void* nativeObject;
    // value: 一个指向已定义对象的指针
    void* value;
    
    // 构造函数
    /**
     * @js NA
     * @lua NA
     */
    BasicScriptData(void* inObject,void* inValue = nullptr)
    : nativeObject(inObject),value(inValue)
    {
    }
};

struct SchedulerScriptData
{
    // lua 使用
    int handler;
    float elapse;
    // js 使用
    void* node;
    
    // 构造函数
    /**
     * @js NA
     * @lua NA
     */
    SchedulerScriptData(int inHandler,float inElapse,void* inNode = nullptr)
    : handler(inHandler),
      elapse(inElapse),
      node(inNode)
    {
    }
};

struct TouchesScriptData
{
    EventTouch::EventCode actionType;
    void* nativeObject;
    const std::vector<Touch*>& touches;
    Event* event;
    
    // 构造函数
    /**
     * @js NA
     * @lua NA
     */
    TouchesScriptData(EventTouch::EventCode inActionType, void* inNativeObject, const std::vector<Touch*>& inTouches, Event* evt)
    : actionType(inActionType),
      nativeObject(inNativeObject),
      touches(inTouches),
      event(evt)
    {
    }
};

struct TouchScriptData
{
    EventTouch::EventCode actionType;
    void* nativeObject;
    Touch* touch;
    Event* event;
    
    // 构造函数
    /**
     * @js NA
     * @lua NA
     */
    TouchScriptData(EventTouch::EventCode inActionType, void* inNativeObject, Touch* inTouch, Event* evt)
    : actionType(inActionType),
      nativeObject(inNativeObject),
      touch(inTouch),
      event(evt)
    {
    }
};

struct KeypadScriptData
{
    EventKeyboard::KeyCode actionType;
    void* nativeObject;
    
    // 构造函数
    /**
     * @js NA
     * @lua NA
     */
    KeypadScriptData(EventKeyboard::KeyCode inActionType,void* inNativeObject)
    : actionType(inActionType),nativeObject(inNativeObject)
    {
    }
};

struct CommonScriptData
{
    // 现在这个结构体只应用于Lua绑定(LuaBinding).
    int handler;
    char eventName[64];
    Ref* eventSource;
    char eventSourceClassName[64];
    
    // 构造函数
    /**
     * @js NA
     * @lua NA
     */
    CommonScriptData(int inHandler,const char* inName, Ref* inSource = nullptr,const char* inClassName = nullptr)
    : handler(inHandler),
      eventSource(inSource)
    {
        strncpy(eventName, inName, 64);
        
        if (nullptr == inClassName)
        {
            memset(eventSourceClassName, 0, 64*sizeof(char));
        }
        else
        {
            strncpy(eventSourceClassName, inClassName, 64);
        }
    }
};

struct ScriptEvent
{
    ScriptEventType type;
    void* data;
    
    // 构造函数
    /**
     * @js NA
     * @lua NA
     */
    ScriptEvent(ScriptEventType inType,void* inData)
    : type(inType),
      data(inData)
    {
    }
};

// 不要从对象中继承ScriptEngineProtocol，因为setScriptEngine只在AppDelegate.cpp中调用一次
// 这么做会影响脚本核心(ScriptCore)实例的生命周期，自动释放池会在脚本核心(ScriptCore)析构之前被销毁。
// 这样的话如果你点击关闭按钮程序会发生崩溃
class CC_DLL ScriptEngineProtocol
{
public:
    ScriptEngineProtocol()
    {};
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ScriptEngineProtocol() {};
    
    /** 获得脚本类型
     * @js NA
     * @lua NA
     */
    virtual ccScriptType getScriptType() { return kScriptTypeNone; };

    /** 移除脚本对象.
     * @js NA
     * @lua NA
     */
    virtual void removeScriptObjectByObject(Ref* obj) = 0;
    
    /** 移除脚本函数句柄，只有Lua引擎类需要实现这个函数
     * @js NA
     * @lua NA
     */
    virtual void removeScriptHandler(int handler) {};
    
    /** 重新分配函数句柄，只有Lua引擎类需要实现这个函数
     * @js NA
     * @lua NA
     */
    virtual int reallocateScriptHandler(int handler) { return 0;}
    
    /**
     @brief         执行给定字符串中包含的脚本代码
     @param         参数codes持有应该被执行的有效的脚本代码
     @return        如果字符串执行正确返回 0.
     @return        如果字符串执行错误返回其它
     * @js NA
     * @lua NA
     */
    virtual int executeString(const char* codes) = 0;
    
    /**
     @brief  执行一个脚本文件。
     @param  参数filename是字符串对象，持有需要被执行的脚本文件的文件名
     * @js NA
     * @lua NA
     */
    virtual int executeScriptFile(const char* filename) = 0;
    
    /**
     @brief   执行一个脚本全局函数
     @brief   该函数不应该带任何参数，应该返回一个整型值
     @param   要执行的函数包含在全局脚本环境中，参数functionName持有该函数的函数名
     @return  该全局脚本函数返回整型值
     * @js NA
     * @lua NA
     */
    virtual int executeGlobalFunction(const char* functionName) = 0;
    
     /** 当触发一个脚本时调用这个函数，在ScriptEvent对象中添加需要的参数。 nativeObject是触发该事件的对象，在lua中可以是置空指针(nullptr)
     * @js NA
     * @lua NA
     */
    virtual int sendEvent(ScriptEvent* evt) = 0;
    
    /** 被CCAssert调用，用来允许脚本引擎处理失败的断言
     * @return  如果断言(assert)被脚本引擎处理则返回true，否则返回false。
     * @js NA
     * @lua NA
     */
    virtual bool handleAssert(const char *msg) = 0;
    
    virtual void setCalledFromScript(bool callFromScript) { CC_UNUSED_PARAM(callFromScript); };
    virtual bool isCalledFromScript() { return false; };
    
    enum class ConfigType
    {
        NONE,
        COCOSTUDIO
    };
    
    /** 解析配置文件 */
    virtual bool parseConfig(ConfigType type, const std::string& str) = 0;
};

/**
 ScriptEngineManager是一个单例(singleton)，它持有ScriptEngineProtocl的一个对象实例
 ScriptEngineManager帮助cocos2d-x和用户代码获得和返回Lua引擎(LuaEngine)对象
 @since v0.99.5-x-0.8.5
 */
class CC_DLL ScriptEngineManager
{
public:
    /**
     * @js NA
     * @lua NA
     */
    ~ScriptEngineManager(void);
    /**
     * @js NA
     * @lua NA
     */
    ScriptEngineProtocol* getScriptEngine(void) {
        return _scriptEngine;
    }
    /**
     * @js NA
     * @lua NA
     */
    void setScriptEngine(ScriptEngineProtocol *scriptEngine);
    /**
     * @js NA
     * @lua NA
     */
    void removeScriptEngine(void);
    /**
     * @js NA
     * @lua NA
     */
    static ScriptEngineManager* getInstance();
    /**
     * @js NA
     * @lua NA
     */
    static void destroyInstance();
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static ScriptEngineManager* sharedManager() { return ScriptEngineManager::getInstance(); };
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedManager() { ScriptEngineManager::destroyInstance(); };
    
private:
    ScriptEngineManager(void)
    : _scriptEngine(nullptr)
    {
    }
    
    ScriptEngineProtocol *_scriptEngine;
};

// end of script_support group
/// @}

NS_CC_END

#endif // #if CC_ENABLE_SCRIPT_BINDING

#endif // __SCRIPT_SUPPORT_H__
