/****************************************************************************
Copyright (c) 2011      Ricardo Quesada
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

#ifndef __CCGLPROGRAMCACHE_H__
#define __CCGLPROGRAMCACHE_H__

#include "base/CCRef.h"

#include <string>
#include <unordered_map>

NS_CC_BEGIN

class GLProgram;

/**
 * @addtogroup shaders
 * @{
 */

/** GLProgramCache
 单例的用于存储管理GL编程对象(shaders着色器)
 @since v2.0
 */
class CC_DLL GLProgramCache : public Ref
{
public:
    /**
     * @js ctor
     */
    GLProgramCache();
    /**
     * @js NA
     * @lua NA
     */
    ~GLProgramCache();

    /** 返回着色器实例 */
    static GLProgramCache* getInstance();

    /** 净化缓存. 释放对该实例的引用. */
    static void destroyInstance();

    /** @deprecated 用 getInstance() 替代 */
    CC_DEPRECATED_ATTRIBUTE static GLProgramCache* sharedShaderCache();

    /** @deprecated 用 destroyInstance() 替代 */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedShaderCache();

    /** 加载默认着色器(shaders) */
    void loadDefaultGLPrograms();
    CC_DEPRECATED_ATTRIBUTE void loadDefaultShaders() { loadDefaultGLPrograms(); }

    /** 重加载加载默认着色器(shaders) */
    void reloadDefaultGLPrograms();
    CC_DEPRECATED_ATTRIBUTE void reloadDefaultShaders() { reloadDefaultGLPrograms(); }

    /** 返回指定key的 GL编程对象
     */
    GLProgram * getGLProgram(const std::string &key);
    CC_DEPRECATED_ATTRIBUTE GLProgram * getProgram(const std::string &key) { return getGLProgram(key); }
    CC_DEPRECATED_ATTRIBUTE GLProgram * programForKey(const std::string &key){ return getGLProgram(key); }

    /** 添加一个(GL编程对象)GLProgram到缓存中，并指定名字 */
    void addGLProgram(GLProgram* program, const std::string &key);
    CC_DEPRECATED_ATTRIBUTE void addProgram(GLProgram* program, const std::string &key) { addGLProgram(program, key); }

private:
    bool init();
    void loadDefaultGLProgram(GLProgram *program, int type);

//    Dictionary* _programs;
    std::unordered_map<std::string, GLProgram*> _programs;
};

// end of shaders group
/// @}

NS_CC_END

#endif /* __CCGLPROGRAMCACHE_H__ */
