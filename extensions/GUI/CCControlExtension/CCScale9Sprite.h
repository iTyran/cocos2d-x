/****************************************************************************
Copyright (c) 2012 cocos2d-x.org

http://www.cocos2d-x.org

Created by Jung Sang-Taik on 12. 3. 16..
Copyright (c) 2012 Neofect. All rights reserved.

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

#ifndef __CCScale9Sprite_H__
#define __CCScale9Sprite_H__

#include "2d/CCNode.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteBatchNode.h"

#include "../../ExtensionMacros.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/**
 * Cocos2d-x的九宫格精灵
 *
 * 九宫格分割机制可以让你指定如何划分Sprite区域
 * 因为九宫格将Sprite分成了3x3的9个格子，所以在放大时不会变形
 * （注）事实上只有四个角不会拉伸变形，边缘和中心部分还是会被拉伸
 *
 * @see http://yannickloriot.com/library/ios/cccontrolextension/Classes/CCScale9Sprite.html
 */
class Scale9Sprite : public Node
{
public:
    /**
     * @js ctor
     */
    Scale9Sprite();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Scale9Sprite();

public:
    static Scale9Sprite* create();

    /**
     * 根据纹理文件名、裁剪区域以及分割位置创建九宫格Sprite
     *
     * @see initWithFile(const char *file, const Rect& rect, const Rect& capInsets)
     */
    static Scale9Sprite* create(const std::string& file, const Rect& rect,  const Rect& capInsets);

    /**
     * 根据分割位置以及纹理文件名创建九宫格Sprite
     * 因为没有裁剪区域参数，所以使用整张纹理图片
     *
     * @see initWithFile(const Rect& capInsets, const char *file)
     */
    static Scale9Sprite* create(const Rect& capInsets, const std::string& file);

    /**
     * 根据纹理文件名以及裁剪区域创建九宫格Sprite
     * 因为没有分割位置参数，所以等分成3x3网格
     *
     * @see initWithFile(const char *file, const Rect& rect)
     */
    static Scale9Sprite* create(const std::string& file, const Rect& rect);

    /**
     * 根据纹理文件名创建九宫格Sprite
     * 使用整张纹理且等分为3x3网格
     *
     * @see initWithFile(const char *file)
     */
    static Scale9Sprite* create(const std::string& file);

