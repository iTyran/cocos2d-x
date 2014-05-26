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

#ifndef __UIWIDGET_H__
#define __UIWIDGET_H__

#include "ui/CCProtectedNode.h"
#include "ui/UILayoutParameter.h"
#include "ui/GUIDefine.h"

NS_CC_BEGIN

namespace ui {
    
CC_DEPRECATED_ATTRIBUTE typedef enum
{
    TOUCH_EVENT_BEGAN,
    TOUCH_EVENT_MOVED,
    TOUCH_EVENT_ENDED,
    TOUCH_EVENT_CANCELED
}TouchEventType;
    
CC_DEPRECATED_ATTRIBUTE typedef void (Ref::*SEL_TouchEvent)(Ref*,TouchEventType);
#define toucheventselector(_SELECTOR) (SEL_TouchEvent)(&_SELECTOR)


/**
*   @js NA
*   @lua NA
*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef ABSOLUTE
#undef ABSOLUTE
#endif
#endif


class Widget : public ProtectedNode
{
public:
    enum class FocusDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    
    enum class PositionType
    {
        ABSOLUTE,
        PERCENT
    };
    
    enum class SizeType
    {
        ABSOLUTE,
        PERCENT
    };
    
    enum class TouchEventType
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELED
    };
    
    enum class TextureResType
    {
        LOCAL = 0,
        PLIST = 1
    };
    
    enum class BrightStyle
    {
        NONE = -1,
        NORMAL,
        HIGHLIGHT
    };

    
    typedef std::function<void(Ref*,Widget::TouchEventType)> ccWidgetTouchCallback;

    
    /**
     * 默认构造函数
     */
    Widget(void);

    /**
     * 默认析构函数
     */
    virtual ~Widget();

    /**
     * 分配空间并初始化widget
     */
    static Widget* create();

    /**
     * 设置widget是否为可用
     * 
     * 参数为true则设置该widget可用，该widget可以响应触摸；参数为false则设置该widget不可用，该widget不能响应触摸
     *
     * 参数默认值为true，widget默认为可用
     *
     * @param enabled
     */
    virtual void setEnabled(bool enabled);

    /**
     * 判断该widget是否可用
     *
     * @return 可用则返回true，不可用则返回false
     */
    bool isEnabled() const;

    /**
     * 设置widget是否为亮色（对应可用状态）
     *
     * 默认值为true，widget默认为亮色
     *
     * @param visible   参数为true则设置该widget为亮色，参数为false则设置该widget为暗色（dark，对应禁用状态）。
     */
    void setBright(bool bright);

    /**
     * 判断该widget是否为亮色
     *
     * @return 亮色则返回true，暗色则返回false
     */
    bool isBright() const;

    /**
     * 设置widget是否可以响应触摸。
     *
     * 默认值为false，widget默认为不能响应触摸
     *
     * @param visible   参数为true则设置该widget可以响应触摸，参数为false则设置该widget不能响应触摸
     */
    virtual void setTouchEnabled(bool enabled);

    /**
     * 设置widget的亮色风格（bright style）
     *
     * @see BrightStyle
     *
     * @param style   BRIGHT_NORMAL 表示该widget为普通亮色, BRIGHT_HIGHLIGHT 表示该widget为高亮
     */
    void setBrightStyle(BrightStyle style);

    /**
     * 判定该widget是否可以响应触摸
     *
     * @return 如果可以响应触摸则返回true，不能响应触摸则返回false
     */
    bool isTouchEnabled() const;

    /**
     * 判定该widget是否为高亮（对应被选中状态）
     *
     * @return 如果该widget处于高亮状态则返回true，如果该widget不处于高亮状态则返回false
     */
    bool isHighlighted() const;

    /**
     * 设置该widget是否处于高亮状态（对应被选中状态）
     *
     * 默认值为false，widget默认为处于非高亮状态
     *
     * @param hilight   参数为true则设置该widget为高亮状态，参数为false则设置该widget为非高亮状态
     */
    void setHighlighted(bool hilight);

    /**
     * 获取该widget左边界横坐标
     *
     * @return 该widget左边界横坐标
     */
    float getLeftInParent();

    /**
     * 获取该widget底部边界纵坐标
     *
     * @return 该widget底部边界纵坐标
     */
    float getBottomInParent();

    /**
     * 获取该widget右边界横坐标
     *
     * @return 该widget右边界横坐标
     */
    float getRightInParent();

    /**
     * 获取该widget顶部边界纵坐标
     *
     * @return 该widget顶部边界纵坐标
     */
    float getTopInParent();

    /**
     * 通过名字从容器中获取一个子节点
     *
     * @param name   用于找到所需widget子节点的关键字（key）
     *
     * @return 名字与输入的参数相同的widget
     */
    virtual Widget* getChildByName(const std::string& name);

