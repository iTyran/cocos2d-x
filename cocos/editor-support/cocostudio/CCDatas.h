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

#ifndef __CCARMATURE_DATAS_H__
#define __CCARMATURE_DATAS_H__

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCVector.h"
#include "base/CCMap.h"
#include "math/CCAffineTransform.h"

#include "cocostudio/CCArmatureDefine.h"
#include "2d/CCTweenFunction.h"


#define CC_CREATE_NO_PARAM_NO_INIT(varType)\
public: \
	static inline varType *create(void){ \
	varType *var = new varType();\
	if (var)\
{\
	var->autorelease();\
	return var;\
}\
	CC_SAFE_DELETE(var);\
	return nullptr;\
}

#define CC_CREATE_NO_PARAM(varType)\
public: \
	static inline varType *create(void){ \
	varType *var = new varType();\
	if (var && var->init())\
{\
	var->autorelease();\
	return var;\
}\
	CC_SAFE_DELETE(var);\
	return nullptr;\
}

namespace cocostudio {

/**
 * 包含大量属性的基础节点
 * @js NA
 * @lua NA
 */
class  BaseData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(BaseData)
public:
	/**
     * @js ctor
     */
    BaseData();
    /**
     * @js NA
     * @lua NA
     */
    ~BaseData(void);

    /*
    * 从node中拷贝数据
    * @param  node 要拷贝的对象
    */
    virtual void copy(const BaseData *node);

    /*
    * 计算两个BaseData之间的值，并赋给自己
    *
    * @param  from   from BaseData
    * @param  to     to BaseData
    */
    virtual void subtract(BaseData *from, BaseData *to, bool limit);

    virtual void setColor(const cocos2d::Color4B &color);
    virtual cocos2d::Color4B getColor();
public:
    float x;					//! x坐标属性
    float y;					//! y坐标属性
    int zOrder;			//! zorder属性，用于定义节点的Z顺序

    /**
    * x y skewX skewY scaleX scaleY 用来定义移动矩阵
    * skewX, skewY 影响旋转因子
    * 想要获取更多的矩阵信息, 参考 : http://www.senocular.com/flash/tutorials/transformmatrix/
    */
    float skewX;
    float skewY;
    float scaleX;
    float scaleY;

    float tweenRotate;       //! SkewX, SkewY, TweenRotate 影响旋转

    bool isUseColorInfo;    //! 该帧是否具有颜色改变信息
    int a, r, g, b;

};


/**
* DisplayType 使用的现实类型
*/
enum DisplayType
{
    CS_DISPLAY_SPRITE,                //! 显示为单独的精灵
    CS_DISPLAY_ARMATURE,         //! 显示为骨骼动画
    CS_DISPLAY_PARTICLE,            //! 现实为粒子效果

    CS_DISPLAY_MAX
};
/**
 *  @js NA
 *  @lua NA
 */
class  DisplayData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(DisplayData)

    static const std::string changeDisplayToTexture(const std::string& displayName);
public:
	/**
     * @js ctor
     */
    DisplayData();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~DisplayData(void) {}

    virtual void copy(DisplayData *displayData);

    DisplayType displayType;	//! 标记使用的显示类型
    std::string displayName;
};


/**
 *  @js NA
 *  @lua NA
 */
class  SpriteDisplayData : public DisplayData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(SpriteDisplayData)
public:
	/**
     * @js ctor
     */
    SpriteDisplayData();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SpriteDisplayData() {};

    void copy(DisplayData *displayData);
public:
    BaseData skinData;
};

/**
 *  @js NA
 *  @lua NA
 */
class  ArmatureDisplayData  : public DisplayData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(ArmatureDisplayData)
public:
	/**
     * @js ctor
     */
    ArmatureDisplayData();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ArmatureDisplayData() {}
};

/**
 *  @js NA
 *  @lua NA
 */
class  ParticleDisplayData : public DisplayData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(ParticleDisplayData)
public:
	/**
     * @js ctor
     */
    ParticleDisplayData();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleDisplayData() {};
};



/**
* BoneData用于初始化骨骼
* BoneData用于保存一系列的显示数据，一个骨骼可以包含很多可以改变的现实信息
* 显示信息保存在DsiplayData中
* @js NA
* @lua NA
*/
class  BoneData : public BaseData
{
public:
    CC_CREATE_NO_PARAM(BoneData)
public:
	/**
     * @js ctor
     */
    BoneData(void);
    /**
     * @js NA
     * @lua NA
     */
    ~BoneData(void);

    virtual bool init();

    void addDisplayData(DisplayData *displayData);
    DisplayData *getDisplayData(int index);
public:
    std::string name;                //! 骨骼名称
    std::string parentName;     //! 骨骼父节点名称
    cocos2d::Vector<DisplayData*> displayDataList;    //! 保存DisplayData
    cocos2d::AffineTransform boneDataTransform;
};


/**

* ArmatureData保存骨骼动画需要的骨骼名称和骨骼数据
* 创建一个骨骼，我们需要获取每个骨骼的BoneData
* 我们可以从ArmatureData的字典中获取BoneData
* @js NA
* @lua NA
*/
class  ArmatureData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM(ArmatureData)
public:
	/**
     * @js ctor
     */
    ArmatureData();
    /**
     * @js NA
     * @lua NA
     */
    ~ArmatureData();

    bool init();
    void addBoneData(BoneData *boneData);
    BoneData *getBoneData(const std::string& boneName);
public:
    std::string name;
    cocos2d::Map<std::string, BoneData*> boneDataDic;
    float dataVersion;
};

