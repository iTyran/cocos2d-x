/****************************************************************************
Copyright (c) 2008      Apple Inc. All Rights Reserved.
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

#ifndef __CCTEXTURE2D_H__
#define __CCTEXTURE2D_H__

#include <string>
#include <map>
#include <map>

#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "base/ccTypes.h"
#ifdef EMSCRIPTEN
#include "CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

class Image;
typedef struct _MipmapInfo MipmapInfo;

/**
 * @addtogroup textures
 * @{
 */

//CONSTANTS:

class GLProgram;

//CLASS INTERFACES:

/** @brief Texture2D
 * 通过Texture2D类，可以根据图像、文本或者原始数据（raw data）创建OpenGL 2D纹理。
 * 创建的纹理的尺寸是POT（power-of-two)。
 * 根据创建Texture2D对象的方法，实际的图像尺寸可能比纹理尺寸小。例如：
 * "contentSize" != (pixelsWide, pixelsHigh) and (maxS, maxT) != (1.0, 1.0).
 * 注意，生成的纹理内容是倒置的。
*/
class CC_DLL Texture2D : public Ref
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    /** @typedef Texture2D::PixelFormat
	 支持的纹理像素格式。
     */
    enum class PixelFormat
    {
        //! 自动检测模式
        AUTO,
        //! 32-bit纹理: BGRA8888
        BGRA8888,
        //! 32-bit纹理: RGBA8888
        RGBA8888,
        //! 24-bit纹理: RGBA888
        RGB888,
        //! 16-bit纹理，不带Alpha通道
        RGB565,
        //! 用作遮罩(masks)的8-bit纹理
        A8,
        //! 8-bit intensity纹理
        I8,
        //! 用作遮罩的16-bit纹理
        AI88,
        //! 16-bit纹理: RGBA4444
        RGBA4444,
        //! 16-bit纹理: RGB5A1
        RGB5A1,
        //! 4-bit PVRTC压缩纹理 texture: PVRTC4
        PVRTC4,
        //! 4-bit PVRTC压缩纹理: PVRTC4 (has alpha channel)
        PVRTC4A,
        //! 2-bit PVRTC压缩纹理: PVRTC2
        PVRTC2,
        //! 2-bit PVRTC压缩纹理: PVRTC2 (has alpha channel)
        PVRTC2A,
        //! ETC压缩纹理: ETC
        ETC,
        //! S3TC压缩纹理: S3TC_Dxt1
        S3TC_DXT1,
        //! S3TC压缩纹理: S3TC_Dxt3
        S3TC_DXT3,
        //! S3TC压缩纹理: S3TC_Dxt5
        S3TC_DXT5,
        //! ATITC压缩纹理: ATC_RGB
        ATC_RGB,
        //! ATITC压缩纹理: ATC_EXPLICIT_ALPHA
        ATC_EXPLICIT_ALPHA,
        //! ATITC压缩纹理: ATC_INTERPOLATED_ALPHA
        ATC_INTERPOLATED_ALPHA,
        //! 默认纹理PixelFormat: AUTO
        DEFAULT = AUTO,
        
        NONE = -1
    };
    
    
    struct PixelFormatInfo {

        PixelFormatInfo(GLenum anInternalFormat, GLenum aFormat, GLenum aType, int aBpp, bool aCompressed, bool anAlpha)
            : internalFormat(anInternalFormat)
            , format(aFormat)
            , type(aType)
            , bpp(aBpp)
            , compressed(aCompressed)
            , alpha(anAlpha)
        {}

        GLenum internalFormat;
        GLenum format;
        GLenum type;
        int bpp;
        bool compressed;
        bool alpha;
    };
    
    typedef std::map<Texture2D::PixelFormat, const PixelFormatInfo> PixelFormatInfoMap;
    
    /**
	 设置Min/Mag filter的方法。
     */
    typedef struct _TexParams {
        GLuint    minFilter;
        GLuint    magFilter;
        GLuint    wrapS;
        GLuint    wrapT;
    }TexParams;
    