    virtual void visit(cocos2d::Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;

    /**
     * 为菜单项的目标／选择器设置触摸事件
     */
    CC_DEPRECATED_ATTRIBUTE void addTouchEventListener(Ref* target,SEL_TouchEvent selector);
    void addTouchEventListener(ccWidgetTouchCallback callback);

    //cocos2d property

    /**
     * 改变该widget在OpenGL坐标系中的绝对位置坐标（x,y）
     *
     * 我们通常使用p(x,y)来组成Vec2对象
     * 原点（0，0）位于屏幕的左下方
     *
     * @param position  该widget在OpenGL坐标系中的绝对位置坐标(x,y)
     */
    virtual void setPosition(const Vec2 &pos) override;

    /**
     * 改变该widget在OpenGL坐标系中的相对百分比位置坐标（x,y）
     *
     * 我们通常使用p(x,y)来组成Vec2对象
     * 原点（0，0）位于屏幕的左下方
     *
     * @param percent   该widget在OpenGL坐标系中的相对百分比位置坐标(x,y)
     */
    void setPositionPercent(const Vec2 &percent);

    /**
     * 获取该widget在OpenGL坐标系中的相对百分比位置坐标(x,y)
     *
     * @see setPosition(const Vec2&)
     *
     * @return 该widget在OpenGL坐标系中的相对百分比位置坐标(x,y)
     */
    const Vec2& getPositionPercent();

    /**
     * 改变该widget的位置坐标类型
     *
     * @see PositionType
     *
     * @param type  该widget的位置坐标类型
     */
    void setPositionType(PositionType type);

    /**
     * 获取该widget的位置坐标类型
     *
     * @see PositionType
     *
     * @return type  该widget的位置坐标类型
     */
    PositionType getPositionType() const;

    /**
     * 设置该widget是否应该被水平翻转.
     *
     * @param bFlippedX true 该widget应该被水平翻转, false 该widget不应被水平翻转.
     */
    virtual void setFlippedX(bool flippedX);

    /**
     * 返回表明该widget是否被水平翻转的标识
     *
     * 只会翻转该widget自身的纹理贴图（texture），不会翻转其子节点（child）的纹理贴图
     * 并且翻转不会改变anchorPoint
     * 如果你想要翻转anchorPoint，并且／或者翻转该widget的子节点，你应该使用:
     * widget->setScaleX(sprite->getScaleX() * -1);
     *
     * @return 如果该widget被水平翻转则返回true，该widget没有被水平翻转则返回false
     */
    virtual bool isFlippedX(){return _flippedX;};

    /**
     * 设置该widget是否应该被垂直翻转.
     *
     * @param bFlippedX true 该widget应该被垂直翻转, false 该widget不应被垂直翻转.
     */
    virtual void setFlippedY(bool flippedY);

    /**
     * 返回表明该widget是否被垂直翻转的标识
     *
     * 只会翻转该widget自身的纹理贴图（texture），不会翻转其子节点（child）的纹理贴图
     * 并且翻转不会改变anchorPoint
     * 如果你想要翻转anchorPoint，并且／或者翻转该widget的子节点，你应该使用:
     * widget->setScaleY(sprite->getScaleY() * -1);
     *
     * @return 如果该widget被垂直翻转则返回true，该widget没有被垂直翻转则返回false
     */
    virtual bool isFlippedY(){return _flippedY;};
    
    virtual void setColor(const Color3B& color) override;
    
    virtual void setOpacity(GLubyte opacity) override;
    
    const Color3B& getColor() const override {return _color;};
    
    GLubyte getOpacity() const override {return _opacity;};

    /** @deprecated 使用 isFlippedX() 作为替代 */
    CC_DEPRECATED_ATTRIBUTE bool isFlipX() { return isFlippedX(); };
    /** @deprecated 使用 setFlippedX() 作为替代 */
    CC_DEPRECATED_ATTRIBUTE void setFlipX(bool flipX) { setFlippedX(flipX); };
    /** @deprecated 使用 isFlippedY() 作为替代 */
    CC_DEPRECATED_ATTRIBUTE bool isFlipY() { return isFlippedY(); };
    /** @deprecated 使用 setFlippedY() 作为替代 */
    CC_DEPRECATED_ATTRIBUTE void setFlipY(bool flipY) { setFlippedY(flipY); };

    /*
     * 检查一个点是否在其父节点的区域内
     *
     * @param point
     *
     * @return 如果该点在其父节点的区域则返回true，该点没有在其父节点的区域则返回false
     */
    bool clippingParentAreaContainPoint(const Vec2 &pt);

    /*
     * 向该widget的父节点发送触摸事件
     */
    virtual void checkChildInfo(int handleState,Widget* sender,const Vec2 &touchPoint);

    /*
     * 在widget被选中时，获取该触摸事件开始时的点
     *
     * @return 触摸事件开始时的点
     */
    const Vec2& getTouchStartPos();

    /*
     * 在widget被选中时，获取该触摸事件进行中的点
     *
     * @return 该触摸事件进行中的点
     */
    const Vec2& getTouchMovePos();

    /*
     * 在widget被选中时，获取该触摸事件结束时的点
     *
     * @return 该触摸事件结束时的点
     */
    const Vec2& getTouchEndPos();

    /**
     * 改变widget的名字，使用名字可以更轻松地识别出该widget
     *
     * @param 一个可用于识别该widget的字符串常量（const std::string）
     */
    void setName(const std::string& name);

    /**
     * 返回widget的名字，使用名字可以更轻松地识别出该widget
     *
     * 你可以为widget设置标签（tag）以更好地识别他们
     *
     * @return 一个可用于识别该widget的字符串常量（const std::string）
     */
    const std::string& getName() const;

    /**
     * 改变widget的尺寸（size）
     *
     * @param size widget的尺寸（size）
     */
    virtual void setSize(const Size &size);

    /**
     * 改变widget的百分比尺寸（percent size）
     *
     * @param percent idget的百分比尺寸（percent size）
     */
    virtual void setSizePercent(const Vec2 &percent);

    /**
     * 改变widget的尺寸类型（size type）
     *
     * @see SizeType
     *
     * @param type widget的尺寸类型（size type）
     */
    void setSizeType(SizeType type);

    /**
     * 获取widget的尺寸类型（size type）
     *
     * @see SizeType
     *
     * @param type widget的尺寸类型（size type）
     */
    SizeType getSizeType() const;

    /**
     * 返回widget的尺寸（size）
     *
     * @return size
     */
    const Size& getSize() const;
    
    const Size& getCustomSize() const;
    
    virtual const Size& getLayoutSize() {return _size;};

    /**
     * 返回widget的尺寸百分比
     *
     * @return size percent
     */
    const Vec2& getSizePercent() const;

    /**
     * 检查一个点是否在该widget所在区域
     *
     * @param point
     *
     * @return 如果改点在widget所在区域则返回true，不在widget所在区域则返回false
     */
    virtual bool hitTest(const Vec2 &pt);

    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);