    /**
     * 根据SpriteFrame创建九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @see initWithSpriteFrame(SpriteFrame *spriteFrame)
     */
    static Scale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame);

    /**
     * 根据SpriteFrame以及分割中心区域矩形的位置尺寸创建九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @see initWithSpriteFrame(SpriteFrame *spriteFrame, const Rect& capInsets)
     */
    static Scale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets);

    /**
     * 根据SpriteFrame名创建九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @see initWithSpriteFrameName(const char *spriteFrameName)
     */
    static Scale9Sprite* createWithSpriteFrameName(const std::string& spriteFrameName);

    /**
     * 根据SpriteFrame名以及分割中心区域矩形的位置尺寸创建九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @see initWithSpriteFrameName(const char *spriteFrameName, const Rect& capInsets)
     */
    static Scale9Sprite* createWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);

    /**
     * 根据纹理文件名、裁剪区域以及分割中心区域矩形的位置尺寸初始化九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @param file 纹理文件名
     * @param rect 用于指定需要使用纹理的哪一部分的矩形
     * 如果整个纹理都要使用则传入完整尺寸
     * @param capInsets 用于确定分割位置
     */
    virtual bool initWithFile(const std::string& file, const Rect& rect,  const Rect& capInsets);
    
    /**
     * 根据纹理文件名以及裁剪区域初始化九宫格Sprite
     * 因为没有分割位置参数，所以等分成3x3网格
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @param file 纹理文件名
     * @param rect 用于指定需要使用纹理的哪一部分的矩形
     * 如果整个纹理都要使用则传入完整尺寸
     */
    virtual bool initWithFile(const std::string& file, const Rect& rect);
    
    /**
     * 根据分割位置以及纹理文件名初始化九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @param capInsets 用于确定分割位置
     * @param file 纹理文件名
     */
    virtual bool initWithFile(const Rect& capInsets, const std::string& file);
    
    /**
     * 根据纹理文件名初始化九宫格Sprite，使用整张纹理且等分为3x3网格
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @param capInsets 用于确定分割位置
     * @param file 纹理文件名
     */
    virtual bool initWithFile(const std::string& file);
    
    /**
     * 根据SpriteFrame以及分割中心区域矩形的位置尺寸初始化九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @param spriteFrame SpriteFrame对象
     * @param capInsets 用于确定分割位置
     */
    virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets);

    /**
     * 根据SpriteFrame初始化九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @param spriteFrame SpriteFrame对象
     */
    virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame);

    /**
     * 根据SpriteFrame名以及分割中心区域矩形的位置尺寸初始化九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @param spriteFrameName SpriteFrame名
     * @param capInsets 用于确定分割位置
     */
    virtual bool initWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);

    /**
     * 根据SpriteFrame名初始化九宫格Sprite
     * 创建完成后，可以通过"setContentSize"方法来修改尺寸
     * 修改尺寸会使所有九个部件的参数重新计算
     * 锚点设置也是有效的
     *
     * @param spriteFrameName SpriteFrame名
     */
    virtual bool initWithSpriteFrameName(const std::string& spriteFrameName);

    virtual bool init();
    virtual bool initWithBatchNode(SpriteBatchNode* batchnode, const Rect& rect, bool rotated, const Rect& capInsets);
    virtual bool initWithBatchNode(SpriteBatchNode* batchnode, const Rect& rect, const Rect& capInsets);

    /**
     * 根据给定分割区域创建并返回一个新的九宫格Sprite
     * 此方法用于新增或者修改现有对象的分割区域
     * 返回值为新建对象，原始九宫格不会发生改变
     *
     * @param capInsets 用于确定分割位置
     */
    Scale9Sprite* resizableSpriteWithCapInsets(const Rect& capInsets);
    
    virtual bool updateWithBatchNode(SpriteBatchNode* batchnode, const Rect& rect, bool rotated, const Rect& capInsets);
    virtual void setSpriteFrame(SpriteFrame * spriteFrame);

    // overrides
    virtual void setContentSize(const Size & size) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
    virtual void setOpacityModifyRGB(bool bValue) override;
    virtual bool isOpacityModifyRGB(void) const override;
    virtual void setOpacity(GLubyte opacity) override;
    virtual void setColor(const Color3B& color) override;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;

protected:
    void updateCapInset();
    void updatePositions();

    bool _spritesGenerated;
    Rect _spriteRect;
    bool   _spriteFrameRotated;
    Rect _capInsetsInternal;
    bool _positionsAreDirty;

    SpriteBatchNode* _scale9Image;
    Sprite* _topLeft;
    Sprite* _top;
    Sprite* _topRight;
    Sprite* _left;
    Sprite* _centre;
    Sprite* _right;
    Sprite* _bottomLeft;
    Sprite* _bottom;
    Sprite* _bottomRight;

    bool _opacityModifyRGB;

    /** Sprite原始尺寸 */
    CC_SYNTHESIZE_READONLY(Size, _originalSize, OriginalSize);
    /** 期望的Sprite尺寸，默认为原始尺寸 */

    //如果值为-1则忽略
    CC_PROPERTY(Size, _preferredSize, PreferredSize);
    /**
     * 九宫格分割的中心区域
     * 对于不能使用九宫格机制的Sprite，将此参数设置为原图尺寸，
     * 则会将精灵直接整体拉伸到目标尺寸。
     */
    CC_PROPERTY(Rect, _capInsets, CapInsets);
    /** 设置左边距 */
    CC_PROPERTY(float, _insetLeft, InsetLeft);
    /** 设置上边距 */
    CC_PROPERTY(float, _insetTop, InsetTop);
    /** 设置右边距 */
    CC_PROPERTY(float, _insetRight, InsetRight);
    /** 设置下边距 */
    CC_PROPERTY(float, _insetBottom, InsetBottom);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif // __CCScale9Sprite_H__
