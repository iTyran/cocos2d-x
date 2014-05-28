/****************************************************************************
Copyright (c) 2009-2010 Ricardo Quesada
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

#ifndef __CCTRANSITION_H__
#define __CCTRANSITION_H__

#include "2d/CCScene.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup transition
 * @{
 */


//静态创建函数宏
// C/C++不支持使用类名创建对象
//所以，所有的类都需要创建方法。

class ActionInterval;
class Node;
class NodeGrid;

/** @brief TransitionEaseScene类可以使场景动画协议更灵活.
@since v0.8.2
*/
class CC_DLL TransitionEaseScene// : public Ref
{
public:
    virtual ~TransitionEaseScene() {}

    /** 返回在一个线性动作上执行更灵活的动作.
    @since v0.8.2
    */
    virtual ActionInterval * easeActionWithAction(ActionInterval * action) = 0;
};

/** @brief 场景转换的基类
*/
class CC_DLL TransitionScene : public Scene
{
public:
    /** 一些用于转换的方向类型
     */
    enum class Orientation
    {
        /// 水平方向，接近左边
        LEFT_OVER = 0,
        /// 水平方向,接近右边
        RIGHT_OVER = 1,
        /// 垂直方向,接近上边
        UP_OVER = 0,
        /// 垂直方向,接近底边
        DOWN_OVER = 1,
    };
    
    /** 创建一个基本的具有持续时间和进入场景的转换(transition) */
    static TransitionScene * create(float t, Scene *scene);

    /** 转换结束调用此方法 */
    void finish(void);

    /** 用于一些转换去隐藏淡出的场景 */
    void hideOutShowIn(void);

    //
    // 重写
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void cleanup() override;
    
CC_CONSTRUCTOR_ACCESS:
    TransitionScene();
    virtual ~TransitionScene();

    /** 初始化一个具有持续时间和进入的场景 转换 */
    bool initWithDuration(float t,Scene* scene);
    
protected:
    virtual void sceneOrder();
    void setNewScene(float dt);

    Scene *_inScene;
    Scene *_outScene;
    float _duration;
    bool _isInSceneOnTop;
    bool _isSendCleanupToScene;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionScene);
};


/**@brief 支持方向的转换
 *可能的方向：LeftOver，RightOver，UpOver，DownOver
 */
class CC_DLL TransitionSceneOriented : public TransitionScene
{
public:
    /** 创建一个基本的具有持续时间和进入场景的转换(transition) */
    static TransitionSceneOriented * create(float t,Scene* scene, Orientation orientation);
    
CC_CONSTRUCTOR_ACCESS:
    TransitionSceneOriented();
    virtual ~TransitionSceneOriented();

    /** 初始化一个具有持续时间和进入的场景 转换 */
    bool initWithDuration(float t,Scene* scene,Orientation orientation);

protected:
    Orientation _orientation;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSceneOriented);
};

/** @brief TransitionRotoZoom:
 旋转和缩放外出的场景，同时旋转缩放进入的场景
*/
class CC_DLL TransitionRotoZoom : public TransitionScene
{
public:
    static TransitionRotoZoom* create(float t, Scene* scene);

    //
    // 重写
    //
    virtual void onEnter() override;

protected:
    TransitionRotoZoom();
    virtual ~TransitionRotoZoom();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionRotoZoom);

};

/** @brief TransitionJumpZoom:
 缩小跳着切出场景, 同时跳着放大传人场景
*/
class CC_DLL TransitionJumpZoom : public TransitionScene
{
public:
    static TransitionJumpZoom* create(float t, Scene* scene);

    //
    // 重写
    //
    virtual void onEnter() override;

protected:
    TransitionJumpZoom();
    virtual ~TransitionJumpZoom();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionJumpZoom);
};

/** @brief TransitionMoveInL:
从左侧传人场景.
*/
class CC_DLL TransitionMoveInL : public TransitionScene, public TransitionEaseScene
{
public:
    static TransitionMoveInL* create(float t, Scene* scene);

    /** 返回将要执行的动作 */
    virtual ActionInterval* action(void);

