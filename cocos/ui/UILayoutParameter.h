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

#ifndef __LAYOUTPARMETER_H__
#define __LAYOUTPARMETER_H__

#include <string>
#include "base/CCRef.h"


NS_CC_BEGIN

namespace ui {

/**
 *   @js NA
 *   @lua NA
 */
class Margin
{
public:
    float left;
    float top;
    float right;
    float bottom;
    
public:
    Margin();
    Margin(float l, float t, float r, float b);
    Margin(const Margin& other);
    Margin& operator= (const Margin& other);
    void setMargin(float l, float t, float r, float b);
    bool equals(const Margin& target) const;
};

const Margin MarginZero = Margin();

/**
*   @js NA
*   @lua NA
*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef RELATIVE
#undef RELATIVE
#endif
#endif

class LayoutParameter : public Ref
{
public:
    enum class Type
    {
        NONE = 0,
        LINEAR,
        RELATIVE
    };
    /**
     * Default constructor(默认构造函数)
     */
    LayoutParameter() : _margin(Margin())
    {
        _layoutParameterType = Type::NONE;
    };
    
    /**
     * Default destructor(默认虚构函数)
     */
    virtual ~LayoutParameter(){};
    
    /**
     * 分配（allocates）并初始化（initializes）.
     * @return 返回一个被标记为自动释放(autorelease)且初始化好的LayoutParameter.
     */
    static LayoutParameter* create();
    
    /**
     * 设置LayoutParameter的边距(Margin)参数.
     * 
     * @see Margin
     *
     * @param margin
     */
    void setMargin(const Margin& margin);
    
    /**
     * 获取LayoutParameter的边距(Margin)参数.
     *
     * @see Margin
     *
     * @return const Margin&
     */
    const Margin& getMargin() const;
    
    /**
     * 获取LayoutParameter的参数类型(LayoutParameterType).
     *
     * @see LayoutParameterType
     *
     * @return LayoutParameterType
     */
    Type getLayoutType() const;
    
    LayoutParameter* clone();
    virtual LayoutParameter* createCloneInstance();
    virtual void copyProperties(LayoutParameter* model);
protected:
    Margin _margin;
    Type _layoutParameterType;
};

    
/**
*   @js NA
*   @lua NA
*/
class LinearLayoutParameter : public LayoutParameter
{
public:
    enum class LinearGravity
    {
        NONE,
        LEFT,
        TOP,
        RIGHT,
        BOTTOM,
        CENTER_VERTICAL,
        CENTER_HORIZONTAL
    };
    /**
     * Default constructor(默认构造函数)
     */
    LinearLayoutParameter()
    : _linearGravity(LinearGravity::NONE)
    {
        _layoutParameterType = Type::LINEAR;
    };
    
    /**
     * Default destructor(默认虚构函数)
     */
    virtual ~LinearLayoutParameter(){};
    
    /**
     * 分配（allocates）并初始化（initializes）.
     * @return 返回一个被标记为自动释放(autorelease)且初始化好的LayoutParameter.
     */
    static LinearLayoutParameter* create();
    
    /**
     * 设置LayoutParameter的线性重力(LinearGravity)参数.
     *
     * @see LinearGravity
     *
     * @param LinearGravity
     */
    void setGravity(LinearGravity gravity);
    
    /**
     * 获取LayoutParameter的线性重力(LinearGravity)参数.
     *
     * @see LinearGravity
     *
     * @return LinearGravity
     */
    LinearGravity getGravity() const;
    virtual LayoutParameter* createCloneInstance() override;
    virtual void copyProperties(LayoutParameter* model) override;
protected:
    LinearGravity _linearGravity;
};
    
    
/**
*   @js NA
*   @lua NA
*/

    
class RelativeLayoutParameter : public LayoutParameter
{
public:
    enum class RelativeAlign
    {
        NONE,
        PARENT_TOP_LEFT,
        PARENT_TOP_CENTER_HORIZONTAL,
        PARENT_TOP_RIGHT,
        PARENT_LEFT_CENTER_VERTICAL,
        
        CENTER_IN_PARENT,
        
        PARENT_RIGHT_CENTER_VERTICAL,
        PARENT_LEFT_BOTTOM,
        PARENT_BOTTOM_CENTER_HORIZONTAL,
        PARENT_RIGHT_BOTTOM,
        
        LOCATION_ABOVE_LEFTALIGN,
        LOCATION_ABOVE_CENTER,
        LOCATION_ABOVE_RIGHTALIGN,
        LOCATION_LEFT_OF_TOPALIGN,
        LOCATION_LEFT_OF_CENTER,
        LOCATION_LEFT_OF_BOTTOMALIGN,
        LOCATION_RIGHT_OF_TOPALIGN,
        LOCATION_RIGHT_OF_CENTER,
        LOCATION_RIGHT_OF_BOTTOMALIGN,
        LOCATION_BELOW_LEFTALIGN,
        LOCATION_BELOW_CENTER,
        LOCATION_BELOW_RIGHTALIGN
    };
    /**
     * Default constructor(默认构造函数)
     */
    RelativeLayoutParameter()
    : _relativeAlign(RelativeAlign::NONE),
    _relativeWidgetName(""),
    _relativeLayoutName(""),
    _put(false)
    {
        _layoutParameterType = Type::RELATIVE;
    };
    
    /**
     * Default destructor(默认虚构函数)
     */
    virtual ~RelativeLayoutParameter(){};
    
    /**
     * 分配（allocates）并初始化（initializes）.
     * @return 返回一个被标记为自动释放(autorelease)且初始化好的LayoutParameter.
     */
    static RelativeLayoutParameter* create();
    
    /**
     * 设置LayoutParameter的相对排列(RelativeAlign)参数.
     *
     * @see RelativeAlign
     *
     * @param RelativeAlign
     */
    void setAlign(RelativeAlign align);
    
    /**
     * 获取LayoutParameter的相对排列(RelativeAlign)参数..
     *
     * @see RelativeAlign
     *
     * @return RelativeAlign
     */
    RelativeAlign getAlign() const;
    
    /**
     * 设置LayoutParameter的key. 这个key和widget的名字相关.
     *
     * @param name
     */
    void setRelativeToWidgetName(const std::string& name);
    
    /**
     *  获取LayoutParameter的key. 这个key和widget的名字相关.
     *
     * @return name
     */
    const std::string& getRelativeToWidgetName() const;
    
    /**
     * 设置LayoutParameter的相对布局(Relative Layout)名字.
     *
     * @param name
     */
    void setRelativeName(const std::string& name);
    
    /**
     * 获取LayoutParameter的相对布局(Relative Layout)名字.
     *
     * @return name
     */
    const std::string& getRelativeName() const;
    
    virtual LayoutParameter* createCloneInstance() override;
    virtual void copyProperties(LayoutParameter* model) override;
protected:
    RelativeAlign _relativeAlign;
    std::string _relativeWidgetName;
    std::string _relativeLayoutName;
    bool _put;
    friend class RelativeLayoutExecutant;
};

}

NS_CC_END

#endif /* defined(__LayoutParameter__) */
