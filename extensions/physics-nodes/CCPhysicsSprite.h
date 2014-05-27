/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __PHYSICSNODES_CCPHYSICSSPRITE_H__
#define __PHYSICSNODES_CCPHYSICSSPRITE_H__

#include "2d/CCSprite.h"
#include "extensions/ExtensionMacros.h"

struct cpBody;
class b2Body;

NS_CC_EXT_BEGIN

/** 精灵(Sprite)的子类，绑定到一个物理Body.
 它和下面的宏一起使用:
 - Chipmunk: 预处理宏 CC_ENABLE_CHIPMUNK_INTEGRATION 应该被定义
 - Objective-Chipmunk: 预处理宏 CC_ENABLE_CHIPMUNK_INTEGRATION 应该被定义
 - Box2d: 预处理宏 CC_ENABLE_BOX2D_INTEGRATION 应该被定义

 特性和限制:
 - 缩放和偏移属性被忽略.
 - 位置和旋转将更新物理Body
 - 如果你手动的更新旋转和位置，Body将被更新.
 - 你不能同时启用Chipmunk支持和Box2d 支持. 在编译时只能启用一种物理引擎
 */
class PhysicsSprite : public Sprite
{
public:

    static PhysicsSprite* create();
    /** 用纹理(texture)创建一个精灵.
     精灵的矩形大小将使用纹理(texture)的大小.
     偏移将会是(0,0).
     */
    static PhysicsSprite* createWithTexture(Texture2D *pTexture);

    /** 指定纹理(texture)和矩形创建一个精灵.
     偏移将会是(0,0).
     */
    static PhysicsSprite* createWithTexture(Texture2D *pTexture, const Rect& rect);

    /** 用精灵帧(sprite frame)创建一个精灵. */
    static PhysicsSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);

    /** 用指定精灵帧名创建一个精灵.
     一个精灵帧将会通过名字从精灵帧缓存中获取.
     如果该精灵帧不存在将会产生异常.
     @since v0.9
     */
    static PhysicsSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);

    /** 使用指定的图片文件名创建一个精灵.
     精灵的矩形将使用图片的大小.
     偏移将会是(0,0).
     */
    static PhysicsSprite* create(const char *pszFileName);

    /** 使用指定的图片文件名和矩形创建一个精灵.
     偏移将会是(0,0).
     */
    static PhysicsSprite* create(const char *pszFileName, const Rect& rect);

    PhysicsSprite();

    virtual bool isDirty() const;

    /** 保持精灵的旋转和Body分开. */
    bool isIgnoreBodyRotation() const;
    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

    //
    // Chipmunk 特有
    //
    /** 访问使用常规Chipmunk物理引擎时的精灵Body */
    cpBody* getCPBody() const;
    void setCPBody(cpBody *pBody);

    //
    // Box2d 特有
    //
    /** 访问使用常规box2d物理引擎时的精灵Body */
    b2Body* getB2Body() const;
    void setB2Body(b2Body *pBody);

    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);

    // 重写
    virtual const Vec2& getPosition() const override;
    virtual void getPosition(float* x, float* y) const override;
    virtual float getPositionX() const override;
    virtual float getPositionY() const override;
    virtual void setPosition(const Vec2 &position) override;
    virtual float getRotation() const override;
    virtual void setRotation(float fRotation) override;
    virtual void syncPhysicsTransform() const;
    virtual const Mat4& getNodeToParentTransform() const override;
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

protected:
    const Vec2& getPosFromPhysics() const;

protected:
    bool    _ignoreBodyRotation;

    // chipmunk 特有
    cpBody  *_CPBody;

    // box2d 特有
    b2Body  *_pB2Body;
    float   _PTMRatio;
};

NS_CC_EXT_END

#endif // __PHYSICSNODES_CCPHYSICSSPRITE_H__
