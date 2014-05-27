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
****************************************************************************/

#ifndef __CCTEXTURE_CACHE_H__
#define __CCTEXTURE_CACHE_H__

#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <string>
#include <unordered_map>
#include <functional>

#include "base/CCRef.h"
#include "2d/CCTexture2D.h"
#include "2d/platform/CCImage.h"

#if CC_ENABLE_CACHE_TEXTURE_DATA
    #include "2d/platform/CCImage.h"
    #include <list>
#endif

NS_CC_BEGIN

/**
 * @addtogroup textures
 * @{
 */
/*
* 从3.0版本开始，TextureCache不再被看作独立的类，它会被认为是director的一部分
* 所有对TextureCache::getInstance()的调用应使用Director::getInstance()->getTextureCache()进行替代
*/

/** @brief 用来处理纹理贴图（texture）的加载的独立的类
* 一旦纹理贴图（texture）被加载，它会在下一次返回
* 一个用来节省GPU和CPU内存的，指向之前被加载的纹理贴图（texture）的引用（reference）
*/
class CC_DLL TextureCache : public Ref
{
public:
    /** 返回缓存的共享的实例 */
    CC_DEPRECATED_ATTRIBUTE static TextureCache * getInstance();

    /** @deprecated 使用getInstance()作为替代 */
    CC_DEPRECATED_ATTRIBUTE static TextureCache * sharedTextureCache();

    /** 清除缓存。释放保留的实例
     @since v0.99.0
     */
    CC_DEPRECATED_ATTRIBUTE static void destroyInstance();

    /** @deprecated 使用destroyInstance()作为替代 */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedTextureCache();

    /** 重新加载所有纹理贴图（texture）
     避免调用该函数，应在框架工作时由框架调用
     目前这个函数不会做任何事，请使用VolatileTextureMgr::reloadAllTextures
     */
    CC_DEPRECATED_ATTRIBUTE static void reloadAllTextures();

public:
    /**
     * @js ctor
     */
    TextureCache();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TextureCache();
    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

//    Dictionary* snapshotTextures();

    /** 返回与给定文件名相对应的Texture2D对象
    * 如果该文件名没有被预加载，这个方法会创建一个新的Texture2D对象，并返回该Texture2D对象
    * 文件名会被用作key
    * 否则会返回一个指向预加载图像的引用（reference）
    * 支持的图像文件的类型有: .png, .bmp, .tiff, .jpeg, .pvr
    */
    Texture2D* addImage(const std::string &filepath);

    /* 返回与给定文件映像（file image）相对应的Texture2D对象
    * 如果该图像文件没有被预加载，这个方法会创建一个新的Texture2D对象，并返回该Texture2D对象
    * 否则该方法会在新的thread中加载一个纹理贴图（texture），并且当图像被加载后，回调函数将会被调用，并且该Texture2D对象会被用作回调函数的参数
    * 回调函数会被从主thread中调用，所以通过回调函数创建任何cocos2d对象都是安全的。
    * 支持的图像文件的类型有: .png, .jpg
    * @since v0.8
    */
    virtual void addImageAsync(const std::string &filepath, const std::function<void(Texture2D*)>& callback);

    /** 返回与给定图像相对应的Texture2D对象
    * 如果该图像没有被预加载，这个方法会创建一个新的Texture2D对象，并返回该Texture2D对象
    * 否则会返回一个指向预加载图像的引用（reference）
    * 参数“key”会被用作缓存中的储存关键字
    * 如果“key”为空值，每次都会创建一个新的纹理贴图（texture）
    */
    Texture2D* addImage(Image *image, const std::string &key);
    CC_DEPRECATED_ATTRIBUTE Texture2D* addUIImage(Image *image, const std::string& key) { return addImage(image,key); }

    /** 返回一个已经被创建的纹理贴图（texture）。如果该纹理贴图不存在则返回nil
    @since v0.99.5
    */
    Texture2D* getTextureForKey(const std::string& key) const;
    CC_DEPRECATED_ATTRIBUTE Texture2D* textureForKey(const std::string& key) const { return getTextureForKey(key); }

