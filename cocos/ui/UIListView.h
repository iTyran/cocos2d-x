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


#ifndef __UILISTVIEW_H__
#define __UILISTVIEW_H__

#include "ui/UIScrollView.h"

NS_CC_BEGIN

namespace ui{
    
CC_DEPRECATED_ATTRIBUTE typedef enum
{
    LISTVIEW_ONSELECTEDITEM_START,
    LISTVIEW_ONSELECTEDITEM_END
}ListViewEventType;

CC_DEPRECATED_ATTRIBUTE typedef void (Ref::*SEL_ListViewEvent)(Ref*,ListViewEventType);
#define listvieweventselector(_SELECTOR) (SEL_ListViewEvent)(&_SELECTOR)

class ListView : public ScrollView
{
 
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class Gravity
    {
        LEFT,
        RIGHT,
        CENTER_HORIZONTAL,
        TOP,
        BOTTOM,
        CENTER_VERTICAL
    };
    
    enum class EventType
    {
        ON_SELECTED_ITEM_START,
        ON_SELECTED_ITEM_END
    };
    
    typedef std::function<void(Ref*, EventType)> ccListViewCallback;
    
    /**
     * 默认构造函数(Default constructor)
     */
    ListView();
    
    /**
     * 默认析构函数（Default destructor）
     */
    virtual ~ListView();
    
    /**
     * 分配（Allocates）并初始化（initializes）.
     */
    static ListView* create();
    
    /**
     * 为列表视图（listview）设置一个项目模型（item model）
     *
     * 此模型（model）即为添加默认项目（item）的模板
     *
     * @param model  listview的项目模型（item model）
     */
    void setItemModel(Widget* model);
    
    /**
     * 推回一个默认项目（使用模型（cloned model）创建）到列表视图（listview）
     */
    void pushBackDefaultItem();
    
    /**
     * 插入一个默认项目（使用模型（cloned model）创建）到列表视图（listview）
     */
    void insertDefaultItem(ssize_t index);
    
    /**
     * 推回自定义项目到列表视图（listview）
     */
    void pushBackCustomItem(Widget* item);
    
    /**
     * 插入自定义项目到列表视图（listview）
     */
    void insertCustomItem(Widget* item, ssize_t index);
    
    /**
     * 删除listview的最后一个项目（item）
     */
    void removeLastItem();
    
    /**
     * 删除索引与参数相同的项
     *
     * @param 项目的索引.
     */
    void removeItem(ssize_t index);
    
    void removeAllItems();
    
    /**
     * 返回索引与参数相同的项
     *
     * @param 项目的索引
     *
     * @return 项目widget.
     */
    Widget* getItem(ssize_t index);
    
    /**
     *返回项目容器（the item container）
     */
    Vector<Widget*>& getItems();
    
    /**
     * 返回项目的索引
     *
     * @param item  需被检查的项目.
     *
     * @return 项目的索引.
     */
    ssize_t getIndex(Widget* item) const;
    
    /**
     * 改变列表视图（listview）的重力（gravity）
     * @see ListViewGravity
     */
    void setGravity(Gravity gravity);
    
    /**
     * 改变项目（item）间的外边距（margin）
     *
     * @param margin
     */
    void setItemsMargin(float margin);
    
    float getItemsMargin();
    
    virtual void sortAllChildren() override;
    
    ssize_t getCurSelectedIndex() const;
    
    CC_DEPRECATED_ATTRIBUTE void addEventListenerListView(Ref* target, SEL_ListViewEvent selector);
    void addEventListener(const ccListViewCallback& callback);
    
    /**
     * 改变scrollview的滚动方向
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL 意为垂直滚动（vertical scroll）, SCROLLVIEW_DIR_HORIZONTAL 意为横向滚动（horizontal scroll）
     *
     * @param SCROLLVIEW_DIR
     */
    virtual void setDirection(Direction dir) override;
    
    virtual std::string getDescription() const override;
    
    void requestRefreshView();
    void refreshView();

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void addChild(Node* child) override{ScrollView::addChild(child);};
    virtual void addChild(Node * child, int zOrder) override{ScrollView::addChild(child, zOrder);};
    virtual void addChild(Node* child, int zOrder, int tag) override{ScrollView::addChild(child, zOrder, tag);};
    virtual void removeChild(Node* widget, bool cleanup = true) override{ScrollView::removeChild(widget, cleanup);};
    
    virtual void removeAllChildren() override{removeAllChildrenWithCleanup(true);};
    virtual void removeAllChildrenWithCleanup(bool cleanup) override {ScrollView::removeAllChildrenWithCleanup(cleanup);};
    virtual Vector<Node*>& getChildren() override{return ScrollView::getChildren();};
    virtual const Vector<Node*>& getChildren() const override{return ScrollView::getChildren();};
    virtual ssize_t getChildrenCount() const override {return ScrollView::getChildrenCount();};
    virtual Node * getChildByTag(int tag) override {return ScrollView::getChildByTag(tag);};
    virtual Widget* getChildByName(const std::string& name) override {return ScrollView::getChildByName(name);};
    void updateInnerContainerSize();
    void remedyLayoutParameter(Widget* item);
    virtual void onSizeChanged() override;
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    void selectedItemEvent(int state);
    virtual void interceptTouchEvent(int handleState,Widget* sender,const Vec2 &touchPoint) override;
protected:
    
    Widget* _model;
    Vector<Widget*> _items;
    Gravity _gravity;
    float _itemsMargin;
    
    Ref*       _listViewEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_ListViewEvent    _listViewEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    ccListViewCallback _eventCallback;
    
    ssize_t _curSelectedIndex;
    bool _refreshViewDirty;
};

}
NS_CC_END

#endif /* defined(__ListView__) */
