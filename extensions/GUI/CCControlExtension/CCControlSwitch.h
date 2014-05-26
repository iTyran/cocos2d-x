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

#ifndef __CCCONTROLSWITCH_H__
#define __CCCONTROLSWITCH_H__

#include "CCControl.h"


namespace cocos2d { class Sprite; }
namespace cocos2d { class Label; }

NS_CC_EXT_BEGIN

class ControlSwitchSprite;

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** @class ControlSwitch Cocos2d-x的开关控件 */
class ControlSwitch : public Control
{
public:
    /** 根据蒙版Sprite、开/关状态Sprite、滑块Sprite、开/关状态Label创建开关控件 */
    static ControlSwitch* create(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite, Label* onLabel, Label* offLabel);
    /** 根据蒙版Sprite、开/关状态Sprite、滑块Sprite创建开关控件 */
    static ControlSwitch* create(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite);
    /**
     * @js ctor
     */
    ControlSwitch();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlSwitch();

    /** 根据蒙版Sprite、开/关状态Sprite、滑块Sprite初始化开关控件 */
    bool initWithMaskSprite(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite);
    /** 根据蒙版Sprite、开/关状态Sprite、滑块Sprite、开/关状态Label初始化开关控件 */
    bool initWithMaskSprite(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite, Label* onLabel, Label* offLabel);

    /**
     * 将开关状态设为开或者关，并可选是否播放过渡动画
     *
     * @param isOn 为真则开关打开，为假则开关关闭
     * 如果开关已经在此状态则什么都不发生
     * @param animated 为真则开关切换播放过渡动画，为假则直接切换
     */
    void setOn(bool isOn, bool animated);
    void setOn(bool isOn);
    bool isOn(void) const { return _on; }
    bool hasMoved() const { return _moved; }
    virtual void setEnabled(bool enabled);

    Vec2 locationFromTouch(Touch* touch);

    // Overrides
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent) override;

protected:
    /** 用于表现本控件的Sprite派生类 */
    ControlSwitchSprite* _switchSprite;
    float _initialTouchXPosition;
    
    bool _moved;
    /** 表示开关状态的布尔值 */
    bool _on;
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif /* __CCCONTROLSWITCH_H__ */

