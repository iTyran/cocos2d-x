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

#ifndef __UISCROLLVIEW_H__
#define __UISCROLLVIEW_H__

#include "ui/UILayout.h"
#include "ui/UIScrollInterface.h"

NS_CC_BEGIN

namespace ui {
    
class ScrollInnerContainer : public Layout
{
public:
    ScrollInnerContainer();
    virtual ~ScrollInnerContainer();
    static ScrollInnerContainer* create();
    virtual const Size& getLayoutSize() override;
};

CC_DEPRECATED_ATTRIBUTE typedef enum
{
    SCROLLVIEW_EVENT_SCROLL_TO_TOP,
    SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM,
    SCROLLVIEW_EVENT_SCROLL_TO_LEFT,
    SCROLLVIEW_EVENT_SCROLL_TO_RIGHT,
    SCROLLVIEW_EVENT_SCROLLING,
    SCROLLVIEW_EVENT_BOUNCE_TOP,
    SCROLLVIEW_EVENT_BOUNCE_BOTTOM,
    SCROLLVIEW_EVENT_BOUNCE_LEFT,
    SCROLLVIEW_EVENT_BOUNCE_RIGHT
}ScrollviewEventType;

CC_DEPRECATED_ATTRIBUTE typedef void (Ref::*SEL_ScrollViewEvent)(Ref*, ScrollviewEventType);
#define scrollvieweventselector(_SELECTOR) (SEL_ScrollViewEvent)(&_SELECTOR)


class ScrollView : public Layout , public UIScrollInterface
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class Direction
    {
        NONE,
        VERTICAL,
        HORIZONTAL,
        BOTH
    };
    
    enum class EventType
    {
        SCROLL_TO_TOP,
        SCROLL_TO_BOTTOM,
        SCROLL_TO_LEFT,
        SCROLL_TO_RIGHT,
        SCROLLING,
        BOUNCE_TOP,
        BOUNCE_BOTTOM,
        BOUNCE_LEFT,
        BOUNCE_RIGHT
    };
    typedef std::function<void(Ref*, EventType)> ccScrollViewCallback;
    /**
     * 默认构造函数
     */
    ScrollView();
    
    /**
     * 默认析构函数
     */
    virtual ~ScrollView();
    
    /**
     * 分配并初始化
     */
    static ScrollView* create();
    
    /**
     * 改变滚动视图的滚动方向
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL 表示滚动视图沿垂直方向滚动, SCROLLVIEW_DIR_HORIZONTAL 表示滚动视图沿水平方向滚动
     *
     * @param SCROLLVIEW_DIR
     */
    virtual void setDirection(Direction dir);
    
    /**
     * 获取滚动视图当前的滚动方向
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL 表示滚动视图沿垂直方向滚动, SCROLLVIEW_DIR_HORIZONTAL 表示滚动视图沿水平方向滚动
     *
     * @return SCROLLVIEW_DIR
     */
    Direction getDirection();
    
