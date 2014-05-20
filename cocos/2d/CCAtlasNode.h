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

/** 简要说明 AtlasNode 是 Node 的子类，实现了 RGBAProtocol 、 TextureProtocol 协议 
 *  如果你要 实现一个 AtlasNode 的子类 TextureAtlas (or AtlasNode 的子类) 
 *  它知道如何实现 TextureAtlas 对象. 
 *  这个类包含所有Note的属性，还包含不透明度和RGB颜色属性 
*/  
class CC_DLL AtlasNode : public Node, public TextureProtocol
{    
public:
    /** 使用 一个 Atlas 文件，创建一个 AtlasNode
     *  参数：每个 item（组成Atlas 的 tile（瓷砖）） 的宽度、高度 要显示的 items 数量  
     */  
    static AtlasNode * create(const std::string& filename, int tileWidth, int tileHeight, int itemsToRender);

    /** 更新Atlas （索引顶点数组）
     *  需要重载它的子类
     */
    virtual void updateAtlasValues();

    void setTextureAtlas(TextureAtlas* textureAtlas);
    TextureAtlas* getTextureAtlas() const;
    
    void setQuadsToDraw(ssize_t quadsToDraw);
    ssize_t getQuadsToDraw() const;

    
    // 重载方法
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    virtual bool isOpacityModifyRGB() const override;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB) override;
    virtual const Color3B& getColor(void) const override;
    virtual void setColor(const Color3B& color) override;
    virtual void setOpacity(GLubyte opacity) override;

    /** 当这个方法扩展到js或者lua的时候，参数会改变
     * 在js中：setBlendFunc(var src, var dst)
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

   /**  使用 一个 Atlas 文件，初始化一个 AtlasNode 
    *   参数：每个 item（组成Atlas 的 tile（瓷砖）） 的宽度、高度 要显示的 items 数量 
   */  
    bool initWithTileFile(const std::string& tile, int tileWidth, int tileHeight, int itemsToRender);
    
    /** 使用 texture，初始化一个 AtlasNode 
     * 参数：每个 item（组成Atlas 的 tile（瓷砖）） 的宽度、高度 要显示的 items 数量 
     */  
    bool initWithTexture(Texture2D* texture, int tileWidth, int tileHeight, int itemsToRender);

protected:
    void calculateMaxItems();
    void updateBlendFunc();
    void updateOpacityModifyRGB();

    friend class Director;
    void setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor);

    //每行字符
    int    _itemsPerRow;
    //每列字符
    int    _itemsPerColumn;

    //每个字符宽度
    int    _itemWidth;
    //每个字符高度
    int    _itemHeight;
    
    Color3B    _colorUnmodified;
    
    TextureAtlas* _textureAtlas;
    //协议变量
    bool _isOpacityModifyRGB;
    BlendFunc _blendFunc;

    //绘制四边形
    ssize_t _quadsToDraw;
    // 均匀的颜色
    GLint    _uniformColor;
    
    //这个变量只需要用于LabelAtlas FPS的展示，所以建议不要修改它的值
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