    virtual ActionInterval* easeActionWithAction(ActionInterval * action);

    //
    // 重写
    //
    virtual void onEnter() override;

protected:
    TransitionMoveInL();
    virtual ~TransitionMoveInL();

    /** initializes the scenes */
    virtual void initScenes();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionMoveInL);
};

/** @brief TransitionMoveInR:
从右侧传人场景.
*/
class CC_DLL TransitionMoveInR : public TransitionMoveInL
{
public:
    static TransitionMoveInR* create(float t, Scene* scene);

protected:
    TransitionMoveInR();
    virtual ~TransitionMoveInR();

    virtual void initScenes();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionMoveInR);
};

/** @brief TransitionMoveInT:
从顶部传人场景.
 */
class CC_DLL TransitionMoveInT : public TransitionMoveInL 
{
public:
    static TransitionMoveInT* create(float t, Scene* scene);

protected:
    TransitionMoveInT();
    virtual ~TransitionMoveInT();

    virtual void initScenes();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionMoveInT);
};

/** @brief TransitionMoveInB:
从底部传人场景.
 */
class CC_DLL TransitionMoveInB : public TransitionMoveInL
{
public:
    static TransitionMoveInB* create(float t, Scene* scene);

protected:
    TransitionMoveInB();
    virtual ~TransitionMoveInB();

    virtual void initScenes();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionMoveInB);
};

/** @brief TransitionSlideInL:
从左边滑入传人场景.
*/
class CC_DLL TransitionSlideInL : public TransitionScene, public TransitionEaseScene
{
public:
    static TransitionSlideInL* create(float t, Scene* scene);

    virtual ActionInterval* easeActionWithAction(ActionInterval * action);

    /** 返回传入/传出 scene 要执行的 action */
    virtual ActionInterval* action(void);

    //
    // 重写
    //
    virtual void onEnter() override;

protected:
    TransitionSlideInL();
    virtual ~TransitionSlideInL();

    /** 初始化scenes */
    virtual void initScenes(void);

    virtual void sceneOrder() override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideInL);
};

/** @brief TransitionSlideInR:
从右边滑入传入场景.
*/
class CC_DLL TransitionSlideInR : public TransitionSlideInL 
{
public:
    static TransitionSlideInR* create(float t, Scene* scene);

    /** 返回传入/传出 scene 要执行的 action */
    virtual ActionInterval* action(void);

protected:
    TransitionSlideInR();
    virtual ~TransitionSlideInR();

    /** 初始化 scenes */
    virtual void initScenes(void);

    virtual void sceneOrder() override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideInR);
};

/** @brief TransitionSlideInB:
从底部滑入传入场景.
*/
class CC_DLL TransitionSlideInB : public TransitionSlideInL
{
public:
    static TransitionSlideInB* create(float t, Scene* scene);

    /** 返回传入/传出 scene 要执行的 action */
    virtual ActionInterval* action(void);

protected:
    TransitionSlideInB();
    virtual ~TransitionSlideInB();

    /** 初始化 scenes */
    virtual void initScenes();

    virtual void sceneOrder() override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideInB);
};

/** @brief TransitionSlideInT:
从顶部滑入传入场景.
*/
class CC_DLL TransitionSlideInT : public TransitionSlideInL
{
public:
    static TransitionSlideInT* create(float t, Scene* scene);

    /** 返回传入/传出 scene 要执行的 action */
    virtual ActionInterval* action(void);

protected:
    TransitionSlideInT();
    virtual ~TransitionSlideInT();

    /**  初始化 scenes */
    virtual void initScenes(void);

    virtual void sceneOrder() override;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideInT);
};

/**
@brief 当增长传入scene的时候，收缩传出的scene
*/
class CC_DLL TransitionShrinkGrow : public TransitionScene , public TransitionEaseScene
{
public:
    static TransitionShrinkGrow* create(float t, Scene* scene);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    virtual ActionInterval* easeActionWithAction(ActionInterval * action) override;

protected:
    TransitionShrinkGrow();
    virtual ~TransitionShrinkGrow();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionShrinkGrow);
};

