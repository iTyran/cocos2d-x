/****************************************************************************
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
#ifndef __SUPPORT_ZIPUTILS_H__
#define __SUPPORT_ZIPUTILS_H__

#include <string>
#include "base/CCPlatformConfig.h"
#include "CCPlatformDefine.h"
#include "base/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "2d/platform/android/CCFileUtilsAndroid.h"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
// for import ssize_t on win32 platform
#include "CCStdC.h"
#endif

namespace cocos2d
{
    /* XXX: 编译指示包 ??? */
    /** @struct CCZHeader
    */
    struct CCZHeader {
        unsigned char   sig[4];             // 签名.应该是 'CCZ!' 4 字节
        unsigned short  compression_type;   // 应该是 0
        unsigned short  version;            // 应该是 2 (尽管版本 type==1 也支持)
        unsigned int    reserved;           // 为用户保留
        unsigned int    len;                // 未压缩文件的大小
    };

    enum {
        CCZ_COMPRESSION_ZLIB,               // zlib 格式.
        CCZ_COMPRESSION_BZIP2,              // bzip2 格式 (还不支持)
        CCZ_COMPRESSION_GZIP,               // gzip 格式 (还不支持)
        CCZ_COMPRESSION_NONE,               // plain (还不支持)
    };

    class CC_DLL ZipUtils
    {
    public:
        /**
        *无论是膨胀的zlib或gzip的瘪内存。膨胀的内存
        *由调用者释放。
        *
        *它会分配256K的目标缓冲区。如果这还不够，将乘2前面的缓冲区大小，直到有足够的存储器。
        *@returns 返回瘪缓冲区的长度
        * 
        @since v0.8.1
        */
        CC_DEPRECATED_ATTRIBUTE static ssize_t ccInflateMemory(unsigned char *in, ssize_t inLength, unsigned char **out) { return inflateMemory(in, inLength, out); }
        static ssize_t inflateMemory(unsigned char *in, ssize_t inLength, unsigned char **out);

        /**
        *无论是膨胀的zlib或gzip的瘪内存。膨胀的内存
        *由调用者释放。
        *
        * outLenghtHint被假定为所需要的空间分配膨胀的缓冲区。
        *
        *@returns 瘪缓冲区的长度
        * 
        @since V1.0.0
        */
        CC_DEPRECATED_ATTRIBUTE static ssize_t ccInflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t outLengthHint) { return inflateMemoryWithHint(in, inLength, out, outLengthHint); }
        static ssize_t inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t outLengthHint);

        /**膨胀一个gzip文件到内存
        *
        *@returns 瘪缓冲区的长度
        *
        *@since v0.99.5
        */
        CC_DEPRECATED_ATTRIBUTE static int ccInflateGZipFile(const char *filename, unsigned char **out) { return inflateGZipFile(filename, out); }
        static int inflateGZipFile(const char *filename, unsigned char **out);
        
        /**测试的文件是否是一个gzip格式的文件
        *
        *@returns true是gzip格式的文件. false则不是
        *
        *@since V3.0
        */
        CC_DEPRECATED_ATTRIBUTE static bool ccIsGZipFile(const char *filename) { return isGZipFile(filename); }
        static bool isGZipFile(const char *filename);

        /**测试缓冲区是否是gzip格式
        *
        *@returns true是gzip格式。false 则不是
        *
        *@since V3.0
        */
        CC_DEPRECATED_ATTRIBUTE static bool ccIsGZipBuffer(const unsigned char *buffer, ssize_t len) { return isGZipBuffer(buffer, len); }
        static bool isGZipBuffer(const unsigned char *buffer, ssize_t len);

        /**膨胀一个CCZ文件到内存
        *
        *@returns 瘪缓冲区的长度
        *
        *@since v0.99.5
        */
        CC_DEPRECATED_ATTRIBUTE static int ccInflateCCZFile(const char *filename, unsigned char **out) { return inflateCCZFile(filename, out); }
        static int inflateCCZFile(const char *filename, unsigned char **out);

        /**一个膨胀的缓冲区CCZ格式转换到内存
        *
        *@returns 瘪缓冲区的长度
        *
        *@since V3.0
        */
        CC_DEPRECATED_ATTRIBUTE static int ccInflateCCZBuffer(const unsigned char *buffer, ssize_t len, unsigned char **out) { return inflateCCZBuffer(buffer, len, out); }
        static int inflateCCZBuffer(const unsigned char *buffer, ssize_t len, unsigned char **out);
        
        /**测试一个文件是否是一个CCZ格式的文件
        *
        *@returns true是CCZ格式的文件。false则不是
        *
        *@since V3.0
        */
        CC_DEPRECATED_ATTRIBUTE static bool ccIsCCZFile(const char *filename) { return isCCZFile(filename); }
        static bool isCCZFile(const char *filename);

        /**测试缓冲区是否是CCZ格式
        *
        *@returns true是CCZ格式。false则不是
        *
        *@since V3.0
        */
        CC_DEPRECATED_ATTRIBUTE static bool ccIsCCZBuffer(const unsigned char *buffer, ssize_t len) { return isCCZBuffer(buffer, len); }
        static bool isCCZBuffer(const unsigned char *buffer, ssize_t len);

        /**分别设置pvr.ccz加密关键部件增加
        *安全性。
        *
        *举例：如果该键用来pvr.ccz加密文件是
        * 0xaaaaaaaabbbbbbbbccccccccdddddddd，你会4次不同的调用这个函数
        *最好是从4个不同的源文件，如下
        *
        * ZipUtils :: setPvrEncryptionKeyPart （0， 0xaaaaaaaa ） ;
        * ZipUtils :: setPvrEncryptionKeyPart （1， 0xbbbbbbbb ） ;
        * ZipUtils :: setPvrEncryptionKeyPart （2， 0xcccccccc ） ;
        * ZipUtils :: setPvrEncryptionKeyPart （3 ， 0xdddddddd ） ;
        *
        *拆分键分为4部分，并
        *从4个不同的源文件调用函数增加了难度
        *逆向工程的加密密钥。请注意， 加密
        *不是"永远"100%安全的，关键代码可以被有知识的人破解
        *
        *
        *重要提示：请务必调用setPvrEncryptionKey或
        * setPvrEncryptionKeyPart与所有的关键部位,在此之前
        *加载spritesheet或解密将失败， spritesheet
        *将无法加载。
        *
        *@param index 部分key[ 0 .. 3]
        *@param value 关键部分的参数value值
        */
        CC_DEPRECATED_ATTRIBUTE static void ccSetPvrEncryptionKeyPart(int index, unsigned int value) { setPvrEncryptionKeyPart(index, value); }
        static void setPvrEncryptionKeyPart(int index, unsigned int value);
        
        /**设置pvr.ccz加密密钥。
        *
        *例如：如果用来加密pvr.ccz文件是密钥是
        *0xaaaaaaaabbbbbbbbccccccccdddddddd你会调用这个函数，
        *密钥拆分成4个部分.如下
        *
        * ZipUtils:: setPvrEncryptionKey（0xaaaaaaaa，0xbbbbbbbb，0xcccccccc，0xdddddddd）;
        *
        *请注意，使用此功能可以更容易地进行逆向工程和
        *发现完整的密钥，因为在关键部位都存在一次
        *函数调用。
        *
        *重要提示：请务必调用setPvrEncryptionKey或
        * setPvrEncryptionKeyPart与所有的密钥部位,在此之前加载
        *在spritesheet或解密将失败，spritesheet
        *将无法加载。
        *
        *@param keyPart1 密钥部分1。
        *@param keyPart2 密钥部分2。
        *@param keyPart3 密钥部分3。
        *@param keyPart4 密钥部分4。
        */
        CC_DEPRECATED_ATTRIBUTE static void ccSetPvrEncryptionKey(unsigned int keyPart1, unsigned int keyPart2, unsigned int keyPart3, unsigned int keyPart4) { setPvrEncryptionKey(keyPart1, keyPart2, keyPart3, keyPart4); }
        static void setPvrEncryptionKey(unsigned int keyPart1, unsigned int keyPart2, unsigned int keyPart3, unsigned int keyPart4);

    private:
        static int inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t *outLength, ssize_t outLenghtHint);
        static inline void decodeEncodedPvr (unsigned int *data, ssize_t len);
        static inline unsigned int checksumPvr(const unsigned int *data, ssize_t len);

        static unsigned int s_uEncryptedPvrKeyParts[4];
        static unsigned int s_uEncryptionKey[1024];
        static bool s_bEncryptionKeyIsValid;
    };

    // 前向声明
    class ZipFilePrivate;

    /**
     * Zip文件 - 读取的辅助类。
     *
     *它会缓存特定zip文件列表在压缩文档中的位置，
     *所以这将是更快的读取某些特定的文件或检查他们的存在性。
     *
     *@since V2.0.5
     */
    class ZipFile
    {
    public:
        /**
        *构造函数，打开zip文件，存储文件列表。
        *
        *@param zipFile Zip文件名
        *@param filter 文件名的第一部分，代表可访问。
        *例如，"assets/”。其他文件将被错过。
        * 
        *@since V2.0.5
        */
        ZipFile(const std::string &zipFile, const std::string &filter = std::string());
        virtual ~ZipFile();

        /**
        *重新根据新的过滤器字符串生成可访问的文件列表。
        *
        *@param filter 过滤器的新字符串（文件名的第一部分）
        *@return true时压缩文件打开成功，这时有可能找到
        *至少在第一个文件，否则返回false
        * 
        *@since V2.0.5
        */
        bool setFilter(const std::string &filter);

        /**
        *检查一个文件是否不在zip文件中
        *
        *@param fileName 待检查存在的文件
        *@return true，文件存在，否则false
        *
        *@since V2.0.5
        */
        bool fileExists(const std::string &fileName) const;

        /**
        *从一个zip文件获取资源文件中的数据。
        *@param fileName 文件名
        *@param[out] pSize 如果文件读取操作成功，这将是数据的大小，否则为0。
        *@return 成功时，返回一个指向数据的指针，否则返回nullptr。
        *@warning 召回(Recall)：在返回任何非nullptr指针时你负责调用free()。
        * 
        *@since V2.0.5
        */
        unsigned char *getFileData(const std::string &fileName, ssize_t *size);

    private:
        /**内部数据如zip文件指针/文件列表数组等等*/
        ZipFilePrivate *_data;
    };
} // end of namespace cocos2d
#endif // __SUPPORT_ZIPUTILS_H__

