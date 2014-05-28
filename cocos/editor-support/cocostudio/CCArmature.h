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

#ifndef __CCARMATURE_H__
#define __CCARMATURE_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCBone.h"
#include "cocostudio/CCBatchNode.h"
#include "cocostudio/CCArmatureAnimation.h"
#include "cocostudio/CCSpriteFrameCacheHelper.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "math/CCMath.h"

class b2Body;
struct cpBody;

namespace cocostudio {

CC_DEPRECATED_ATTRIBUTE typedef ProcessBase CCProcessBase;
CC_DEPRECATED_ATTRIBUTE typedef BaseData CCBaseData;
CC_DEPRECATED_ATTRIBUTE typedef DisplayData CCDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef SpriteDisplayData CCSpriteDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureDisplayData CCArmatureDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef ParticleDisplayData CCParticleDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef BoneData CCBoneData;
CC_DEPRECATED_ATTRIBUTE typedef FrameData CCFrameData;
CC_DEPRECATED_ATTRIBUTE typedef MovementBoneData CCMovementBoneData;
CC_DEPRECATED_ATTRIBUTE typedef MovementData CCMovementData;
CC_DEPRECATED_ATTRIBUTE typedef AnimationData CCAnimationData;
CC_DEPRECATED_ATTRIBUTE typedef ContourData CCContourData;
CC_DEPRECATED_ATTRIBUTE typedef TextureData CCTextureData;
CC_DEPRECATED_ATTRIBUTE typedef DecorativeDisplay CCDecorativeDisplay;
CC_DEPRECATED_ATTRIBUTE typedef DisplayData CCDisplayData;
CC_DEPRECATED_ATTRIBUTE typedef DisplayFactory CCDisplayFactory;
CC_DEPRECATED_ATTRIBUTE typedef BatchNode CCBatchNode;
CC_DEPRECATED_ATTRIBUTE typedef DecorativeDisplay CCDecorativeDisplay;
CC_DEPRECATED_ATTRIBUTE typedef DisplayManager CCDisplayManager;
CC_DEPRECATED_ATTRIBUTE typedef ColliderBody CCColliderBody;
CC_DEPRECATED_ATTRIBUTE typedef ColliderDetector CCColliderDetector;
CC_DEPRECATED_ATTRIBUTE typedef SpriteFrameCacheHelper CCSpriteFrameCacheHelper;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureData CCArmatureData;
CC_DEPRECATED_ATTRIBUTE typedef Bone CCBone;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureAnimation CCArmatureAnimation;
CC_DEPRECATED_ATTRIBUTE typedef Armature CCArmature;
CC_DEPRECATED_ATTRIBUTE typedef ArmatureDataManager CCArmatureDataManager;
CC_DEPRECATED_ATTRIBUTE typedef cocos2d::tweenfunc::TweenType CCTweenType;

class  Armature : public cocos2d::Node, public cocos2d::BlendProtocol
{

public:

    /**
    * 分配并初始化骨骼动画
    * @return 分配病初始化过的骨骼动画
    */
    static Armature *create();

    /**
    * 分配一个骨骼动画,并且给它一个存放到ArmatureDataManage中作为索引的名称
    *
    * @param  name 骨骼动画的名称
    * @return 分配并初始化过的骨骼动画
    */
    static Armature *create(const std::string& name);

    static Armature *create(const std::string& name, Bone *parentBone);

public:
    /**
     *  @js ctor
     */
    Armature();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Armature(void);

    /**
     * 初始化创建好的骨骼动画
     */
    virtual bool init() override;

    /**
     * 初始化创建好的骨骼动画，并命名
     * @param name 骨骼动画名称
     */
    virtual bool init(const std::string& name);

