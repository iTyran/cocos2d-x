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

#ifndef __CC_EVENT_DISPATCHER_H__
#define __CC_EVENT_DISPATCHER_H__

#include "base/CCPlatformMacros.h"
#include "base/CCEventListener.h"
#include "base/CCEvent.h"
#include "CCStdC.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <list>
#include <vector>

NS_CC_BEGIN

class Event;
class EventTouch;
class Node;
class EventCustom;
class EventListenerCustom;

/**
这个类管理事件侦听器的订阅和事件的分发

 
事件侦听器列表以这样的方式来进行管理：当事件正在分发的过程中，事件侦听器可以被添加或者移除，包括事件侦听器内部的侦听器
*/
class EventDispatcher : public Ref
{
public:
    // 添加事件侦听器  Adds event listener
    
    /** 给一个指定的事件添加一个事件侦听器，该侦听器带有基于场景图的优先级 .
     *  @param listener 指定事件的侦听器.
     *  @param node     侦听器的优先级基于此节点的绘制顺序.
     *  @note  场景图的优先级会被设置为固定值0，因此在容器(vector)中的侦听器的次序将会是：' <0, scene graph (0 priority), >0' .
     */
    void addEventListenerWithSceneGraphPriority(EventListener* listener, Node* node);

    /** 给一个事件添加一个固定优先级的时间侦听器.
     *  @param listener        给定事件的侦听器
     *  @param fixedPriority   侦听器的固定优先级.
     *  @note  低优先级的侦听器在高优先级的侦听器之前被调用
     *        0用来作为场景图的基础优先级，禁止被设置为一个固定优先级值
     */
    void addEventListenerWithFixedPriority(EventListener* listener, int fixedPriority);

    /** 添加一个自定义事件侦听器.
     该侦听器会使用值为1的一个固定优先级.
     @return  返回产生的事件，需要返回值以便从调度程序中移除这个事件
     */
    EventListenerCustom* addCustomEventListener(const std::string &eventName, const std::function<void(EventCustom*)>& callback);

    /////////////////////////////////////////////
    
    // 移除事件侦听器
    
    /** 移除一个侦听器
     *  @param listener  需要被移除的指定事件侦听器.
     */
    void removeEventListener(EventListener* listener);

    /** 移除所有使用相同事件侦听器类型的侦听器 */
    void removeEventListenersForType(EventListener::Type listenerType);

    /** 移除所有与指定目标相关联的侦听器 */
    void removeEventListenersForTarget(Node* target, bool recursive = false);
    
    /** 移除所有使用相同事件名称的自定义侦听器 */
    void removeCustomEventListeners(const std::string& customEventName);

    /** 移除所有侦听器 */
    void removeAllEventListeners();

    /////////////////////////////////////////////
    
    // 暂停/恢复事件侦听器
    
    /** 暂停所有与指定目标相关联的侦听器. */
    void pauseEventListenersForTarget(Node* target, bool recursive = false);
    
    /** 恢复所有与指定目标相关联的侦听器. */
    void resumeEventListenersForTarget(Node* target, bool recursive = false);
    
    /////////////////////////////////////////////
    
    /** 设置侦听器的优先级为固定值. */
    void setPriority(EventListener* listener, int fixedPriority);

    /** 是否启用调度事件 */
    void setEnabled(bool isEnabled);

    /** 检查是否启用了调度事件 */
    bool isEnabled() const;

    /////////////////////////////////////////////
    
    /** 事件分发
     *  还移除在事件分发列表中所有标记为删除的事件侦听器
     */
    void dispatchEvent(Event* event);

    /** 分发一个带有事件名称和可选用户数据的自定义事件 */
    void dispatchCustomEvent(const std::string &eventName, void *optionalUserData = nullptr);

    /////////////////////////////////////////////
    
    /** 事件调度类的构造函数 */
    EventDispatcher();
    /** 事件调度类的析构函数 */
    ~EventDispatcher();

#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS && COCOS2D_DEBUG > 0
    
    /**
     * 这个函数帮助在调试版本中跟踪调试事件侦听器的相关问题。.
     * 验证给定节点在销毁时没有事件侦听器与其相关联.
     */
    void debugCheckNodeHasNoEventListenersOnDestruction(Node* node);
    
#endif

protected:
    friend class Node;
    
    /** 给一个节点设置一个'脏标记'(dirty flag) */
    void setDirtyForNode(Node* node);
    
    /**
     *  该容器(vector)用来存储带有基于场景图优先级和固定优先级的事件侦听器
     *
     */
    class EventListenerVector
    {
    public:
        EventListenerVector();
        ~EventListenerVector();
        size_t size() const;
        bool empty() const;
        
        void push_back(EventListener* item);
        void clearSceneGraphListeners();
        void clearFixedListeners();
        void clear();
        
