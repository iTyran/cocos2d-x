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

#ifndef __ActionFRAME_H__
#define __ActionFRAME_H__

#include "math/CCGeometry.h"
#include "2d/CCActionInterval.h"

namespace cocostudio {
    
enum FrameType
{
	kKeyframeMove = 0,
	kKeyframeScale,
	kKeyframeRotate,
	kKeyframeTint,
	kKeyframeFade,
	kKeyframeMax
};

enum class FrameEaseType
{
	Custom = -1,

	LINERAR = 0,

    SINE_EASEIN,
	SINE_EASEOUT,
	SINE_EASEINOUT,

    QUAD_EASEIN,
	QUAD_EASEOUT,
    QUAD_EASEINOUT,

    CUBIC_EASEIN,
    CUBIC_EASEOUT,
    CUBIC_EASEINOUT,

    QUART_EASEIN,
    QUART_EASEOUT,
    QUART_EASEINOUT,

    QUINT_EASEIN,
	QUINT_EASEOUT,
    QUINT_EASEINOUT,

    EXPO_EASEIN,
    EXPO_EASEOUT,
    EXPO_EASEINOUT,

    CIRC_EASEIN,
    CIRC_EASEOUT,
    CIRC_EASEINOUT,

    ELASTIC_EASEIN,
    ELASTIC_EASEOUT,
    ELASTIC_EASEINOUT,

    BACK_EASEIN,
    BACK_EASEOUT,
    BACK_EASEINOUT,

    BOUNCE_EASEIN,
    BOUNCE_EASEOUT,
    BOUNCE_EASEINOUT,

	TWEEN_EASING_MAX = 10000
};
/**
*  @js NA
*  @lua NA
*/
class ActionFrame: public cocos2d::Ref
{

public:

	/**
	* 默认构造函数
	*/
	ActionFrame();

	/**
	* 默认析构函数
	*/
	virtual ~ActionFrame();

	/**
	* 改变动作帧的索引值
	*
	* @param index   动作帧的索引值
	*/
	void setFrameIndex(int index);

	/**
	* 获取动作帧的索引值
	*
	* @return 动作帧的索引
	*/
	int getFrameIndex();

	/**
	* 改变动作帧的时间
	*
	* @param fTime  动画帧的时间
	*/
	void setFrameTime(float fTime);

	/**
	* 获取动作帧的时间
	*
	* @return fTime  动作帧的时间
	*/
	float getFrameTime();

	/**
	* 改变动作帧的类型
	*
	* @param frameType   动作帧的类型
	*/
	void setFrameType(int frameType);

	/**
	* 获取动作帧的类型
	*
	* @return 动作帧的类型
	*/
	int getFrameType();

	/**
	* 更改移除类型
	*
	* @param easingType 移除类型
	*/
	void setEasingType(int easingType);

	/**
	* 获取移除类型
	*
	* @return 移除类型
	*/
	int getEasingType();

	/**
	* 获取ActionFrame的ActionInterval
	*
	* @parame duration   ActionFrame的时间间隔
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
	/**
	* 获取ActionFrame的ActionInterval
	*
	* @parame duration   ActionFrame的时间间隔
	*
	* @parame srcFrame   源ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration,ActionFrame* srcFrame);

	/**
	* 设置ActionInterval的移除参数.
	*
	*@parame parameter   移除参数
	*
	*/
	virtual void setEasingParameter(std::vector<float>& parameter);
protected:
	/**
	* 获取ActionFrame的移除动作
	*
	* @parame action   ActionFrame的时间周期
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getEasingAction(cocos2d::ActionInterval* action);
protected:
	int _frameType;	
	int _frameIndex;
	float _fTime;
	FrameEaseType _easingType;
	std::vector<float> _Parameter;
};

/**
*  @js NA
*  @lua NA
*/
class ActionMoveFrame:public ActionFrame
{
public:

	/**
	* 默认构造函数
	*/
	ActionMoveFrame();

