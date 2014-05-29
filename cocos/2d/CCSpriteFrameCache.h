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

/** @brief Singleton that handles the loading of the sprite frames.
 It saves in a cache the sprite frames.
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
     * 如果你想要用另一个纹理，你应该用
addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName) 方法.
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
     @since v0.99.5
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames. 
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string&plist, Texture2D *texture);

    /** Adds an sprite frame with a given name.
     If the name already exists, then the contents of the old name will be replaced with the new one.
     */
    void addSpriteFrame(SpriteFrame *frame, const std::string& frameName);

    /** Purges the dictionary of loaded sprite frames.
     * Call this method if you receive the "Memory Warning".
     * In the short term: it will free some resources preventing your app from being killed.
     * In the medium term: it will allocate more resources.
     * In the long term: it will be the same.
     */
    void removeSpriteFrames();

    /** Removes unused sprite frames.
     * Sprite Frames that have a retain count of 1 will be deleted.
     * It is convenient to call this method after when starting a new Scene.
     */
    void removeUnusedSpriteFrames();

    /** Deletes an sprite frame from the sprite frame cache. */
    void removeSpriteFrameByName(const std::string& name);

    /** Removes multiple Sprite Frames from a plist file.
    * Sprite Frames stored in this file will be removed.
    * It is convenient to call this method when a specific texture needs to be removed.
    * @since v0.99.5
    */
    void removeSpriteFramesFromFile(const std::string& plist);

    /** Removes all Sprite Frames associated with the specified textures.
     * It is convenient to call this method when a specific texture needs to be removed.
     * @since v0.995.
     */
    void removeSpriteFramesFromTexture(Texture2D* texture);

    /** Returns an Sprite Frame that was previously added.
     If the name is not found it will return nil.
     You should retain the returned copy if you are going to use it.
     * @js getSpriteFrame
     * @lua getSpriteFrame
     */
    SpriteFrame* getSpriteFrameByName(const std::string& name);

    /** @deprecated use getSpriteFrameByName() instead */
    CC_DEPRECATED_ATTRIBUTE SpriteFrame* spriteFrameByName(const std::string&name) { return getSpriteFrameByName(name); }

private:
    /*Adds multiple Sprite Frames with a dictionary. The texture will be associated with the created sprite frames.
     */
    void addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture);

    /** Removes multiple Sprite Frames from Dictionary.
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