        inline std::vector<EventListener*>* getFixedPriorityListeners() const { return _fixedListeners; };
        inline std::vector<EventListener*>* getSceneGraphPriorityListeners() const { return _sceneGraphListeners; };
        inline ssize_t getGt0Index() const { return _gt0Index; };
        inline void setGt0Index(ssize_t index) { _gt0Index = index; };
    private:
        std::vector<EventListener*>* _fixedListeners;
        std::vector<EventListener*>* _sceneGraphListeners;
        ssize_t _gt0Index;
    };
    
    /** 为某一项添加一个事件侦听器 Adds an event listener with item
     *  @note  如果是正在分发中的事件，添加操作会被延迟到当前分发操作的结束
     *  @see forceAddEventListener
     */
    void addEventListener(EventListener* listener);
    
    /** 强制添加一个事件侦听器 Force adding an event listener
     *  @note 强制添加一个事件侦听器，该事件无论是否在调度过程中都会忽略
     *  @see addEventListener
     */
    void forceAddEventListener(EventListener* listener);
    
    /** 获取指定侦听器类型的事件监听器列表 . */
    EventListenerVector* getListeners(const EventListener::ListenerID& listenerID);
    
    /** 更新'脏标记'(dirty flag) */
    void updateDirtyFlagForSceneGraph();
    
    /** 移除所有使用相同事件侦听器ID的侦听器*/
    void removeEventListenersForListenerID(const EventListener::ListenerID& listenerID);
    
    /** 事件侦听器排序 */
    void sortEventListeners(const EventListener::ListenerID& listenerID);
    
    /** 通过场景图的优先级排序指定类型的侦听器 */
    void sortEventListenersOfSceneGraphPriority(const EventListener::ListenerID& listenerID, Node* rootNode);
    
    /** 通过固定优先级排序指定类型的侦听器 */
    void sortEventListenersOfFixedPriority(const EventListener::ListenerID& listenerID);
    
    /** 更新所有侦听器
     *  1) 在事件分发过程中移除所有已经标记为'移除'的侦听器项.
     *  2) 在事件分发过程中添加所有已经标记为'添加'的侦听器项.
     */
    void updateListeners(Event* event);

    /** 触摸事件的处理与其它事件不同，因为触摸事件需要支持ALL_AT_ONCE和ONE_BY_NONE模式 */
    void dispatchTouchEvent(EventTouch* event);
    
    /** 关联节点和事件侦听器 */
    void associateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** 分离节点和事件侦听器 */
    void dissociateNodeAndEventListener(Node* node, EventListener* listener);
    
    /** 分发事件给带有指定侦听器类型的侦听器 */
    void dispatchEventToListeners(EventListenerVector* listeners, const std::function<bool(EventListener*)>& onEvent);
    
    /// 带优先级的'脏标记'(dirty flag)
    enum class DirtyFlag
    {
        NONE = 0,
        FIXED_PRIORITY = 1 << 0,
        SCENE_GRAPH_PRIORITY = 1 << 1,
        ALL = FIXED_PRIORITY | SCENE_GRAPH_PRIORITY
    };
    
    /** 为一个指定的侦听器ID设置一个'脏标志'(dirty flag) */
    void setDirty(const EventListener::ListenerID& listenerID, DirtyFlag flag);
    
    /** 遍历场景图获取每一个节点的绘制顺序，该函数在以场景图优先级排序的事件侦听器之前被调用 */
    void visitTarget(Node* node, bool isRootNode);
    
    /** 侦听器映射图 */
    std::unordered_map<EventListener::ListenerID, EventListenerVector*> _listenerMap;
    
    /** '脏标志'(dirty flag)映射图 */
    std::unordered_map<EventListener::ListenerID, DirtyFlag> _priorityDirtyFlagMap;
    
    /** 节点和事件侦听器的映射图 */
    std::unordered_map<Node*, std::vector<EventListener*>*> _nodeListenersMap;
    
    /** 节点映射和它的事件优先级 */
    std::unordered_map<Node*, int> _nodePriorityMap;
    
    /** key: 全局Z轴次序, value: 排好序的节点 */
    std::unordered_map<float, std::vector<Node*>> _globalZOrderNodeMap;
    
    /** 在事件分发后需要被添加的侦听器 */
    std::vector<EventListener*> _toAddedListeners;
    
    /** 这些节点与基于场景图优先级的侦听器相关联 */
    std::set<Node*> _dirtyNodes;
    
    /** 调度程序是否正在进行事件分发 */
    int _inDispatch;
    
    /** 是否要使分发事件可用 */
    bool _isEnabled;
    
    int _nodePriorityIndex;
    
    std::set<std::string> _internalCustomListenerIDs;
};


NS_CC_END


#endif // __CC_EVENT_DISPATCHER_H__
