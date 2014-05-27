/****************************************************************************
Copyright (c) 2009      Jason Booth
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
#ifndef __CCRENDER_TEXTURE_H__
#define __CCRENDER_TEXTURE_H__

#include "2d/CCNode.h"
#include "2d/CCSprite.h"
#include "2d/platform/CCImage.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class EventCustom;

/**
 * @addtogroup textures
 * @{
 */

/**
@brief RenderTexture是通用的渲染目标。执行以下步骤，可以把相应的节点渲染到该目标上。
创建一个渲染目标，执行它的begin方法，对想要渲染的cocos场景（scenes）或对象，执行visit，
然后执行渲染目标的end方法。
为方便使用，RenderTexture使用Sprite来展示结果，因此，你可以直接将RenderTexture的对象添加到场景中，像使用其他的cocos Node一样使用它。
RenderTexture类也提供了将纹理以PNG或者JPG格式保存到硬盘的方法。
@since v0.8.1
*/
class CC_DLL RenderTexture : public Node 
{
public:
    /** 指定宽、高（以point为单位）、像素格式（仅支持RGB和RGBA格式）以及深度模版格式，创建RenderTexture对象。*/
    static RenderTexture * create(int w ,int h, Texture2D::PixelFormat format, GLuint depthStencilFormat);

    /** 指定宽、高（以point为单位）以及像素格式（仅支持RGB和RGBA格式），创建RenderTexture对象。 */
    static RenderTexture * create(int w, int h, Texture2D::PixelFormat format);

    /** 指定以point为单位的宽、高以及RGBA8888像素格式，创建RenderTexture对象。 */
    static RenderTexture * create(int w, int h);

    /** 开始抓取屏幕*/
    virtual void begin();

    /** 先清除纹理，然后再渲染纹理。
	 比先调用-clear然后再调用-begin更高效。*/
    virtual void beginWithClear(float r, float g, float b, float a);

    /** 先清除纹理，然后再渲染纹理。
	 比先调用-clear然后再调用-begin更高效。*/
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue);

    /** 先清除纹理，然后再渲染纹理。
	 比先调用-clear然后再调用-begin更高效。 */
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue);

    /** “end”是lua语言的关键字，因此当绑定到lua时，需要使用其他的名字*/
    inline void endToLua(){ end();};

    /** 抓取结束*/
    virtual void end();

    /** 指定颜色清除纹理*/
    void clear(float r, float g, float b, float a);

    /** 指定深度模版值清除纹理。*/
    virtual void clearDepth(float depthValue);

    /** 指定模版值清除纹理。*/
    virtual void clearStencil(int stencilValue);
    /* 根据纹理数据创建新的Image对象。
	   需要手动调用delete来释放该对象。
     */
    
    Image* newImage(bool flipImage = true);
    
    CC_DEPRECATED_ATTRIBUTE Image* newCCImage(bool flipImage = true) { return newImage(flipImage); };

    /** 将纹理以JPG格式保存到Documents文件夹下指定的文件。
		当保存成功后，返回true。
     */
    bool saveToFile(const std::string& filename);

    /** 将纹理保存到Documents文件夹下指定的文件。支持JPG和PNG格式。
		当保存成功后，返回true。
     */
    bool saveToFile(const std::string& filename, Image::Format format);
    
    /** 监听“进入后台”的消息，并保存纹理。
	 仅在Android平台使用。
     */
    void listenToBackground(EventCustom *event);
    
    /** 监听“返回到前台”的消息，然后恢复帧缓冲区。
	 仅在Android平台使用。
     */
    void listenToForeground(EventCustom *event);
    
    /** 有效的标志：GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT。多个标志可以通过“或”的方式同时使用。仅当"autoDraw"为true时有效。*/
    inline unsigned int getClearFlags() const { return _clearFlags; };
    inline void setClearFlags(unsigned int clearFlags) { _clearFlags = clearFlags; };
    
    /** 颜色清除的值。仅当"autoDraw"为true时有效。*/
    inline const Color4F& getClearColor() const { return _clearColor; };
    inline void setClearColor(const Color4F &clearColor) { _clearColor = clearColor; };
    
    /** 深度缓冲区值。仅当"autoDraw"为true时有效。*/
    inline float getClearDepth() const { return _clearDepth; };
    inline void setClearDepth(float clearDepth) { _clearDepth = clearDepth; };
    
    /** 模版清除的值。仅当"autoDraw"为true时有效。*/
    inline int getClearStencil() const { return _clearStencil; };
    inline void setClearStencil(int clearStencil) { _clearStencil = clearStencil; };
    
    /** 当使能时，自动将其所有子结点绘制到纹理中。为保持兼容性，默认不使能。
	 未来版本中将默认使能。
     */
    inline bool isAutoDraw() const { return _autoDraw; };
    inline void setAutoDraw(bool isAutoDraw) { _autoDraw = isAutoDraw; };

    /** 获取使用的Sprite */
    inline Sprite* getSprite() const { return _sprite; };
    
    /** 设置使用的Sprite */
    inline void setSprite(Sprite* sprite) {
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE(_sprite);
        _sprite = sprite;
    };
    
    // Overrides
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

    //flag: use stack matrix computed from scene hierarchy or generate new modelView and projection matrix
    void setKeepMatrix(bool keepMatrix);
    /**抓取屏幕部分内容保存为纹理。
	//rtBegin: renderTexture在整个屏幕上的起始位置。
	//fullRect: 整个屏幕的大小
	//fullViewport: 整个viewport的大小。
    */
    void setVirtualViewport(const Vec2& rtBegin, const Rect& fullRect, const Rect& fullViewport);

