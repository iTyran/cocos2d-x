/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
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
#ifndef __CCLABELTTF_H__
#define __CCLABELTTF_H__

#include "2d/CCNode.h"

NS_CC_BEGIN

class Label;

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */


/** @brief LabelTTF是TextureNode的一个子类，它懂得如何渲染文本标签。
 *
 * 在LabelTTF中，从TextureNode继承的所有特性都是可用的。
 *
 * LabelTTF类实例化的对象比较慢。可以考虑用LabelAtlas或者LabelBMFont类来代替。
 *
 * 自定义的ttf文件要被放到"assets/"目录下或者外部存储以便应用程序可以访问到。
 *
 * @code
 * LabelTTF *label1 = LabelTTF::create("alignment left", "A Damn Mess", fontSize, blockSize, 
 *                                          TextHAlignment::LEFT, TextVAlignment::CENTER);
 * LabelTTF *label2 = LabelTTF::create("alignment right", "/mnt/sdcard/Scissor Cuts.ttf", fontSize, blockSize,
 *                                          TextHAlignment::LEFT, TextVAlignment::CENTER);
 * @endcode
 *
 */
class CC_DLL CC_DEPRECATED_ATTRIBUTE LabelTTF : public Node, public LabelProtocol, public BlendProtocol
{
public:
    /**
     * @js ctor
     */
    LabelTTF();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelTTF();

    /** 通过字体名称，对齐方式，维度(以点为单位)和字体大小（以点为单位）来创建标签。
     @since v2.0.1
     */
    static LabelTTF * create(const std::string& string, const std::string& fontName, float fontSize,
                             const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::CENTER,
                             TextVAlignment vAlignment = TextVAlignment::TOP);
    
    
    /** 通过字符串和一个字体定义来创建标签。*/
    static LabelTTF * createWithFontDefinition(const std::string& string, FontDefinition &textDefinition);
    
    /** 通过字体名称，对齐方式，维度和字体大小来初始化LabelTTF类。 */
    bool initWithString(const std::string& string, const std::string& fontName, float fontSize,
                        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT, 
                        TextVAlignment vAlignment = TextVAlignment::TOP);
    
    /** 通过字体名称，对齐方式，维度和字体大小来初始化LabelTTF类。*/
    bool initWithStringAndTextDefinition(const std::string& string, FontDefinition &textDefinition);
    
    /** 用这个标签设置文本定义 */
    void setTextDefinition(const FontDefinition& theDefinition);
    
    /** 用这个标签获取文本定义*/
    const FontDefinition& getTextDefinition() const;
    
    
    /** 添加或者取消标签阴影 */
    void enableShadow(const Size &shadowOffset, float shadowOpacity, float shadowBlur, bool mustUpdateTexture = true);
    
    /** 取消阴影渲染 */
    void disableShadow(bool mustUpdateTexture = true);
    
    /** 添加或者取消空心效果 */
    void enableStroke(const Color3B &strokeColor, float strokeSize, bool mustUpdateTexture = true);
    
    /** 取消空心效果*/
    void disableStroke(bool mustUpdateTexture = true);
    
    /** 给文本着色*/
    void setFontFillColor(const Color3B &tintColor, bool mustUpdateTexture = true);

    /** 创建一个标签
     */
    static LabelTTF * create();

    /** 修改字符串来渲染
     * @warning 修改字符串和创建一个新的LabelTTF类一样麻烦。可以通过使用LabelAtlas类来获得更好的性能。
     */
    virtual void setString(const std::string &label) override;
    virtual const std::string& getString(void) const override ;
    
    TextHAlignment getHorizontalAlignment() const;
    void setHorizontalAlignment(TextHAlignment alignment);
    
    TextVAlignment getVerticalAlignment() const;
    void setVerticalAlignment(TextVAlignment verticalAlignment);
    
    const Size& getDimensions() const;
    void setDimensions(const Size &dim);
    
    float getFontSize() const;
    void setFontSize(float fontSize);
    
    const std::string& getFontName() const;
    void setFontName(const std::string& fontName);

    virtual void setBlendFunc(const BlendFunc &blendFunc) override;

    virtual const BlendFunc &getBlendFunc() const override;

    virtual void setFlippedX(bool flippedX);
    virtual void setFlippedY(bool flippedY);

    virtual Rect getBoundingBox() const override;

    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
    virtual const Size& getContentSize() const override;
protected:
    Label*    _renderLabel;
    bool _contentDirty;
};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCLABEL_H__