enum BlendType
{
    BLEND_NORMAL,
    BLEND_LAYER,
    BLEND_DARKEN,
    BLEND_MULTIPLY,
    BLEND_LIGHTEN,
    BLEND_SCREEN,
    BLEND_OVERLAY,
    BLEND_HARD_LIGHT,
    BLEND_ADD,
    BLEND_SUBSTRACT,
    BLEND_DIFFERENCE,
    BLEND_INVERT,
    BLEND_ALPHA,
    BLEND_ERASE
};

/**
 *  @js NA
 *  @lua NA
 */
class  FrameData : public BaseData
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(FrameData)
public:
	/**
     * @js ctor
     */
    FrameData();
    /**
     * @js NA
     * @lua NA
     */
    ~FrameData();

    virtual void copy(const BaseData *baseData);
public:
    int frameID;
    int duration;                //! 该帧持续的时间

    cocos2d::tweenfunc::TweenType tweenEasing;     //! 每一帧之间的过渡动画类型
    int easingParamNumber;
    float *easingParams;

    bool isTween;                //! 是否是过渡关键帧

    /**
    * 改变到当前帧时当前的显示索引
    * 如果值为-1，显示将不可见
    */
    int displayIndex;

    cocos2d::BlendFunc blendFunc;

    std::string strEvent;
    /**
    * strMovement, strEvent, strSound, strSoundEffect 目前尚未支持
    */
    std::string strMovement;
    std::string strSound;
    std::string strSoundEffect;
};

/**
 *  @js NA
 *  @lua NA
 */
class  MovementBoneData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM(MovementBoneData)
public:
	/**
     * @js ctor
     */
    MovementBoneData();
    /**
     * @js NA
     * @lua NA
     */
    ~MovementBoneData(void);

    virtual bool init();

    void addFrameData(FrameData *frameData);
    FrameData *getFrameData(int index);
public:
    float delay;             //! movement 延迟比例, 该值会造成延迟效果
    float scale;             //! 缩放当前movement
    float duration;        //! 当前骨骼的movement将持续m_iDuration帧
    std::string name;    //! 骨骼名称

    cocos2d::Vector<FrameData*> frameList;
};

/**
 *  @js NA
 *  @lua NA
 */
class  MovementData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(MovementData)
public:
	/**
     * @js ctor
     */
    MovementData(void);
    /**
     * @js NA
     * @lua NA
     */
    ~MovementData(void);

    void addMovementBoneData(MovementBoneData *movBoneData);
    MovementBoneData *getMovementBoneData(const std::string& boneName);
public:
    std::string name;
    int duration;        //! 该movement持续的帧数
    float scale;		  //! 缩放movement

    /**
    * Change to this movement will last durationTo frames. Use this effect can avoid too suddenly changing.
    * 改变到当前movement将会持续durationTo帧。使用这个效果能避免突然的改变。
    *
    * Example : 当前movement状态为"stand",我们想要改变成"run"，我们将会在改变为"run"之前填充durationTo的帧
    */
    int durationTo;

    /*
    * 和duration不同，durationTween包含过渡效果
    * duration是动画持续的时间信息，同ActionEditor中设置的信息相同
    * durationTween是真实的动画持续的时间
    */
    int durationTween;

    bool loop;           //! movement是否循环播放

    /**
    * movement使用哪种过渡效果
    * TWEEN_EASING_MAX : 使用MovementData中的值
    */
    cocos2d::tweenfunc::TweenType tweenEasing;

    /**
    * @brief	保存movement骨骼的值
    * @key	const std::string& 
    * @value	MovementBoneData *
    */
    cocos2d::Map<std::string, MovementBoneData*> movBoneDataDic;
};


/**
*  AnimationData include all movement infomation for the Armature
*  动画数据包含骨骼动画中所有的movment信息
*  结构信息： AnimationData -> MovementData -> MovementBoneData -> FrameData
*                                              -> MovementFrameData
*  @js NA
*  @lua NA
*/
class  AnimationData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM_NO_INIT(AnimationData)
public:
	/**
     * @js ctor
     */
    AnimationData(void);
    /**
     * @js NA
     * @lua NA
     */
    ~AnimationData(void);

    void addMovement(MovementData *movData);
    MovementData *getMovement(const std::string& movementName);
    ssize_t getMovementCount();
public:
    std::string name;
    cocos2d::Map<std::string, MovementData*> movementDataDic;
    std::vector<std::string> movementNames;
};



/*
* ContourData 包括轮廓的顶点信息
* @js NA
* @lua NA
*/
class  ContourData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM(ContourData)
public:
	/**
     * @js ctor
     */
    ContourData();
    /**
     * @js NA
     * @lua NA
     */
    ~ContourData(void);

    virtual bool init();
    virtual void addVertex(cocos2d::Vec2 &vertex);
public:
    std::vector<cocos2d::Vec2> vertexList;	//! 保存轮廓的顶点信息，顶点信息保存在Vec2中
};




/*
* TextureData 包含纹理的数据
* @js NA
* @lua NA
*/
class  TextureData : public cocos2d::Ref
{
public:
    CC_CREATE_NO_PARAM(TextureData)
public:
	/**
     * @js ctor
     */
    TextureData();
    /**
     * @js NA
     * @lua NA
     */
    ~TextureData(void);

    virtual bool init();

    void addContourData(ContourData *contourData);
    ContourData *getContourData(int index);
public:

    float height;		//! 纹理的高度和宽度
    float width;

    float pivotX;		//! 纹理的锚点
    float pivotY;

    std::string name;	//! 纹理的名称

    cocos2d::Vector<ContourData*> contourDataList;
};


}

#endif /*__CCARMATURE_DATAS_H__*/
