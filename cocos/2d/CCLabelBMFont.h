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

Use any of these editors to generate BMFonts:
  http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
  http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
  http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
  http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/
#ifndef __CCBITMAP_FONT_ATLAS_H__
#define __CCBITMAP_FONT_ATLAS_H__

#include "2d/CCLabel.h"
#if CC_LABELBMFONT_DEBUG_DRAW
#include "renderer/CCCustomCommand.h"
#endif

NS_CC_BEGIN

/** @brief LabelBMFont is a subclass of SpriteBatchNode.
＃＃＃＃＃＃@摘要   LabelBMFont 是SpriteBatchNode的一个子类。

Features:
- Treats each character like a Sprite. This means that each individual character can be:
- rotated
- scaled
- translated
- tinted
- change the opacity
- It can be used as part of a menu item.
- anchorPoint can be used to align the "label"
- Supports AngelCode text format
＃＃＃＃＃＃特征：
＃＃＃＃＃＃－每一个字符都被和精灵一样同等看待。这就意味着对每一个单独的字符都可以被如下操作：
＃＃＃＃＃＃－旋转
＃＃＃＃＃＃－缩放
＃＃＃＃＃＃－翻译
＃＃＃＃＃＃－着色
＃＃＃＃＃＃－改变透明度
＃＃＃＃＃＃－它可以被用来作为菜单项的一部分。
＃＃＃＃＃＃－anchorPoint可用于对齐“label”
＃＃＃＃＃＃－支持AngelCode文本格式

Limitations:
- All inner characters are using an anchorPoint of (0.5f, 0.5f) and it is not recommend to change it
because it might affect the rendering
＃＃＃＃＃＃限制：
＃＃＃＃＃＃－所有的内部字符都以点(0.5f, 0.5f)作为锚点，而且不建议去修改锚点位置，因为这样会影响渲染。

LabelBMFont implements the protocol LabelProtocol, like Label and LabelAtlas.
LabelBMFont has the flexibility of Label, the speed of LabelAtlas and all the features of Sprite.
If in doubt, use LabelBMFont instead of LabelAtlas / Label.
＃＃＃＃＃＃LabelBMFont实现了协议LabelProtocol，就像Label和LabelAtlas一样。
＃＃＃＃＃＃LabelBMFont有Label的灵活性，LabelAtlas的速度以及Sprite的所有特性。
＃＃＃＃＃＃ 如有疑问，请使用LabelBMFont来代替LabelAtlas / Label。

Supported editors:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

@since v0.8
*/

class CC_DLL CC_DEPRECATED_ATTRIBUTE LabelBMFont : public Node, public LabelProtocol, public BlendProtocol
{
public:
    /**
     * @js ctor
     */
    LabelBMFont();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelBMFont();

    /** creates a bitmap font atlas with an initial string and the FNT file */
    /** 使用一个初始化字符串和FNT文件创建一个“atlas”字体的位图*/
    static LabelBMFont * create(const std::string& str, const std::string& fntFile, float width = 0, TextHAlignment alignment = TextHAlignment::LEFT,const Vec2& imageOffset = Vec2::ZERO);

    /** Creates an label.  创建一个label
     */
    static LabelBMFont * create();

    /** init a bitmap font atlas with an initial string and the FNT file */
    /** 使用一个初始化字符串和FNT文件初始化一个“atlas”字体的位图*/
    bool initWithString(const std::string& str, const std::string& fntFile, float width = 0, TextHAlignment alignment = TextHAlignment::LEFT,const Vec2& imageOffset = Vec2::ZERO);

    // super method  －－ 父类方法
    virtual void setString(const std::string& newString) override;

    virtual const std::string& getString() const override;

    virtual void setAlignment(TextHAlignment alignment);
    virtual void setWidth(float width);
    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
    
    // RGBAProtocol  －－ RGBA协议
    virtual bool isOpacityModifyRGB() const;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB);

    void setFntFile(const std::string& fntFile, const Vec2& imageOffset = Vec2::ZERO);
    const std::string& getFntFile() const;

    virtual void setBlendFunc(const BlendFunc &blendFunc) override;

    virtual const BlendFunc &getBlendFunc() const override;

    virtual Sprite * getLetter(int ID);
    virtual Node * getChildByTag(int tag) override;

    virtual void setColor(const Color3B& color) override;

    virtual const Size& getContentSize() const override;
    virtual Rect getBoundingBox() const override;

    virtual std::string getDescription() const override;
#if CC_LABELBMFONT_DEBUG_DRAW
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
#endif

private:
#if CC_LABELBMFONT_DEBUG_DRAW
    CustomCommand   _customDebugDrawCommand;
    void drawDebugData(const Mat4& transform, bool transformUpdated);
#endif
    
    // name of fntFile －－ FNT 文件名
    std::string _fntFile;

    Label*      _label;

};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCBITMAP_FONT_ATLAS_H__
