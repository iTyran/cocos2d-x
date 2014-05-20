/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
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

#ifndef __CCMENU_ITEM_H__
#define __CCMENU_ITEM_H__

// C++ includes
#include <functional>

// cocos2d includes
#include "2d/CCNode.h"
#include "2d/CCProtocols.h"

NS_CC_BEGIN

typedef std::function<void(Ref*)> ccMenuCallback;

class Label;
class LabelAtlas;
class Sprite;
class SpriteFrame;
#define kItemSize 32
    
/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu
 * @{
 */

/** @brief MenuItem base class
 *
 *  可以继承MenuItem创建自定义MenuItem
 */
class CC_DLL MenuItem : public Node
{
public:
    /** 创建一个空MenuItem */
    static MenuItem* create();
    /** 创建一个具有target/selector的MenuItem */
    CC_DEPRECATED_ATTRIBUTE static MenuItem* create(Ref *rec, SEL_MenuHandler selector);
    /** 创建一个具有target/selector的MenuItem */
    static MenuItem* create(const ccMenuCallback& callback);

    /** 返回外边框 */
    Rect rect() const;
    /** 激活item */
    virtual void activate();
    /** 选中item(注:未激活), 类似于鼠标点击完毕状态 */
    virtual void selected();
    /** 取消选中的item */
    virtual void unselected();
    /** 返回item是否可用 */
    virtual bool isEnabled() const;
    /** 设置item是否可用 */
    virtual void setEnabled(bool value);
    /** 返回item是否选中 */
    virtual bool isSelected() const;

    /** 设置menu item的回调
    * @code
    * js中，包含两个参数，其中第二个参数为jsptr
    * @endcode
    * @lua NA
    */
    void setCallback(const ccMenuCallback& callback);
    /** 设置menu item的target/selector
    * @js NA
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE void setTarget(Ref *rec, SEL_MenuHandler selector);


    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItem()
    : _selected(false)
    , _enabled(false)
	, _callback(nullptr)
    , _target(nullptr)
    {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItem();
    
    /** 初始化具有target/selector的MenuItem
     * @js NA
     * @lua NA
     */
    bool initWithCallback(const ccMenuCallback& callback);
    /** 初始化具有target/selector的MenuItem
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref *rec, SEL_MenuHandler selector);

protected:
    bool            _selected;
    bool            _enabled;
	// 回调
	ccMenuCallback _callback;
	// 如果使用的是旧的API，那么_target需要retained / released
	Ref		*_target;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItem);
};

/** @brief An abstract class for "label" MenuItemLabel items 
	任何支持LabelProtocol协议都可以被加入
	支持的Nodes如下：
 - BitmapFontAtlas
 - LabelAtlas
 - LabelTTF
 - Label
 */
class CC_DLL MenuItemLabel : public MenuItem
{
public:
    /** 创建一个具有Label,target和selector的MenuItemLabel */
    CC_DEPRECATED_ATTRIBUTE static MenuItemLabel * create(Node*label, Ref* target, SEL_MenuHandler selector);

	  /** 创建一个具有Label和callback的MenuItemLabel */
    static MenuItemLabel * create(Node*label, const ccMenuCallback& callback);

    /** 创建一个具有Label,Target和selector为nil的MenuItemLabel */
    static MenuItemLabel* create(Node *label);

    /** 设置inner label的新string */
    void setString(const std::string& label);

    /** 获取item禁用状态时的颜色值 */
    inline const Color3B& getDisabledColor() const { return _disabledColor; };

    /** 设置item禁用状态时的颜色值 */
    inline void setDisabledColor(const Color3B& color) { _disabledColor = color; };
    
    /** 获取被渲染的label. */
    inline Node* getLabel() const { return _label; };
    
    /** 设置需要渲染的label. */
    void setLabel(Node* node);
    
    // Overrides
    virtual void activate() override;
    virtual void selected() override;
    virtual void unselected() override;
    virtual void setEnabled(bool enabled) override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemLabel()
    : _originalScale(0.0)
    , _label(nullptr)
    {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemLabel();
    
	  /** 初始化一个具有Label,target和selector的MenuItemLabel */
    bool initWithLabel(Node* label, const ccMenuCallback& callback);
    
    /** 初始化一个具有Label,target和selector的MenuItemLabel */
    CC_DEPRECATED_ATTRIBUTE bool initWithLabel(Node* label, Ref* target, SEL_MenuHandler selector);
    
protected:
    Color3B    _colorBackup;
    float      _originalScale;

    /** item处于禁用状态时的颜色值 */
    Color3B _disabledColor;
    /** 需要渲染的Label. 可以是任何实现了LabelProtocol的Node */
    Node* _label;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemLabel);
};


/** @brief A MenuItemAtlasFont
 用于创建带LabelAtlas的MenuItemLabel的类
 */
class CC_DLL MenuItemAtlasFont : public MenuItemLabel
{
public:
    /** 从参数string,atlas创建一个具有target/selector的menu item */
    static MenuItemAtlasFont* create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap);
    /** 从参数string,atlas创建一个用于MenuItemToggle的menu item */
    CC_DEPRECATED_ATTRIBUTE static MenuItemAtlasFont* create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector);
    /** 从参数string,atlas创建一个用于MenuItemToggle的menu item */
    static MenuItemAtlasFont* create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemAtlasFont(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemAtlasFont(){}
    
    /** 从参数string,atlas初始化一个具有target/selector的menu item */
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector);
    
    /** 从参数string,atlas初始化一个具有target/selector的menu item */
    bool initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemAtlasFont);
};


