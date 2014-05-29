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

#ifndef __CCPROTOCOLS_H__
#define __CCPROTOCOLS_H__

#include "base/ccTypes.h"
#include "2d/CCTexture2D.h"
#include <string>

NS_CC_BEGIN

/**
 * RGBA protocol 影响Node的颜色和不透明度
 */
class CC_DLL __RGBAProtocol
{
public:
    virtual ~__RGBAProtocol() {}
    
    /**
     * 通过R,G,B字节的值来改变颜色
     *
     * @param color Example: Color3B(255,100,0) 表示 R=255, G=100, B=0
     * @js NA
     * @lua NA
     */
    virtual void setColor(const Color3B& color) = 0;
    
    /**
     * 返回当前使用的颜色值
     *
     * @return 包括R,G,B的值Color3B对象
     * @js NA
     * @lua NA
     */
    virtual const Color3B& getColor() const = 0;
    
    /**
     * 返回显示的颜色值
     *
     * @return 包括R,G,B的值Color3B对象
     * @js NA
     * @lua NA
     */
    virtual const Color3B& getDisplayedColor() const = 0;
    
    /**
     * 返回当前显示的不透明度
     *
     * @return  精灵的不透明度，从0~255
     * @js NA
     * @lua NA
     */
    virtual GLubyte getDisplayedOpacity() const = 0;
    /**
     * 返回当前不透明度
     *
     * 不透明度表示Node是透明还是不透明，0表示完全透明，255表示完全不透明
     *
     * @return  精灵的不透明度, 从0到255
     * @js NA
     * @lua NA
     */
    virtual GLubyte getOpacity() const = 0;
    
    /**
     * 改变不透明度
     *
     * @param opacity   从0-255，0表示完全透明，255表示完全不透明
     * @js NA
     * @lua NA
     */
    virtual void setOpacity(GLubyte opacity) = 0;
    
    // optional
    
    /**
     * 改变OpacityModifyRGB的属性
     * 如果这个属性为true,那么渲染的颜色将会受到不透明的影响
     *
     * @param value 颜色值是否受到不透明度影响
     * @js NA
     * @lua NA
     */
    virtual void setOpacityModifyRGB(bool value) = 0;
    
    /**
     * 返回不透明是否应用到颜色上
     *
     * @return  不透明度是否应用到颜色上
     * @js NA
     * @lua NA
     */
    virtual bool isOpacityModifyRGB() const = 0;
    
    /**
     *  颜色是否传播到子节点上
     * @js NA
     * @lua NA
     */
    virtual bool isCascadeColorEnabled() const = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) = 0;
    
    /**
     *  更新显示颜色的递归方法
     * @js NA
     * @lua NA
     */
    virtual void updateDisplayedColor(const Color3B& color) = 0;
    
    /**
     *  不透明度是否传递到子节点上
     * @js NA
     * @lua NA
     */
    virtual bool isCascadeOpacityEnabled() const = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) = 0;
    
    /**
     *  更新显示透明度的递归方法
     * @js NA
     * @lua NA
     */
    virtual void updateDisplayedOpacity(GLubyte opacity) = 0;
};

/**
 * 指定glBlendFunc使用的混合方法
 * 参考glBlendFunc的手册
 * http://www.khronos.org/opengles/sdk/docs/man/xhtml/glBlendFunc.xml
 */
class CC_DLL BlendProtocol
{
public:
    virtual ~BlendProtocol() {}

    /**
     * 设置源混合方法
     *
     * @param blendFunc 包含源和目标因子的结构体
     *                  e.g. {GL_ONE, GL_ONE}, {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}.
     * @js NA
     * @lua NA
     */
    virtual void setBlendFunc(const BlendFunc &blendFunc) = 0;

    /**
     * 返回当前使用的混合方法
     * 
     * @return 包含源和目标因子的结构体
     * @js NA
     * @lua NA
     */
    virtual const BlendFunc &getBlendFunc() const = 0;
};

/** 
 * Node对象使用Texture2D来渲染图片
 * 纹理可以使用混合方法
 * 如果纹理有alpha通道，那么默认混合方法为
 *   src=GL_ONE dst= GL_ONE_MINUS_SRC_ALPHA
 * 否则
 *   src=GL_SRC_ALPHA dst= GL_ONE_MINUS_SRC_ALPHA
 * 但是你可以进行改变
 */
class CC_DLL TextureProtocol : public BlendProtocol
{
public:
    virtual ~TextureProtocol() {}
    /**
     * 返回当前使用的所有的纹理
     *
     * @return  当前使用的纹理
     * @js NA
     * @lua NA
     */
    virtual Texture2D* getTexture() const = 0;

    /**
     * 设置一个新的纹理，在内部会进行一次retain
     *
     * @param   texture 有效的Texture2D对象
     * @js NA
     * @lua NA
     */
    virtual void setTexture(Texture2D *texture) = 0;
};

/**
 * Label的通用接口
 */
class CC_DLL LabelProtocol
{
public:
    virtual ~LabelProtocol() {}

    /**
     * label设置一个新的string
     *
     * @param label 一个以null结尾的字符串
     * @js NA
     * @lua NA
     */
    virtual void setString(const std::string &label) = 0;

    /** 
     * 返回label使用的string
     *
     * @return label当前使用的字符串
     * @js NA
     * @lua NA
     */
    virtual const std::string& getString() const = 0;
};

/** 
 * OpenGL用于显示的接口
 */
class CC_DLL DirectorDelegate
{
public:
    virtual ~DirectorDelegate() {}

    /**
     * 如果显示的项目有更新，该方法将会被Director调用
     * @js NA
     * @lua NA
     */
    virtual void updateProjection() = 0;
};

NS_CC_END

#endif // __CCPROTOCOLS_H__
