/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __AssetsManager__
#define __AssetsManager__

#include <string>

#include <mutex>

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"

NS_CC_EXT_BEGIN

class AssetsManagerDelegateProtocol;

/*
 *  这个是用来自动更新诸如图片、脚本等资源的类，
 *  更新包应该是一个zip文件，并且在服务器端应该有一个命名为version的文件，里面包含版本代码
 *  
 */
class AssetsManager : public Node
{
public:
    enum class ErrorCode
    {
        //通过创建一个存储下载数据的文件引起的错误
        CREATE_FILE,
        /** 网络错误
         -- 网络不可用
         -- 超时
         -- ...
         */
        NETWORK,
        /** 没有新的版本
         */
        NO_NEW_VERSION,
        /** 因为压缩文件引起的错误
         -- 无法打开zip文件
         -- 无法读取文件全局信息
         -- 无法读取文件信息
         -- 无法创建目录
         -- ...
         */
        UNCOMPRESS,
    };
    
    /* @brief 通过新包的资源定位符、版本代码、存储路径来创建AssetsManager
     *
     * @param packageUrl 新包的URL, 这个包应该是一个zip文件.
     * @param versionFileUrl 版本文件的URL. 它应该包含新包的版本代码.
     * @param storagePath 存储下载的文件的路径.
     * @js NA
     */
    AssetsManager(const char* packageUrl = NULL, const char* versionFileUrl = NULL, const char* storagePath = NULL);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~AssetsManager();
    
    typedef std::function<void(int)> ErrorCallback;
    typedef std::function<void(int)> ProgressCallback;
    typedef std::function<void(void)> SuccessCallback;

    /* @brief 在脚本环境中访问
     */
    static AssetsManager* create(const char* packageUrl, const char* versionFileUrl, const char* storagePath, ErrorCallback errorCallback, ProgressCallback progressCallback, SuccessCallback successCallback );

    /* @brief 检查是否有新版本的资源.
     *       你应该在更新之前调用这个方法，然后让用户决定是否更新资源
     */
    virtual bool checkUpdate();
    
    using Node::update;
    /* @brief  如果有新的版本，就下载并且解压缩下载的zip文件。当然需要设置下载的文件的搜寻路径。
     */
    virtual void update();
    
    /* @brief 获取包的URL.
     */
    const char* getPackageUrl() const;
    
    /* @brief 设置包的URL.
     */
    void setPackageUrl(const char* packageUrl);
    
    /* @brief 获取版本文件的URL.
     */
    const char* getVersionFileUrl() const;
    
    /* @brief 设置版本文件的URL.
     */
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief 获取当前版本.
     */
    std::string getVersion();
    
    /* @brief 删除以记录的版本代码.
     */
    void deleteVersion();
    
    /* @brief 获取存储路径.
     */
    const char* getStoragePath() const;
    
    /* @brief 设置存储路径.
     *
     * @param storagePath 已下载资源的路径.
     * @warm 这应该是一个有效的路径.
     */
    void setStoragePath(const char* storagePath);
    
    /** @brief 设置委托，这个委托将会接收消息
     * @js NA
     * @lua NA
     */
    void setDelegate(AssetsManagerDelegateProtocol *delegate);
    
    /**
     * @js NA
     * @lua NA
     */
    AssetsManagerDelegateProtocol* getDelegate() const { return _delegate ;}
    
    /** @brief 设置以秒为单位的连接超时时间
     */
    void setConnectionTimeout(unsigned int timeout);
    
    /** @brief 获取以秒为单位的连接超时时间
     */
    unsigned int getConnectionTimeout();
    
    /* 通过一个新的线程来实现下载和解压缩
     */
    friend int assetsManagerProgressFunc(void *, double, double, double, double);

protected:
    bool downLoad();
    void checkStoragePath();
    bool uncompress();
    bool createDirectory(const char *path);
    void setSearchPath();
    void downloadAndUncompress();

private:
    /** @brief 初始化存储路径.
     */
    void createStoragePath();
    
    /** @brief 销毁存储路径
     */
    void destroyStoragePath();
    
private:
    
    //存储下载的资源的路径
    std::string _storagePath;
    
   
    //下载的资源的版本
    std::string _version;
    
    std::string _packageUrl;
    std::string _versionFileUrl;
    
    std::string _downloadedVersion;
    
    void *_curl;

    unsigned int _connectionTimeout;
    
    AssetsManagerDelegateProtocol *_delegate; 
    
    bool _isDownloading;
    bool _shouldDeleteDelegateWhenExit;
    
    std::string keyOfVersion() const;
    std::string keyOfDownloadedVersion() const;
};

class AssetsManagerDelegateProtocol
{
public:
    virtual ~AssetsManagerDelegateProtocol(){};
public:
    /* @brief 如果发生错误，则调用这个回调函数
       @param 错误类型
     * @js NA
     * @lua NA
     */
    virtual void onError(AssetsManager::ErrorCode errorCode) {};
    /** @brief 用来记录下载进度的回调函数
        @param 以下载的百分比
        @warning    这个回调函数只是用来记录正在下载的百分比.
              你可以在onSuccess()中编写代码来让AssetsManager在下载完成之后会做一些其他的事情。
     * @js NA
     * @lua NA
     */
    virtual void onProgress(int percent) {};
    /** @brief 如果成功，则调用这个回调函数
     * @js NA
     * @lua NA
     */
    virtual void onSuccess() {};
};

// 弃用的声明
CC_DEPRECATED_ATTRIBUTE typedef AssetsManager CCAssetsManager;
CC_DEPRECATED_ATTRIBUTE typedef AssetsManagerDelegateProtocol CCAssetsManagerDelegateProtocol;

NS_CC_EXT_END;

#endif /* defined(__AssetsManager__) */
