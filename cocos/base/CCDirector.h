/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2013 cocos2d-x.org
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

#ifndef __CCDIRECTOR_H__
#define __CCDIRECTOR_H__

#include "base/CCPlatformMacros.h"

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCGeometry.h"
#include "base/CCVector.h"
#include "CCGL.h"
#include "2d/CCLabelAtlas.h"
#include <stack>
#include "math/CCMath.h"

NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

/* Forward declarations. */
class LabelAtlas;
class Scene;
class GLView;
class DirectorDelegate;
class Node;
class Scheduler;
class ActionManager;
class EventDispatcher;
class EventCustom;
class EventListenerCustom;
class TextureCache;
class Renderer;

#if  (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
class Console;
#endif

/**
@brief 此类负责创建和操作主窗口，同时管理如何和何时执行场景(Scenes)
 
 Director 也负责以下:
  - 初始化 OpenGL 上下文
  - 设置 OpenGL像素格式 (默认值时 RGB565)
  - 设置 OpenGL 缓存大小 (默认是 0-bit)
  - 设置 投影 (默认是一个 3D)
  - 设置 方向 (默认是 Portrait)    //竖屏
 
 自从 Director 是一个 singleton, 标准的调用方法是:
 _ Director::getInstance()->methodName();
 
 Director 也设置默认的 OpenGL 上下文:
 - GL_TEXTURE_2D 可行的
 - GL_VERTEX_ARRAY 可行的
 - GL_COLOR_ARRAY 可行的
 - GL_TEXTURE_COORD_ARRAY 可行的

*/
enum class MATRIX_STACK_TYPE
{
    MATRIX_STACK_MODELVIEW,
    MATRIX_STACK_PROJECTION,
    MATRIX_STACK_TEXTURE
};

class CC_DLL Director : public Ref
{
private:
    std::stack<Mat4> _modelViewMatrixStack;
    std::stack<Mat4> _projectionMatrixStack;
    std::stack<Mat4> _textureMatrixStack;
protected:
    void initMatrixStack();
public:
    void pushMatrix(MATRIX_STACK_TYPE type);
    void popMatrix(MATRIX_STACK_TYPE type);
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);
    void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    Mat4 getMatrix(MATRIX_STACK_TYPE type);
    void resetMatrixStack();
