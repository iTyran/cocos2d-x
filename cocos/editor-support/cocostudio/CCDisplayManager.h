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

#ifndef __CCDISPLAYMANAGER_H__
#define __CCDISPLAYMANAGER_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDecorativeDisplay.h"
#include "cocostudio/CCDatas.h"

namespace cocostudio {

class Bone;

/**! DisplayManager管理骨骼(Bone)的显示
 *  @js NA
 *  @lua NA
 */
class  DisplayManager : public cocos2d::Ref
{
public:
    static DisplayManager *create(Bone *bone);

public:
    DisplayManager();
    ~DisplayManager();

    bool init(Bone *bone);

    /**
     * 使用骨骼数据(BoneData)初始化显示列表.
     * 如果显示的是一个在TexutreData中有纹理信息的精灵，就使用TexutreData去初始化显示的锚点
     * 如果显示的是骨架(Armature),就创建一个新的骨架
     */
    virtual void initDisplayList(BoneData *boneData);

    /**
     * 添加显示对象，然后用_DisplayData初始化显示对象.
     * 如果索引位置已经有了显示对象，就替换掉.
     * 如果索引位置就是当前显示所在的索引，就把当前显示切换为_index
     *
     *	@param 	displayData 包含显示信息，比如显示类型.
     *					如果要创建一个精灵显示，就创建一个SpriteDisplayData参数
     *
     *	@param 	index   需要替换或者添加的显示的索引
     *					-1 : 从后台添加的显示
     */
    void addDisplay(DisplayData *displayData, int index);

    void addDisplay(cocos2d::Node *display, int index);

    void removeDisplay(int index);

    const cocos2d::Vector<DecorativeDisplay*>& getDecorativeDisplayList() const;

    /*
     * @deprecated, 请使用changeDisplayWithIndex 和 changeDisplayWithName
     */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const std::string& name, bool force);
    
    /**
     * 通过index来切换显示对象，你可以使用这个方法在切换在显示列表中得显示对象
     * 该显示列表只用于这个骨骼动画，它是可应用在每一帧的显示对象
     *
     * Note : 如果索引(index)与上一个显示对象索引相同，这个方法不会起作用
     *
     * @param index 要切换的显示对象索引
     * @param force 如果是true，就强制切换当前显示到指定的显示对象，或者当前显示会设置为在flash每一个关键帧中编辑的显示对象索引
     */
    void changeDisplayWithIndex(int index, bool force);
    void changeDisplayWithName(const std::string& name, bool force);

    cocos2d::Node *getDisplayRenderNode() const;
    DisplayType getDisplayRenderNodeType() const;

    int getCurrentDisplayIndex() const;

    virtual void setCurrentDecorativeDisplay(DecorativeDisplay *decoDisplay);
    virtual DecorativeDisplay *getCurrentDecorativeDisplay() const;
    virtual DecorativeDisplay *getDecorativeDisplayByIndex( int index) const;

    /**
     * 设置显示对象是否可见
     * 默认值是true，一个节点默认是可见的
     *
     * @param visible   如果节点是可见的参数visible就是true，如果节点是隐藏的visible是false
     */
    virtual void setVisible(bool visible);
    /**
     * 确定显示对象是否可见
     *
     * @see setVisible(bool)
     * @return true 如果节点可见返回true，如果节点隐藏返回false
     */
    virtual bool isVisible() const;

    cocos2d::Size getContentSize() const;
    cocos2d::Rect getBoundingBox() const;

    cocos2d::Vec2 getAnchorPoint() const;
    cocos2d::Vec2 getAnchorPointInPoints() const;

    /**
     * 检查给定位置是否在骨骼内部.
     */
    virtual bool containPoint(cocos2d::Vec2 &_point);

    /**
     * 检查给定位置是否在骨骼内部.
     */
    virtual bool containPoint(float x, float y);

    virtual void setForceChangeDisplay(bool force) { _forceChangeDisplay = force; }
    virtual bool isForceChangeDisplay() const { return _forceChangeDisplay; }
protected:
    cocos2d::Vector<DecorativeDisplay*> _decoDisplayList;
    //! 显示渲染节点.
    cocos2d::Node *_displayRenderNode;
    //! 显示渲染节点类型
    DisplayType _displayType;
    //! 包括当前显示信息，比如轮廓，精灵等.
    DecorativeDisplay *_currentDecoDisplay;
    //! 当前的显示索引
    int _displayIndex;

    bool _forceChangeDisplay;

    //! 骨骼是否可见的，默认是true
    bool _visible;

    Bone *_bone;
};

}

#endif /*__CCDISPLAYMANAGER_H__*/
