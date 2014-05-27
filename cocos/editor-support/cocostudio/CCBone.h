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

#ifndef __CCBONE_H__
#define __CCBONE_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CCTween.h"
#include "cocostudio/CCDecorativeDisplay.h"
#include "cocostudio/CCDisplayManager.h"
#include "2d/CCNode.h"
#include "math/CCMath.h"

namespace cocostudio {

class Armature;

class Bone : public cocos2d::Node
{
public:
    /**
     * 分配空间并初始化一个骨架（bone）
     * @return 一个经过初始化并被标记为"autorelease"的骨架（bone）
     */
    static Bone *create();
    /**
     * 分配空间并初始化一个骨架（bone）
     *
     * @param  name 如果该名字参数非空，就将该参数设置为骨架（bone）的名字
     * @return 一个经过初始化并被标记为"autorelease"的骨架（bone）
     */
    static Bone *create(const std::string& name);

public:
    /**
     *  @js ctor
     */
    Bone();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Bone(void);

    /**
     * 初始化一个内部细节没有初始化的空骨架（bone）
     */
    virtual bool init() override;

    /**
     * 用一个特定的名字参数来初始化该骨架（bone）
     * @param name 骨架（bone）的名字
     */
    virtual bool init(const std::string& name);

    /**
     * 添加display并使用displayData初始化该display
     * 如果参数所示索引（index）下已经有一个display，就替换该display
     * 如果参数所示索引（index）是当前display的索引，仍然改变该display至_index
     *
     * @param displayData 该参数包括display的基本信息，比如DisplayType。如果你希望创建一个精灵display，那么就创建一个SpriteDisplayData参数
     *
     * @param index 你希望用来替换或者添加的display的索引（index）
     *          －1:从后追加display
     */
    void addDisplay(DisplayData *displayData, int index);

    void addDisplay(cocos2d::Node *display, int index);

    void removeDisplay(int index);

    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const std::string& name, bool force);

    void changeDisplayWithIndex(int index, bool force);
    void changeDisplayWithName(const std::string& name, bool force);

    /**
     * 向骨架（bone）中增加一个子节点，并且允许该子节点通过调用 setParent(Bone *parent) 函数方法来设置其自身的父节点
     * @param 	child  你希望添加的子节点
     */
    void addChildBone(Bone *child);

    /**
     * 设置父骨架（bone）
     * 如果将父节点设置为空，会将该骨架从Armature中清除
     * 这个方法不会对Armature进行设置，如果你希望向Armature中添加骨架（bone），你应该使用Armature::addBone(Bone *bone, const char* parentName)
     *
     * @param parent  父骨架（bone）
     *          nullptr : 从Armature中清除该骨架
     */
    void setParentBone(Bone *parent);

    /**
     * 获取父骨架（bone）
     * @return 父骨架（bone）
     */
    Bone *getParentBone();

    using Node::removeFromParent;
    /**
     * 从其父节点中清除其自身
     * @param recursion    是否清除该子骨架（bone）的display
     */
    void removeFromParent(bool recursion);

    /**
     * 清除一个子骨架（bone）
     * @param 	bone   你希望清除的骨架（bone）
     */
    void removeChildBone(Bone *bone, bool recursion);

    void update(float delta) override;

    void updateDisplayedColor(const cocos2d::Color3B &parentColor) override;
    void updateDisplayedOpacity(GLubyte parentOpacity) override;

    //! 更新颜色，渲染display
    virtual void updateColor() override;

    //! 更新zorder
    void updateZOrder();

    virtual void setLocalZOrder(int zOrder) override;

    Tween *getTween();

    /*
     * 检查该骨架（bone）的变换属性是否发生改变。如果变化属性发生了变化，该骨架（bone）会依据该变化更新其自身
     */
    virtual void setTransformDirty(bool dirty) { _boneTransformDirty = dirty; }
    virtual bool isTransformDirty() { return _boneTransformDirty; }

    virtual cocos2d::Mat4 getNodeToArmatureTransform() const;
    virtual cocos2d::Mat4 getNodeToWorldTransform() const override;

    cocos2d::Node *getDisplayRenderNode();
    DisplayType getDisplayRenderNodeType();

    /*
     * 获取该骨架中的ColliderBody表。序列中的对象为ColliderBody
     */
    virtual ColliderDetector* getColliderDetector() const;

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    virtual void setColliderFilter(ColliderFilter *filter);
    virtual ColliderFilter *getColliderFilter();
#endif

    virtual void setBoneData(BoneData *boneData);
    virtual BoneData *getBoneData() const;

    virtual void setArmature(Armature *armature);
    virtual Armature *getArmature() const;

    virtual void setChildArmature(Armature *childArmature);
    virtual Armature *getChildArmature() const;

    virtual DisplayManager *getDisplayManager() const { return _displayManager; }
    /**
     *  @lua NA
     */
    virtual void setIgnoreMovementBoneData(bool ignore) { _ignoreMovementBoneData = ignore; }
    virtual bool isIgnoreMovementBoneData() const { return _ignoreMovementBoneData; }

    /*
     * 该函数已被弃用，请使用isIgnoreMovementBoneData()
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual bool getIgnoreMovementBoneData() const { return isIgnoreMovementBoneData(); }

    
    /*
     * 设置blend函数
     */
    virtual void setBlendFunc(const cocos2d::BlendFunc& blendFunc);
    virtual cocos2d::BlendFunc getBlendFunc(void) { return _blendFunc; }

    /*
     * 设置是否blend函数已经过期
     */
    virtual void setBlendDirty(bool dirty) { _blendDirty = dirty; }
    virtual bool isBlendDirty(void) { return _blendDirty; }

    virtual FrameData *getTweenData() const { return _tweenData; }

    virtual void setName(const std::string &name) { _name = name; }
    virtual const std::string getName() const { return _name; }

    virtual BaseData *getWorldInfo() const { return _worldInfo; }
protected:
    void applyParentTransform(Bone *parent);

    /*
     *  骨架（bone）的起始状态。display的状态会受到_boneData, m_pNode, _tweenData的影响
     *  当调用setData函数时，它会在BoneData处进行复制
     */
    BoneData *_boneData;

    //! 指向Armature的弱引用
    Armature *_armature;

    //! 指向子Armature的弱引用
    Armature *_childArmature;

    DisplayManager *_displayManager;

    /*
     *	当Armature播放动画时，如果在这个MovementData中没有这个骨架（bone）的MovementBoneData，这个骨架（bone）会被隐藏
     *	将IgnoreMovementBoneData设置为true，那么这个骨架（bone）也会被显示出来
     */
    bool _ignoreMovementBoneData;

    cocos2d::BlendFunc _blendFunc;
    bool _blendDirty;

    Tween *_tween;				//! 计算tween效果

    //! 用来在每一个框架中制造tween效果
    FrameData *_tweenData;

    std::string _name;

    Bone *_parentBone;	               //! A weak reference to its parent
    bool _boneTransformDirty;          //! Whether or not transform dirty

    //! 自变换（self transform）, 用这个方法来改变display的状态
    cocos2d::Mat4 _worldTransform;

    BaseData *_worldInfo;
    
    //! Armature的父骨架（bone）
    Bone *_armatureParentBone;
    
    //! 数据的版本
    float _dataVersion;
};

}

#endif /*__CCBONE_H__*/
