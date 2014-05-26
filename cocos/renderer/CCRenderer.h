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


#ifndef __CC_RENDERER_H_
#define __CC_RENDERER_H_

#include "base/CCPlatformMacros.h"
#include "CCRenderCommand.h"
#include "renderer/CCGLProgram.h"
#include "CCGL.h"
#include <vector>
#include <stack>

NS_CC_BEGIN

class EventListenerCustom;
class QuadCommand;

/** 该类知道如何排序 `RenderCommand` 对象.
 `z == 0`的命令被压人正确的位置，只有`z < 0` 和 `z > 0`的`RenderCommand`对象需要排序.
*/
class RenderQueue {

public:
    void push_back(RenderCommand* command);
    ssize_t size() const;
    void sort();
    RenderCommand* operator[](ssize_t index) const;
    void clear();

protected:
    std::vector<RenderCommand*> _queueNegZ;
    std::vector<RenderCommand*> _queue0;
    std::vector<RenderCommand*> _queuePosZ;
};

struct RenderStackElement
{
    int renderQueueID;
    ssize_t currentIndex;
};

class GroupCommandManager;

/* 该类负责渲染.

 尽可能选择使用“QuadCommand”对象,因为自渲染器会自动批处理.
 */
class Renderer
{
public:
    static const int VBO_SIZE = 65536 / 6;
    static const int BATCH_QUADCOMMAND_RESEVER_SIZE = 64;

    Renderer();
    ~Renderer();

    //TODO 管理渲染器(Render)自己内部的GLView
    void initGLView();

    /** 加入一条 `RenderComamnd`命令到渲染器(renderer) */
    void addCommand(RenderCommand* command);

    /** 加入一条渲染指令`RenderComamnd`到渲染器(renderer),并指定特定的渲染顺序ID */
    void addCommand(RenderCommand* command, int renderQueue);

    /**压入一组到渲染队列 */
    void pushGroup(int renderQueueID);

    /** 从渲染队列中弹出一组 */
    void popGroup();

    /** 创建一组渲染队列并返回Id */
    int createRenderQueue();

    /** 渲染所有加入到GLView中的`RenderCommand`队列对象 */
    void render();

    /** 清除队列中的渲染指令(`RenderCommand`) */
    void clean();

    /* 返回最后一帧批绘制的数量 */
    ssize_t getDrawnBatches() const { return _drawnBatches; }
    /* 渲染指令（RenderCommands） (除了) QuadCommand 应该更新该值 */
    void addDrawnBatches(ssize_t number) { _drawnBatches += number; };
    /* 返回最后一帧画三角形(triangles)的数量 */
    ssize_t getDrawnVertices() const { return _drawnVertices; }
    /* 渲染指令（RenderCommands） (除了) QuadCommand 应该更新该值 */
    void addDrawnVertices(ssize_t number) { _drawnVertices += number; };

    inline GroupCommandManager* getGroupCommandManager() const { return _groupCommandManager; };

    /** 返回矩形区域是否可见 */
    bool checkVisibility(const Mat4& transform, const Size& size);

protected:

    void setupIndices();
    //基于OpenGL扩展建立 VBO or VAO
    void setupBuffer();
    void setupVBOAndVAO();
    void setupVBO();
    void mapBuffers();

    void drawBatchedQuads();

    //绘制以前的队列quads和刷新以前的内容
    void flush();
    
    void visitRenderQueue(const RenderQueue& queue);

    void convertToWorldCoordinates(V3F_C4B_T2F_Quad* quads, ssize_t quantity, const Mat4& modelView);

    std::stack<int> _commandGroupStack;
    
    std::vector<RenderQueue> _renderGroups;

    uint32_t _lastMaterialID;

    std::vector<QuadCommand*> _batchedQuadCommands;

    V3F_C4B_T2F_Quad _quads[VBO_SIZE];
    GLushort _indices[6 * VBO_SIZE];
    GLuint _quadVAO;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

    int _numQuads;
    
    bool _glViewAssigned;

    // stats
    ssize_t _drawnBatches;
    ssize_t _drawnVertices;
    //标记当前是否在渲染中
    bool _isRendering;
    
    GroupCommandManager* _groupCommandManager;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _cacheTextureListener;
#endif
};

NS_CC_END

#endif //__CC_RENDERER_H_