public:
    static const char *EVENT_PROJECTION_CHANGED;
    static const char* EVENT_AFTER_UPDATE;
    static const char* EVENT_AFTER_VISIT;
    static const char* EVENT_AFTER_DRAW;


    /** @typedef ccDirectorProjection
     导演(director)可能使用 OpenGL 的投影
     */
    enum class Projection
    {
        /// 设定的二维投影（正投影orthogonal projection)
        _2D,
        
        /// 使用 fovy=60, znear=0.5f and zfar=1500 设置一个3D投影.sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
        _3D,
        
        /// 投影委托里面它调用 "updateProjection".
        CUSTOM,
        
        /// 默认投影是 3D 投影
        DEFAULT = _3D,
    };
    
    /** 返回导演(Director)的共享实例 */
    static Director* getInstance();

    /** @deprecated 使用 getInstance() 替代 */
    CC_DEPRECATED_ATTRIBUTE static Director* sharedDirector() { return Director::getInstance(); }
    /**
     * @js ctor
     */
    Director(void);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Director();
    virtual bool init();

    // 属性

    /** 获取当前运行的场景(Scene). Director 在这个时候只能运行一个场景. */
    inline Scene* getRunningScene() { return _runningScene; }

    /** Get  FPS 值 */
    inline double getAnimationInterval() { return _animationInterval; }
    /** Set FPS 值. */
    virtual void setAnimationInterval(double interval) = 0;

    /**是否在左下角显示 FPS */
    inline bool isDisplayStats() { return _displayStats; }
    /** 在左下角显示 FPS */
    inline void setDisplayStats(bool displayStats) { _displayStats = displayStats; }
    
    /** 每帧秒 */
    inline float getSecondsPerFrame() { return _secondsPerFrame; }

    /**  获取渲染所有东西的 EGLView
    * @js NA
    * @lua NA
    */
    inline GLView* getOpenGLView() { return _openGLView; }
    void setOpenGLView(GLView *openGLView);

    TextureCache* getTextureCache() const;

    inline bool isNextDeltaTimeZero() { return _nextDeltaTimeZero; }
    void setNextDeltaTimeZero(bool nextDeltaTimeZero);

    /** Director 是否被暂停 */
    inline bool isPaused() { return _paused; }

    /** director 开始到现在持续了多少帧 */
    inline unsigned int getTotalFrames() { return _totalFrames; }
    
    /** 设置一个 OpenGL 投影
     @since v0.8.2
     * @js NA
     * @lua NA
     */
    inline Projection getProjection() { return _projection; }
    void setProjection(Projection projection);
    
    /** 设置 glViewport*/
    void setViewport();

    /** director 开始到现在持续了多少帧 */
    
    
    /** 场景是否收到替换清楚的消息
     如果新的场景已经被 pushed （推出），那么旧的场景将不会收到“执行清理”("cleanup")的消息。
     如果新的场景替换了旧的，它会收到“执行清理”("cleanup")消息。
     @since v0.99.0
     */
    inline bool isSendCleanupToScene() { return _sendCleanupToScene; }

    /** 主场景访问后这个对象将被访问
     这个对象必须实现"访问"("visit") 选择器.
     和通知对象挂钩, 像这个 Notifications (http://github.com/manucorporat/CCNotifications)
     @since v0.99.5
     */
    Node* getNotificationNode() const { return _notificationNode; }
    void setNotificationNode(Node *node);
    
    //窗口大小

    /** 返回以点为单位的 OpenGL 视图的大小.
    */
    const Size& getWinSize() const;

    /** 返回以像素为单位的 OpenGL 视图的大小.
    */
    Size getWinSizeInPixels() const;
    
    /** returns 以点为单位的 OpenGL 视图的可见大小.
     *  如果不调用 EGLView::setDesignResolutionSize() 值等于 getWinSize
     */
    Size getVisibleSize() const;
    
    /** returns 以点为单位的 OpenGL 视图的初始化时的可见大小
     */
    Vec2 getVisibleOrigin() const;

    /** UIKit的坐标转换到一个OpenGL坐标
     *  使用当前布局（横向或纵向）有效的（多）触摸坐标
     */
    Vec2 convertToGL(const Vec2& point);

    /** 一个OpenGL坐标转换到UIKit的坐标
     点组成的窗口调用有效的节点上面的点，例如 glScissor
     */
    Vec2 convertToUI(const Vec2& point);

    /// XXX: 缺少描述
    float getZEye() const;

    //场景管理

    /** 根据给定的场景进入 Director的主循环
     * 只能调用他运行你的第一个场景.
     * 如果已经有一个场景在运行了就不要在调用他来
     *
     * 它将调用pushScene：然后它会调用startAnimation
     */
    void runWithScene(Scene *scene);

    /** 暂停执行正在运行的场景中，pushing一个在堆栈上推暂停的场景。
     * 新的场景将被执行.
     * 尽量避免在堆栈上存放一个很大的场景以减少内存非陪，
     * 仅在有一个正在运行的场景的时候调用他.
     */
    void pushScene(Scene *scene);

    /** 从队列中弹出一个场景。
     * 这个场景将替换正在运行的场景.
     * 正在运行的场景将被删除。如果有堆栈中没有其它的场景那么 popScene 的执行会被终止。
     * 仅在有一个正在运行的场景的时候调用他.
     */
    void popScene();

    /** 从队列中弹出所有的场景，直到只有根场景在队列中
     * 这个场景将替换正在运行的场景.
     * 在内部塌毁调用 `popToSceneStackLevel(1)`
     */
    void popToRootScene();

    /** 弹出从队列中的所有场景，直到它到达 `level`.
     如果 level 是 0,它将结束 director.
     如果 level 是 1, 从队列中弹出所有的场景，直到只有根场景在队列中
     如果 level <= 当前的堆栈水平，它不会做任何事情。
     */
 	void popToSceneStackLevel(int level);

    /** 用一个新的替换正在运行的场景。终止正在运行的场景。
     * 仅在有一个正在运行的场景的时候调用他.
     */
    void replaceScene(Scene *scene);

    /** 结束执行，释放正在运行的场景。
     它不会从其父视图中删除的OpenGL视图。你有做手工。
     * @lua endToLua
     */
    void end();

    /** 暂停正在运行的场景。.
     正在运行的场景将被绘制，的所有预定的定时器将被暂停
     暂停时，绘制周期将只有4个FPS，以降低CPU消耗
     */
    void pause();

    /** 恢复暂停的场景
     预定的定时器将被再次激活。
     “推迟执行”的时间将是0（如果游戏没有暂停）
     */
    void resume();

    /** 停止动画，什么也不画. 主循环线程再也不会被触发.
     如果你不希望那样，那么就用暂停你的游戏代替
     */
    virtual void stopAnimation() = 0;

    /** 主循环线程重新被触发发.
     这个函数只在你已经调用 [stopAnimation] 函数的时候调用
     @warning 不要使用这个函数启动主线程循环. 请使用 主线程调用 runWithScene
     */
    virtual void startAnimation() = 0;

    /** 绘制场景.
     这个方法每一帧都会调用，不要手动调用这个方法.
     */
    void drawScene();

    // 内存助手
    /** 移除所有 cocos2d 缓存数据.
     他将清楚 TextureCache, SpriteFrameCache, LabelBMFont 缓存
     @since v0.99.3
     */
    void purgeCachedData();

	/** 设置配置信息的默认值 */
    void setDefaultValues();

    // OpenGL 助手

    /** 设置 OpenGL 默认值 */
    void setGLDefaultValues();

    /** 启用/禁用 OpenGL alpha 混合 */
    void setAlphaBlending(bool on);

    /** 启用/禁用 OpenGL 深度测试 */
    void setDepthTest(bool on);

    virtual void mainLoop() = 0;

    /** 基于像素的 surface 尺寸. 它可以和屏幕尺寸不同        //表面
     High-res 设备或许有一个高于屏幕尺寸的 surface 尺寸
     只在编译 SDK >= 4.0 时有效.
     @since v0.99.4
     */
    void setContentScaleFactor(float scaleFactor);
    float getContentScaleFactor() const { return _contentScaleFactor; }

    /** 获取和这个 director 关联的调度器
     @since v2.0
     */
    Scheduler* getScheduler() const { return _scheduler; }
    
    /** 设置和这个 director 关联的调度器
     @since v2.0
     */
    void setScheduler(Scheduler* scheduler);

    /** 获取和这个 director 关联的 ActionManager
     @since v2.0
     */
    ActionManager* getActionManager() const { return _actionManager; }
    
    /** 设置和这个 director 关联的 ActionManager
     @since v2.0
     */
    void setActionManager(ActionManager* actionManager);
    
    /** 获取和这个director 关联的EventDispatcher
     @since v3.0
     */
    EventDispatcher* getEventDispatcher() const { return _eventDispatcher; }
    
    /** 设置和这个director 关联的EventDispatcher
     @since v3.0
     */
    void setEventDispatcher(EventDispatcher* dispatcher);

    /** 返回渲染器(Renderer)
     @since v3.0
     */
    Renderer* getRenderer() const { return _renderer; }

    /** 返回控制台(Console)
     @since v3.0
     */