/** @brief TransitionFlipX:
 水平翻转屏幕。
 正面是传出的场景，背面是传入的场景
 */
class CC_DLL TransitionFlipX : public TransitionSceneOriented
{
public:
    static TransitionFlipX* create(float t, Scene* s, Orientation o);
    static TransitionFlipX* create(float t, Scene* s);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

protected:
    TransitionFlipX();
    virtual ~TransitionFlipX();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFlipX);
};

/** @brief TransitionFlipY:
 垂直翻转屏幕。.
 正面是传出的场景，背面是传入的场景。 
 */
class CC_DLL TransitionFlipY : public TransitionSceneOriented
{
public:
    static TransitionFlipY* create(float t, Scene* s, Orientation o);
    static TransitionFlipY* create(float t, Scene* s);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

protected:
    TransitionFlipY();
    virtual ~TransitionFlipY();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFlipY);
};

/** @brief TransitionFlipAngular:
 水平垂直翻转一半屏幕.（类似一种镜面）
 正面是传出的场景，背面是传入的场景。
*/
class CC_DLL TransitionFlipAngular : public TransitionSceneOriented
{
public:
    static TransitionFlipAngular* create(float t, Scene* s, Orientation o);
    static TransitionFlipAngular* create(float t, Scene* s);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

protected:
    TransitionFlipAngular();
    virtual ~TransitionFlipAngular();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFlipAngular);
};

/** @brief TransitionZoomFlipX:
 水平翻转屏幕，做一个 传入/穿出 缩放
 正面是传出的场景，背面是传入的场景。
 */
class CC_DLL TransitionZoomFlipX : public TransitionSceneOriented
{
public:
    static TransitionZoomFlipX* create(float t, Scene* s, Orientation o);
    static TransitionZoomFlipX* create(float t, Scene* s);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

protected:
    TransitionZoomFlipX();
    virtual ~TransitionZoomFlipX();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionZoomFlipX);
};

/** @brief TransitionZoomFlipY:
 垂直翻转屏幕，做一个 传入/穿出 缩放
 正面是传出的场景，背面是传入的场景。
*/
class CC_DLL TransitionZoomFlipY : public TransitionSceneOriented
{
public:
    static TransitionZoomFlipY* create(float t, Scene* s, Orientation o);
    static TransitionZoomFlipY* create(float t, Scene* s);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

protected:
    TransitionZoomFlipY();
    virtual ~TransitionZoomFlipY();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionZoomFlipY);
};

/** @brief TransitionZoomFlipAngular:
 一半水平一半垂直  传入/穿出  翻转并一点点的缩放屏幕
 正面是传出的场景，背面是传入的场景。 
 */
class CC_DLL TransitionZoomFlipAngular : public TransitionSceneOriented
{
public:
    static TransitionZoomFlipAngular* create(float t, Scene* s, Orientation o);
    static TransitionZoomFlipAngular* create(float t, Scene* s);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

protected:
    TransitionZoomFlipAngular();
    virtual ~TransitionZoomFlipAngular();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionZoomFlipAngular);
};

/** @brief TransitionFade:
淡出传出 scene ，淡入传入 scene.'''
*/
class CC_DLL TransitionFade : public TransitionScene
{
public:
    /** 使用 duration、RGB 颜色 创建一个 transition（过渡）
     * Example: FadeTransition::create(2, scene, Color3B(255,0,0); //  红色
     */
    static TransitionFade* create(float duration, Scene* scene, const Color3B& color);
    static TransitionFade* create(float duration, Scene* scene);

    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;
    
CC_CONSTRUCTOR_ACCESS:
    TransitionFade();
    virtual ~TransitionFade();

    /** 使用 duration、RGB color 初始化一个 transition（过渡） */
    bool initWithDuration(float t, Scene*scene, const Color3B& color);
    bool initWithDuration(float t, Scene* scene);

protected:
    Color4B _color;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFade);

};

class RenderTexture;

/**
 @brief TransitionCrossFade:
 两个 scenes 使用 RenderTexture 对象交叉淡入淡出
 */
