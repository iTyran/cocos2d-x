/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
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

#ifndef __SPRITE_CCSPRITE_FRAME_CACHE_H__
#define __SPRITE_CCSPRITE_FRAME_CACHE_H__

/*
 * 创建精灵帧和纹理图集，用这个工具：
 * http://zwoptex.zwopple.com/
 */

#include "2d/CCSpriteFrame.h"
#include "2d/CCTexture2D.h"
#include "base/CCRef.h"
#include "base/CCValue.h"
#include "base/CCMap.h"

#include <set>
#include <string>

NS_CC_BEGIN

class Sprite;

/**
 * @addtogroup sprite_nodes
 * @{
 */

/** @brief 
处理精灵帧的载入的单例。
它将精灵帧保存在缓存里。
 @since v0.9
 */
class CC_DLL SpriteFrameCache : public Ref
{
public:
    /** 返回精灵帧缓存的共享实例*/
    static SpriteFrameCache* getInstance(void);

    /** @deprecated 用getInstance()来代替 */
    CC_DEPRECATED_ATTRIBUTE static SpriteFrameCache* sharedSpriteFrameCache() { return SpriteFrameCache::getInstance(); }

    /** 清空缓存。释放所有的精灵帧并且保留实例。 */
    static void destroyInstance();

    /** @deprecated 用destroyInstance()来代替*/
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedSpriteFrameCache() { return SpriteFrameCache::destroyInstance(); }

protected:
    // MARMALADE: Made this protected not private, as deriving from this class is pretty useful
    SpriteFrameCache(){}

public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SpriteFrameCache();
    bool init(void);

public:
    /** 
      从一个.plist文件添加多个精灵帧。
     * 一个纹理将被自动加载。纹理名称将把.plist后缀名替换为.png来组成。
     * 如果你想要用另一个纹理，你应该用addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName) 方法.
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist);

    /** 通过一个.plist文件添加多个精灵帧。纹理将与被创建的精灵帧结合。
     @since v0.99.5
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName);

    /** 通过一个.plist文件添加多个精灵帧。纹理将与被创建的精灵帧结合。
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string&plist, Texture2D *texture);

    /** 通过给定的名称添加一个精灵帧。
        如果名称已经存在，那么原来名称的内容将被新的所替代。
     */
    void addSpriteFrame(SpriteFrame *frame, const std::string& frameName);

    /** 清除载入精灵帧的字典。
         如果接收到“Memory Warning”,那么需要调用这个方法。
         就眼前来说，它将释放一些资源来阻止你的应用崩溃掉。
         从中期的角度，它将分配更多的资源。
         从长远来说，它将变成相同的。
     */
    void removeSpriteFrames();

    /** Removes unused sprite frames.
       移除没用的精灵帧。
       保留数为1的精灵帧将被删除。
       在开始一个新的场景之后调用这个方法很方便。
     */
    void removeUnusedSpriteFrames();

    /** 从精灵帧缓存中删除一个精灵帧. */
    void removeSpriteFrameByName(const std::string& name);

    /** 从一个.plist文件移除多重精灵帧。
         存储在这个文件的精灵帧将被删除。
         当某个特定的纹理需要被删除时候调用这个方法很方便。
         * @since v0.99.5
    */
    void removeSpriteFramesFromFile(const std::string& plist);

    /** 移除与特定的纹理结合的所有的精灵帧。
         当某个特定的纹理需要被删除时候调用这个方法很方便。
     * @since v0.995.
     */
    void removeSpriteFramesFromTexture(Texture2D* texture);

    /** 返回之前所添加的精灵帧。
        如果找不到名称则返回空值。
        如果你想要使用它，你应该保留返回的备份。
     * @js getSpriteFrame
     * @lua getSpriteFrame
     */
    SpriteFrame* getSpriteFrameByName(const std::string& name);

    /** @deprecated 用getSpriteFrameByName() 来代替。*/
    CC_DEPRECATED_ATTRIBUTE SpriteFrame* spriteFrameByName(const std::string&name) { return getSpriteFrameByName(name); }

private:
    /**通过一个字典添加多重精灵帧。纹理将和被创建的精灵帧结合。
     */
    void addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture);

    /**从Dictionary移除多重精灵帧。
    * @since v0.99.5
    */
    void removeSpriteFramesFromDictionary(ValueMap& dictionary);

protected:
    Map<std::string, SpriteFrame*> _spriteFrames;
    ValueMap _spriteFramesAliases;
    std::set<std::string>*  _loadedFileNames;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __SPRITE_CCSPRITE_FRAME_CACHE_H__
