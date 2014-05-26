/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
CopyRight (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCATLAS_NODE_H__
#define __CCATLAS_NODE_H__

#include "2d/CCNode.h"
#include "2d/CCProtocols.h"
#include "base/ccTypes.h"
#include "renderer/CCQuadCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

class TextureAtlas;

/** @brief AtlasNode是Node的扩展，实现了RGBAProtocol和TextureProtocol协议

它知道如何渲染TextureAtlas对象

所有关于Node的特性都可能，并具有下面的特性:
- opacity and RGB colors
*/
class CC_DLL AtlasNode : public Node, public TextureProtocol
{    
public:
	/** 从Atlas文件创建一个AtlasNode，并设置它的宽、高以及itme数量 */
	static AtlasNode * create(const std::string& filename, int tileWidth, int tileHeight, int itemsToRender);

    /** 更新Atlas (定点索引数组).
    * 需要被子类重写
    */
    virtual void updateAtlasValues();

    void setTextureAtlas(TextureAtlas* textureAtlas);
    TextureAtlas* getTextureAtlas() const;
    
    void setQuadsToDraw(ssize_t quadsToDraw);
    ssize_t getQuadsToDraw() const;

    
    // Overrides
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual const Color3B& getColor(void) const override;
    virtual void setColor(const Color3B& color) override;
    virtual void setOpacity(GLubyte opacity) override;
    /**
    * @code
    * 当绑定到js或lua，参数将发生变化
    * js中: var setBlendFunc(var src, var dst)
    * @endcode
    * @lua NA
    */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc() const override;

CC_CONSTRUCTOR_ACCESS:
    AtlasNode();
    virtual ~AtlasNode();

    /** 用Atlas文件初始化AtlasNode，并设置宽、高、itme数量*/
    bool initWithTileFile(const std::string& tile, int tileWidth, int tileHeight, int itemsToRender);
    
    /** 用纹理初始化AtlasNode，并设置宽、高、itme数量*/
    bool initWithTexture(Texture2D* texture, int tileWidth, int tileHeight, int itemsToRender);

protected:
    void calculateMaxItems();
    void updateBlendFunc();
    void updateOpacityModifyRGB();

    friend class Director;
    void setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor);

    //! 每行的字数
    int    _itemsPerRow;
    //! 每列的字数
    int    _itemsPerColumn;

    //! 每个字的宽度
    int    _itemWidth;
    //! 每个字的高度
    int    _itemHeight;
    
    Color3B    _colorUnmodified;
    
    TextureAtlas* _textureAtlas;
    // protocol variables
    bool _isOpacityModifyRGB;
    BlendFunc _blendFunc;

    // quads to draw
    ssize_t _quadsToDraw;
    // color uniform
    GLint    _uniformColor;
    // This varible is only used for LabelAtlas FPS display. So plz don't modify its value.
    bool _ignoreContentScaleFactor;
    // quad command
    QuadCommand _quadCommand;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(AtlasNode);

};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCATLAS_NODE_H__


