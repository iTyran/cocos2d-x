/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Leonardo Kasperavičius
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
#ifndef __CC_PARTICLE_SYSTEM_QUAD_H__
#define __CC_PARTICLE_SYSTEM_QUAD_H__

#include  "CCParticleSystem.h"
#include "renderer/CCQuadCommand.h"

NS_CC_BEGIN

class SpriteFrame;
class EventCustom;

/**
 * @addtogroup particle_nodes
 * @{
 */

/** @brief ParticleSystemQuad 是 ParticleSystem 的子类

它包含ParticleSystem的所有特性

额外的特性和局限:    
- 粒子大小可以是任意浮点数
- 系统可缩放
- 粒子可旋转
- 支持子区域
- 支持批量渲染 （从1.1开始）
@since v0.8
*/
class CC_DLL ParticleSystemQuad : public ParticleSystem
{
public:

    /** 创建粒子发生器 */
    static ParticleSystemQuad * create();
    /** 创建一定数量粒子的发生器 */
    static ParticleSystemQuad * createWithTotalParticles(int numberOfParticles);
    /** 从plist创建粒子发生器
     */
    static ParticleSystemQuad * create(const std::string& filename);
    /** 从字典创建粒子发生器 */
    static ParticleSystemQuad * create(ValueMap &dictionary);

    /** 为粒子设置一个新的帧.
    WARNING: 实验接口。用setTextureWithRect代替。
    @since v0.99.4
    */
    void setDisplayFrame(SpriteFrame *spriteFrame);

    /** 设置新的纹理和区域
     @since v0.99.4
     * @js NA
     * @lua NA
     */
    void setTextureWithRect(Texture2D *texture, const Rect& rect);

    /** 监听Android从后台切换到前台的事件
     * @js NA
     * @lua NA
     */
    void listenBackToForeground(EventCustom* event);

    /**
     * @js NA
     * @lua NA
     */
    virtual void setTexture(Texture2D* texture) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void updateQuadWithParticle(tParticle* particle, const Vec2& newPosition) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void postStep() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

    /**
     * @js NA
     * @lua NA
     */
    virtual void setBatchNode(ParticleBatchNode* batchNode) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void setTotalParticles(int tp) override;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleSystemQuad();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSystemQuad();
    
    // Overrides
    /**
     * @js NA
     * @lua NA
     */
    virtual bool initWithTotalParticles(int numberOfParticles) override;

protected:
    /** 初始化顶点数组*/
    void initIndices();
    
    /** 初始化纹理区域 */
    void initTexCoordsWithRect(const Rect& rect);
    
    /** 更新纹理坐标 */
    void updateTexCoords();

    void setupVBOandVAO();
    void setupVBO();
    bool allocMemory();

    V3F_C4B_T2F_Quad    *_quads;        // quads to be rendered
    GLushort            *_indices;      // indices
    GLuint              _VAOname;
    GLuint              _buffersVBO[2]; //0: vertex  1: indices

    QuadCommand _quadCommand;           // quad command

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSystemQuad);
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif //__CC_PARTICLE_SYSTEM_QUAD_H__