public:
    /** 指定包含alpha通道的UIImage的默认PixelFormat。
	 如果UIImage包含alpha通道，那么支持以下选项：
	 －生成32-bit纹理：Texture2D::PixelFormat::RGBA8888 (default one)
     －生成24-bit纹理：Texture2D::PixelFormat::RGB888
     －生成16-bit纹理：Texture2D::PixelFormat::RGBA4444
     －生成16-bit纹理：Texture2D::PixelFormat::RGB5A1
     －生成16-bit纹理：Texture2D::PixelFormat::RGB565
     －生成8-bit纹理：Texture2D::PixelFormat::A8（仅当使用一种颜色时选择该选项）

	 工作原理：
	 －图像是RGBA(带Alpha通道)格式，那么使用默认的PixelFormat（可以是8-bit、16-bit或32-bit纹理）
	 －图像是RGBA(不带Alpha通道)格式，如果默认的PixelFormat为RGBA8888，那么使用RGBA8888(32-bit)模式，否则使用RGB565(16-bit纹理)。

	 该参数对PVR/PVR.CCZ文件无效。

     @since v0.8
     */
    static void setDefaultAlphaPixelFormat(Texture2D::PixelFormat format);

    /** 获取alpha通道PixelFormat
     @since v0.8
     */
    static Texture2D::PixelFormat getDefaultAlphaPixelFormat();
    CC_DEPRECATED_ATTRIBUTE static Texture2D::PixelFormat defaultAlphaPixelFormat() { return Texture2D::getDefaultAlphaPixelFormat(); };

    /** 设置PVR格式图像是否已自乘alpha值。
	 因为在运行时无法获PVR图像是否已自乘alpha值，因为，只能在加载的时候指定是否已自乘alpha值。

	 默认为未自乘alpha值。

     @since v0.99.5
     */
    static void PVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied);
    
public:
    /**
     * @js ctor
     */
    Texture2D();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Texture2D();
    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /** 指定数据，初始化Texture2D。
     * @js NA
     * @lua NA
     */
    bool initWithData(const void *data, ssize_t dataLen, Texture2D::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh, const Size& contentSize);

    /** 指定MipmapInfo，初始化Texture2D*/
    bool initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, Texture2D::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh);

    /** 指定数据，更新Texture2D*/
    bool updateWithData(const void *data,int offsetX,int offsetY,int width,int height);
    /**
	绘制方法的拓展，可以轻松的根据Texture2D对象绘制基本的quads。
	这些方法需要使能GL_TEXTURE_2D、GL_VERTEX_ARRAY、GL_TEXTURE_COORD_ARRAY。
    */
    /** 指定点，绘制纹理*/
    void drawAtPoint(const Vec2& point);
    /** 指定矩形(Rect)，绘制纹理*/
    void drawInRect(const Rect& rect);

    /**
	扩展库：方便的根据图像文件创建Texture2D对象。
    */
    /** 
	指定UIImage对象，初始化纹理。
	根据setDefaultAlphaPixelFormat方法所指定的格式，将图像转化为纹理。
	注意：不支持pvr格式文件。
	*/
    bool initWithImage(Image * image);
    
    /** 
	指定UIImage对象，初始化纹理。
	根据传入的PixelFormat，将图像格式转化为对应的纹理。
	如果传入PixelFormat::Automatic，那么会用自动检测到的图像格式来初始化纹理。
    **/
    bool initWithImage(Image * image, PixelFormat format);

    /** 指定大小、对齐方式、字体名和字体大小，根据输入的字符串初始化纹理 */
    bool initWithString(const char *text,  const std::string &fontName, float fontSize, const Size& dimensions = Size(0, 0), TextHAlignment hAlignment = TextHAlignment::CENTER, TextVAlignment vAlignment = TextVAlignment::TOP);
    /** 指定FontDefinition，根据输入的字符串初始化纹理*/
    bool initWithString(const char *text, const FontDefinition& textDefinition);

    /** 设置纹理的min filter, mag filter, wrap s和wrap t参数。
	如果纹理大小为NPOT(非2的整数次幂)，那么只能参数GL_TEXTURE_WRAP_{S,T}只能为GL_CLAMP_TO_EDGE。

	@warning 调用本方法将会导致额外的纹理内存开销。

    @since v0.8
    * @code 
	* 当将本方法绑定到js或者lua是，输入参数按如下改变：
	* js: var setBlendFunc(var arg1, var arg2, var arg3, var arg4)
    * lua: local setBlendFunc(local arg1, local arg2, local arg3, local arg4)
    * @endcode
    */
    void setTexParameters(const TexParams& texParams);
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void setTexParameters(const TexParams* texParams) { return setTexParameters(*texParams); };

    /** 设置antialias纹理参数：
    - GL_TEXTURE_MIN_FILTER = GL_LINEAR
    - GL_TEXTURE_MAG_FILTER = GL_LINEAR

	@warning 调用本方法会导致额外的纹理内存开销。

    @since v0.8
    */
    void setAntiAliasTexParameters();

    /** 设置alias纹理参数
    - GL_TEXTURE_MIN_FILTER = GL_NEAREST
    - GL_TEXTURE_MAG_FILTER = GL_NEAREST

	@warning 调用本方法会导致额外的纹理内存开销。

    @since v0.8
    */
    void setAliasTexParameters();


    /**生成纹理的mipmap图像。
	仅对大小为POT(2的整数次幂)的纹理有效。
    @since v0.99.0
    */
    void generateMipmap();

    /** 返回像素格式。
     @since v2.0
     */
    const char* getStringForFormat() const;
    CC_DEPRECATED_ATTRIBUTE const char* stringForFormat() const { return getStringForFormat(); };

    /** 返回in-memory OpenGL纹理每个像素占用的bit位数(bits-per-pixel)。
    @since v1.0
    */
    unsigned int getBitsPerPixelForFormat() const;
    CC_DEPRECATED_ATTRIBUTE unsigned int bitsPerPixelForFormat() const { return getBitsPerPixelForFormat(); };

    /** 指定像素格式，返回每个像素所占用的bit位数。
     @since v2.0
     */
    unsigned int getBitsPerPixelForFormat(Texture2D::PixelFormat format) const;
    CC_DEPRECATED_ATTRIBUTE unsigned int bitsPerPixelForFormat(Texture2D::PixelFormat format) const { return getBitsPerPixelForFormat(format); };

    /** 获取content大小。 */
    const Size& getContentSizeInPixels();

    bool hasPremultipliedAlpha() const;
    bool hasMipmaps() const;

    /** 获取纹理的像素格式。*/
    Texture2D::PixelFormat getPixelFormat() const;
    
    /** 获取纹理的宽度，以像素为单位 */
    int getPixelsWide() const;
    
    /** 获取纹理的高度，以像素为单位*/
    int getPixelsHigh() const;
    
    /** 获取纹理名称*/
    GLuint getName() const;
    
    /** 获取最大的S值*/
    GLfloat getMaxS() const;
    /** 设置最大的S值*/
    void setMaxS(GLfloat maxS);
    
    /** 获取最大的T值*/
    GLfloat getMaxT() const;
    /** 设置最大的T值*/
    void setMaxT(GLfloat maxT);
    
    Size getContentSize() const;
    
    void setGLProgram(GLProgram* program);
    GLProgram* getGLProgram() const;
    
