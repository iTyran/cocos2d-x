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
#ifndef __CCPARTICLE_SYSTEM_H__
#define __CCPARTICLE_SYSTEM_H__

#include "2d/CCProtocols.h"
#include "2d/CCNode.h"
#include "base/CCValue.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN

/**
 * @addtogroup particle_nodes
 * @{
 */

class ParticleBatchNode;

/**
粒子数据结构
*/
typedef struct sParticle {
    Vec2     pos;
    Vec2     startPos;

    Color4F    color;
    Color4F    deltaColor;

    float        size;
    float        deltaSize;

    float        rotation;
    float        deltaRotation;

    float        timeToLive;

    unsigned int    atlasIndex;

    //! 模式 A: 引力, 方向, 径向加速度, 切向加速度
    struct {
        Vec2        dir;
        float        radialAccel;
        float        tangentialAccel;
    } modeA;

    //! 模式 B: 半径模式
    struct {
        float        angle;
        float        degreesPerSecond;
        float        radius;
        float        deltaRadius;
    } modeB;

}tParticle;

//typedef void (*CC_UPDATE_PARTICLE_IMP)(id, SEL, tParticle*, Vec2);

class Texture2D;

/** @brief 粒子系统基类
粒子系统属性：
- 粒子排放速率
- 引力模式 (Mode A):
- 引力
- 方向
- 速度 +- 范围
- 切向加速度 +- 范围
- 径向加速度 +- 范围
- 半径模式 (Mode B):
- 开始半径 +- 范围
- 结束半径 +- 范围
- 旋转 +- 范围
- 所有模式公用属性:
- 生命 +- 生命范围
- 开始旋角 +- 范围
- 结束旋角 +- 范围
- 开始大小 +- 范围
- 结束大小 +- 范围
- 开始颜色 +- 范围
- 结束颜色 +- 范围
- 生命 +- 范围
- 绑定函数
- 纹理

Cocos2d-x支持由Particle Designer (http://particledesigner.71squared.com/)生成的粒子.
Particle Designer中的'Radius Mode'的发射速率被固定在30 hz，因为它在Cocos2d-x中不能被保障。
Cocos2d-x使用另一种方式，但是结果是一致的。

Cocos2d-x支持所有Particle Designer变量，并支持:
- 纺织粒子 (ParticleSystemQuad使用)
- 切向加速度 (引力模式)
- 径向加速度 (引力模式)
- 半径方向 (半径模式) (Particle Designer只支持由外向内的方向)

你可以在运行时修改所有以上提到的属性。例如：

@code
emitter.radialAccel = 15;
emitter.startSpin = 0;
@endcode

*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef RELATIVE
#undef RELATIVE
#endif
#endif

class CC_DLL ParticleSystem : public Node, public TextureProtocol
{
public:
    enum class Mode
    {
        GRAVITY,
        RADIUS,
    };
    
    /** @typedef PositionType
     粒子可能的位置类型
     */
    enum class PositionType
    {
        /** 粒子添加到世界后，不会受到发射定位的影响 */
        FREE,
        
        /** 粒子添加到世界后，受到发射定位的影响
         用例: 添加一个发射器到一个精灵，并让发射器随精灵的移动而移动。
         */
        RELATIVE,
        
        /** 粒子附着在发生器上并随它一起移动 */
        GROUPED,
    };
    
    //* @enum
    enum {
        /** 粒子发生器一直存在 */
        DURATION_INFINITY = -1,
        
        /** 开始大小和结束大小相等 */
        START_SIZE_EQUAL_TO_END_SIZE = -1,
        
        /** 开始半径和结束半径相等 */
        START_RADIUS_EQUAL_TO_END_RADIUS = -1,
    };
    
    /** 从plist创建并初始化一个粒子系统
    plist可以手动创建或从Particle Designer创建:
    http://particledesigner.71squared.com/
    @since v2.0
    */
    static ParticleSystem * create(const std::string& plistFile);

    //! 创建固定数量的粒子系统
    static ParticleSystem* createWithTotalParticles(int numberOfParticles);

    //! 添加一个粒子到发射器
    bool addParticle();
    //! 初始化一个粒子
    void initParticle(tParticle* particle);
    //! 停止发射粒子
    void stopSystem();
    //! 停止所有活着的粒子
    void resetSystem();
    //! 系统是否满了
    bool isFull();

    //! 必须被子类重写
    virtual void updateQuadWithParticle(tParticle* particle, const Vec2& newPosition);
    //! 必须被子类重写
    virtual void postStep();

    virtual void updateWithNoTime(void);

    virtual bool isAutoRemoveOnFinish() const;
    virtual void setAutoRemoveOnFinish(bool var);

    // 模式 A
    virtual const Vec2& getGravity();
    virtual void setGravity(const Vec2& g);
    virtual float getSpeed() const;
    virtual void setSpeed(float speed);
    virtual float getSpeedVar() const;
    virtual void setSpeedVar(float speed);
    virtual float getTangentialAccel() const;
    virtual void setTangentialAccel(float t);
    virtual float getTangentialAccelVar() const;
    virtual void setTangentialAccelVar(float t);
    virtual float getRadialAccel() const;
    virtual void setRadialAccel(float t);
    virtual float getRadialAccelVar() const;
    virtual void setRadialAccelVar(float t);
    virtual bool getRotationIsDir() const;
    virtual void setRotationIsDir(bool t);
    // 模式 B
    virtual float getStartRadius() const;
    virtual void setStartRadius(float startRadius);
    virtual float getStartRadiusVar() const;
    virtual void setStartRadiusVar(float startRadiusVar);
    virtual float getEndRadius() const;
    virtual void setEndRadius(float endRadius);
    virtual float getEndRadiusVar() const;
    virtual void setEndRadiusVar(float endRadiusVar);
    virtual float getRotatePerSecond() const;
    virtual void setRotatePerSecond(float degrees);
    virtual float getRotatePerSecondVar() const;
    virtual void setRotatePerSecondVar(float degrees);

    virtual void setScale(float s);
    virtual void setRotation(float newRotation);
    virtual void setScaleX(float newScaleX);
    virtual void setScaleY(float newScaleY);

    virtual bool isActive() const;
    virtual bool isBlendAdditive() const;
    virtual void setBlendAdditive(bool value);

    virtual ParticleBatchNode* getBatchNode() const;
    virtual void setBatchNode(ParticleBatchNode* batchNode);
    
    // index of system in batch node array
    inline int getAtlasIndex() const { return _atlasIndex; };
    inline void setAtlasIndex(int index) { _atlasIndex = index; };

    /** 当前粒子数量 */
    inline unsigned int getParticleCount() const { return _particleCount; };
    
    /** 发射器运行多少时间。 -1表示永远 */
    inline float getDuration() const { return _duration; };
    inline void setDuration(float duration) { _duration = duration; };
    
    /** 发射器原坐标 */
    inline const Vec2& getSourcePosition() const { return _sourcePosition; };
    inline void setSourcePosition(const Vec2& pos) { _sourcePosition = pos; };
    
    /** 发射器坐标变化区间 */
    inline const Vec2& getPosVar() const { return _posVar; };
    inline void setPosVar(const Vec2& pos) { _posVar = pos; };

    /** 生命周期 */
    inline float getLife() const { return _life; };
    inline void setLife(float life) { _life = life; };

    /** 生命变化区间 */
    inline float getLifeVar() const { return _lifeVar; };
    inline void setLifeVar(float lifeVar) { _lifeVar = lifeVar; };

    /** 角度 */
    inline float getAngle() const { return _angle; };
    inline void setAngle(float angle) { _angle = angle; };

    /** 角度变化区间 */
    inline float getAngleVar() const { return _angleVar; };
    inline void setAngleVar(float angleVar) { _angleVar = angleVar; };
    
    /** 在不同的发射器模式之间切换:
     - kParticleModeGravity: 引力模式
     - kParticleModeRadius: 半径模式
     */
    inline Mode getEmitterMode() const { return _emitterMode; };
    inline void setEmitterMode(Mode mode) { _emitterMode = mode; };
    
    /** 粒子开始像素 */
    inline float getStartSize() const { return _startSize; };
    inline void setStartSize(float startSize) { _startSize = startSize; };

    /** 粒子开始像素变化区间 */
    inline float getStartSizeVar() const { return _startSizeVar; };
    inline void setStartSizeVar(float sizeVar) { _startSizeVar = sizeVar; };

    /** 粒子结束像素 */
    inline float getEndSize() const { return _endSize; };
    inline void setEndSize(float endSize) { _endSize = endSize; };

    /** 粒子结束像素变化区间 */
    inline float getEndSizeVar() const { return _endSizeVar; };
    inline void setEndSizeVar(float sizeVar) { _endSizeVar = sizeVar; };

    /** 粒子开始颜色 */
    inline const Color4F& getStartColor() const { return _startColor; };
    inline void setStartColor(const Color4F& color) { _startColor = color; };

    /** 粒子开始颜色变化区间 */
    inline const Color4F& getStartColorVar() const { return _startColorVar; };
    inline void setStartColorVar(const Color4F& color) { _startColorVar = color; };

    /** 粒子结束颜色 */
    inline const Color4F& getEndColor() const { return _endColor; };
    inline void setEndColor(const Color4F& color) { _endColor = color; };

    /** 粒子结束颜色变化区间 */
    inline const Color4F& getEndColorVar() const { return _endColorVar; };
    inline void setEndColorVar(const Color4F& color) { _endColorVar = color; };

    //* 粒子开始角度
    inline float getStartSpin() const { return _startSpin; };
    inline void setStartSpin(float spin) { _startSpin = spin; };

    //* 粒子开始角度变化区间
    inline float getStartSpinVar() const { return _startSpinVar; };
    inline void setStartSpinVar(float pinVar) { _startSpinVar = pinVar; };

    //* 粒子结束角度
    inline float getEndSpin() const { return _endSpin; };
    inline void setEndSpin(float endSpin) { _endSpin = endSpin; };

    //* 粒子结束角度变化区间
    inline float getEndSpinVar() const { return _endSpinVar; };
    inline void setEndSpinVar(float endSpinVar) { _endSpinVar = endSpinVar; };

    /** 粒子发射速率 */
    inline float getEmissionRate() const { return _emissionRate; };
    inline void setEmissionRate(float rate) { _emissionRate = rate; };

    /** 最大粒子数量 */
    virtual int getTotalParticles() const;
    virtual void setTotalParticles(int totalParticles);

    /** alpha是否修改颜色值 */
    inline void setOpacityModifyRGB(bool opacityModifyRGB) { _opacityModifyRGB = opacityModifyRGB; };
    inline bool isOpacityModifyRGB() const { return _opacityModifyRGB; };
    CC_DEPRECATED_ATTRIBUTE inline bool getOpacityModifyRGB() const { return isOpacityModifyRGB(); }
    
    /** 粒子移动类型: Free 或 Grouped
     @since v0.8
     */
    inline PositionType getPositionType() const { return _positionType; };
    inline void setPositionType(PositionType type) { _positionType = type; };
    
    // Overrides
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float dt) override;
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    /**
    *@code
    *当这个函数绑定到js或lub，参数会变化。
    *js中: var setBlendFunc(var src, var dst)
    *lua中: local setBlendFunc(local src, local dst)
    *@endcode
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc &getBlendFunc() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ParticleSystem();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSystem();

    /** 初始化粒子系统 */
    bool init();
    /** 从plist文件初始化粒子系统
     plist可以手动创建，也可以用Particle Designer:
     http://particledesigner.71squared.com/
     @since v0.99.3
     */
    bool initWithFile(const std::string& plistFile);
    
    /** 从字典初始化粒子系统
     @since v0.99.3
     */
    bool initWithDictionary(ValueMap& dictionary);
    
    /** 从字典初始化粒子系统，字典文件路径在dirname
     @since v2.1
     */
    bool initWithDictionary(ValueMap& dictionary, const std::string& dirname);
    
    //! 初始化一个固定数量的粒子系统。
    virtual bool initWithTotalParticles(int numberOfParticles);