class CC_DLL TransitionCrossFade : public TransitionScene
{
public :
    static TransitionCrossFade* create(float t, Scene* scene);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;

protected:
    TransitionCrossFade();
    virtual ~TransitionCrossFade();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionCrossFade);
};

/** @brief TransitionTurnOffTiles:
 随机顺序关闭淡出场景的 tiles
 */
class CC_DLL TransitionTurnOffTiles : public TransitionScene ,public TransitionEaseScene
{
public :
    static TransitionTurnOffTiles* create(float t, Scene* scene);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual ActionInterval * easeActionWithAction(ActionInterval * action) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

protected:
    TransitionTurnOffTiles();
    virtual ~TransitionTurnOffTiles();

    virtual void sceneOrder() override;
    NodeGrid* _outSceneProxy;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionTurnOffTiles);
};

/** @brief TransitionSplitCols:
 奇数列向上推移而偶数列向下推移.
 */
class CC_DLL TransitionSplitCols : public TransitionScene , public TransitionEaseScene
{
public:
    static TransitionSplitCols* create(float t, Scene* scene);

    virtual ActionInterval* action();

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    virtual ActionInterval * easeActionWithAction(ActionInterval * action) override;
    virtual void onExit() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
protected:
    TransitionSplitCols();
    virtual ~TransitionSplitCols();
    void switchTargetToInscene();
    NodeGrid* _gridProxy;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSplitCols);
};

/** @brief TransitionSplitRows:
奇数行行从左侧推移，偶数行从右侧推移. 
 */
class CC_DLL TransitionSplitRows : public TransitionSplitCols
{
public:
    static TransitionSplitRows* create(float t, Scene* scene);

    //
    // 重写
    //
    virtual ActionInterval* action(void) override;

protected:
    TransitionSplitRows();
    virtual ~TransitionSplitRows();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSplitRows);
};

/** @brief TransitionFadeTR:
从从左下角到右上角淡出 scene 的所有 tiles.
 */
class CC_DLL TransitionFadeTR : public TransitionScene , public TransitionEaseScene
{
public:
    static TransitionFadeTR* create(float t, Scene* scene);

    virtual ActionInterval* actionWithSize(const Size& size);

    //
    // 重写
    //
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;
    virtual ActionInterval* easeActionWithAction(ActionInterval * action) override;
    virtual void onExit() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
protected:
    TransitionFadeTR();
    virtual ~TransitionFadeTR();

    virtual void sceneOrder();

    NodeGrid* _outSceneProxy;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFadeTR);
};

/** @brief TransitionFadeBL:
从右上角到左下角淡出 scene 的所有 tiles.
 */
class CC_DLL TransitionFadeBL : public TransitionFadeTR
{
public:
    static TransitionFadeBL* create(float t, Scene* scene);

    //
    // 重写
    //
    virtual ActionInterval* actionWithSize(const Size& size) override;

protected:
    TransitionFadeBL();
    virtual ~TransitionFadeBL();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFadeBL);
};

/** @brief TransitionFadeUp:
* 从下向上淡出 scene 的所有 tiles..
*/
class CC_DLL TransitionFadeUp : public TransitionFadeTR
{
public:
    static TransitionFadeUp* create(float t, Scene* scene);

    //
    // 重写
    //
    virtual ActionInterval* actionWithSize(const Size& size) override;

protected:
    TransitionFadeUp();
    virtual ~TransitionFadeUp();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFadeUp);
};

/** @brief TransitionFadeDown:
* 从上向下淡出 scene 的所有 tiles..
*/
class CC_DLL TransitionFadeDown : public TransitionFadeTR
{
public:
    static TransitionFadeDown* create(float t, Scene* scene);

    //
    // 重写
    //
    virtual ActionInterval* actionWithSize(const Size& size) override;

protected:
    TransitionFadeDown();
    virtual ~TransitionFadeDown();

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionFadeDown);

};

// end of transition group
/// @}

NS_CC_END

#endif // __CCTRANSITION_H__

