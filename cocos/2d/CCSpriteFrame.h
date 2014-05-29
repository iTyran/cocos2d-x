/****************************************************************************
Copyright (c) 2008-2011 Ricardo Quesada
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
****************************************************************************/

#ifndef __SPRITE_CCSPRITE_FRAME_H__
#define __SPRITE_CCSPRITE_FRAME_H__

#include "2d/CCNode.h"
#include "2d/CCProtocols.h"
#include "base/CCRef.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

class Texture2D;

/**
 * @addtogroup sprite_nodes
 * @{
 */

/** @brief 一个精灵帧包括：
    - 纹理：一个被精灵使用的二维纹理
    - 矩形：一个纹理矩形

 你可以通过这样做来修改一个精灵帧：
    SpriteFrame *frame = SpriteFrame::frameWithTexture(texture, rect, offset);
    sprite->setDisplayFrame(frame);
 */
class CC_DLL SpriteFrame : public Ref, public Clonable
{
public:

    /** 通过纹理文件名，矩形(以点为单位)创建一个精灵帧。
         假设帧没有被修剪。
     */
    static SpriteFrame* create(const std::string& filename, const Rect& rect);
    
    /** 通过纹理文件名，矩形，旋转，偏移量和原始大小（以像素为单位）创建一个精灵帧。
     原始大小是帧在被修剪前的大小（以像素为单位）。
     */
    static SpriteFrame* create(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
    
    /**通过纹理，矩形（以点为单位）创建一个精灵帧。
        假设帧没有被修剪。
     */
    static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect);

    /** 通过纹理，矩形，旋转，偏移量和原始大小（以像素为单位）创建一个精灵帧。
        原始大小是帧在被修剪前的大小（以点为单位）。
     */
    static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SpriteFrame(void);

    /** 通过纹理，矩形（以点为单位）初始化一个精灵帧。
        假设帧没有被修剪。
     */
    bool initWithTexture(Texture2D* pobTexture, const Rect& rect);

    /**通过纹理文件名，矩形(以点为单位)初始化一个精灵帧。
       假设帧没有被修剪。
     */
    bool initWithTextureFilename(const std::string& filename, const Rect& rect);

    /**通过纹理，矩形，旋转，偏移量和原始大小（以像素为单位）初始化一个精灵帧。
       原始大小是帧在被修剪前的大小（以点为单位）。
    */
    bool initWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);

    /** 通过纹理，矩形，旋转，偏移量和原始大小（以像素为单位）来初始化一个精灵帧。
        原始大小是帧在被修剪前的大小（以像素为单位）。
     @since v1.1
     */
    bool initWithTextureFilename(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);


    // attributes
    inline const Rect& getRectInPixels() const { return _rectInPixels; }
    void setRectInPixels(const Rect& rectInPixels);

    inline bool isRotated(void) const { return _rotated; }
    inline void setRotated(bool rotated) { _rotated = rotated; }

    /** 获取帧的矩形*/
    inline const Rect& getRect(void) const { return _rect; }
    /** 设置帧的矩形*/
    void setRect(const Rect& rect);

    /** 获取帧的偏移量*/
    const Vec2& getOffsetInPixels(void) const;
    /** 设置帧的偏移量*/
    void setOffsetInPixels(const Vec2& offsetInPixels);

    /** 获取被修剪图片的原始尺寸*/
    inline const Size& getOriginalSizeInPixels(void) const { return _originalSizeInPixels; }
    /** 设置被修剪图片的原始尺寸*/
    inline void setOriginalSizeInPixels(const Size& sizeInPixels) { _originalSizeInPixels = sizeInPixels; }

    /** 获取被修剪图片的原始尺寸*/
    inline const Size& getOriginalSize(void) const { return _originalSize; }
    /** 设置被修剪图片的原始尺寸*/
    inline void setOriginalSize(const Size& sizeInPixels) { _originalSize = sizeInPixels; }

    /** 获取帧的纹理*/
    Texture2D* getTexture(void);
    /** 设置帧的纹理，纹理被保留*/
    void setTexture(Texture2D* pobTexture);

    const Vec2& getOffset(void) const;
    void setOffset(const Vec2& offsets);

    // Overrides
	virtual SpriteFrame *clone() const override;

protected:
    Vec2 _offset;
    Size _originalSize;
    Rect _rectInPixels;
    bool   _rotated;
    Rect _rect;
    Vec2 _offsetInPixels;
    Size _originalSizeInPixels;
    Texture2D *_texture;
    std::string  _textureFilename;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif //__SPRITE_CCSPRITE_FRAME_H__