protected:
    virtual void updateBlendFunc();

    /** 是否粒子被混合
     如何是下面的代码将被调用
     @code
     source blend function = GL_SRC_ALPHA;
     dest blend function = GL_ONE;
     @endcode
     */
    bool _isBlendAdditive;

    /** 粒子发生器是否在生命结束的时候自动移除
     By default it is false.
     @since v0.8
     */
    bool _isAutoRemoveOnFinish;

    std::string _plistFile;
    //! 消逝时间(秒)
    float _elapsed;

    // 不同的模式
    //! 模式A:引力 + 切向加速度 + 径向加速度
    struct {
        /** 引力值 */
        Vec2 gravity;
        /** 每个粒子的速度 */
        float speed;
        /** 速度变化区间 */
        float speedVar;
        /** 切向加速度 */
        float tangentialAccel;
        /** 切向加速度变化区间 */
        float tangentialAccelVar;
        /** 径向加速度 */
        float radialAccel;
        /** 径向加速度变化区间 */
        float radialAccelVar;
        /** 是否旋转 */
        bool rotationIsDir;
    } modeA;

    //! 模式
    struct {
        /** 初始半径 */
        float startRadius;
        /** 初始半径变化区间 */
        float startRadiusVar;
        /** 结束半径 */
        float endRadius;
        /** 结束半径变化区间 */
        float endRadiusVar;
        /** 每秒旋转的角度 */
        float rotatePerSecond;
        /** 每秒旋转的角度变化区间 */
        float rotatePerSecondVar;
    } modeB;

    //! 粒子数组
    tParticle *_particles;

    //Emitter name
    std::string _configName;

    // color modulate
    //    BOOL colorModulate;

    //! 每秒发射的粒子数量
    float _emitCounter;

    //!  粒子idx值
    int _particleIdx;

    // Optimization
    //CC_UPDATE_PARTICLE_IMP    updateParticleImp;
    //SEL                        updateParticleSel;

    /** 弱引用渲染精灵的SpriteBatchNode */
    ParticleBatchNode* _batchNode;

    // index of system in batch node array
    int _atlasIndex;

    //true if scaled or rotated
    bool _transformSystemDirty;
    // Number of allocated particles
    int _allocatedParticles;

    /** 是否发射器激活 */
    bool _isActive;
    
    /** 当前的粒子数量 */
    int _particleCount;
    /** 发射器运行多少时间。 -1 永远 */
    float _duration;
    /** 发射器原位置 */
    Vec2 _sourcePosition;
    /** 发射器位置变化范围 */
    Vec2 _posVar;
    /** 粒子生命 */
    float _life;
    /** 粒子生命变化区间 */
    float _lifeVar;
    /** 粒子角度 */
    float _angle;
    /** 粒子角度变化区间 */
    float _angleVar;

    /** 发射器不同模式:
     - kParticleModeGravity: 引力模式
     - kParticleModeRadius: 半径模式
     */
    Mode _emitterMode;

    /** 开始大小 */
    float _startSize;
    /** 开始大小变化区间 */
    float _startSizeVar;
    /** 结束大小 */
    float _endSize;
    /** 结束大小变化区间 */
    float _endSizeVar;
    /** 开始颜色 */
    Color4F _startColor;
    /** 开始颜色变化区间 */
    Color4F _startColorVar;
    /** 结束颜色 */
    Color4F _endColor;
    /** 结束颜色变化区间 */
    Color4F _endColorVar;
    //* 初始角度
    float _startSpin;
    //* 初始角度变化
    float _startSpinVar;
    //* 结束角度
    float _endSpin;
    //* 结束角度变化
    float _endSpinVar;
    /** 发射频率 */
    float _emissionRate;
    /** 最大粒子数 */
    int _totalParticles;
    /** 纹理 */
    Texture2D* _texture;
    /** blend协议函数 */
    BlendFunc _blendFunc;
    /** alpha是否改变RGB值 */
    bool _opacityModifyRGB;
    /** FlippedY是否影响所有粒子 */
    int _yCoordFlipped;


    /** 粒子移动类型: Free 或 Grouped
     @since v0.8
     */
    PositionType _positionType;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSystem);
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif //__CCPARTICLE_SYSTEM_H__
