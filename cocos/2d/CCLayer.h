/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCLAYER_H__
#define __CCLAYER_H__

#include "2d/CCNode.h"
#include "2d/CCProtocols.h"
#include "base/CCEventTouch.h"
#ifdef EMSCRIPTEN
#include "CCGLBufferedNode.h"
#endif // EMSCRIPTEN

#include "base/CCEventKeyboard.h"
#include "renderer/CCCustomCommand.h"

#include "physics/CCPhysicsWorld.h"

NS_CC_BEGIN

/**
 * @addtogroup layer
 * @{
 */

/**
 * @addtogroup 布景层
 * @{
 */
class __Set;
class TouchScriptHandlerEntry;

class EventListenerTouch;
class EventListenerKeyboard;
class EventListenerAcceleration;

//
// Layer
//
/** @brief Layer is a subclass of Node that implements the TouchEventsDelegate protocol.

All features from Node are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
/** @brief 
Layer类是Node类的一个子类，它实现了触屏事件代理（TouchEventsDelegate）协议。

 它可以实现Node类的所有功能,并且它还添加了以下这些新功能：
-它可以接收iPhone触屏事件
-它可以接收加速度传感器输入
*/
class CC_DLL Layer : public Node
{
public:    
    /** creates a fullscreen black layer */
    /**创建一个全屏的黑色布景层 */
    static Layer *create();