#if  (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    Console* getConsole() const { return _console; }
#endif

    /* 获取主循环线程之间的延迟时间 */
	float getDeltaTime() const;
    
    /**
     *  获取帧频率(Frame Rate)
     */
    float getFrameRate() const { return _frameRate; }

protected:
    void purgeDirector();
    bool _purgeDirectorInNextLoop; // 在 end() 这个参数将会被设置成
    
    void setNextScene();
    
    void showStats();
    void createStatsLabel();
    void calculateMPF();
    void getFPSImageData(unsigned char** datapointer, ssize_t* length);
    
    /**计算上次和这次主循环线程之间的延迟时间 */
    void calculateDeltaTime();

    //纹理缓存(textureCache)创建和释放
    void initTextureCache();
    void destroyTextureCache();

    /** 和 director 关联的调度器(Scheduler)
     @since v2.0
     */
    Scheduler *_scheduler;
    
    /** 和 director 关联的ActionManager
     @since v2.0
     */
    ActionManager *_actionManager;
    
    /** 和 director 关联的事件派发器(EventDispatcher)
     @since v3.0
     */
    EventDispatcher* _eventDispatcher;
    EventCustom *_eventProjectionChanged, *_eventAfterDraw, *_eventAfterVisit, *_eventAfterUpdate;
        
    /* 自从上次触发主循环线程的延迟时间 */
	float _deltaTime;
    
    /* GLView, 渲染一切东西地方 */
    GLView *_openGLView;

    //属于该director的纹理缓存(texture cache)
    TextureCache *_textureCache;

    double _animationInterval;
    double _oldAnimationInterval;

    /* 横屏模式 ? */
    bool _landscape;
    
    bool _displayStats;
    float _accumDt;
    float _frameRate;
    
    LabelAtlas *_FPSLabel;
    LabelAtlas *_drawnBatchesLabel;
    LabelAtlas *_drawnVerticesLabel;
    
    /** Director 是否暂停了 */
    bool _paused;

    /* director 启动后到现在经过了多少帧 */
    unsigned int _totalFrames;
    unsigned int _frames;
    float _secondsPerFrame;
    
    /* 正在运行的场景 */
    Scene *_runningScene;
    
    /* 下一帧将要运行的场景，下一帧将要运行的场景是弱引用. */
    Scene *_nextScene;
    
    /* true, 那么 "old" 旧的场景会收到清除消息 */
    bool _sendCleanupToScene;

    /* 调度场景scenes的集合 */
    Vector<Scene*> _scenesStack;
    
    /* 主循环线程上次更新但时间 */
    struct timeval *_lastUpdate;

    /*是否将下次但延迟时间设置为0 */
    bool _nextDeltaTimeZero;
    
    /* 使用的投影 */
    Projection _projection;

    /* 点组成的窗口尺寸 */
    Size _winSizeInPoints;
    
    /* 内容比例因子 */
    float _contentScaleFactor;

    /* 主场景访问后这个对象将被访问，和通知对象挂钩 */
    Node *_notificationNode;

    /* Director的渲染器(Renderer) */
    Renderer *_renderer;

#if  (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    /* director的控制台Console */
    Console *_console;
#endif

    // GLViewProtocol 将重新创建状态标签，以适应可见部分矩形
    friend class GLViewProtocol;
};


/**
 @brief DisplayLinkDirector是一个Director的子类, 表示屏幕刷新速率的同步定时器
 
 特点和局限性:
 - 调度定时器(Scheduled timers) & 绘制和屏幕刷新速率保持同步
 - 只支持动画间隔时 1/60 1/30 & 1/15 的情况
 
 @since v0.8.2
 */
class DisplayLinkDirector : public Director
{
public:
    DisplayLinkDirector() 
        : _invalid(false)
    {}
    virtual ~DisplayLinkDirector(){}

    //
    // Overrides
    //
    virtual void mainLoop() override;
    virtual void setAnimationInterval(double value) override;
    virtual void startAnimation() override;
    virtual void stopAnimation() override;

protected:
    bool _invalid;
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCDIRECTOR_H__
