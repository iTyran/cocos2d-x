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

#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

CC_DEPRECATED_ATTRIBUTE typedef enum
{
    SLIDER_PERCENTCHANGED
}SliderEventType;

CC_DEPRECATED_ATTRIBUTE typedef void (Ref::*SEL_SlidPercentChangedEvent)(Ref*,SliderEventType);
#define sliderpercentchangedselector(_SELECTOR) (SEL_SlidPercentChangedEvent)(&_SELECTOR)

/**
*   @js NA
*   @lua NA
*/
class Slider : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class EventType
    {
        ON_PERCENTAGE_CHANGED
    };
    typedef std::function<void(Ref*,EventType)> ccSliderCallback;
    /**
     * 默认构造函数
     */
    Slider();
    
    /**
     * 默认析构函数
     */
    virtual ~Slider();
    
    /**
     * 分配并初始化
     */
    static Slider* create();
    
    /**
     * 加载滑动条的纹理贴图（texture）
     *
     * @param fileName   纹理贴图（texture）名.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadBarTexture(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * 设置是否使用九宫（scale9）渲染器渲染滑动条
     *
     * @param 如果是true就使用九宫（scale9）渲染器进行渲染，如果是false则不是用九宫（scale9）渲染器进行渲染
     */
    void setScale9Enabled(bool able);
    
    bool isScale9Enabled();
    
    /**
     * 如果滑动条使用九宫（scale9）渲染器进行渲染，设置滑动条的capinsets
     *
     * @param capInsets    滑动条的capinsets
     */
    void setCapInsets(const Rect &capInsets);
    
    /**
     * 如果滑动条使用九宫（scale9）渲染器进行渲染，设置滑动条的capinsets
     *
     * @param capInsets    滑动条的capinsets
     */
    void setCapInsetsBarRenderer(const Rect &capInsets);
    
    const Rect& getCapInsetsBarRenderer();
    
    /**
     * 如果滑动条使用九宫（scale9）渲染器进行渲染，设置滑动条的capinsets
     *
     * @param capInsets    滑动条的capinsets
     */
    void setCapInsetProgressBarRebderer(const Rect &capInsets);
    
    const Rect& getCapInsetsProgressBarRebderer();
    
    /**
     * Load textures for slider ball.加载滑动条的纹理贴图（texture）
     *
     * @param slider ball normal    正常状态下的纹理贴图（texture）
     *
     * @param slider ball selected    被选中状态下的纹理贴图（texture）.
     *
     * @param slider ball disabled    禁用状态下的纹理贴图（texture）.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTextures(const std::string& normal,
                              const std::string& pressed,
                              const std::string& disabled,
                              TextureResType texType = TextureResType::LOCAL);
    
    /**
     * 加载滑动条在正常状态下的纹理贴图（texture）
     *
     * @param normal    正常状态下的纹理贴图（texture）
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTextureNormal(const std::string& normal,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * 加载滑动条在被选中状态下的纹理贴图（texture）
     *
     * @param selected    被选中状态下的纹理贴图（texture）
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTexturePressed(const std::string& pressed,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * 加载滑动条禁用状态下的纹理贴图（texture）
     *
     * @param disabled    禁用状态下的纹理贴图（texture）
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTextureDisabled(const std::string& disabled,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * 加载滑动进度条在禁用状态下的纹理贴图（texture）
     *
     * @param fileName    纹理贴图（texture）的文件目录
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadProgressBarTexture(const std::string& fileName, TextureResType texType = TextureResType::LOCAL);
    
    /**
     * 改变滑动条目前的进度
     *
     * @param percent    1到100的任意整数，用于表示百分比
     */
    void setPercent(int percent);
    
    /**
     * 获取滑动条的当前进度
     *
     * @return percent    1到100的任意整数，用于表示百分比
     */
    int getPercent();
    
    /**
     * 添加在改变滑动条当前进度时调用的回调函数
     */
    CC_DEPRECATED_ATTRIBUTE void addEventListenerSlider(Ref* target,SEL_SlidPercentChangedEvent selector);
    void addEventListener(const ccSliderCallback& callback);
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    
    //重写widget的 "getVirtualRendererSize" 方法
    virtual const Size& getVirtualRendererSize() const override;
    
    //重写widget的 "getVirtualRenderer" 方法
    virtual Node* getVirtualRenderer() override;
    
    //重写widget的 "ignoreContentAdaptWithSize" 方法
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    //重写widget的 hitTest 函数以用于展示其自身
    virtual bool hitTest(const Vec2 &pt) override;
    /**
     * 返回widget的类名
     */
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:
    virtual void initRenderer() override;
    float getPercentWithBallPos(float location);
    void percentChangedEvent();
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    void barRendererScaleChangedWithSize();
    void progressBarRendererScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    Node*  _barRenderer;
    Node* _progressBarRenderer;
    Size _progressBarTextureSize;
    
    Sprite* _slidBallNormalRenderer;
    Sprite* _slidBallPressedRenderer;
    Sprite* _slidBallDisabledRenderer;
    Node* _slidBallRenderer;
    
    float _barLength;
    int _percent;
    
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    std::string _textureFile;
    std::string _progressBarTextureFile;
    std::string _slidBallNormalTextureFile;
    std::string _slidBallPressedTextureFile;
    std::string _slidBallDisabledTextureFile;

    Rect _capInsetsBarRenderer;
    Rect _capInsetsProgressBarRenderer;

    Ref*       _sliderEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 或者其更高版本
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_SlidPercentChangedEvent    _sliderEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 或者其更高版本
#pragma warning (pop)
#endif
    
    ccSliderCallback  _eventCallback;
    
    TextureResType _barTexType;
    TextureResType _progressBarTexType;
    TextureResType _ballNTexType;
    TextureResType _ballPTexType;
    TextureResType _ballDTexType;
    bool _barRendererAdaptDirty;
    bool _progressBarRendererDirty;
};

}
NS_CC_END

#endif /* defined(__CocoGUI__Slider__) */
