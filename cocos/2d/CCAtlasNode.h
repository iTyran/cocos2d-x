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

/** @brief AtlasNode is a subclass of Node that implements the RGBAProtocol and TextureProtocol protocol

It knows how to render a TextureAtlas object.
If you are going to render a TextureAtlas consider subclassing AtlasNode (or a subclass of AtlasNode)

All features from Node are valid, plus the following features:
- opacity and RGB colors
*/
class CC_DLL AtlasNode : public Node, public TextureProtocol
{    
public:
    /**根据Altas文件，创建一个AltasNode
     * 参数：组成Atlas 的 tile的宽度，高度，和item的个数
    */
    static AtlasNode * create(const std::string& filename, int tileWidth, int tileHeight, int itemsToRender);

    /**更新Atlas类（索引顶点数组）
     * 子类需要重载这个方法
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
    * 当这个方法扩展到js和lua，参数会改变
    * In js: var setBlendFunc(var src, var dst)
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

    /** 使用Atlas file初始化一个AtlasNode，
     * 参数：组成每个item的width，height，item的个数
    */
    bool initWithTileFile(const std::string& tile, int tileWidth, int tileHeight, int itemsToRender);
    
    /** 使用texture初始化AtlasNode
     *  参数：组成item的width，height，要显示的item的数量
    */
    bool initWithTexture(Texture2D* texture, int tileWidth, int tileHeight, int itemsToRender);

protected:
    void calculateMaxItems();
    void updateBlendFunc();
    void updateOpacityModifyRGB();

    friend class Director;
    void setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor);

    // 每行字符
    int    _itemsPerRow;
    // 每列字符
    int    _itemsPerColumn;

    // 每个字符宽度
    int    _itemWidth;
    // 每个字符高度
    int    _itemHeight;
    
    Color3B    _colorUnmodified;
    
    TextureAtlas* _textureAtlas;
    // 协议变量
    bool _isOpacityModifyRGB;
    BlendFunc _blendFunc;

    // 绘制四边形
    ssize_t _quadsToDraw;
    // 均匀颜色
    GLint    _uniformColor;
    // 这个变量仅用于LabelAtlas FPS的展示，所以建议不要修改它的值
    bool _ignoreContentScaleFactor;
    // quad 命令
    QuadCommand _quadCommand;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(AtlasNode);

};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCATLAS_NODE_H__