    /**
     * 为widget设置LayoutParameter
     *
     * @see LayoutParameter
     *
     * @param LayoutParameter LayoutParameter指针
     *
     * @param type  相对的（relative）或者线性的（linear）
     */
    void setLayoutParameter(LayoutParameter* parameter);

    /**
     * 获取widget的LayoutParameter
     *
     * @see LayoutParameter
     *
     * @param type  相对的或者线性的
     *
     * @return LayoutParameter
     */
    LayoutParameter* getLayoutParameter(LayoutParameter::Type type);

    /**
     * 忽略widget的尺寸（size）
     *
     * @param ignore, 参数为true则忽略widget的尺寸，使用纹理贴图的尺寸，参数为false则不忽略widget的尺寸。参数的默认值为true
     */
    virtual void ignoreContentAdaptWithSize(bool ignore);

    /**
     * 检查该widget的尺寸（size）是否被忽略
     *
     * @param 参数为true则忽略widget的尺寸，使用纹理贴图的尺寸，参数为false则不忽略widget的尺寸。参数的默认值为true
     */
    bool isIgnoreContentAdaptWithSize() const;

    /**
     * 获取widget在全局中的位置坐标
     *
     * @return widget在全局中的位置坐标
     */
    Vec2 getWorldPosition();

    /**
     * 获取widget的虚拟渲染器
     *
     * 比如说，按钮的虚拟渲染器渲染器就是该按钮的纹理贴图的渲染器
     *
     * @return Node pointer.
     */
    virtual Node* getVirtualRenderer();

//    /**
//     * 获取widget的content size
//     *
//     * Content size是指widget所用纹理贴图的尺寸
//     */
//    virtual const Size& getContentSize() const;
    virtual const Size& getVirtualRendererSize() const;
    
    

    /**
     * 返回widget的类名
     */
    virtual std::string getDescription() const override;

    Widget* clone();

    virtual void onEnter() override;
    virtual void onExit() override;

    void updateSizeAndPosition();

    void updateSizeAndPosition(const Size& parentSize);
    
    /*临时动作*/
    void setActionTag(int tag);
	int getActionTag();
    
    /**
     *@return  widget是否被focus
     */
    bool isFocused();
    
    /**
     *@param focus  传递参数true来使得widget处于focus状态或者传递参数false来取消focus状态
     *@return void
     */
    void setFocused(bool focus);
    
    /**
     *@return 如果widget可以被focus则返回true，如果widget不能被focus则返回false
     */
    bool isFocusEnabled();
    
    /**
     *@param enable 传递参数true/flase来使得widget可以／不可以被focus
     *@return void
     */
    void setFocusEnabled(bool enable);
    
