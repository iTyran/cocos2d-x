/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot.
 * http://yannickloriot.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Converted to c++ / cocos2d-x by Angus C
 */


#ifndef __CCCONTROL_H__
#define __CCCONTROL_H__

#include "CCControlUtils.h"
#include "2d/CCLayer.h"

NS_CC_EXT_BEGIN


class Invocation;

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** 控件事件的种类 */
#define kControlEventTotalNumber 9


/*
 * @class
 * Control类是受到CocoaTouch里UIKit库的UIControl类API启发而来
 * 它是诸如按钮、滚动条等用户交互控件的基类。
 *
 * Control类的目的就是定义一个标准接口，并提供了一个基础实现用于 
 * 准备动作消息以及向目标派发特定事件。
 *
 * 使用Control类时从该类派生即可。
 */
class Control : public Layer
{
public:
    /** 控件对象可能产生的事件种类 */
    enum class EventType
    {
        TOUCH_DOWN           = 1 << 0,    // 控件内按下
        DRAG_INSIDE          = 1 << 1,    // 控件范围内的拖拽
        DRAG_OUTSIDE         = 1 << 2,    // 控件范围外的拖拽
        DRAG_ENTER           = 1 << 3,    // 手指拖拽并刚好从控件范围外移入控件范围
        DRAG_EXIT            = 1 << 4,    // 手指拖拽并刚好从控件范围内移入控件范围
        TOUCH_UP_INSIDE      = 1 << 5,    // 手指在控件范围内抬起
        TOUCH_UP_OUTSIDE     = 1 << 6,    // 手指在控件范围外抬起
        TOUCH_CANCEL         = 1 << 7,    // 取消当前触摸的系统事件
        VALUE_CHANGED        = 1 << 8      // 因为拖拽或者操作一个控件，导致控件取值发生改变
    };
    
    typedef void (Ref::*Handler)(Ref*, EventType);
    
    /** 控件的可能状态  */
    enum class State
    {
        NORMAL         = 1 << 0, // 控件的普通以及默认状态，功能可用但是未被选中或者高亮。
        HIGH_LIGHTED   = 1 << 1, // 控件的高亮状态，当在控件内按下，控件内拖拽或者拖拽进入控件时处于此状态，可以通过highlighted相关方法进行判断或设置。
        DISABLED       = 1 << 2, // 控件的禁用状态，表明控件当前不可用，可以通过enabled相关方法进行判断或设置。
        SELECTED       = 1 << 3  // 控件的选中状态，表明控件当前被选中，可以通过selected相关方法进行判断或设置。
    };

    /** 创建控件对象 */
    static Control* create();

    /** 设置/判断控件是否被启用 */
    virtual void setEnabled(bool bEnabled);
    virtual bool isEnabled() const;

    /** 设置/判断控件是否被选中 */
    virtual void setSelected(bool bSelected);
    virtual bool isSelected() const;

    /** 设置/判断控件是否高亮 */
    virtual void setHighlighted(bool bHighlighted);
    virtual bool isHighlighted() const;

    bool hasVisibleParents() const;
    /**
     * 根据控件当前内部状态更新布局显示
     */
    virtual void needsLayout();

    /**
     * 为指定控件事件发送动作消息
     *
     * @param controlEvents 用于标明动作消息在哪些控件事件下需要发送的位掩码
     * 位掩码常量参见"EventType"
     */
    virtual void sendActionsForControlEvents(EventType controlEvents);

    /**
     * 在内部派发表中，为指定事件（或事件们）增加一个目标及动作。
     * 动作消息中，可能会依次加入发送者以及事件类型作为参数。
     * 调用此方法时，目标不会被retain。
     *
     * @param target 派发动作消息的目标对象，不能为空且不会被retain
     * @param action 用于标示动作消息的selector，不能为空
     * @param controlEvents 用于标明动作消息在哪些控件事件下需要发送的位掩码
     * 位掩码常量参见"EventType"
     */
    virtual void addTargetWithActionForControlEvents(Ref* target, Handler action, EventType controlEvents);