    virtual bool init(const std::string& name, Bone *parentBone);
    /**
     * 在骨骼动画中增加一个骨骼
     *
     * @param bone  想要加入骨骼动画中的骨骼
     * @param parentName   想要骨骼加入的骨骼动画名称
     */
    virtual void addBone(Bone *bone, const std::string& parentName);
    /**
     * 通过指定名称获取骨骼
     *
     * @param name 想要获取的骨骼的名称
     */
    virtual Bone *getBone(const std::string& name) const;
    /**
     * 改变骨骼的挂靠父节点到指定名称的父节点上
     *
     * @param bone 要改变的骨骼
     * @param parentName 新的父节点的名称
     */
    virtual void changeBoneParent(Bone *bone, const std::string& parentName);
    /**
     * Remove a bone with the specified name. If recursion it will also remove child Bone recursionly.
     * 移除指定名称的骨骼。如果recursion为true，有子骨骼的话，会一同移除
     *
     * @param bone 要移除的骨骼
     * @param recursion 是否要移除子骨骼
     */
    virtual void removeBone(Bone *bone, bool recursion);

    /**
     * 获取骨骼动画的骨骼字典
     * @return 骨骼动画的骨骼字典
     */
    const cocos2d::Map<std::string, Bone*>& getBoneDic() const;

    /**
     * 获取的boundingBox是根据骨骼动画的变化而一直变化的
     */
    virtual cocos2d::Rect getBoundingBox() const override;

    Bone *getBoneAtPoint(float x, float y) const;

    // overrides
    /**
     * @js NA
     * @lua NA
     */
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, bool parentTransformUpdated) override;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated) override;
    virtual void update(float dt) override;

    virtual void onEnter() override;
    virtual void onExit() override; 

    virtual const cocos2d::Mat4& getNodeToParentTransform() const override;
    /**
     *  @js NA
     *  @lua NA
     */
    inline void setBlendFunc(const cocos2d::BlendFunc &blendFunc) override { _blendFunc = blendFunc; }
    /**
     *  @js NA
     *  @lua NA
     */
    inline const cocos2d::BlendFunc &getBlendFunc(void) const override{ return _blendFunc; }
	

    /**
     * 设置ContentSize和AnchorPoint
     */
    virtual void updateOffsetPoint();
    virtual void setAnchorPoint(const cocos2d::Vec2& point) override;
    virtual const cocos2d::Vec2& getAnchorPointInPoints() const override;

    virtual void setAnimation(ArmatureAnimation *animation);
    virtual ArmatureAnimation *getAnimation() const;
    
    virtual bool getArmatureTransformDirty() const;


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setColliderFilter(ColliderFilter *filter);
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    virtual void drawContour();
#endif


    virtual void setArmatureData(ArmatureData *armatureData) { _armatureData = armatureData; }
    virtual ArmatureData *getArmatureData() const { return _armatureData; }

    virtual void setName(const std::string &name) { _name = name; }
    virtual const std::string &getName() const { return _name; } 


    virtual void setParentBone(Bone *parentBone);
    virtual Bone *getParentBone() const;

    virtual void setVersion(float version) { _version = version; }
    virtual float getVersion() const { return _version; }

    virtual void setBatchNode(BatchNode *batchNode) { _batchNode = batchNode; }
    virtual BatchNode *getBatchNode() const { return _batchNode; }

#if ENABLE_PHYSICS_BOX2D_DETECT
    virtual b2Fixture *getShapeList();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void setBody(b2Body *body);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual b2Body *getBody() const;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    /**
     *  @js NA
     *  @lua NA
     */
    virtual cpShape *getShapeList();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual void setBody(cpBody *body);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual cpBody *getBody() const;
#endif

protected:

    /*
     * 创建骨骼
     * @js NA
     * @lua NA
     */
    Bone *createBone(const std::string& boneName );

protected:
    ArmatureData *_armatureData;

    BatchNode *_batchNode;

    std::string _name;
    Bone *_parentBone;
    float _version;

    mutable bool _armatureTransformDirty;

    cocos2d::Map<std::string, Bone*> _boneDic;                    //! 骨骼的字典，包含骨骼动画中所有的骨骼，包括直接的骨骼和间接的骨骼。同m_pChildren不同。

    cocos2d::Vector<Bone*> _topBoneList;

    cocos2d::BlendFunc _blendFunc;                    //! 为了CCTextureProtocol继承

    cocos2d::Vec2 _offsetPoint;
    cocos2d::Vec2 _realAnchorPointInPoints;

    ArmatureAnimation *_animation;

#if ENABLE_PHYSICS_BOX2D_DETECT
    b2Body *_body;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    cpBody *_body;
#endif
};

}

#endif /*__CCARMATURE_H__*/
