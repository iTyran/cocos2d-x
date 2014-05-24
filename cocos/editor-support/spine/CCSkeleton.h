/******************************************************************************
 * Spine Runtime Software License - Version 1.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms in whole or in part, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. A Spine Essential, Professional, Enterprise, or Education License must
 *    be purchased from Esoteric Software and the license must remain valid:
 *    http://esotericsoftware.com/
 * 2. Redistributions of source code must retain this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer.
 * 3. Redistributions in binary form must reproduce this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer, in the documentation and/or other materials provided with the
 *    distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_CCSKELETON_H_
#define SPINE_CCSKELETON_H_

#include <spine/spine.h>

#include "2d/CCNode.h"
#include "2d/CCProtocols.h"
#include "2d/CCTextureAtlas.h"
#include "renderer/CCCustomCommand.h"

namespace spine {

/**
用于绘制骨骼的cocos2d-x类.
*/
class Skeleton: public cocos2d::Node, public cocos2d::BlendProtocol {
public:
	spSkeleton* skeleton;
	spBone* rootBone;
	float timeScale;
	bool debugSlots;
	bool debugBones;
	bool premultipliedAlpha;
    cocos2d::BlendFunc blendFunc;

	static Skeleton* createWithData (spSkeletonData* skeletonData, bool ownsSkeletonData = false);
	static Skeleton* createWithFile (const char* skeletonDataFile, spAtlas* atlas, float scale = 0);
	static Skeleton* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 0);

	Skeleton (spSkeletonData* skeletonData, bool ownsSkeletonData = false);
	Skeleton (const char* skeletonDataFile, spAtlas* atlas, float scale = 0);
	Skeleton (const char* skeletonDataFile, const char* atlasFile, float scale = 0);

	virtual ~Skeleton ();

	virtual void update (float deltaTime) override;
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated) override;
    void onDraw(const cocos2d::Mat4 &transform, bool transformUpdated);
	void onEnter() override;
	void onExit() override;
	virtual cocos2d::Rect getBoundingBox () const override;

	// --- 调用Skeleton_*方法的简便方式.
	void updateWorldTransform ();

	void setToSetupPose ();
	void setBonesToSetupPose ();
	void setSlotsToSetupPose ();

	/* 查找指定名字的骨骼（bone）如果找不到返回0. */
	spBone* findBone (const char* boneName) const;
	/* 查找指定名字槽（slot）如果找不到返回0. */
	spSlot* findSlot (const char* slotName) const;
	
	/* 设置皮肤（skin）用于查找在默认皮肤中的SkeletonData数据中找不到的附件（attachment），如果在新皮肤中的附件（attachment）
	 * 在之前的皮肤中已经存在，皮肤就会被加载（译者注：换言之如果原来的皮肤里不存在的话是不会自动加载的，你需要调用setSlotsToSetupPose.
	 * 更多详情请参考http://esotericsoftware.com/spine-using-runtimes#Skin-changes），如果皮肤找不到返回false
	 * Sets the skin used to look up attachments not found in the SkeletonData defaultSkin. Attachments from the new skin are
	 * attached if the corresponding attachment from the old skin was attached. Returns false if the skin was not found.
	 * @param skin 可以是0.*/
	bool setSkin (const char* skinName);
	
	/* 查找附件（attachment）如果slot或者attachment找不到返回0. */
	spAttachment* getAttachment (const char* slotName, const char* attachmentName) const;
	/* 设置附件（attachment）如果slot或者attachment找不到返回false. */
	bool setAttachment (const char* slotName, const char* attachmentName);

	// --- CCBlendProtocol
    virtual const cocos2d::BlendFunc& getBlendFunc() const override;
    virtual void setBlendFunc(const cocos2d::BlendFunc& func) override;

protected:
	Skeleton ();
	void setSkeletonData (spSkeletonData* skeletonData, bool ownsSkeletonData);
	virtual cocos2d::TextureAtlas* getTextureAtlas (spRegionAttachment* regionAttachment) const;

private:
	bool ownsSkeletonData;
	spAtlas* atlas;
	void initialize ();
    // Util function that setting blend-function by nextRenderedTexture's premultiplied flag
    void setFittedBlendingFunc(cocos2d::TextureAtlas * nextRenderedTexture);
    
    cocos2d::CustomCommand _customCommand;    
};

}

#endif /* SPINE_CCSKELETON_H_ */
