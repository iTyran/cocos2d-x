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

#ifndef __CCCONTROLSTEPPER_H__
#define __CCCONTROLSTEPPER_H__

#include "CCControl.h"
#include "2d/CCLabel.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class ControlStepper : public Control
{
public:
    enum class Part
    {
        MINUS,
        PLUS,
        NONE
    };
    
    static ControlStepper* create(Sprite *minusSprite, Sprite *plusSprite);
    /**
     * @js ctor
     */
    ControlStepper();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlStepper();

    bool initWithMinusSpriteAndPlusSprite(Sprite *minusSprite, Sprite *plusSprite);

    virtual void setWraps(bool wraps);
    virtual void setMinimumValue(double minimumValue);
    virtual void setMaximumValue(double maximumValue);
    virtual void setValue(double value);

    virtual double getValue() const;
    virtual void setStepValue(double stepValue);
    /** 为stepper设置数值. 如果send参数取值为真, Control::EventType::VALUE_CHANGED事件会被发送 */
    virtual void setValueWithSendingEvent(double value, bool send);
    virtual bool isContinuous() const;

    // Overrides
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;
    void update(float dt);

    /** 根据所给触摸位置，更新stepper的布局 */
    void updateLayoutUsingTouchLocation(Vec2 location);

    /** 开始自动重复增加/减少 */
    void startAutorepeat();

    /** 停止自动重复 */
    void stopAutorepeat();

protected:
    /** stepper的数值 */
    double                  _value;
    /** stepper的状态是否为连续 */
    bool                    _continuous;
    /** stepper的状态是否为自动重复 */
    bool                    _autorepeat;
    /** stepper的状态是否为可循环（超出最大值后变成最小值，反之亦然） */
    bool                    _wraps;
    /** stepper的最小值 */
    double                  _minimumValue;
    /** stepper的最大值 */
    double                  _maximumValue;
    /** stepper的步长 */
    double                  _stepValue;
    bool                    _touchInsideFlag;
    Part                    _touchedPart;
    int                     _autorepeatCount;

    // Weak links to children
	CC_SYNTHESIZE_RETAIN(Sprite*, _minusSprite, MinusSprite)
    CC_SYNTHESIZE_RETAIN(Sprite*, _plusSprite, PlusSprite)
    CC_SYNTHESIZE_RETAIN(Label*, _minusLabel, MinusLabel)
    CC_SYNTHESIZE_RETAIN(Label*, _plusLabel, PlusLabel)
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif /* __CCCONTROLSTEPPER_H__ */