public:
    static const PixelFormatInfoMap& getPixelFormatInfoMap();
    
private:

    /**转换函数*/

    /**
	将像素格式转换为指定的格式，如果像素格式是PixelFormat::Automatic,将自动检测像素格式并转换为最接近的格式。
	返回转换后的像素格式。如果outData != data,那么你需要手动释放outData。
    */
    static PixelFormat convertDataToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat originFormat, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);

    static PixelFormat convertI8ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);
    static PixelFormat convertAI88ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);
    static PixelFormat convertRGB888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);
    static PixelFormat convertRGBA8888ToFormat(const unsigned char* data, ssize_t dataLen, PixelFormat format, unsigned char** outData, ssize_t* outDataLen);

    //I8 to XXX
    static void convertI8ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertI8ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

    //AI88 to XXX
    static void convertAI88ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertAI88ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

    //RGB888 to XXX
    static void convertRGB888ToRGBA8888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGB888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

    //RGBA8888 to XXX
    static void convertRGBA8888ToRGB888(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToRGB565(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToI8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToA8(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToAI88(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToRGBA4444(const unsigned char* data, ssize_t dataLen, unsigned char* outData);
    static void convertRGBA8888ToRGB5A1(const unsigned char* data, ssize_t dataLen, unsigned char* outData);

protected:
    /** 纹理的像素格式*/
    Texture2D::PixelFormat _pixelFormat;

    /** 宽度，以像素为单位*/
    int _pixelsWide;

    /** 高度，以像素为单位*/
    int _pixelsHigh;

    /** 纹理名称*/
    GLuint _name;

    /** 纹理的最大S值*/
    GLfloat _maxS;
    
    /** 纹理的最大T值*/
    GLfloat _maxT;

    /** content大小*/
    Size _contentSize;

    /** 指示纹理是否自乘Alpha值 */
    bool _hasPremultipliedAlpha;

    bool _hasMipmaps;

    /** drawAtPoint和drawInRect方法所使用的shader程序*/
    GLProgram* _shaderProgram;

    static const PixelFormatInfoMap _pixelFormatInfoTables;

    bool _antialiasEnabled;
};


// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE2D_H__