    /**
     * 获取该滚动视图的内部容器(inner container)
     *
     * 滚动视图的内部容器(inner container)是指包含该滚动视图内的子节点(children)的容器
     *
     * @return inner container.
     */
    Layout* getInnerContainer();
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图的底部边界(bottom boundary)
     */
    void scrollToBottom(float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图的顶部边界(top boundary)
     */
    void scrollToTop(float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图的左边界(left boundary)
     */
    void scrollToLeft(float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图的右边界(right boundary)
     */
    void scrollToRight(float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图的左上边界(top and left boundary)
     */
    void scrollToTopLeft(float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图的右上边界(top and right boundary)
     */
    void scrollToTopRight(float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图的左下边界(bottom and left boundary)
     */
    void scrollToBottomLeft(float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图的右下边界(bottom and right boundary)
     */
    void scrollToBottomRight(float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图上沿垂直方向一定比例的位置(vertical percent position)
     */
    void scrollToPercentVertical(float percent, float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图上沿水平方向一定比例的位置(horizontal percent position)
     */
    void scrollToPercentHorizontal(float percent, float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)滚动至滚动视图上沿水平方向一定比例且沿垂直方向一定比例的位置(both direction percent position)
     */
    void scrollToPercentBothDirection(const Vec2& percent, float time, bool attenuated);
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图的底部边界(bottom boundary)
     */
    void jumpToBottom();
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图的顶部边界(top boundary)
     */
    void jumpToTop();
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图的左边界(left boundary)
     */
    void jumpToLeft();
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图的右边界(right boundary)
     */
    void jumpToRight();
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图的左上边界(top and left boundary)
     */
    void jumpToTopLeft();
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图的右上边界(top and right boundary)
     */
    void jumpToTopRight();
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图的左下边界(bottom and left boundary)
     */
    void jumpToBottomLeft();
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图的右下边界(bottom and right boundary)
     */
    void jumpToBottomRight();
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图上沿垂直方向一定比例的位置(vertical percent position)
     */
    void jumpToPercentVertical(float percent);
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图上沿水平方向一定比例的位置(horizontal percent position)
     */
    void jumpToPercentHorizontal(float percent);
    
    /**
     * 将滚动视图的内部容器(inner container)直接移动（move）至滚动视图上沿水平方向一定比例且沿垂直方向一定比例的位置(both direction percent position)
     */
    void jumpToPercentBothDirection(const Vec2& percent);
    
    /**
     * 改变滚动视图内部容器的尺寸(size)
     *
     * 滚动视图的内部容器的尺寸必须大于或者等于该滚动视图的尺寸
     *
     * @param inner container size.
     */
    void setInnerContainerSize(const Size &size);
    
    /**
     * 获取该滚动视图内部容器的尺寸
     *
     * 滚动视图的内部容器的尺寸必须大于或者等于该滚动视图的尺寸
     *
     * @return inner container size.
     */
	const Size& getInnerContainerSize() const;
    
    /**
     * 添加由滚动事件触发的回调函数
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerScrollView(Ref* target, SEL_ScrollViewEvent selector);
    void addEventListener(const ccScrollViewCallback& callback);
        
    virtual void addChild(Node * child) override;
    /**
     * 在内部容器中加入一个子节点（child）并确定其在画布中的z-order
     *
     * 如果在一个running节点上添加子节点，'onEnter'和'onEnterTransitionDidFinish'方法会被立刻调用
     *
     * @param child     一个子节点（A child node）
     * @param zOrder    Z order 用于确定绘图时的优先级. 具体细节轻参考setLocalZOrder(int)
     */
    virtual void addChild(Node * child, int zOrder) override;
    /**
     * 在内部容器中加入一个子节点（child）并确定其在画布中的z-order和其在父节点中的标签（tag）
     *
     * 如果在一个running节点上添加子节点，'onEnter'和'onEnterTransitionDidFinish'方法会被立刻调用
     *
     * @param child     一个子节点（A child node）
     * @param zOrder    Z order 用于确定绘图时的优先级. 具体细节轻参考setLocalZOrder(int)
     * @param tag       一个有助于辨认不同节点的整型变量. 具体细节请参考setTag(int)
     */
    virtual void addChild(Node* child, int zOrder, int tag) override;
    
    //重载widget的"removeAllChildrenAndCleanUp"方法.
    virtual void removeAllChildren() override;
    
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    
    //重载widget的"removeChild"方法.
	virtual void removeChild(Node* child, bool cleaup = true) override;
    
    //重载widget的"getChildren"方法.
    virtual Vector<Node*>& getChildren() override;
    virtual const Vector<Node*>& getChildren() const override;
    
    virtual ssize_t getChildrenCount() const override;
    
    virtual Node * getChildByTag(int tag) override;
    
    virtual Widget* getChildByName(const std::string& name) override;
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    
    virtual void update(float dt) override;
    
    void setBounceEnabled(bool enabled);
    
    bool isBounceEnabled() const;
    
    void setInertiaScrollEnabled(bool enabled);
    
    bool isInertiaScrollEnabled() const;
    
    /**
     * 设置 LayoutType.
     *
     * @see LayoutType
     *
     * @param LayoutType
     */
    virtual void setLayoutType(Type type) override;
    
    /**
     * 获取 LayoutType.
     *
     * @see LayoutType
     *
     * @return LayoutType
     */
    virtual Type getLayoutType() const override;
    
    /**
     * 返回widget的类名称
     */
    virtual std::string getDescription() const override;
    
    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:
    virtual void initRenderer() override;
    void moveChildren(float offsetX, float offsetY);
    void autoScrollChildren(float dt);
    void bounceChildren(float dt);
    void checkBounceBoundary();
    bool checkNeedBounce();
    void startAutoScrollChildrenWithOriginalSpeed(const Vec2& dir, float v, bool attenuated, float acceleration);
    void startAutoScrollChildrenWithDestination(const Vec2& des, float time, bool attenuated);
    void jumpToDestination(const Vec2& des);
    void stopAutoScrollChildren();
    void startBounceChildren(float v);
    void stopBounceChildren();
    bool checkCustomScrollDestination(float* touchOffsetX, float* touchOffsetY);
    virtual bool scrollChildren(float touchOffsetX, float touchOffsetY);
    bool bounceScrollChildren(float touchOffsetX, float touchOffsetY);
    void startRecordSlidAction();
    virtual void endRecordSlidAction();
    virtual void handlePressLogic(const Vec2 &touchPoint) override;
    virtual void handleMoveLogic(const Vec2 &touchPoint) override;
    virtual void handleReleaseLogic(const Vec2 &touchPoint) override;
    virtual void interceptTouchEvent(int handleState,Widget* sender,const Vec2 &touchPoint) override;
    virtual void checkChildInfo(int handleState,Widget* sender,const Vec2 &touchPoint) override;
    void recordSlidTime(float dt);
    void scrollToTopEvent();
    void scrollToBottomEvent();
    void scrollToLeftEvent();
    void scrollToRightEvent();
    void scrollingEvent();
    void bounceTopEvent();
    void bounceBottomEvent();
    void bounceLeftEvent();
    void bounceRightEvent();
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    virtual void setClippingEnabled(bool able) override{Layout::setClippingEnabled(able);};
    virtual void doLayout() override;
protected:
    Layout* _innerContainer;
    
    Direction _direction;

    Vec2 _touchBeganPoint;
    Vec2 _touchMovedPoint;
    Vec2 _touchEndedPoint;
    Vec2 _touchMovingPoint;
    Vec2 _autoScrollDir;
    
    float _topBoundary;
    float _bottomBoundary;
    float _leftBoundary;
    float _rightBoundary;
    
    float _bounceTopBoundary;
    float _bounceBottomBoundary;
    float _bounceLeftBoundary;
    float _bounceRightBoundary;

    
    bool _autoScroll;
    float _autoScrollAddUpTime;
    
    float _autoScrollOriginalSpeed;
    float _autoScrollAcceleration;
    bool _isAutoScrollSpeedAttenuated;
    bool _needCheckAutoScrollDestination;
    Vec2 _autoScrollDestination;
    
    bool _bePressed;
    float _slidTime;
    Vec2 _moveChildPoint;
    float _childFocusCancelOffset;
    
    bool _leftBounceNeeded;
    bool _topBounceNeeded;
    bool _rightBounceNeeded;
    bool _bottomBounceNeeded;
    
    bool _bounceEnabled;
    bool _bouncing;
    Vec2 _bounceDir;
    float _bounceOriginalSpeed;
    bool _inertiaScrollEnabled;


    
    Ref* _scrollViewEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //支持 vs 2005 或其更高版本
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_ScrollViewEvent _scrollViewEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //支持 vs 2005 或其更高版本
#pragma warning (pop)
#endif
    ccScrollViewCallback _eventCallback;
};

}
NS_CC_END
#endif /* defined(__CocoGUI__ScrollView__) */