	/**
	* 默认析构函数
	*/
	virtual ~ActionMoveFrame();

	/**
	* 改变move动作的位置
	*
	* @param move动作的位置
	*/
	void setPosition(cocos2d::Vec2 pos);

	/**
	* 获取move动作的位置
	*
	* @return 移除动作的位置
	*/
	cocos2d::Vec2 getPosition();

	/**
	* 获取ActionFrame的ActionInterval
	*
	* @parame duration   ActionFrame的持续时间
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
protected:
    cocos2d::Vec2 _position;
};

/**
*  @js NA
*  @lua NA
*/
class ActionScaleFrame:public ActionFrame
{
public:

	/**
	* 默认构造函数
	*/
	ActionScaleFrame();

	/**
	* 默认析构函数
	*/
	virtual ~ActionScaleFrame();

	/**
	* 改变scale动作的x上的缩放
	*
	* @param scale动作的x上的缩放
	*/
	void setScaleX(float scaleX);

	/**
	* 获取scale动作的x上的缩放
	*
	* @return scale动作的x上的缩放
	*/
	float getScaleX();

	/**
	* 改变scale动作的y上的缩放
	*
	* @param scale动作的x上的缩放
	*/
	void setScaleY(float scaleY);

	/**
	* 获取scale动作的y上的缩放
	*
	* @return scale动作的y上的缩放
	*/
	float getScaleY();

	/**
	* 获取ActionFrame的ActionInterval
	*
	* @parame duration  ActionFrame的持续时间
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
protected:
	float _scaleX;
	float _scaleY;
};
/**
*  @js NA
*  @lua NA
*/
class ActionRotationFrame:public ActionFrame
{
public:

	/**
	* 默认构造函数
	*/
	ActionRotationFrame();

	/**
	* 默认析构函数
	*/
	virtual ~ActionRotationFrame();

	/**
	* 改变Rotation动作的值
	*
	* @param rotation 旋转的值
	*/
	void setRotation(float rotation);

	/**
	* 获取Rotation的值
	*
	* @return Rotation的值
	*/
	float getRotation();

	/**
	* 获取ActionFrame的ActionInterval
	*
	* @parame duration   ActionFrame的持续时间
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
	/**
	* 获取ActionFrame的ActionInterval值
	*
	* @parame duration   ActionFrame的持续时间
	*
	* @parame duration   源ActionFrame
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration,ActionFrame* srcFrame);
public:
	float _rotation;
};
/**
*  @js NA
*  @lua NA
*/
class ActionFadeFrame:public ActionFrame
{
public:

	/**
	* 默认构造函数
	*/
	ActionFadeFrame();

	/**
	* 默认析构函数
	*/
	virtual ~ActionFadeFrame();

	/**
	* 改变fade动作的不透明度(opacity)
	*
	* @param opacity fade动作的不透明度
	*/
	void setOpacity(int opacity);

	/**
	* 获取fade动作的不透明度
	*
	* @return fade动作的不透明度
	*/
	int getOpacity();

	/**
	* 获取ActionFrame的ActionInterval
	*
	* @parame duration   ActionFrame的持续时间
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
protected:
	float _opacity;
};
/**
*  @js NA
*  @lua NA
*/
class ActionTintFrame:public ActionFrame
{

public:

	/**
	* 默认构造函数
	*/
	ActionTintFrame();

	/**
	* 默认析构函数
	*/
	virtual ~ActionTintFrame();

	/**
	* 改变tint动作的颜色
	*
	* @param ccolor tint动作的颜色
	*/
	void setColor(cocos2d::Color3B ccolor);

	/**
	* 获取tint动作的颜色
	*
	* @return tint动作的颜色
	*/
	cocos2d::Color3B getColor();

	/**
	* 获取ActionFrame的ActionInterval
	*
	* @parame duration   ActionFrame的持续时间
	*
	* @return ActionInterval
	*/
	virtual cocos2d::ActionInterval* getAction(float duration);
protected:
	cocos2d::Color3B _color;
};

}

#endif
