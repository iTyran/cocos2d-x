/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
CopyRight (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __CC_ANIMATION_CACHE_H__
#define __CC_ANIMATION_CACHE_H__

#include "base/CCRef.h"
#include "base/CCMap.h"
#include "base/CCValue.h"

#include <string>

NS_CC_BEGIN

class Animation;

/**
 * @addtogroup sprite_nodes
 * @{
 */

/** 动画缓存单例类。
 如何你想要保存动画，你需要使用这个缓存。

v0.99.5之前, 建议在sprite中保存动画。v0.99.5之后，建议使用这个缓存类。

@since v0.99.5
*/
class CC_DLL AnimationCache : public Ref
{
public:
    /**
     * @js ctor
     */
    AnimationCache();
    /**
     * @js NA
     * @lua NA
     */
    ~AnimationCache();
    /** 返回缓存单例实体 */
    static AnimationCache* getInstance();

    /** 清空缓存，所有动画对象都将被释放。
     */
    static void destroyInstance();

    /** @deprecated 使用getInstance() 代替 */
    CC_DEPRECATED_ATTRIBUTE static AnimationCache* sharedAnimationCache() { return AnimationCache::getInstance(); }

    /** @deprecated 使用 destroyInstance() 代替 */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedAnimationCache() { return AnimationCache::destroyInstance(); }

    bool init(void);

    /** 添加入一个动画到缓存，并以name作为标示。
    */
    void addAnimation(Animation *animation, const std::string& name);

    /** 从缓存中删除一个名为name的动画。
     
     */
    void removeAnimation(const std::string& name);
    /** @deprecated. 使用 removeAnimation() 替代
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void removeAnimationByName(const std::string& name){ removeAnimation(name);}

    /** Returns 查找并返回名了name的动画。
     * 如果找不到，返回NULL
    */
    Animation* getAnimation(const std::string& name);
    /**
     @deprecated. 使用getAnimation() 替代
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Animation* animationByName(const std::string& name){ return getAnimation(name); }

    /** 从字典添加一个动画
     * 确保帧已经加载到了SpriteFrameCache中。
     @param plist plist文件的相对路径，用来加载SpriteFrames。
     @since v1.1
     */
    void addAnimationsWithDictionary(const ValueMap& dictionary,const std::string& plist);

    /** 从plist添加一个动画。
     * 确保帧已经加载到了SpriteFrameCache中。
     * @since v1.1
     * @js addAnimations
     * @lua addAnimations
     */
    void addAnimationsWithFile(const std::string& plist);

private:
    void parseVersion1(const ValueMap& animations);
    void parseVersion2(const ValueMap& animations);

private:
    Map<std::string, Animation*> _animations;
    static AnimationCache* s_sharedAnimationCache;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_ANIMATION_CACHE_H__
