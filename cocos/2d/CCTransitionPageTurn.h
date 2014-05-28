/****************************************************************************
Copyright (c) 2009      Sindesso Pty Ltd http://www.sindesso.com/
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCPAGE_TURN_TRANSITION_H__
#define __CCPAGE_TURN_TRANSITION_H__

#include "2d/CCTransition.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class NodeGrid;

/**
 * @addtogroup transition
 * @{
 */

/**
@brief 一个过渡效果这个剥落卷页场景的右下角过渡
 过渡到场景下方模拟翻页。
 
 这将使用一个3DAction,所以强烈建议在Director中开启深度缓冲区
 用法：
 Director::getInstance()->setDepthBufferFormat(kDepthBuffer16);

 @since v0.8.2
*/
class CC_DLL TransitionPageTurn : public TransitionScene
{
public:
    /**
     * 使用 duration、传入的scene 创建一个基础过渡.
     * 如果返回 true 传入效果会出现反转
     * scene 从左覆盖传入 scene.
     */
    static TransitionPageTurn* create(float t,Scene* scene,bool backwards);
    /**
     * @js ctor
     */
    TransitionPageTurn();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TransitionPageTurn();
    
    //
    // 重写
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

    /**
     * 使用 duration、传入的scene 初始化一个基础过渡.
     * 如果返回 true 传入效果会出现反转
     * scene 从左覆盖传入 scene.
     */
    bool initWithDuration(float t,Scene* scene,bool backwards);

    ActionInterval* actionWithSize(const Size& vector);

    //
    // 重写
    //
    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    virtual void sceneOrder() override;

protected:
    NodeGrid* _inSceneProxy;
    NodeGrid* _outSceneProxy;
    bool    _back;    
    static float POLYGON_OFFSET_FACTOR;
    static float POLYGON_OFFSET_UNITS;
    
protected:
    CustomCommand _enableOffsetCmd;
    CustomCommand _disableOffsetCmd;
    void onEnablePolygonOffset();
    void onDisablePolygonOffset();
};

// end of transition group
/// @}

NS_CC_END

#endif // __CCPAGE_TURN_TRANSITION_H__