/** @brief A MenuItemFont
 Helper class that creates a MenuItemLabel class with a Label
 */
class CC_DLL MenuItemFont : public MenuItemLabel
{
public:
    /** 从参数string创建一个用于MenuItemToggle的并不具有target/selector的menu item */
    static MenuItemFont * create(const std::string& value = "");
    /** 从参数string创建一个具有target/selector的menu item */
    CC_DEPRECATED_ATTRIBUTE static MenuItemFont * create(const std::string& value, Ref* target, SEL_MenuHandler selector);
    /** 从参数string创建一个具有target/selector的menu item */
    static MenuItemFont * create(const std::string& value, const ccMenuCallback& callback);

    /** 设置默认字体大小 */
    static void setFontSize(int size);
    /** 获取默认字体大小 */
    static int getFontSize();
    CC_DEPRECATED_ATTRIBUTE static int fontSize() { return MenuItemFont::getFontSize(); };
    /** 设置默认字体名字 */
    static void setFontName(const std::string& name);
    /** 获取默认字体名字 */
    static const std::string& getFontName();
    CC_DEPRECATED_ATTRIBUTE static const std::string& fontName() { return MenuItemFont::getFontName(); };

    /** 设置字体大小
     * c++不能重载静态函数和具有相同参数类型的非静态函数
     * 因此setFontSize函数不能重载，改名为setFontSizeObj来实现设置字体大小
     * @js setFontSize
     */
    void setFontSizeObj(int size);
    
    /** 获取字体大小
     * @js getFontSize
     */
    int getFontSizeObj() const;
    CC_DEPRECATED_ATTRIBUTE int fontSizeObj() const { return getFontSizeObj(); };
    
    /** set the font name 
     *  c++不能重载静态函数和具有相同参数类型的非静态函数
     * 因此setFontName函数不能重载，改名为setFontNameObj来实现设置字体名称
     * @js setFontName
     */
    void setFontNameObj(const std::string& name);

    /** 获取字体名称
     * @js getFontNameObj
     */
    const std::string& getFontNameObj() const;

    /** 已经被剥离,请使用getFontNameObj()来代替 */
    CC_DEPRECATED_ATTRIBUTE const std::string& fontNameObj() const { return getFontNameObj(); }
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemFont();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemFont();
    
    /** 从参数string初始化一个具有target/selector的menu item */
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const std::string& value, Ref* target, SEL_MenuHandler selector);
    
    /** 从参数string初始化一个具有target/selector的menu item */
    bool initWithString(const std::string& value, const ccMenuCallback& callback);
    
protected:
    int _fontSize;
    std::string _fontName;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemFont);
};


/** @brief MenuItemSprite accepts Node<RGBAProtocol> objects as items.
 有三种不同状态的图片:
 - 未选中图片(unselected image)
 - 选中状态图片(selected image)
 - 禁用状态图片(disabled image)
 
 @since v0.8.0
 */
class CC_DLL MenuItemSprite : public MenuItem
{
public:
    /** 创建一个具有常用、选中和禁用状态图片的menu item*/
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite = nullptr);
    /** 创建一个具有常用和选中状态图片并具有target/selector的menu item */
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Ref* target, SEL_MenuHandler selector);
    /** 创建一个具有常用、选中和禁用状态图片并具有target/selector的menu item */
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Ref* target, SEL_MenuHandler selector);
    /** 创建一个具有常用和选中状态图片并具有回调(callback)的menu item */
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback);
    /** 创建一个具有常用、选中和禁用状态图片并具有target/selector的menu item */
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);

    /** 获取item常用状态(未选中状态)的图片 */
    inline Node* getNormalImage() const { return _normalImage; };
    
    /** 设置item常用状态(未选中状态)时的图片 */
    void setNormalImage(Node* image);
    
    /** 获取item选中状态时的图片 */
    inline Node* getSelectedImage() const { return _selectedImage; };
    
    /** 设置item选中状态时的图片 */
    void setSelectedImage(Node* image);
    
    /** 获取item禁用状态时的图片 */
    inline Node* getDisabledImage() const { return _disabledImage; };
    
    /** 设置item禁用状态时的图片 */
    void setDisabledImage(Node* image);
    
    /**
     @since v0.99.5
     */
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool bEnabled);
    
CC_CONSTRUCTOR_ACCESS:
    MenuItemSprite()
    :_normalImage(nullptr)
    ,_selectedImage(nullptr)
    ,_disabledImage(nullptr)
    {}
    
    /** 初始化一个具有常用、选中和禁用状态图片并具有target/selector的menu item */
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Ref* target, SEL_MenuHandler selector);
    
    /** 一个具有常用、选中和禁用状态图片并具有回调(callback)的menu item */
    bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);
    
