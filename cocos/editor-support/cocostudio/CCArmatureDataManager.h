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

#ifndef __CCARMATUREDATAMANAGER_H__
#define __CCARMATUREDATAMANAGER_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"


namespace cocostudio {

struct RelativeData
{
    std::vector<std::string> plistFiles;
    std::vector<std::string> armatures;
    std::vector<std::string> animations;
    std::vector<std::string> textures;
};

/**
 *	@brief	格式化和管理骨骼动画的配置和骨骼动画
 */
class  ArmatureDataManager : public cocos2d::Ref
{
public:
	/** @deprecated 用getInstance()替换 */
    CC_DEPRECATED_ATTRIBUTE static ArmatureDataManager *sharedArmatureDataManager() { return ArmatureDataManager::getInstance(); }

    /** @deprecated 用destoryInstance() 替换*/
    CC_DEPRECATED_ATTRIBUTE static void purge() { ArmatureDataManager::destroyInstance(); };
    
    static ArmatureDataManager *getInstance();
    static void destroyInstance();
    
private:
	/**
     * @js ctor
     */
    ArmatureDataManager(void);
    /**
     * @js NA
     * @lua NA
     */
    ~ArmatureDataManager(void);

public:

    /**
     * 初始化ArmatureDataManager
     */
    virtual bool init();

    /**
     * 添加骨骼动画数据
     * @param id 骨骼动画数据的id
     * @param armatureData ArmatureData *
     */
    void addArmatureData(const std::string& id, ArmatureData *armatureData, const std::string& configFilePath = "");

    /**
     *	@brief	获取骨骼动画数据
     *	@param	id 骨骼动画数据的id
     *  @return	ArmatureData *
     */
    ArmatureData *getArmatureData(const std::string& id);

    /**
     *	@brief	移除骨骼动画数据
     *	@param	id 骨骼动画数据的id
     */
    void removeArmatureData(const std::string& id);

    /**
     *	@brief	添加骨骼动画数据
     *	@param 	id 骨骼动画数据id
     *  @return AnimationData *
     */
    void addAnimationData(const std::string& id, AnimationData *animationData, const std::string& configFilePath = "");

    /**
     *	@brief	从 _animationDatas(Dictionary)中获取骨骼动画数据
     *	@param 	id 骨骼动画数据id
     *  @return AnimationData *
     */
    AnimationData *getAnimationData(const std::string& id);

    /**
     *	@brief	移除骨骼动画数据
     *	@param 	id 骨骼动画数据id
     */
    void removeAnimationData(const std::string& id);

    /**
     *	@brief	添加纹理数据id
     *	@param 	id  纹理id
     *  @return TextureData *
     */
    void addTextureData(const std::string& id, TextureData *textureData, const std::string& configFilePath = "");

    /**
     *	@brief	获取纹理数据
     *	@param 	id 要获取的纹理数据id
     *  @return TextureData *
     */
    TextureData *getTextureData(const std::string& id);

    /**
     *	@brief	移除纹理数据
     *	@param 	id 要获取的纹理id
     */
    void removeTextureData(const std::string& id);

    /**
     *	@brief	添加ArmatureFileInfo,由ArmatureDataManager管理
     */
    void addArmatureFileInfo(const std::string& configFilePath);

    /**
     *	@brief	添加ArmatureFileInfo, 由ArmatureDataManager管理
     *			将会在新的线程中加载
     */
    void addArmatureFileInfoAsync(const std::string& configFilePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    /**
     *	@brief	添加ArmatureFileInfo, 由ArmatureDataManager管理
     */
    void addArmatureFileInfo(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath);

    /**
     *	@brief	添加ArmatureFileInfo, 由ArmatureDataManager管理
     *			将会在新的线程中加载
     */
    void addArmatureFileInfoAsync(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath, cocos2d::Ref *target, cocos2d::SEL_SCHEDULE selector);

    /**
     *	@brief	添加精灵到CCSpriteFrameCache中, 它将保存现实的名称和对应的图片名称
     */
    void addSpriteFrameFromFile(const std::string& plistPath, const std::string& imagePath, const std::string& configFilePath = "");

    virtual void removeArmatureFileInfo(const std::string& configFilePath);


    /**
     *	@brief	判断是否需要自动加载精灵的图片
     */
    bool isAutoLoadSpriteFile();


    const cocos2d::Map<std::string, ArmatureData*>&     getArmatureDatas() const;
    const cocos2d::Map<std::string, AnimationData*>&    getAnimationDatas() const;
    const cocos2d::Map<std::string, TextureData*>&      getTextureDatas() const;

protected:
    void addRelativeData(const std::string& configFilePath);
    RelativeData *getRelativeData(const std::string& configFilePath);
private:
    /**
     *	@brief	保存骨骼数据
     *  @key	std::string
     *  @value	ArmatureData *
     */
    cocos2d::Map<std::string, ArmatureData*> _armarureDatas;

    /**
     *	@brief	保存骨骼动画数据
     *  @key	std::string
     *  @value	AnimationData *
     */
    cocos2d::Map<std::string, AnimationData*> _animationDatas;

    /**
     *	@brief	保存纹理数据
     *  @key	std::string
     *  @value	TextureData *
     */
    cocos2d::Map<std::string, TextureData*> _textureDatas;

    bool _autoLoadSpriteFile;

    std::unordered_map<std::string, RelativeData> _relativeDatas;
};


}

#endif/*__CCARMATUREDATAMANAGER_H__*/
