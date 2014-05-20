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

/** 管理动画的单例
 * 用于保存动画缓存
 * 在V0.99.5版本之前，推荐的方法是保存Sprite，在这之后的版本，用这个类代替。
*/
class CC_DLL AnimationCache : public Ref
{
public:

    AnimationCache();

    ~AnimationCache();

    /** 返回一个动画缓存的单例*/
    static AnimationCache* getInstance();

     /** 清除缓存，清除所有的动画对象和单例*/
    static void destroyInstance();

    /** 使用下面的方法代替getInstance()*/
    CC_DEPRECATED_ATTRIBUTE static AnimationCache* sharedAnimationCache() { return AnimationCache::getInstance(); }

    /** 使用下面的方法代替destroyInstance()*/
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedAnimationCache() { return AnimationCache::destroyInstance(); }

    bool init(void);

    /** 添加一个动画，带名字*/
    void addAnimation(Animation *animation, const std::string& name);

     /** 从缓存中删除一个动画*/
    void removeAnimation(const std::string& name);

     /** 在js和lua中使用removeAnimation()代替 
     */
    CC_DEPRECATED_ATTRIBUTE void removeAnimationByName(const std::string& name){ removeAnimation(name);}

    /** 返回一个预先加载的动画
     * 如果动画名字为空
     * 需要retain之后再使用
    */
    Animation* getAnimation(const std::string& name);

     /** 在js和lua中使用getAnimation()代替 
     */
    CC_DEPRECATED_ATTRIBUTE Animation* animationByName(const std::string& name){ return getAnimation(name); }

     /** 从字典中添加一个动画 
      * 确保帧动画是预先加载在Sprite帧缓存中的
      * 参数plist：是一个相对的文件路径，使用它可以找到plist路径，从而加载Sprite帧
     */
    void addAnimationsWithDictionary(const ValueMap& dictionary,const std::string& plist);

     /** 从plist文件中添加一个动画
      * 确保这个帧动画事先加载到了Sprite帧缓存中
      * 从V1.1版本开式js和lua语言中使用addAnimation代替
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