    /**
     * 当一个widget处于某一个layout中的时候，你可以通过调用这个方法在指定的方向获取下一个被focus的widget
     * 如果一个widget没有在一个layout中，调用这个方法会获得该widget自身
     *@param dir 在该layout中找寻下一个被focus的widget的方向
     *@param current  目前被focus的widget
     *@return 该layout中下一个被focus的widget
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current);
    
    /**
     *当一个widget调用了这个方法，这个widget会立刻被focus
     */
    void requestFocus();
    
CC_CONSTRUCTOR_ACCESS:
    //初始化widget的状态
    virtual bool init() override;
    
    /**
     * 这个方法会在focus状态发生改变的时候被调用
     *@param widgetLostFocus  失去focus状态的widget
     *@param widgetGetFocus  得到focus状态的widget
     *@return void
     */
    void onFocusChange(Widget* widgetLostFocus, Widget* widgetGetFocus);
    
    /**
     * 通过EventDispatcher来调度EventFocus
     *@param widgetLoseFocus  失去focus状态的widget
     *@param widgetGetFocus  得到focus状态的widget
     *@return void
     */
    void  dispatchFocusEvent(Widget* widgetLoseFocus, Widget* widgetGetFocus);

    
protected:
    //尺寸（size）改变时的回调函数
    virtual void onSizeChanged();

    //初始化widget的渲染内容
    virtual void initRenderer();

    //当widget回到正常状态时的回调函数
    virtual void onPressStateChangedToNormal();

    //当widget切换到被选中状态时的回调函数
    virtual void onPressStateChangedToPressed();

    //当widget切换到不可用状态时的回调函数
    virtual void onPressStateChangedToDisabled();
    void pushDownEvent();
    void moveEvent();
    void releaseUpEvent();
    void cancelUpEvent();
    virtual void updateTextureColor(){};
    virtual void updateTextureOpacity(){};
    virtual void updateTextureRGBA(){};
    virtual void updateFlippedX(){};
    virtual void updateFlippedY(){};
    void updateColorToRenderer(Node* renderer);
    void updateOpacityToRenderer(Node* renderer);
    void updateRGBAToRenderer(Node* renderer);
    void copyProperties(Widget* model);
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    Widget* getWidgetParent();
    void updateContentSizeWithTextureSize(const Size& size);
    virtual void adaptRenderers(){};
    bool isAncestorsEnabled();
    Widget* getAncensterWidget(Node* node);
    bool isAncestorsVisible(Node* node);

protected:
    bool _enabled;            ///< widget的最高控制
    bool _bright;             ///< widget是否为亮色（bright）
    bool _touchEnabled;       ///< widget是否能响应触摸
    bool _highlight;              ///< widget是否被focus
    BrightStyle _brightStyle; ///< 亮色风格（bright style）
    Vec2 _touchStartPos;    ///< 触摸开始点
    Vec2 _touchMovePos;     ///< 触摸移动点
    Vec2 _touchEndPos;      ///< 触摸结束点
    
    //如果要使用原有的API, 我们必须保留_touchEventListener
    Ref*       _touchEventListener;
    
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 或者更高版本
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_TouchEvent    _touchEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 或者更高版本
#pragma warning (pop)
#endif
    
    ccWidgetTouchCallback _touchEventCallback;
    
    std::string _name;
    int _actionTag;
    Size _size;
    Size _customSize;
    bool _ignoreSize;
    bool _affectByClipping;
    SizeType _sizeType;
    Vec2 _sizePercent;
    PositionType _positionType;
    Vec2 _positionPercent;
    bool _reorderWidgetChildDirty;
    bool _hitted;
    EventListenerTouchOneByOne* _touchListener;
    Color3B _color;
    GLubyte _opacity;
    bool _flippedX;
    bool _flippedY;
    Map<int, LayoutParameter*> _layoutParameterDictionary;
    
    bool _focused;
    bool _focusEnabled;
    
    /**
     * 储存唯一一个处于被focus状态的widget
     */
    static Widget *_focusedWidget;  //layout和widget都会被储存在这个变量中
    static Widget *_realFocusedWidget; //只有widget类的变量会被储存在这个变量里
public:
    /**
     * 不管你想要调用这个方法去获得什么样的widget对象，这个方法会返回给你被focus的widget
     * @param isWidget  如果你将参数isWidget设置为true，这个方法会返回_realFocusedWidget，它只是一个widget类的变量；如果你将参数isWidget设置为false，这个方法会返回一个widget类变量或者一个layout类变量
     */
    Widget* getCurrentFocusedWidget(bool isWidget);
    
    std::function<void(Widget*,Widget*)> onFocusChanged;
    std::function<Widget*(FocusDirection)> onNextFocusedWidget;
};
}

NS_CC_END

#endif /* defined(__Widget__) */
