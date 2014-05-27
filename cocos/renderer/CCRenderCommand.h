/****************************************************************************
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


#ifndef __CCRENDERCOMMAND_H_
#define __CCRENDERCOMMAND_H_

#include "base/CCPlatformMacros.h"
#include <stdint.h>
#include "base/ccTypes.h"

NS_CC_BEGIN

/** `RenderCommand`体系的基类.
*
  渲染器(`Renderer`) 指定如何渲染`RenderCommands`对象.
 */
class RenderCommand
{
public:

    enum class Type
    {
        UNKNOWN_COMMAND,
        QUAD_COMMAND,
        CUSTOM_COMMAND,
        BATCH_COMMAND,
        GROUP_COMMAND,
    };

    /** 获取渲染器指令Id */
    inline float getGlobalOrder() const { return _globalOrder; }

    /** 返回指令类型 */
    inline Type getType() const { return _type; }

protected:
    RenderCommand();
    virtual ~RenderCommand();

    void printID();

    // 类型(Type)用于避免动态转换，快速的
    Type _type;

    // 命令通过深度排序
    float _globalOrder;
};

NS_CC_END

#endif //__CCRENDERCOMMAND_H_