    // Deprecated touch callbacks.
    //被废弃的触屏回调
    CC_DEPRECATED_ATTRIBUTE virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchMoved(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchEnded(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesBegan(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesMoved(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesEnded(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesCancelled(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    
    /* Callback function should not be deprecated, it will generate lots of warnings.
       Since 'setTouchEnabled' was deprecated, it will make warnings if developer overrides onTouchXXX and invokes setTouchEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    /* 回调函数不能被弃用。这将生成很多警告。
       由于 'setTouchEnabled' 被废弃, 如果开发者重写 onTouchXXX方法并且调用setTouchEnabled(true)来代替使用EventDispatcher::addEventListenerWithXXX将导致警告.
    */
    virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    /** @deprecated Please override onAcceleration */
    /** @deprecated 请重写onAcceleration方法 */
    CC_DEPRECATED_ATTRIBUTE virtual void didAccelerate(Acceleration* accelerationValue) final {};

	/* Callback function should not be deprecated, it will generate lots of warnings.
	Since 'setAccelerometerEnabled' was deprecated, it will make warnings if developer overrides onAcceleration and invokes setAccelerometerEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    /* 回调函数不能被弃用。这将生成很多警告。
       由于 'setAccelerometerEnabled'被弃用, 如果开发者重写onAcceleration方法并且调用setAccelerometerEnabled(true)来代替使用EventDispatcher::addEventListenerWithXXX将导致警告.
    */
    virtual void onAcceleration(Acceleration* acc, Event* unused_event);

    /** If isTouchEnabled, this method is called onEnter. Override it to change the
    way Layer receives touch events.
如果触屏事件可用，这个方法可以叫做onEnter.重写它来改变Layer接收触屏事件的方式。
    ( Default: TouchDispatcher::sharedDispatcher()->addStandardDelegate(this,0); )
    Example:
    void Layer::registerWithTouchDispatcher()
    {
    TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,INT_MIN+1,true);
    }
    @since v0.8.0
    */
    CC_DEPRECATED_ATTRIBUTE virtual void registerWithTouchDispatcher() final {};

    /** whether or not it will receive Touch events.
    You can enable / disable touch events with this property.
    Only the touches of this node will be affected. This "method" is not propagated to it's children.
    @since v0.8.1
    */
    /** 它是否将接收触屏事件。
你可以通过这个属性来开启或关闭触屏事件。
只有这个节点的触屏事件被影响。这个“方法”不会传播给它的孩子节点。
    @since v0.8.1
    */
    CC_DEPRECATED_ATTRIBUTE bool isTouchEnabled() const;
    CC_DEPRECATED_ATTRIBUTE void setTouchEnabled(bool value);
    
    CC_DEPRECATED_ATTRIBUTE virtual void setTouchMode(Touch::DispatchMode mode);
    CC_DEPRECATED_ATTRIBUTE virtual Touch::DispatchMode getTouchMode() const;

    /** swallowsTouches of the touch events. Default is true */
    /**触屏事件中的  swallowsTouches 事件。默认是true.*/
    CC_DEPRECATED_ATTRIBUTE virtual void setSwallowsTouches(bool swallowsTouches);
    CC_DEPRECATED_ATTRIBUTE virtual bool isSwallowsTouches() const;

    /** whether or not it will receive Accelerometer events
    You can enable / disable accelerometer events with this property.
    @since v0.8.1
    */
    /**它是否接收加速度传感器事件。
   你可以通过这个属性来开启或者关闭加速度传感器事件。
    @since v0.8.1
    */
    CC_DEPRECATED_ATTRIBUTE virtual bool isAccelerometerEnabled() const;
    CC_DEPRECATED_ATTRIBUTE virtual void setAccelerometerEnabled(bool value);
    CC_DEPRECATED_ATTRIBUTE virtual void setAccelerometerInterval(double interval);

    /** whether or not it will receive keyboard or keypad events
    You can enable / disable accelerometer events with this property.
    it's new in cocos2d-x
    */
/**
它是否接收键盘或者平板的键盘事件。
你可以通过这个属性来开启或者关闭键盘或者平板的键盘事件。
这是cocos2d-x中的新特性。
    */
    CC_DEPRECATED_ATTRIBUTE virtual bool isKeyboardEnabled() const;
    CC_DEPRECATED_ATTRIBUTE virtual void setKeyboardEnabled(bool value);

    /** Please use onKeyPressed instead. */
    /** 请用 onKeyPressed 来代替. */
CC_DEPRECATED_ATTRIBUTE virtual void keyPressed(int keyCode) final {};
    
    /** Please use onKeyReleased instead. */
    /**请用onKeyReleased 来代替. */
    CC_DEPRECATED_ATTRIBUTE virtual void keyReleased(int keyCode) final {};

	/* Callback function should not be deprecated, it will generate lots of warnings.
	Since 'setKeyboardEnabled' was deprecated, it will make warnings if developer overrides onKeyXXX and invokes setKeyboardEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    /* 回调函数不能被弃用。这将生成很多警告。
       由于 'setKeyboardEnabled' 被弃用, 如果开发者覆盖  onKeyXXX方法并且调用setKeyboardEnabled(true)来代替使用EventDispatcher::addEventListenerWithXXX将导致警告.
    */
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    CC_DEPRECATED_ATTRIBUTE virtual bool isKeypadEnabled() const final { return _keyboardEnabled; }
    CC_DEPRECATED_ATTRIBUTE virtual void setKeypadEnabled(bool value);

    /** @deprecated Please override onKeyReleased and check the keycode of KeyboardEvent::KeyCode::Menu(KEY_BACKSPACE) instead. */
    /** @deprecated 请重写onKeyReleased并且检查 KeyboardEvent::KeyCode::Menu(KEY_BACKSPACE) 的键盘码来代替. */
    CC_DEPRECATED_ATTRIBUTE virtual void keyBackClicked() final {};
    CC_DEPRECATED_ATTRIBUTE virtual void keyMenuClicked() final {};

    // Overrides
    virtual std::string getDescription() const override;

CC_CONSTRUCTOR_ACCESS:
    Layer();
    virtual ~Layer();

    virtual bool init() override;

protected:
    //add the api for avoid use deprecated api
    //添加api来避免使用废弃的api
    void _addTouchListener();

    CC_DEPRECATED_ATTRIBUTE void addTouchListener() { _addTouchListener();};
    CC_DEPRECATED_ATTRIBUTE int executeScriptTouchHandler(EventTouch::EventCode eventType, Touch* touch, Event* event);
    CC_DEPRECATED_ATTRIBUTE int executeScriptTouchesHandler(EventTouch::EventCode eventType, const std::vector<Touch*>& touches, Event* event);

    bool _touchEnabled;
    bool _accelerometerEnabled;
    bool _keyboardEnabled;
    EventListener* _touchListener;
    EventListenerKeyboard* _keyboardListener;
    EventListenerAcceleration* _accelerationListener;

    Touch::DispatchMode _touchMode;
    bool _swallowsTouches;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Layer);

};


/** LayerRGBA is a subclass of Layer that implements the RGBAProtocol protocol using a solid color as the background.
 
 All features from Layer are valid, plus the following new features that propagate into children that conform to the RGBAProtocol:
 - opacity
 - RGB colors
 @since 2.1
 *//** LayerRGBA 是Layer的一个子类，它通过使用一个单色背景实现了 RGBAProtocol 协议。
 它实现了Layer类的所有功能，并且添加了以下这些遵守RGBAProtocol协议并且传播到子类的新特性：
 - 透明度
 - RGB颜色
 @since 2.1
 */
class CC_DLL __LayerRGBA : public Layer, public __RGBAProtocol
{
public:
    CREATE_FUNC(__LayerRGBA);
    
    
    //
    // Overrides
    //
    virtual GLubyte getOpacity() const override { return Layer::getOpacity(); }
    virtual GLubyte getDisplayedOpacity() const override { return Layer::getDisplayedOpacity(); }
    virtual void setOpacity(GLubyte opacity) override { return Layer::setOpacity(opacity); }
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override { return Layer::updateDisplayedOpacity(parentOpacity); }
    virtual bool isCascadeOpacityEnabled() const override { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override { return Layer::setCascadeOpacityEnabled(cascadeOpacityEnabled); }

    virtual const Color3B& getColor() const override { return Layer::getColor(); }
    virtual const Color3B& getDisplayedColor() const override { return Layer::getDisplayedColor(); }
    virtual void setColor(const Color3B& color) override { return Layer::setColor(color); }
    virtual void updateDisplayedColor(const Color3B& parentColor) override { return Layer::updateDisplayedColor(parentColor); }
    virtual bool isCascadeColorEnabled() const override { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override { return Layer::setCascadeColorEnabled(cascadeColorEnabled); }

    virtual void setOpacityModifyRGB(bool bValue) override { return Layer::setOpacityModifyRGB(bValue); }
    virtual bool isOpacityModifyRGB() const override { return Layer::isOpacityModifyRGB(); }

protected:
    __LayerRGBA();
    virtual ~__LayerRGBA() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__LayerRGBA);
};

//
// LayerColor
//
/** @brief LayerColor is a subclass of Layer that implements the RGBAProtocol protocol.

All features from Layer are valid, plus the following new features:
- opacity
- RGB colors
*/
/** @brief 
LayerColor是Layer的一个子类，它实现了RGBAProtocol协议。
它实现了Layer类的所有功能，还添加了以下这些新功能：
- 透明度
- RGB颜色
*/
class CC_DLL LayerColor : public Layer, public BlendProtocol
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    /** creates a fullscreen black layer */
    /** 创建一个全屏的黑色布景层*/
    static LayerColor* create();
    /** creates a Layer with color, width and height in Points */
    /**  通过颜色，宽度和高度（以点为单位）来创建一个布景层 */
    static LayerColor * create(const Color4B& color, GLfloat width, GLfloat height);
    /** creates a Layer with color. Width and height are the window size. */
    /** 通过颜色来创建一个布景层。宽度和高度设置为窗口的大小 */
    static LayerColor * create(const Color4B& color);

   * change width in Points*/
/** 改变宽度（以点为单位）*/
    void changeWidth(GLfloat w);
    /** change height in Points*/
/**改变高度（以点为单位）*/ /*
    void changeHeight(GLfloat h);
    /** change width and height in Points
    @since v0.8
    */
    /** 改变宽度和高度（以点为单位）
    @since v0.8
    */
    void changeWidthAndHeight(GLfloat w ,GLfloat h);

    //
    // Overrides
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

    virtual void setContentSize(const Size & var) override;
    /** BlendFunction. Conforms to BlendProtocol protocol */
    /** BlendFunction.遵守BlendProtocol协议。 */

    /**
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc() const override;
    /**
    *@code
    *When this function bound into js or lua,the parameter will be changed
当这个函数绑定到js或者lua,参数将改变。
    *In js: var setBlendFunc(var src, var dst)
    *In lua: local setBlendFunc(local src, local dst)
    *@endcode
    */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerColor();
    virtual ~LayerColor();
    
    bool init();
    bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);
    bool initWithColor(const Color4B& color);

protected:
    void onDraw(const Mat4& transform, bool transformUpdated);

    virtual void updateColor() override;

    BlendFunc _blendFunc;
    Vec2 _squareVertices[4];
    Color4F  _squareColors[4];
    CustomCommand _customCommand;
    Vec3 _noMVPVertices[4];
private:
    CC_DISALLOW_COPY_AND_ASSIGN(LayerColor);

};

//
// LayerGradient
//
/** @brief LayerGradient is a subclass of LayerColor that draws gradients across the background.
All features from LayerColor are valid, plus the following new features:
- direction
- final color
- interpolation mode

LayerGradient是LayerColor的一个子类，它在背景上画渐变效果。
它实现了LayerColor类的所有功能，还添加了以下这些新功能：
- 渐变方向
- 渐变最终颜色
- 插值模式

Color is interpolated between the startColor and endColor along the given
vector (starting at the origin, ending at the terminus).  If no vector is
supplied, it defaults to (0, -1) -- a fade from top to bottom.
颜色沿着给定的向量插在起始颜色和终止颜色之间（从起点开始，到终点结束）。如果没有提供向量，则默认到（0，-1）点-一个从顶部到底部的淡入淡出。
If 'compressedInterpolation' is disabled, you will not see either the start or end color for
non-cardinal vectors; a smooth gradient implying both end points will be still
be drawn, however.
如果'compressedInterpolation'不可用，你将看到非基本向量的起始颜色或者终止颜色；不过无论如何，一个平滑的渐变（包括终点）最终还是会呈现出来。
If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.
如果'compressedInterpolation'是可用的(默认模式)，你将看到渐变的起始颜色和终止颜色。
@since v0.99.5
*/
class CC_DLL LayerGradient : public LayerColor
{
public:
    /** Creates a fullscreen black layer */
/**创建一个全屏的黑色布景层*/
    static LayerGradient* create();

    /** Creates a full-screen Layer with a gradient between start and end. */
/**创建从起始到末尾渐变的一个全屏的布景层。*/
    static LayerGradient* create(const Color4B& start, const Color4B& end);

    /** Creates a full-screen Layer with a gradient between start and end in the direction of v. */
/**创建以参数v为方向的从起始到末尾渐变的一个全屏的布景层。*/
    static LayerGradient* create(const Color4B& start, const Color4B& end, const Vec2& v);
    
    /** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors
     Default: true
     */
    /** 
不管插值是否被压缩，最终都为了呈现包括规范向量和不规范向量渐变的所有颜色。
默认：true
     */
    void setCompressedInterpolation(bool compressedInterpolation);
    bool isCompressedInterpolation() const;

    /** Sets the start color of the gradient */
    /**设置渐变的起始颜色*/
    void setStartColor( const Color3B& startColor );
    /** Returns the start color of the gradient */
    /**返回渐变的起始颜色*/
    const Color3B& getStartColor() const;

    /** Sets the end color of the gradient */
    /** 设置渐变的终止颜色*/
    void setEndColor( const Color3B& endColor );
    /** Returns the end color of the gradient */
    /** 返回渐变的终止颜色 */
    const Color3B& getEndColor() const;

    /** Returns the start opacity of the gradient */
    /** 返回渐变的起始透明度*/
    void setStartOpacity( GLubyte startOpacity );
    /** Returns the start opacity of the gradient */
    /** 返回渐变的起始透明度*/
    GLubyte getStartOpacity() const;

    /** Returns the end opacity of the gradient */
    /** 设置渐变的终止透明度*/
    void setEndOpacity( GLubyte endOpacity );
    /** Returns the end opacity of the gradient */
    /** 返回渐变的终止透明度*/
    GLubyte getEndOpacity() const;

    /** Sets the directional vector that will be used for the gradient.
    The default value is vertical direction (0,-1). 
     */
    /** 
      设置将用于渐变的方向向量。默认值是垂直方向（0，-1）。
     */
    void setVector(const Vec2& alongVector);
    /** Returns the directional vector used for the gradient */
    /**返回用于渐变的方向向量。*/
    const Vec2& getVector() const;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerGradient();
    virtual ~LayerGradient();
    
    virtual bool init();
    /** Initializes the Layer with a gradient between start and end.
     * @js init
     * @lua init
     */
    /** 通过从起始到终止的渐变来初始化布景层。
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    /** Initializes the Layer with a gradient between start and end in the direction of v.
     * @js init
     * @lua init
     */
    /**通过沿着方向v的从起始到终止的渐变来初始化图层。
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end, const Vec2& v);

protected:
    virtual void updateColor() override;

    Color3B _startColor;
    Color3B _endColor;
    GLubyte _startOpacity;
    GLubyte _endOpacity;
    Vec2   _alongVector;
    bool    _compressedInterpolation;
};


/** @brief MultipleLayer is a Layer with the ability to multiplex it's children.
Features:
- It supports one or more children
- Only one children will be active a time
*/
/** @brief 

*/
class CC_DLL LayerMultiplex : public Layer
{
public:
    /** creates and initializes a LayerMultiplex object 
     * @js NA
     * @lua NA
     */
    /** 创建并且初始化一个LayerMultiplex对象 
     * @js NA
     * @lua NA
     */
    static LayerMultiplex* create();

    /** creates a LayerMultiplex with an array of layers.
     @since v2.1
     * @js NA
     */
    /** 用一个layers数组创建一个 LayerMultiplex .
     @since v2.1
     * @js NA
     */
    static LayerMultiplex* createWithArray(const Vector<Layer*>& arrayOfLayers);

    /** creates a LayerMultiplex with one or more layers using a variable argument list. 
     * @code
     * When this function bound to lua or js,the input params are changed.
     * In js:var create(...)
     * In lua:local create(...)
     * @endcode
     */ 
    /** 用不少于一个通过使用一个变量参数列表的层来创建一个LayerMultiplex.
     * @code
     * 当这个函数绑定到 lua或者 js,输入参数产生了变化.
     * In js:var create(...)
     * In lua:local create(...)
     * @endcode
     */ 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // WP8 in VS2012 does not support nullptr in variable args lists and variadic templates are also not supported
    typedef Layer* M;
    static LayerMultiplex* create(M m1, std::nullptr_t listEnd) { return createVariadic(m1, NULL); }
    static LayerMultiplex* create(M m1, M m2, std::nullptr_t listEnd) { return createVariadic(m1, m2, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for variable argument lists longer than 10 items, use //createWithArray or createVariadic with NULL as the last argument
//

    static LayerMultiplex* createVariadic(Layer* item, ...) CC_REQUIRES_NULL_TERMINATION;
#else
    static LayerMultiplex * create(Layer* layer, ... );
#endif

    /**
     * lua script can not init with undetermined number of variables
     * so add these functions to be used with lua.
*lua脚本不能通过未确定数目的变量来初始化。
*所以用lua来加这些函数。
     * @js NA
     * @lua NA
     */
    static LayerMultiplex * createWithLayer(Layer* layer);


    void addLayer(Layer* layer);

    /** switches to a certain layer indexed by n.
     The current (old) layer will be removed from it's parent with 'cleanup=true'.
     */
/**
通过索引n切换到某个图层。
当前图层（旧的）将从它的父级图层用“cleanup=true"来删除。
*/
    void switchTo(int n);
    /** release the current layer and switches to another layer indexed by n.
    The current (old) layer will be removed from it's parent with 'cleanup=true'.
    */
  /** 
发布当前图层并且通过索引n来切换到另一个图层。当前图层（旧的）将从它的父级图层用“cleanup=true"来删除。
    */
    void switchToAndReleaseMe(int n);

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    LayerMultiplex();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LayerMultiplex();
    
    virtual bool init();
    /** initializes a MultiplexLayer with one or more layers using a variable argument list.
     * @js NA
     * @lua NA
     */
    /** 用不少于一个通过使用一个变量参数列表的层来初始化一个MultiplexLayer.
     * @js NA
     * @lua NA
     */
    bool initWithLayers(Layer* layer, va_list params);
    
    /** initializes a MultiplexLayer with an array of layers
     @since v2.1
     */  
    /** 通过layers数组来初始化MultiplexLayer
     @since v2.1
     */
    bool initWithArray(const Vector<Layer*>& arrayOfLayers);

protected:
    unsigned int _enabledLayer;
    Vector<Layer*>    _layers;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(LayerMultiplex);
};


// end of layer group
/// @}

NS_CC_END

#endif // __CCLAYER_H__
