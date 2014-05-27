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

#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

/**
 *  @js NA
 *  @lua NA
 */
class LayoutExecutant;
    
class Layout : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class Type
    {
        ABSOLUTE,
        VERTICAL,
        HORIZONTAL,
        RELATIVE
    };
    
    enum class ClippingType
    {
        STENCIL,
        SCISSOR
    };
    
    enum class BackGroundColorType
    {
        NONE,
        SOLID,
        GRADIENT
    };
    
    /**
     * 默认构造函数（constructor）
     */
    Layout();
    
    /**
     * 默认析构函数（destructor）
     */
    virtual ~Layout();
    
    /**
     * 分配（Allocates）并初始化（initializes）一个布局（layout）.
     */
    static Layout* create();
    
    //背景
    /**
     * 为layout设置一个背景图片
     *
     * @param 图片路径及文件名.
     *
     * @param texType @see TextureResType. UI_TEX_TYPE_LOCAL 意为本地文件, UI_TEX_TYPE_PLIST 意为精灵帧（sprite frame）.
     */
    void setBackGroundImage(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * 如果背景图使用九宫（scale9）渲染（render）,为layout的背景图片设置一个capinsets.
     *
     * @param 背景图片的capinsets.
     *
     */
    void setBackGroundImageCapInsets(const Rect& capInsets);
    
    const Rect& getBackGroundImageCapInsets();
    
    /**
     * 为layout设置颜色类型（Color Type）.
     *
     * @param type   @see LayoutBackGroundColorType.
     */
    void setBackGroundColorType(BackGroundColorType type);
    
    BackGroundColorType getBackGroundColorType();
    
    /**
     * 使用九宫渲染器（scale9 renderer）设置背景图片.
     *
     * @param enabled   true 为使用九宫渲染器（scale9 renderer）, false 为不使用.
     */
    void setBackGroundImageScale9Enabled(bool enabled);
    
    bool isBackGroundImageScale9Enabled();
    
    /**
     * 如果颜色类型（color type）为LAYOUT_COLOR_SOLID，为layout设置背景颜色.
     *
     * @param color
     */
    void setBackGroundColor(const Color3B &color);
    
    const Color3B& getBackGroundColor();
    
    /**
     * 如果颜色类型（color type）为LAYOUT_COLOR_GRADIENT，为layout设置背景颜色.
     *
     * @param 起始颜色
     *
     * @param 结束颜色
     */
    void setBackGroundColor(const Color3B &startColor, const Color3B &endColor);
    
    const Color3B& getBackGroundStartColor();
    
    const Color3B& getBackGroundEndColor();
    
    /**
     * 为layout的背景设置不透明度（opacity）.
     *
     * @param opacity
     */
    void setBackGroundColorOpacity(GLubyte opacity);
    
    GLubyte getBackGroundColorOpacity();
    
    /**
     * 如果颜色类型（color type）是 LAYOUT_COLOR_GRADIENT，为layout设置矢量（vector）背景色 
     *
     * @param vector
     */
    void setBackGroundColorVector(const Vec2 &vector);
    
    const Vec2& getBackGroundColorVector();
    
    void setBackGroundImageColor(const Color3B& color);
    
    void setBackGroundImageOpacity(GLubyte opacity);
    
    const Color3B& getBackGroundImageColor();
    
    GLubyte getBackGroundImageOpacity();
    
    /**
     * 删除layout的背景图片.
     */
    void removeBackGroundImage();
    
    /**
     * 获取背景纹理（texture）贴图的尺寸.
     *
     * @return 背景纹理（texture）贴图尺寸.
     */
    const Size& getBackGroundImageTextureSize() const;
    
    /**
     * 改变layout可裁剪（clip）其内容（content）及child.
     *
     * 如果真的需要此方法，请使其为可用（enable）.但此方法会影响渲染效率（rendering efficiency）.
     *
     * @param  使裁剪（clipping）可用.
     */
    virtual void setClippingEnabled(bool enabled);
    
    void setClippingType(ClippingType type);
    
    ClippingType getClippingType();
    
    /**
     * 获取layout的裁剪（clipping）是否为可用.
     *
     * @return layout的裁剪（clipping）是否为可用.
     */
    virtual bool isClippingEnabled();
    
    /**
     * 返回widget的“类名（class name）”
     */
    virtual std::string getDescription() const override;
    

    virtual void setLayoutType(Type type);
    
    virtual  Type getLayoutType() const;

    virtual void addChild(Node * child) override;
    /**
     * 添加一个child（定义其z轴次序（z-order））到容器（container）中.
     *
     * 如果child被添加到一个“运行中（running）”的节点（node），则'onEnter'和'onEnterTransitionDidFinish'方法将被立即调用.
     *
     * @param child     一个子节点（child node）
     * @param zOrder    z轴次序（Z order）决定绘制优先级. 请参照setLocalZOrder(int)
     */
    virtual void addChild(Node * child, int zOrder) override;
    /**
     * 添加一个child（定义其z order及tag）到容器（container）中.
     *
     * 如果child被添加到一个“运行中（running）”的节点（node），则'onEnter'和'onEnterTransitionDidFinish'方法将被立即调用.
     *
     * @param child     一个子节点（child node）
     * @param zOrder   z轴次序（Z order）决定绘制优先级. 请参照setLocalZOrder(int)
     * @param tag       tag指定node的id，一般为整数. 请参照setTag(int)
     */
    virtual void addChild(Node* child, int zOrder, int tag) override;
    
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;

    virtual void removeChild(Node* child, bool cleanup = true) override;
    
    /**
     * 使用cleanup清空容器（container）中的所有子节点（children）
     *
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren() override;
    /**
    * 清空容器（container）中的所有子节点（children），同时也清空所有运行中的动作（取决于cleanup的参数）.
     *
     * @param cleanup   为 true 时所有运行中的动作及容器中的子节点都将被清空, 为 false 则不会.
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;

    virtual void sortAllChildren() override;
    
    void requestDoLayout();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    /**
     * 如果一个layout开启了循环集中（loop focused），则意味着此焦点（focus）将在此layout内部运动.
     *@param loop pass  为 true 时使焦点（focus）在layout内部循环运动（movement loop）.
     */
    void setLoopFocus(bool loop);
    
    /**
     *@return  如果焦点循环（focus loop）是可用的（enabled），则返回true，否则将返回 false. 默认值是 false.
     */
    bool isLoopFocus();
    
    /**
     *@param pass 指定是否将layout的焦点（focus）传递给其child.
     */
    void setPassFocusToChild(bool pass);
    
    /**
     * @return  查询（query）是否layout将传递其焦点（focus）给其children.默认值为true.
     */
    bool isPassFocusToChild();
    
    /**
     * 当一个widget在一个layout中，你可以调用此方法在指定的方向（specified direction）来获取下一个被聚焦的（focused）widget.
     * 如果此widget不在layout中，它将返回它自己（itself）.
     *@param  指示出在layout中寻找下一个被聚焦（focused）的widget的方向.
     *@param current  现在正被聚焦（focused）的widget
     *@return   layout中下一个被聚焦（focused）的widget
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current) override;
    
    /**
     * 指定一个用户定义函数（user-defined functor），以确定哪个layout的子widget将被聚焦（focused）.
     * @param  FocusDirection 查找方向.
     * @param  上一个被聚焦（focused）的 widget
     * @return  返回layout中widget的索引（index）.
     */
    std::function<int(FocusDirection, Widget*)> onPassFocusToChild;

CC_CONSTRUCTOR_ACCESS:
    //重写 widget 的 "init" 方法.
    virtual bool init() override;
    
protected:
    //重写 widget 的 "onSizeChanged" 方法.
    virtual void onSizeChanged() override;
    
    //初始化背景图像渲染器.
    void addBackGroundImage();
    
    void supplyTheLayoutParameterLackToChild(Widget* child);
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    
    void stencilClippingVisit(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated);
    void scissorClippingVisit(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated);
    
    void setStencilClippingSize(const Size& size);
    const Rect& getClippingRect();
    virtual void doLayout();
    
    //clipping
    void onBeforeVisitStencil();
    void onAfterDrawStencil();
    void onAfterVisitStencil();
    
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
    void updateBackGroundImageColor();
    void updateBackGroundImageOpacity();
    void updateBackGroundImageRGBA();
    LayoutExecutant* createCurrentLayoutExecutant();
    
    /**
     * 获取layout的内容大小（size），它将积累（accumulate）所有子节点（children）的内容大小.
     */
    Size getLayoutContentSize() const;
    
    /**
     * 当layout获得焦点，layout要传递焦点（focus）给其child，它将使用此方法判定传递给哪个child.
     * 将得到焦点（focus）.当前的算法（algorithm）决定哪个child 将得到焦点（focus）是最近距离优先算法（nearest-distance-priority algorithm）.
     * @param 指出下一个聚焦的（focused） widget 的方向（direction）.
     * @return 容器（container）中child widget的索引（index）.
     */
     int findNearestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * 当layout获得焦点，layout要传递焦点（focus）给其child，它将使用此方法判定传递给哪个child.
     * 将得到焦点（focus）.当前的算法（algorithm）决定哪个child 将得到焦点（focus）是最近距离优先算法（nearest-distance-priority algorithm）.
     *@param 指出下一个聚焦的（focused） widget 的方向（direction）.
     *@return 容器（container）中child widget的索引（index）.
     */
    int findFarestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * 计算 baseWidget 和 layout 的 children 之间的最近距离.
     *@param  base widget被用来计算layout的children和它自己（指base widget.译者注）间的距离.
     *@return  返回 baseWidget 和 layout 的 children 之间的最近距离.
     */
    float caculateNearestDistance(Widget* baseWidget);
    
    /**
     * 计算 baseWidget 和 layout 的 children 之间的最远距离.
     *@param base widget被用来计算layout的children和它自己（指base widget.译者注）间的距离.
     *@return 返回 baseWidget 和 layout 的 children 之间的最远距离.
     */

    float caculateFarestDistance(Widget* baseWidget);
    
    /**
     *  当layout传递焦点（focus）给其child，使用此方法确定使用哪种算法（algorithm），使用最近距离（nearest）或者最远距离（farest）算法，或者都不使用.
     */
    void findProperSearchingFunctor(FocusDirection dir, Widget* baseWidget);
    
    /**
     * 在此layout中查找第一个 non-layout widget 
     */
    Widget *findFirstNonLayoutWidget();
    
    /**
     * 在layout中查找第一个焦点可用（focus enabled）的 widget 索引（index）, 它将递回（recusive） 搜索到的 child widget
     */
    int findFirstFocusEnabledWidgetIndex();
    
    /**
     * 通过索引（index）在layout中查找焦点可用（focus enabled）的child Widget
     */
    Widget* findFocusEnabledChildWidgetByIndex(ssize_t index);
    
    /**
     * 在世界坐标空间（world space）中获取一个widget的中点（center point）
     */
    Vec2 getWorldCenterPoint(Widget* node);
    
    /**
     * 这个方法将被nextFocusedWidget立即调用. 当方向为右/下（Right/Down）时, 此方法将被调用.
     *@param dir  方向.
     *@param current  当前聚焦的widget
     *@return  下一个聚焦的widget
     */
    Widget* getNextFocusedWidget(FocusDirection direction,Widget *current);
    
    /**
     * 这个方法将被nextFocusedWidget立即调用. 当方向为左/上（Left/Up）时, 此方法将被调用.
     *@param dir  方向.
     *@param current  当前聚焦的widget
     *@return  下一个聚焦的widget
     */
    Widget* getPreviousFocusedWidget(FocusDirection direction, Widget *current);
    
    /**
     * 在 _children 数组中找到第n个元素. 仅返回 Widget 的子孙（descendant）对象.
     *@param index  _children 数组中元素的索引.
     */
    Widget* getChildWidgetByIndex(ssize_t index);
    /**
     * 根据所有父元素（parents）判断是否为最后的元素.
     */
    bool  isLastWidgetInContainer(Widget* widget, FocusDirection direction);
    
    /**查找任何使用布局（layout）类型作为方向的父 widget .
     * 如果layout循环获得焦点（loop focused），则返回true，否则返回false
     */
    bool  isWidgetAncestorSupportLoopFocus(Widget* widget, FocusDirection direction);
    
    /**
     * 传递焦点（focus）给layout的下一个焦点可用（focus enabled）的child
     */
    Widget* passFocusToChild(FocusDirection direction, Widget* current);
    
    /**
     * 如果在layout中没有焦点可用（focus enabled）的child，它将返回false，否则返回true.
     */
    bool checkFocusEnabledChild();
    
protected:
    bool _clippingEnabled;
    
    //background
    bool _backGroundScale9Enabled;
    Node* _backGroundImage;
    std::string _backGroundImageFileName;
    Rect _backGroundImageCapInsets;
    BackGroundColorType _colorType;
    TextureResType _bgImageTexType;
    LayerColor* _colorRender;
    LayerGradient* _gradientRender;
    Color3B _cColor;
    Color3B _gStartColor;
    Color3B _gEndColor;
    Vec2 _alongVector;
    GLubyte _cOpacity;
    Size _backGroundImageTextureSize;
    Type _layoutType;
    ClippingType _clippingType;
    DrawNode* _clippingStencil;
    bool _scissorRectDirty;
    Rect _clippingRect;
    Layout* _clippingParent;
    bool _doLayoutDirty;
    bool _clippingRectDirty;
    
    //clipping

    GLboolean _currentStencilEnabled;
    GLuint _currentStencilWriteMask;
    GLenum _currentStencilFunc;
    GLint _currentStencilRef;
    GLuint _currentStencilValueMask;
    GLenum _currentStencilFail;
    GLenum _currentStencilPassDepthFail;
    GLenum _currentStencilPassDepthPass;
    GLboolean _currentDepthWriteMask;
    
    GLboolean _currentAlphaTestEnabled;
    GLenum _currentAlphaTestFunc;
    GLclampf _currentAlphaTestRef;
    
    
    Color3B _backGroundImageColor;
    GLubyte _backGroundImageOpacity;
    
    LayoutExecutant* _curLayoutExecutant;
    
    GLint _mask_layer_le;
    GroupCommand _groupCommand;
    CustomCommand _beforeVisitCmdStencil;
    CustomCommand _afterDrawStencilCmd;
    CustomCommand _afterVisitCmdStencil;
    CustomCommand _beforeVisitCmdScissor;
    CustomCommand _afterVisitCmdScissor;
    
    bool _loopFocus; //是否启用循环集中(loop focus)
    bool _passFocusToChild;  //默认会传递焦点(focus)给下一个最近的widget
};
    
}
NS_CC_END
#endif /* defined(__Layout__) */