public:
    // XXX should be procted.
    // but due to a bug in PowerVR + Android,
    // the constructor is public again
    RenderTexture();
    virtual ~RenderTexture();
    /** 指定宽、高（以point为单位）以及像素格式（仅支持RGB和RGBA模式），初始化RenderTexture对象 */
    bool initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat format);
    /** 指定宽、高（以point为单位）、像素格式（仅支持RGB和RGBA模式）以及深度模版(depthStencil)格式，初始化RenderTexture对象 */
    bool initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat format, GLuint depthStencilFormat);

protected:
    virtual void beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags);
    
    //flags: whether generate new modelView and projection matrix or not
    bool         _keepMatrix;
    Rect         _rtTextureRect;
    Rect         _fullRect;
    Rect         _fullviewPort;
    
    GLuint       _FBO;
    GLuint       _depthRenderBufffer;
    GLint        _oldFBO;
    Texture2D* _texture;
    Texture2D* _textureCopy;    // a copy of _texture
    Image*     _UITextureImage;
    Texture2D::PixelFormat _pixelFormat;
    
    // code for "auto" update
    GLbitfield   _clearFlags;
    Color4F    _clearColor;
    GLclampf     _clearDepth;
    GLint        _clearStencil;
    bool         _autoDraw;

    /** 使用的Sprite
	 Sprite默认使用下面的混合函数（blending function）：GL_ONE, GL_ONE_MINUS_SRC_ALPHA。
	 运行过程中，可以通过调用下面的方法来改变混合函数：
     - renderTexture->getSprite()->setBlendFunc((BlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
     */
    Sprite* _sprite;
    
    GroupCommand _groupCommand;
    CustomCommand _beginWithClearCommand;
    CustomCommand _clearDepthCommand;
    CustomCommand _clearCommand;
    CustomCommand _beginCommand;
    CustomCommand _endCommand;
    CustomCommand _saveToFileCommand;
protected:
    //renderer caches and callbacks
    void onBegin();
    void onEnd();

    void onClear();
    void onClearDepth();

    void onSaveToFile(const std::string& fileName);
    
    Mat4 _oldTransMatrix, _oldProjMatrix;
    Mat4 _transformMatrix, _projectionMatrix;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(RenderTexture);

};

// end of textures group
/// @}

NS_CC_END

#endif //__CCRENDER_TEXTURE_H__