    /**
     * 在内部派发表中，为指定事件（或事件们）移除一个目标及动作。
     *
     * @param target 目标对象，即动作消息的接收者
     * 传入空则移除所有与动作-控件事件对相匹配的目标
     * @param action 用于标示动作消息的selector
     * 传入空则移除所有与目标对象相匹配的动作消息
     * @param controlEvents 用于标明与目标及动作关联的控件事件的位掩码
     * 位掩码常量参见"EventType"
     */
    virtual void removeTargetWithActionForControlEvents(Ref* target, Handler action, EventType controlEvents);

    /**
     * 获取转换到控件坐标系的触摸点位置
     * @param touch 触摸对象
     */
    virtual Vec2 getTouchLocation(Touch* touch);

    virtual bool onTouchBegan(Touch *touch, Event *event) { return false; };
    virtual void onTouchMoved(Touch *touch, Event *event) {};
    virtual void onTouchEnded(Touch *touch, Event *event) {};
    virtual void onTouchCancelled(Touch *touch, Event *event) {};
    
    /**
     * 判断触摸是否在接收者的包围框内
     * 所给触摸参数必须相对世界坐标
     *
     * @param touch 触摸对象
     *
     * @return 触摸是否在接收者的包围框内
     */
    virtual bool isTouchInside(Touch * touch);

    // Overrides
    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool bOpacityModifyRGB) override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    Control();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Control();

    virtual bool init(void) override;

protected:
    /**
     * 返回一个Invocation对象，能根据所给目标-动作对构建消息
     * （Invocation对象可能依次包含发送者和事件作为参数）
     *
     * @param target 目标对象
     * @param action 用于标示动作消息的selector
     * @param controlEvent 用于标示动作消息发送时机的控件事件
     * 常量取值参见"EventType"
     *
     * @return 一个Invocation对象，能根据所给目标-动作对构建消息
     */
    Invocation* invocationWithTargetAndActionForControlEvent(Ref* target, Handler action, EventType controlEvent);

    /**
    * 根据所给控件事件，返回对应Invocation的vector
    * 如果这个list不存在，则创建一个空序列返回
    *
    * @param controlEvent 用于标示动作消息发送时机的控件事件
    * 常量取值参见"EventType"
    *
    * @return 对应所给控件事件的Invocation vector
    */
    Vector<Invocation*>& dispatchListforControlEvent(EventType controlEvent);

    /**
     * 在内部派发表中，为指定事件增加目标与动作。
     * 动作消息中，可能会依次加入发送者以及事件类型作为参数。
     * 调用此方法时，目标不会被retain。
     *
     * @param target 派发动作消息的目标对象，不能为空且不会被retain。
     * @param action 用于标示动作消息的selector，不能为空
     * @param controlEvent 用于标示动作消息发送时机的控件事件
     * 常量取值参见"EventType"
     */
    void addTargetWithActionForControlEvent(Ref* target, Handler action, EventType controlEvent);
    
    /**
     * 在内部派发表中，为指定事件移除一个目标及动作。
     *
     * @param target 目标对象，即动作消息的接收者
     * 传入空则移除所有与动作-控件事件对相匹配的目标
     * @param action 用于标示动作消息的selector
     * 传入空则移除所有与目标对象相匹配的动作消息
     * @param controlEvent 用于标示动作消息发送时机的控件事件
     * 常量取值参见"EventType"
     */
    void removeTargetWithActionForControlEvent(Ref* target, Handler action, EventType controlEvent);

    bool _enabled;
    bool _selected;
    bool _highlighted;

    /** 控件所有父亲节点为可见时值为真 */
    bool _hasVisibleParents;

    /**
     * 存放控件事件及对应目标-动作对之间联系的表格
     * 每一个按钮事件均对应指向一个Invocation的vector(存放目标-动作对)。
     */
    std::unordered_map<int, Vector<Invocation*>*> _dispatchTable;

    //CCRGBAProtocol
    bool _isOpacityModifyRGB;

    /** 当前控件状态 */
    CC_SYNTHESIZE_READONLY(State, _state, State);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Control);
};

Control::EventType operator|(Control::EventType a, Control::EventType b);

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif
