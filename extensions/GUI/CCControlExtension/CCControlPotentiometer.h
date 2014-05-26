/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2012 Yannick Loriot. All rights reserved.
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
 */
#ifndef __CCCONTROLPOTENTIOMETER_H__
#define __CCCONTROLPOTENTIOMETER_H__

#include "CCControl.h"
#include "2d/CCProgressTimer.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** @class ControlPotentiometer，Cocos2d-x的旋钮控件 */
class ControlPotentiometer : public Control
{
public:
    /**
     * 根据轨道、进度条、旋钮的资源文件名创建potentiometer。
     */
    static ControlPotentiometer* create(const char* backgroundFile, const char* progressFile, const char* thumbFile);
    /**
     * @js ctor
     */
    ControlPotentiometer();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlPotentiometer();

    /** 
     * 用轨道精灵，进度条对象以及旋钮精灵初始化potentiometer
     *
     * @param trackSprite   用于做背景的精灵
     * @param progressTimer 用于计时器
     * @param thumbSprite   用于旋钮的精灵
     */
    bool initWithTrackSprite_ProgressTimer_ThumbSprite(Sprite* trackSprite, ProgressTimer* progressTimer, Sprite* thumbSprite);

    void setValue(float value);
    float getValue();
     
    void setMinimumValue(float minimumValue);
    float getMinimumValue();

    void setMaximumValue(float maximumValue);
    float getMaximumValue();

    // Overrides
    virtual bool isTouchInside(Touch * touch) override;
    void setEnabled(bool enabled) override;
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;

    /** 将事件分解派发到这些方法 */
    void potentiometerBegan(Vec2 location);
    void potentiometerMoved(Vec2 location);
    void potentiometerEnded(Vec2 location);

    /** 返回点1与点2之间的距离 */
    float distanceBetweenPointAndPoint(Vec2 point1, Vec2 point2);
    /** 返回线1与线2之间的角度，单位为度 */
    float angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint(
        Vec2 beginLineA, 
        Vec2 endLineA,
        Vec2 beginLineB,
        Vec2 endLineB);

protected:
    /** 存放接收者当前值 */
    float           _value;
    /** 存放接收者的最小值，默认为0.0 */
    float           _minimumValue;
    /** 存放接收者的最大值，默认为1.0 */
    float           _maximumValue;

    CC_SYNTHESIZE_RETAIN(Sprite*, _thumbSprite, ThumbSprite)
    CC_SYNTHESIZE_RETAIN(ProgressTimer*, _progressTimer, ProgressTimer)
    CC_SYNTHESIZE(Vec2, _previousLocation, PreviousLocation)
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif /* __CCCONTROLPOTENTIOMETER_H__ */