    /** 从图像文件重新加载纹理贴图（texture）
    * 如果这个图像文件没有被加载过，就加载该图像文件。
    * 否则会从文件映像（file image）中重新加载该纹理贴图（texture）
    * 参数“filenName”是文件映像（file image）的相对或绝对路径
    * 如果重新加载成功就返回true，否则返回false
    */
    bool reloadTexture(const std::string& fileName);

    /** 清除加载纹理贴图的记录
    * 如果你收到“内存警告”请调用该方法
    * 在短期内: 会释放一些资源文件来防止你的app出现闪退现象
    * 在中期: 会分配更多资源
    * 从长远来看: 没有区别
    */
    void removeAllTextures();

    /** 清除所有没有在使用中的纹理贴图（texture）
    * 保留计数（retain count）为1的纹理贴图（texture）会被删除
    * 在进入一个新场景后，调用本方法会带来不少方便
    * @since v0.8
    */
    void removeUnusedTextures();

    /** 通过给定的纹理贴图（texture）从缓存中删除该纹理贴图
    */
    void removeTexture(Texture2D* texture);

    /** 通过给定的纹理贴图（texture）的关键名（key name）从缓存中删除该纹理贴图
    @since v0.99.4
    */
    void removeTextureForKey(const std::string &key);

    /** 将该TextureCache目前的内容输出到CCLog
    * 这个方法会尝试去计算每一个纹理贴图（texture）的size和当前使用中的所有纹理贴图（texture）所占用内存的总和
    *
    * @since v1.0
    */
    std::string getCachedTextureInfo() const;

    //在销毁实例前，等待纹理贴图缓存的退出
    //由director调用，请不要在外部调用
    void waitForQuit();

private:
    void addImageAsyncCallBack(float dt);
    void loadImage();

public:
    struct AsyncStruct
    {
    public:
        AsyncStruct(const std::string& fn, std::function<void(Texture2D*)> f) : filename(fn), callback(f) {}

        std::string filename;
        std::function<void(Texture2D*)> callback;
    };

protected:
    typedef struct _ImageInfo
    {
        AsyncStruct *asyncStruct;
        Image        *image;
    } ImageInfo;
    
    std::thread* _loadingThread;

    std::queue<AsyncStruct*>* _asyncStructQueue;
    std::deque<ImageInfo*>* _imageInfoQueue;

    std::mutex _asyncStructQueueMutex;
    std::mutex _imageInfoMutex;

    std::mutex _sleepMutex;
    std::condition_variable _sleepCondition;

    bool _needQuit;

    int _asyncRefCount;

    std::unordered_map<std::string, Texture2D*> _textures;
};

#if CC_ENABLE_CACHE_TEXTURE_DATA

class VolatileTexture
{
    typedef enum {
        kInvalid = 0,
        kImageFile,
        kImageData,
        kString,
        kImage,
    }ccCachedImageType;

private:
    VolatileTexture(Texture2D *t);
    /**
     * @js NA
     * @lua NA
     */
    ~VolatileTexture();

protected:
    friend class  VolatileTextureMgr;
    Texture2D *_texture;
    
    Image *_uiImage;

    ccCachedImageType _cashedImageType;

    void *_textureData;
    int  _dataLen;
    Size _textureSize;
    Texture2D::PixelFormat _pixelFormat;

    std::string _fileName;

    bool                      _hasMipmaps;
    Texture2D::TexParams      _texParams;
    std::string               _text;
    FontDefinition            _fontDefinition;
};

class VolatileTextureMgr
{
public:
    static void addImageTexture(Texture2D *tt, const std::string& imageFileName);
    static void addStringTexture(Texture2D *tt, const char* text, const FontDefinition& fontDefinition);
    static void addDataTexture(Texture2D *tt, void* data, int dataLen, Texture2D::PixelFormat pixelFormat, const Size& contentSize);
    static void addImage(Texture2D *tt, Image *image);

    static void setHasMipmaps(Texture2D *t, bool hasMipmaps);
    static void setTexParameters(Texture2D *t, const Texture2D::TexParams &texParams);
    static void removeTexture(Texture2D *t);
    static void reloadAllTextures();
public:
    static std::list<VolatileTexture*> _textures;
    static bool _isReloading;
private:
    // 通过 Texture2D* 寻找VolatileTexture
    // 如果没有找到，就重新创建一个
    static VolatileTexture* findVolotileTexture(Texture2D *tt);
};

#endif

// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE_CACHE_H__

