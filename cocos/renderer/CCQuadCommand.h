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

#ifndef _CC_QUADCOMMAND_H_
#define _CC_QUADCOMMAND_H_

#include "renderer/CCRenderCommand.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderCommandPool.h"

NS_CC_BEGIN

/** 使用一个或多个Quad去渲染的命令 */
class QuadCommand : public RenderCommand
{
public:
    static const int MATERIAL_ID_DO_NOT_BATCH = 0;

    QuadCommand();
    ~QuadCommand();

    /** 使用一个全局ZOrder(globalZOrder), 一个纹理ID(texture ID), 一个GL编程(`GLProgram`), 一个混合函数, 一个quads指针,
     * quads的质量, 和用于quads模型视图转换初始化命令. */
    void init(float globalOrder, GLuint texutreID, GLProgramState* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quads, ssize_t quadCount,
              const Mat4& mv);

    void useMaterial() const;


    inline uint32_t getMaterialID() const { return _materialID; }
    inline GLuint getTextureID() const { return _textureID; }
    inline V3F_C4B_T2F_Quad* getQuads() const { return _quads; }
    inline ssize_t getQuadCount() const { return _quadsCount; }
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    inline BlendFunc getBlendType() const { return _blendType; }
    inline const Mat4& getModelView() const { return _mv; }
    

protected:
    void generateMaterialID();

    uint32_t _materialID;
    GLuint _textureID;
    GLProgramState* _glProgramState;
    BlendFunc _blendType;
    V3F_C4B_T2F_Quad* _quads;
    ssize_t _quadsCount;
    Mat4 _mv;
};
NS_CC_END

#endif //_CC_QUADCOMMAND_H_