protected:
    virtual void updateImagesVisibility();

    /** 常用状态(未选中)时的图片 */
    Node* _normalImage;
    /** 选中状态时的图片 */
    Node* _selectedImage;
    /** 禁用状态时的图片 */
    Node* _disabledImage;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemSprite);
};


/** @brief MenuItemImage accepts images as items.
 有三种不同状态的图片:
 - 未选中图片(unselected image)
 - 选中状态图片(selected image)
 - 禁用状态图片(disabled image)
 
 最佳方案是所有的图片具有相同尺寸
 */
class CC_DLL MenuItemImage : public MenuItemSprite
{
public:
    /** 创建一个MenuItemImage. */
    static MenuItemImage* create();
    /** 创建一个具有常用和选中状态图片的menu item*/
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage);
    /** 创建一个具有常用、选中和禁用状态图片的menu item*/
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage);
    /** 创建一个具有常用和选中状态图片并具有target/selector的menu item */
    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, Ref* target, SEL_MenuHandler selector);
    /** 创建一个具有常用和选中状态图片并具有回调(callback)的menu item */
    static MenuItemImage* create(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback);

    /** 创建一个具有常用、选中和禁用状态图片并具有target/selector的menu item */
    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    /** 创建一个具有常用、选中和禁用状态图片并具有回调(callback)的menu item */
    static MenuItemImage* create(const std::string&normalImage, const std::string&selectedImage, const std::string&disabledImage, const ccMenuCallback& callback);

    /** 设置图片常用状态时的sprite frame */
    void setNormalSpriteFrame(SpriteFrame* frame);
    /** 设置图片选中状态时的sprite frame */
    void setSelectedSpriteFrame(SpriteFrame* frame);
    /** 设置图片禁用状态时的sprite frame */
    void setDisabledSpriteFrame(SpriteFrame* frame);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemImage(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemImage(){}
    
    bool init();
    
    /** 初始化一个具有常用、选中和禁用状态图片并具有target/selector的menu item */
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    
    /** 初始化一个具有常用、选中和禁用状态图片并具有回调(callback)的menu item */
    bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemImage);
};


/** @brief A MenuItemToggle
 一个简单的包含内部items的容器类
 内部items可以是任何MenuItem
 */
class CC_DLL MenuItemToggle : public MenuItem
{
public:
    /** 从包含item的Array参数创建一个具有target/selector的menu item
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle * createWithTarget(Ref* target, SEL_MenuHandler selector, const Vector<MenuItem*>& menuItems);
    /** 从包含item的list参数创建一个具有target/selector的menu item
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle* createWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, ...)CC_REQUIRES_NULL_TERMINATION;
    
    /** 从包含item的Array参数创建一个具有回调(callback)的menu item */
    static MenuItemToggle * createWithCallback(const ccMenuCallback& callback, const Vector<MenuItem*>& menuItems);
    /** 从包含item的list参数创建一个具有回调(callback)的menu item */
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
    /** 创建一个空menu item(没有target/selector,且不包含items) */
    static MenuItemToggle* create();
    /** 创建包含一个item的menu item */
    static MenuItemToggle* create(MenuItem *item);
    /** 创建包含多个item的menu item */
    void addSubItem(MenuItem *item);
    
    /** 返回选中的item */
    MenuItem* getSelectedItem();
    /** 已剥离,请使用getSelectedItem()代替 */
    CC_DEPRECATED_ATTRIBUTE MenuItem* selectedItem() { return getSelectedItem(); }

    /** 获取选中item的索引(index) */
    inline unsigned int getSelectedIndex() const { return _selectedIndex; };
    
    /** 设置选中item的索引 */
    void setSelectedIndex(unsigned int index);
    
    /** 获取包含subitems的array
     你可以在运行时添加或删除items,也可用一个新的array替换.
     @since v0.7.2
     * @js NA
     * @lua NA
     */
    inline const Vector<MenuItem*>& getSubItems() const { return _subItems; };
    inline Vector<MenuItem*>& getSubItems() { return _subItems; };

    /** 设置包含subitems的array */
    inline void setSubItems(const Vector<MenuItem*>& items) {
        _subItems = items;
    }
    
    // Overrides
    virtual void activate() override;
    virtual void selected() override;
    virtual void unselected() override;
    virtual void setEnabled(bool var) override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemToggle()
    : _selectedIndex(0)
    {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemToggle();
    
    /** 从包含item的list参数初始化一个具有target/selector的menu item
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, va_list args);
    
    /** 从包含item的list参数初始化一个具有回调(callback)的menu item */
    bool initWithCallback(const ccMenuCallback& callback, MenuItem* item, va_list args);
    
    /** 初始化一个menu item,使之具有一个item */
    bool initWithItem(MenuItem *item);

protected:
    /** 选中的item索引 */
    unsigned int _selectedIndex;
    /** 包含subitems的array,你可以在运行时添加或删除items,也可用一个新的array替换.
     @since v0.7.2
     */
    Vector<MenuItem*> _subItems;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemToggle);

};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCMENU_ITEM_H__
