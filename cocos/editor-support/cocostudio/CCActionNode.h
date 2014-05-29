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

#ifndef __ActionNODE_H__
#define __ActionNODE_H__

#include "cocostudio/CCActionFrame.h"
#include "cocostudio/DictionaryHelper.h"

namespace cocostudio {

/**
*  @js NA
*  @lua NA
*/
class ActionNode : public cocos2d::Ref
{
public:

	/**
	* 默认构造函数
	*/
	ActionNode();

	/**
	* 默认析构函数
	*/
	virtual ~ActionNode();
	/**
	* 设置帧之间的间隔时间
	*
	* @param fTime   帧之间的间隔时间
	*/
	void setUnitTime(float fTime);

	/**
	* 获取帧之间的时间间隔
	*
	* @return fTime   帧之间的时间间隔
	*/
	float getUnitTime();
	/**
	* 设置ActionNode的tag
	*
	* @param tag    ActionNode的tag
	*/
	void setActionTag(int tag);

	/**
	* 获取ActionNode的tag
	*
	* @return tag    ActionNode的tag
	*/
	int getActionTag();

	/**
	* 设置执行action的node
	*
	* @param  node 执行action的node
	*/
	void setObject(cocos2d::Ref* node);

	/**
	* 获取执行action的node
	*
	* @return  执行action的node
	*/
	cocos2d::Ref* getObject();

	/**
	* 插入ActionFrame到ActionNode中
	*
	* @param index  ActionFrame的索引
	*
	* @param frame  插入的ActionFrame
	*/
	void insertFrame(int index, ActionFrame* frame);

	/**
	* 插入ActionFrame到ActionNode尾部
	*
	* @param frame  插入的ActionFrame
	*/
	void addFrame(ActionFrame* frame);

	/**
	* 从ActionNode中移除ActionFrame
	*
	* @param frame  要移除的ActionFrame
	*/
	void deleteFrame(ActionFrame* frame );

	/**
	* 移除ActionNode中的所有ActionFrame
	*/
	void clearAllFrame();

	/**
	* 获取第一个ActionFrame的索引
	*
	* @return  第一个ActionFrame的索引
	*/
	int getFirstFrameIndex();

	/**
	* 获取最后一个ActionFrame的索引
	*
	* @return  最后一个ActionFrame的索引
	*/
	int getLastFrameIndex();

	/**
	* 设置action需要更新状态的时间
	*
	* @param fTime   需要更新状态的时间
	*/
	virtual bool updateActionToTimeLine(float fTime);

	/**
	* 播放动作
	*/
	virtual void playAction();

	/**
	* 停止动作
	*/
	virtual void stopAction();

	/*init properties with a json dictionary*/
	virtual void initWithDictionary(const rapidjson::Value& dic, cocos2d::Ref* root);

	/**
	* 动作是否已经执行完成
	*
	* @return   动作是否已经执行完成
	*/
	virtual bool isActionDoneOnce();
protected:
	int _currentFrameIndex;
	int _destFrameIndex;

	float _fUnitTime;

	int _actionTag;
	cocos2d::Spawn * _actionSpawn;
	cocos2d::Action* _action;
	cocos2d::Ref* _object;

	std::vector<cocos2d::Vector<ActionFrame*>*> _frameArray;
	int _frameArrayNum;

protected:
	virtual cocos2d::Node* getActionNode();
	virtual cocos2d::Spawn * refreshActionProperty();
	virtual void runAction();
	virtual void initActionNodeFromRoot(cocos2d::Ref* root);
	virtual void easingToFrame(float duration,float delayTime,ActionFrame* srcFrame,ActionFrame* destFrame);
};

}

#endif
