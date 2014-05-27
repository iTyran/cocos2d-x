/*
 * Copyright (C) 2009 Matt Oswald
 * Copyright (c) 2009-2010 Ricardo Quesada
 * Copyright (c) 2010-2012 cocos2d-x.org
 * Copyright (c) 2011      Zynga Inc.
 * Copyright (c) 2011      Marco Tillemans
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * http://www.cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#ifndef __CCPARTICLEBATCHNODE_H__
#define __CCPARTICLEBATCHNODE_H__

#include "2d/CCNode.h"
#include "2d/CCProtocols.h"
#include "renderer/CCBatchCommand.h"

NS_CC_BEGIN

class Texture2D;
class TextureAtlas;
class ParticleSystem;

/**
 * @addtogroup particle_nodes
 * @{
 */

#define kParticleDefaultCapacity 500

/** ParticleBatchNode是一个批处理节点: 如果它包含很多子节点, 它将只调用1次OpenGL把它们全部绘制出来.
 * (就是大家熟知的“批处理绘制”).
 *
 * 一个ParticleBatchNode只能引用一个纹理(一个图像文件或者一个纹理贴图集).
 * 只有ParticleSystems包含在那个纹理中才能被添加到SpriteBatchNode.
 * 所有添加到SpriteBatchNode中的ParticleSystems将通过一个OpenGL ES绘制调用来绘制.
 * 如果ParticleSystems没有被添加到某个ParticleBatchNode中，那么每绘制一个ParticleSystem都将需要一次OpenGL ES绘制调用,这会导致效率降低.
 *
 *
 * 限制:
 * - 目前只支持ParticleSystemQuad
 * - 所有系统必须在相同的参数、混合方式、别名和纹理下绘制
 *
 * 最高效的用法
 * - 使用纹理来初始化ParticleBatchNode，并且确保所有的粒子系统有足够的容量
 * - 初始化所有粒子系统，然后把它们作为子节点添加到批处理节点中。
 * @since v1.1
 */

class CC_DLL ParticleBatchNode : public Node, public TextureProtocol
{
public:
    /** 初始化粒子系统的批处理结点，参数一为对应的纹理，参数二为创建批处理结点所能容纳的最大粒子数量 */
    static ParticleBatchNode* createWithTexture(Texture2D *tex, int capacity = kParticleDefaultCapacity);

    /** 初始化粒子系统的批处理结点，参数一为保存到磁盘上的图片文件名(Texture2D类中列出了支持的格式)，参数二为创建批处理结点所能容纳的最大粒子数量 */
    static ParticleBatchNode* create(const std::string& fileImage, int capacity = kParticleDefaultCapacity);

    /** 将一个粒子系统按照指定的索引位置做为子结点加入批处理结点 */
    void insertChild(ParticleSystem* system, int index);

    void removeChildAtIndex(int index, bool doCleanup);
    void removeAllChildrenWithCleanup(bool doCleanup);

    /** 设置对应索引的粒子失效不显示 */
    void disableParticle(int particleIndex);

    /** 获取用来绘制矩形区域的纹理 */
    inline TextureAtlas* getTextureAtlas() const { return _textureAtlas; };
    
    /** 设置用来绘制矩形区域的纹理 */
    inline void setTextureAtlas(TextureAtlas* atlas) { _textureAtlas = atlas; };
    
    // Overrides
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;

    using Node::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void removeChild(Node* child, bool cleanup) override;
    virtual void reorderChild(Node * child, int zOrder) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    virtual Texture2D* getTexture(void) const override;
    virtual void setTexture(Texture2D *texture) override;
    /**
    * @code
    * 在js或者lua下使用这个函数,需要改变传递的参数
    * In js: var setBlendFunc(var src, var dst)
    * @endcode
    * @lua NA
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc(void) const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleBatchNode();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleBatchNode();
    
    /** 初始化粒子系统，参数一为对应的二维纹理，参数二为粒子系统所能容纳的最大粒子数量 */
    bool initWithTexture(Texture2D *tex, int capacity);
    
    /**  初始化粒子系统，参数一为保存到磁盘上的图片文件名(Texture2D类中列出了支持的格式)，参数二为粒子系统所能容纳的最大粒子数量 */
    bool initWithFile(const std::string& fileImage, int capacity);
    
private:
    void updateAllAtlasIndexes();
    void increaseAtlasCapacityTo(ssize_t quantity);
    int searchNewPositionInChildrenForZ(int z);
    void getCurrentIndex(int* oldIndex, int* newIndex, Node* child, int z);
    int addChildHelper(ParticleSystem* child, int z, int aTag);
    void updateBlendFunc(void);
    /** 用来绘制矩形区域的纹理 */
    TextureAtlas* _textureAtlas;

    /** 用来绘制矩形区域的混合方式 */
    BlendFunc _blendFunc;
    // 矩阵命令
    BatchCommand _batchCommand;
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif /* __CCPARTICLEBATCHNODE_H__ */

