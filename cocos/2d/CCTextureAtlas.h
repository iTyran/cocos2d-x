/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
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

#ifndef __CCTEXTURE_ATLAS_H__
#define __CCTEXTURE_ATLAS_H__

#include "base/ccTypes.h"
#include "base/CCRef.h"
#include "base/ccConfig.h"
#include <string>

NS_CC_BEGIN

class Texture2D;
class EventCustom;
class EventListenerCustom;

/**
 * @addtogroup textures
 * @{
 */


/** @brief 代表纹理图块的一个类.
 支持特性:
 * 贴图集文件可以是PVRTC、PNG或者其他支持Texture2D的格式
 * 方块可以在运行时更新
 * 方块可以在运行时增加
 * 方块可以在运行时移除
 * 方块可以在运行时重新排序
 * 纹理贴图集容量可以在运行时增加或减少
 * OpenGL的组成: V3F, C4B, T2F
 方块使用OpenGL ES VBO来渲染
 为了使用隔行扫描顶点数组列表来渲染方块，你应该修改ccConfig.h文件
 
 @warning 如果你想使用TextureAtlas，你最好设置总帐状态之前，它的呈现。
          否则，TextureAtlas的效果会受到其他节点的GL状态。
 */

class CC_DLL TextureAtlas : public Ref 
{
public:
    
    /** 用一个文件名和方块初始容量创建纹理贴图集
     * 纹理贴图集容量可以在运行时增加
     */
    static TextureAtlas* create(const std::string& file , ssize_t capacity);

    /** 用一个事先初始化的Texture2D对象创建纹理贴图集，并为n个方块初始化容量
     * 纹理贴图集容量可以在运行时增加
     */
    static TextureAtlas* createWithTexture(Texture2D *texture, ssize_t capacity);
    /**
     * @js ctor
     */
    TextureAtlas();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TextureAtlas();

    /** 用一个文件名和确定的方块容量初始化纹理贴图集
     * 纹理贴图集容量可以在运行时增加
     * 警告：不要重置纹理贴图集因为它会内存泄露（问题 #706）
     */
    bool initWithFile(const std::string& file, ssize_t capacity);

    /** 用一个事先初始化的Texture2D对象初始化纹理贴图集，并为方块初始化容量
     * 纹理贴图集的容量可以在运行时增加
     * 警告：不要重置纹理贴图集因为它会内存泄露（问题 #706）
     */
    bool initWithTexture(Texture2D *texture, ssize_t capacity);

    /** 在一个确定的索引里更新方块（纹理、顶点和颜色）
     * 索引必须在 0 ~ 贴图集容量-1 之间
     @since v0.8
     */
    void updateQuad(V3F_C4B_T2F_Quad* quad, ssize_t index);

    /** 在一个确定的索引里插入方块（纹理、顶点和颜色）
     * 索引必须在 0 ~ 贴图集容量-1 之间
     @since v0.8
     */
    void insertQuad(V3F_C4B_T2F_Quad* quad, ssize_t index);

    /** 在一个特定的索引里为方块插入C数组
     * 索引必须在 0 ~ 贴图集容量-1 之间
     * 当 数量 + 索引 > 全部方块 时，这个方法不能扩充数组
     @since v1.1
     */
    void insertQuads(V3F_C4B_T2F_Quad* quads, ssize_t index, ssize_t amount);

    /** 在一个确定的索引里移除方块，并插入到一个新索引
     * 这个操作比在2个不同步骤里移除和插入方块更快
     @since v0.7.2
     */
    void insertQuadFromIndex(ssize_t fromIndex, ssize_t newIndex);

    /** 在一个特定索引数字里移除方块
     * 相同的剩余容量，但渲染的方块总数会减1
     @since v0.7.2
     */
    void removeQuadAtIndex(ssize_t index);

    /** 开始从索引里移除一个方块数量
     @since 1.1
     */
    void removeQuadsAtIndex(ssize_t index, ssize_t amount);
    /** 移除所有方块
     * 剩余的纹理贴图集容量未受影响，没有内存被释放
     * 渲染的方块总数将会变成0
     @since v0.7.2
     */
    void removeAllQuads();

    /** 调整CCTextureAtlas容量的大小
     * 新的容量可以比当前的更低或更高
     * 如果调整大小成功，返回YES
     * 如果调整大小失败，返回NO，新的容量为0
     */
    bool resizeCapacity(ssize_t capacity);

    /** 通过CCParticleBatchNode内部使用
     * 除非你知道自己在做什么，否则不要使用这个方法
     @since 1.1
     */
    void increaseTotalQuadsWith(ssize_t amount);

    /** 从旧索引移动一个方块数量到新索引
     @since v1.1
     */
    void moveQuadsFromIndex(ssize_t oldIndex, ssize_t amount, ssize_t newIndex);

    /** 从索引移动所有方块到新索引
     * 通过CCParticleBatchNode内部使用
     * 如果 新索引+方块 使 移动量>容量 ，这个方法不会扩充数组
     @since 1.1
     */
    void moveQuadsFromIndex(ssize_t index, ssize_t newIndex);

    /** 确保realloc后的方块仍然为空
     * 通过CCParticleBatchNode内部使用
     @since 1.1
     */
    void fillWithEmptyQuadsFromIndex(ssize_t index, ssize_t amount);

    /** 绘制n个方块
     * n不能大于贴图集容量
     */
    void drawNumberOfQuads(ssize_t n);

    /** 从一个索引（偏移量）绘制n个方块
     * n+开始不能大于贴图集容量
     @since v1.0
     */
    void drawNumberOfQuads(ssize_t numberOfQuads, ssize_t start);

    /** 绘制所有的贴图集方块 */
    void drawQuads();
    /** 监听来到安卓前台的事件 */
    void listenBackToForeground(EventCustom* event);

    /** VOB数组缓冲区是否需要更新 */
    inline bool isDirty(void) { return _dirty; }
    /** 指定的VBO数组缓冲区是否需要更新 */
    inline void setDirty(bool bDirty) { _dirty = bDirty; }
    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /** Gets将被绘制的方块数量 */
    ssize_t getTotalQuads() const;
    
    /** Gets 可以存储当前纹理贴图集尺寸的方块数量 */
    ssize_t getCapacity() const;
    
    /** Gets 纹理贴图集的纹理 */
    Texture2D* getTexture() const;
    
    /** Sets 纹理贴图集的纹理 */
    void setTexture(Texture2D* texture);
    
    /** Gets将被渲染的方块 */
    V3F_C4B_T2F_Quad* getQuads();
    
    /** Sets 将被渲染的方块 */
    void setQuads(V3F_C4B_T2F_Quad* quads);
    
private:
    void renderCommand();

    void setupIndices();
    void mapBuffers();
    void setupVBOandVAO();
    void setupVBO();

protected:
    GLushort*           _indices;
    GLuint              _VAOname;
    GLuint              _buffersVBO[2];  // 0: 顶点  1: 索引
    bool                _dirty; // 指出VBO数组缓冲区是否需要更新
    /** 将被绘制的方块数量 */
    ssize_t _totalQuads;
    /** 可以存储当前纹理贴图集尺寸的方块数量 */
    ssize_t _capacity;
    /** 纹理贴图集的纹理 */
    Texture2D* _texture;
    /** 将被渲染的方块 */
    V3F_C4B_T2F_Quad* _quads;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _backToForegroundlistener;
#endif
};

// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE_ATLAS_H__


