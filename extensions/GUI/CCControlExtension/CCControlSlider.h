/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot. All rights reserved.
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


#ifndef __CCCONTROL_SLIDER_H__
#define __CCCONTROL_SLIDER_H__

#include "CCControl.h"
#include "CCInvocation.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

class ControlSlider: public Control
{
public:
    /**
     * 根据背景文件名，进度条文件名以及滑块文件名创建滑动条
     */
    static ControlSlider* create(const char* bgFile, const char* progressFile, const char* thumbFile);

    /**
     * 根据背景Sprite，进度条Sprite以及滑块Sprite创建滑动条
     *
     * @see initWithSprites
     */
    static ControlSlider* create(Sprite * backgroundSprite, Sprite* pogressSprite, Sprite* thumbSprite);

    /**
     * 根据背景文件名，进度条文件名、滑块普通及选中状态文件名创建滑动条
     */
    static ControlSlider* create(const char* bgFile, const char* progressFile, const char* thumbFile,
            const char* selectedThumbSpriteFile);

    /**
     * 根据背景Sprite，进度条Sprite、滑块普通及选中状态Sprite创建滑动条
     *
     * @see initWithSprites
     */
    static ControlSlider* create(Sprite * backgroundSprite, Sprite* pogressSprite, Sprite* thumbSprite,
            Sprite* selectedThumbSprite);
    /**
     * @js ctor
     */
    ControlSlider();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlSlider();

    /**
    * 根据背景Sprite，进度条Sprite以及滑块Sprite初始化滑动条
    *
    * @param backgroundSprite          用作背景的Sprite
    * @param progressSprite            用作进度条的Sprite
    * @param thumbSprite               用作滑块的Sprite
    */
    virtual bool initWithSprites(Sprite * backgroundSprite, Sprite* progressSprite, Sprite* thumbSprite);

    /** 
    * 根据背景Sprite，进度条Sprite、滑块普通及选中状态Sprite初始化滑动条
    *
    * @param backgroundSprite          用作背景的Sprite
    * @param progressSprite            用作进度条的Sprite
    * @param thumbSprite               用作滑块的Sprite
    * @param selectedThumbSprite       用作滑块选中状态的Sprite
    */
    virtual bool initWithSprites(Sprite * backgroundSprite, Sprite* progressSprite, Sprite* thumbSprite,
            Sprite* selectedThumbSprite);

    virtual void needsLayout();

    virtual void setMaximumValue(float val);
    virtual void setEnabled(bool enabled);
    virtual bool isTouchInside(Touch * touch);
    Vec2 locationFromTouch(Touch* touch);
    virtual void setValue(float val);
    virtual void setMinimumValue(float val);

protected:
    void sliderBegan(Vec2 location);
    void sliderMoved(Vec2 location);
    void sliderEnded(Vec2 location);

    virtual bool onTouchBegan(Touch* touch, Event* pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

    /** 返回给定位置对应的值 */
    float valueForLocation(Vec2 location);

    //maunally put in the setters
    /** 存放接收者的当前值 */
    CC_SYNTHESIZE_READONLY(float, _value, Value);

    /** 存放接收者的最小值
     * 默认取值为0.0 */
    CC_SYNTHESIZE_READONLY(float, _minimumValue, MinimumValue);

    /** 存放接收者的最大值
     * 默认取值为1.0 */
    CC_SYNTHESIZE_READONLY(float, _maximumValue, MaximumValue);

    CC_SYNTHESIZE(float, _minimumAllowedValue, MinimumAllowedValue);
    CC_SYNTHESIZE(float, _maximumAllowedValue, MaximumAllowedValue);

    // maybe this should be read-only
    CC_SYNTHESIZE_RETAIN(Sprite*, _thumbSprite, ThumbSprite);
    CC_SYNTHESIZE_RETAIN(Sprite*, _selectedThumbSprite, SelectedThumbSprite);
    CC_SYNTHESIZE_RETAIN(Sprite*, _progressSprite, ProgressSprite);
    CC_SYNTHESIZE_RETAIN(Sprite*, _backgroundSprite, BackgroundSprite);

};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif
