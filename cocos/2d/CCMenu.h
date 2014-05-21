/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
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
#ifndef __CCMENU_H_
#define __CCMENU_H_

#include "2d/CCMenuItem.h"
#include "2d/CCLayer.h"
#include "base/CCVector.h"
#include "base/CCEventTouch.h"
#include "base/CCValue.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu
 * @{
 */



/** @brief A Menu
* 
* 特征与限制:
*  - 你可以在运行的时候通过addChild函数添加MenuItem对象：
*  - 但是可以接受的子节点必须是MenuItem对象
*/
class CC_DLL Menu : public Layer
{
public:
    enum class State
    {
        WAITING,
        TRACKING_TOUCH,
    };
    
    /** 创建空的菜单 */
    static Menu* create();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    //WP8在VS2012中，不支持在可变参数列表中使用nullptr，也不支持可变参数模板
    typedef MenuItem* M;
    static Menu* create(M m1, std::nullptr_t listEnd) { return variadicCreate(m1, NULL); }
    static Menu* create(M m1, M m2, std::nullptr_t listEnd) { return variadicCreate(m1, m2, NULL); }
    static Menu* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    //在WP8平台上，当参数列表大于10项时，可以使用createWithArray或者以NULL作为最后一个参数的variadicCreate来创建菜单
    static Menu* variadicCreate(MenuItem* item, ...);
#else
    /** 用菜单项对象创建菜单 */
    static Menu* create(MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /** 用一组菜单项对象创建菜单*/
    static Menu* createWithArray(const Vector<MenuItem*>& arrayOfItems);

    /** creates a Menu with it's item, then use addChild() to add 
      * other items. It is used for script, it can't init with undetermined
      * number of variables.
    */
    /**用菜单项创建一个菜单，然后使用addChild()函数来添加其他的菜单项。
     * 对于脚本语言，不能使用不确定数量的变量来初始化
    */
    static Menu* createWithItem(MenuItem* item);
    
    /** 用菜单项对象来创建菜单 */
    static Menu* createWithItems(MenuItem *firstItem, va_list args);

    /** 使菜单项垂直排列 */
    void alignItemsVertically();
    /** 
     * 通过填补空白来调整菜单项垂直排列
    @since v0.7.2
    */
    void alignItemsVerticallyWithPadding(float padding);

    /** 使菜单项水平排列*/
    void alignItemsHorizontally();
    /**通过填补空白来调整菜单项水平排列
    @since v0.7.2
    */
    void alignItemsHorizontallyWithPadding(float padding);

    /** align items in rows of columns */
    /**使各列中的菜单项按指定的个数排列*/
    void alignItemsInColumns(int columns, ...) CC_REQUIRES_NULL_TERMINATION;
    void alignItemsInColumns(int columns, va_list args);
    void alignItemsInColumnsWithArray(const ValueVector& rows);

    /** align items in columns of rows */
    /**使各行中的菜单项按指定的个数排列*/
    void alignItemsInRows(int rows, ...) CC_REQUIRES_NULL_TERMINATION;
    void alignItemsInRows(int rows, va_list args);
    void alignItemsInRowsWithArray(const ValueVector& columns);

    virtual bool isEnabled() const { return _enabled; }
    virtual void setEnabled(bool value) { _enabled = value; };

    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    // 重载
    virtual void removeChild(Node* child, bool cleanup) override;
    
    virtual void addChild(Node * child) override;
    virtual void addChild(Node * child, int zOrder) override;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void setOpacityModifyRGB(bool bValue) override {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) const override { return false;}

    virtual std::string getDescription() const override;

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    Menu() : _selectedItem(nullptr) {}
    virtual ~Menu();

    /** 初始化一个空的菜单 */
    bool init();

    /**用以MenuItem对象为成员的Vecotor初始化菜单*/
    bool initWithArray(const Vector<MenuItem*>& arrayOfItems);

protected:



    /** 决定菜单能否接收事件的变量 */
    bool _enabled;

    MenuItem* getItemForTouch(Touch * touch);
    State _state;
    MenuItem *_selectedItem;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Menu);
};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif//__CCMENU_H_
