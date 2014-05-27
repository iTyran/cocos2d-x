/****************************************************************************
 Copyright (c) 2011      Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (C) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCGLSTATE_H__
#define __CCGLSTATE_H__

#include <cstdint>

#include "CCGL.h"
#include "base/CCPlatformMacros.h"

NS_CC_BEGIN

/**
 * @addtogroup shaders
 * @{
 */

class GLProgram;

namespace GL {

/** 顶点(vertex)的属性标志 */
enum {
    VERTEX_ATTRIB_FLAG_NONE       = 0,

    VERTEX_ATTRIB_FLAG_POSITION   = 1 << 0,
    VERTEX_ATTRIB_FLAG_COLOR      = 1 << 1,
    VERTEX_ATTRIB_FLAG_TEX_COORD = 1 << 2,

    VERTEX_ATTRIB_FLAG_POS_COLOR_TEX = (VERTEX_ATTRIB_FLAG_POSITION | VERTEX_ATTRIB_FLAG_COLOR | VERTEX_ATTRIB_FLAG_TEX_COORD),
};

/** @file ccGLStateCache.h
*/

/** 使GL 的状态缓存作废.
 如果启用 CC_ENABLE_GL_STATE_CACHE 会重置 GL 状态缓存.
 @since v2.0.0
 */
void CC_DLL invalidateStateCache(void);

/** 使用GL编程传人参数(in case)program不同于当前.
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用, 它会直接使用 glUseProgram()方法.
 @since v2.0.0
 */
void CC_DLL useProgram(GLuint program);

/** 删除 GL编程. 如果program正在使用，该方法是program无效.
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用, 他会直接执行 glDeleteProgram() 方法.
 @since v2.0.0
 */
void CC_DLL deleteProgram(GLuint program);

/** 使用混合方法，传人参数(in case)是没有被使用的.
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用, 它会直接执行 glBlendFunc()方法.
 @since v2.0.0
 */
void CC_DLL blendFunc(GLenum sfactor, GLenum dfactor);

/** 重设混合模式恢复缓存状态，假使你使用glBlendFuncSeparate() 或者 glBlendEquation()方法.
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用, 它将仅仅使用GL_FUNC_ADD设置默认混合模式.
 @since v2.0.0
 */
void CC_DLL blendResetToCache(void);

/** 设置投影矩阵暗淡(dirty)
 @since v2.0.0
 */
void CC_DLL setProjectionMatrixDirty(void);

/** 将会使顶点属性像标记一样传递.
 可能的标记(flags):

    * VERTEX_ATTRIB_FLAG_POSITION
    * VERTEX_ATTRIB_FLAG_COLOR
    * VERTEX_ATTRIB_FLAG_TEX_COORDS

 这些标记可以是ORed. 标记没有指定, 将会被禁用.

 @since v2.0.0
 */
void CC_DLL enableVertexAttribs(uint32_t flags);

/** 如果纹理(texture)没有绑定到纹理单位0,绑定它.
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用, 它将直接调用 glBindTexture()方法.
 @since v2.0.0
 */
void CC_DLL bindTexture2D(GLuint textureId);


/** 如果纹理(texture)没有被绑定到指定的单位，绑定它.
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用,它将直接调用 glBindTexture() 方法.
 @since v2.1.0
 */
void CC_DLL bindTexture2DN(GLuint textureUnit, GLuint textureId);

/** 它将删除指定的textureId的纹理. 如果该纹理已经绑定,此方法会是它的缓存无效.
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用, 它将直接调用glDeleteTextures()方法.
 @since v2.0.0
 */
void CC_DLL deleteTexture(GLuint textureId);

/** 它将删除指定的textureId的纹理.如果该纹理已经绑定, 它将使缓存从给定的纹理单元失效.
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用, 它将直接调用 glDeleteTextures() 方法.
 @since v2.1.0
 */
void CC_DLL deleteTextureN(GLuint textureUnit, GLuint textureId);

/** 选取活动的纹理单元(texture unit).
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用, 它将直接调用 glActiveTexture() 方法.
 @since v3.0
 */
void CC_DLL activeTexture(GLenum texture);

/** 如果顶点(vertex)数组没有绑定, 绑定它.
 如果 CC_ENABLE_GL_STATE_CACHE 被禁用, 它将直接调用 glBindVertexArray() 方法.
 @since v2.0.0
 */
void CC_DLL bindVAO(GLuint vaoId);

// end of shaders group
/// @}

} // Namespace GL
NS_CC_END
    

#endif /* __CCGLSTATE_H__ */
