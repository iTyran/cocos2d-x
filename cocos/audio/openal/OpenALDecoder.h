#ifndef COCOSDENSHION_OPENALLOADER_H
#define COCOSDENSHION_OPENALLOADER_H

#include <vector>
#include <string>
#include <stdio.h>
#include <AL/al.h>
#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN
#define DISABLE_VORBIS
#endif

namespace CocosDenshion {

struct OpenALFile
{
    std::string debugName; ///< Log名称.
    FILE *file;
    void *mappedFile; ///< 保留给解码器使用
    size_t fileSize; ///< 保留给解码器使用.

    OpenALFile() : file(0), mappedFile(0), fileSize(0) {}
    ~OpenALFile() { clear(); }

    /// 取消内存映射并关闭文件
    void clear();
    /// 如果原来没有做内存映射，那么映射到内存
    bool mapToMemory();
};

class OpenALDecoder
{
public:
    enum Format {
        Mp3 = 0,
        Vorbis,
        Wav,
        Raw,
        Flac,
        Midi,
        Aac
    };

    virtual ~OpenALDecoder() {}
    /// 如果该格式已经支持并且成功解码
    virtual bool decode(OpenALFile &file, ALuint &result) = 0;
    virtual bool acceptsFormat(Format format) const = 0;

    static const std::vector<OpenALDecoder *> &getDecoders();
    static void installDecoders();

protected:
    static void addDecoder(OpenALDecoder *decoder);
    bool initALBuffer(ALuint &result, ALenum format,
                      const ALvoid* data, ALsizei size, ALsizei freq);

    static std::vector<OpenALDecoder *> _decoders;
};

} // namespace CocosDenshion

#endif // COCOSDENSHION_OPENALLOADER_H
