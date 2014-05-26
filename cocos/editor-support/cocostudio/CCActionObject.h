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

#ifndef __ActionObject_H__
#define __ActionObject_H__

#include "cocostudio/CCActionNode.h"
#include "2d/CCActionInstant.h"
#include "cocostudio/DictionaryHelper.h"

namespace cocostudio {

/**
*  @js NA
*  @lua NA
*/
class ActionObject : public cocos2d::Ref
{
public:

	/**
	* 默认构造函数
	*/
	ActionObject();

	/**
	* 默认析构函数
	*/
	virtual ~ActionObject();

	/**
	* 设置对象的名称
	*
	* @param name    对象的名称
	*/
	void setName(const char* name);

	/**
	* 获取对象的名称
	*
	* @return 对象的名称
	*/
	const char* getName();

	/**
	* 设置action是否循环播放
	*
	* @param bLoop     action是否循环播放
	*/
	void setLoop(bool bLoop);

	/**
	* 获取action是否循环播放
	*
	* @return   action是否循环播放
	*/
	bool getLoop();

	/**
	* 设置帧（frame）的时间间隔
	*
	* @param fTime   帧（frame）的时间间隔
	*/
	void setUnitTime(float fTime);

	/**
	* 获取帧（frame）的时间间隔
	*
	* @return 帧（frame）的时间间隔
	*/
	float getUnitTime();

	/**
	* 设置帧（frame）的当前时间
	*
	* @param fTime   帧（frame）的当前时间
	*/
	void setCurrentTime(float fTime);

	/**
	* 获取帧（frame）的当前时间
	*
	* @return 帧（frame）的当前时间
	*/
	float getCurrentTime();

	/**
	* 获取帧（frame）的总时间
	*
	* @return 帧（frame）的总时间
	*/
	float getTotalTime();

	/**
	* 返回action是否正在播放。
	*
	* @return 如果action正在播放，返回true，否则返回false
	*/
	bool isPlaying();

	/**
	* 播放action
	*/
	void play();

	/**
	* 播放action
	*
	* @param func Action回调函数
	*/
	void play(cocos2d::CallFunc* func);

	/** 
	* 暂停action
	*/
	void pause();

	/**
	* 停止action
	*/
	void stop();

	/**
	* 添加播放action的ActionNode
	*
	* @node    播放action的ActionNode
	*/
	void addActionNode(ActionNode* node);

	/**
	* 删除播放action的ActionNode
	*
	* @node    播放action的ActionNode
	*/
	void removeActionNode(ActionNode* node);

	/*update frame method*/
	void updateToFrameByTime(float fTime);

	/*init properties with a json dictionary*/
	void initWithDictionary(const rapidjson::Value& dic, cocos2d::Ref* root);

	/*scheduler update function*/
	void simulationActionUpdate(float dt);
protected:
	cocos2d::Vector<ActionNode*> _actionNodeList;
	std::string _name;
	bool _loop;
	bool _bPause;
	bool _bPlaying;
	float _fUnitTime;
	float _currentTime;
	cocos2d::Scheduler *_pScheduler;
	cocos2d::CallFunc *_CallBack;
	float _fTotalTime;
};

}

#endif
