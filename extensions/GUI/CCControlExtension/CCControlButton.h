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


#ifndef __CCCONTROL_BUTTON_H__
#define __CCCONTROL_BUTTON_H__

#include "CCControl.h"
#include "CCInvocation.h"
#include "CCScale9Sprite.h"
#include "base/CCMap.h"

NS_CC_EXT_BEGIN

/* 定义按钮左右边缘空出的尺寸 */
#define ControlButtonMarginLR 8 // px
/* 定义按钮上下边缘空出的尺寸 */
#define ControlButtonMarginTB 2 // px


/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** @class ControlButton Cocos2d-x的按钮控件 */
class ControlButton : public Control
{        
public:
    static ControlButton* create();
    static ControlButton* create(Scale9Sprite* sprite);
    static ControlButton* create(Node* label, Scale9Sprite* backgroundSprite);
    static ControlButton* create(const std::string& title, const std::string& fontName, float fontSize);

    virtual void needsLayout(void);

    virtual void setEnabled(bool enabled);
    virtual void setSelected(bool enabled);
    virtual void setHighlighted(bool enabled);

    bool isPushed() const { return _isPushed; }

    /**
     * 返回指定状态对应的标题文本
     *
     * @param state 用于指定标题文本的状态，取值范围见"Control::State"。
     *
     * @return 指定状态对应的标题文本
     */
    virtual std::string getTitleForState(State state);

    /**
     * 设置用于指定状态的标题文本
     * 如果某状态没有被赋值，则默认使用ButtonStateNormal对应的值
     *
     * @param title 用于所给状态的标题文本
     * @param state 标题文本对应的状态，取值范围见"Control::State"
     */
    virtual void setTitleForState(const std::string& title, State state);

    /**
     * 返回指定状态对应的标题文本颜色
     *
     * @param state 用于指定标题文本颜色的状态，取值范围见"Control::State"。
     *
     * @return 指定状态对应的标题文本颜色
     */

    virtual Color3B getTitleColorForState(State state) const;

    /**
     * 设置指定状态对应的标题文本颜色
     *
     * @param color 用于所给状态的标题文本颜色
     * @param state 标题文本颜色对应的状态，取值范围见"Control::State"
     */
    virtual void setTitleColorForState(const Color3B& color, State state);

    /**
     * 返回指定状态对应的标题Label
     *
     * @param state 用于指定标题Label的状态，取值范围见"Control::State"。
     */
    virtual Node* getTitleLabelForState(State state);

    /**
     * 设置用于指定状态的标题Label
     * 如果某状态没有被赋值，则默认使用ButtonStateNormal对应的值
     *
     * @param label 用于所给状态的标题Label
     * @param state 标题Label对应的状态，取值范围见"Control::State"
     */
    virtual void setTitleLabelForState(Node* label, State state);

    virtual void setTitleTTFForState(const std::string& fntFile, State state);
    virtual const std::string& getTitleTTFForState(State state);

    virtual void setTitleTTFSizeForState(float size, State state);
    virtual float getTitleTTFSizeForState(State state);

    /**
     * 设置Label的字体，如果情况需要则改用BMFont。
     * @param fntFile 用于所给状态的目标字体名称
     * @param state 字体对应的状态，取值范围见"Control::State"
     */
    virtual void setTitleBMFontForState(const std::string& fntFile, State state);
    virtual const std::string& getTitleBMFontForState(State state);

    /**
     * 返回指定状态对应的背景精灵
     *
     * @param state 用于指定背景精灵的状态，取值范围见"Control::State"。
     */
    virtual Scale9Sprite* getBackgroundSpriteForState(State state);

    /**
     * 设置用于指定状态的背景精灵
     *
     * @param sprite 用于所给状态的背景精灵
     * @param state 背景精灵对应的状态，取值范围见"Control::State"
     */
    virtual void setBackgroundSpriteForState(Scale9Sprite* sprite, State state);

    /**
     * 设置用于指定状态的spriteFrame
     *
     * @param spriteFrame 用于所给状态的spriteFrame
     * @param state spriteFrame对应的状态，取值范围见"Control::State"
     */
    virtual void setBackgroundSpriteFrameForState(SpriteFrame * spriteFrame, State state);

    //同时设置按钮水平与竖直方向的空白尺寸 (needsLayout只用调用一次)
    virtual void setMargins(int marginH, int marginV);

    /** 是否调整背景图，默认为是。
     如果设为否，则背景图直接使用prefered size指定的尺寸 */
    bool doesAdjustBackgroundImage();
    void setAdjustBackgroundImage(bool adjustBackgroundImage);

    // Overrides
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    virtual void onTouchMoved(Touch *touch, Event *event) override;
    virtual void onTouchEnded(Touch *touch, Event *event) override;
    virtual void onTouchCancelled(Touch *touch, Event *event) override;
    virtual GLubyte getOpacity(void) const override;
    virtual void setOpacity(GLubyte var) override;
	virtual const Color3B& getColor(void) const override;
	virtual void setColor(const Color3B&) override;


    const std::string& getCurrentTitle() const { return _currentTitle; };
    std::string getCurrentTitle() { return _currentTitle; };
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ControlButton();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlButton();
    
    virtual bool init() override;
    virtual bool initWithLabelAndBackgroundSprite(Node* label, Scale9Sprite* backgroundSprite);
    virtual bool initWithBackgroundSprite(Scale9Sprite* sprite);
    virtual bool initWithTitleAndFontNameAndFontSize(const std::string& title, const std::string& fontName, float fontSize);
    
protected:
    bool _isPushed;
    bool _parentInited;
    bool _doesAdjustBackgroundImage;

    /** 按钮当前显示的标题文本 */
    std::string _currentTitle;

    /** 标题文本的当前颜色 */
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(Color3B, _currentTitleColor, CurrentTitleColor);

    /** 当前标题Label */
    CC_SYNTHESIZE_RETAIN(Node*, _titleLabel, TitleLabel);

    /** 当前背景精灵 */
    CC_SYNTHESIZE_RETAIN(Scale9Sprite*, _backgroundSprite, BackgroundSprite);

    /** 按钮的期望尺寸，如果标题Label更大则扩充尺寸 */
    CC_PROPERTY_PASS_BY_REF(Size, _preferredSize, PreferredSize);

    /** 设置按钮是否需要在按下时进行缩放，默认为是 */
    CC_PROPERTY(bool, _zoomOnTouchDown, ZoomOnTouchDown);
    /** 设置按钮在按下时的放大比例，默认为 1.1f */
    CC_SYNTHESIZE(float, _scaleRatio, ScaleRatio);

    CC_PROPERTY_PASS_BY_REF(Vec2, _labelAnchorPoint, LabelAnchorPoint);

    std::unordered_map<int, std::string> _titleDispatchTable;
    std::unordered_map<int, Color3B> _titleColorDispatchTable;

    Map<int, Node*> _titleLabelDispatchTable;
    Map<int, Scale9Sprite*> _backgroundSpriteDispatchTable;

    /* 定义按钮上下边缘的空白尺寸 */
    CC_SYNTHESIZE_READONLY(int, _marginV, VerticalMargin);
    /* 定义按钮左右边缘的空白尺寸 */
    CC_SYNTHESIZE_READONLY(int, _marginH, HorizontalOrigin);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ControlButton);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif
