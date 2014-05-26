/****************************************************************************
Copyright (c) 2010      Neophit
Copyright (c) 2010      Ricardo Quesada
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
#ifndef __CCTMX_OBJECT_GROUP_H__
#define __CCTMX_OBJECT_GROUP_H__

#include "math/CCGeometry.h"
#include "base/CCValue.h"
#include "base/CCRef.h"

NS_CC_BEGIN

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** @brief TMXObjectGroup代表TMX对象组
@since v0.99.0
*/
class CC_DLL TMXObjectGroup : public Ref
{
public:
    /**
     * @js ctor
     */
    TMXObjectGroup();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXObjectGroup();

    inline const std::string& getGroupName(){ return _groupName; }
    inline void setGroupName(const std::string& groupName){ _groupName = groupName; }

    /** 获取指定属性名的值 */
    Value getProperty(const std::string& propertyName) const;
    
    CC_DEPRECATED_ATTRIBUTE Value propertyNamed(const std::string& propertyName) const { return getProperty(propertyName); };

    /** 获取指定对象名的字典.
    返回的是指定名字数组中第一个对象.
    */
    ValueMap getObject(const std::string& objectName) const;
    
    CC_DEPRECATED_ATTRIBUTE ValueMap objectNamed(const std::string& objectName) const { return getObject(objectName); };
    
    /** 获取子对象的偏移位置 */
    inline const Vec2& getPositionOffset() const { return _positionOffset; };
    
    /** 设置子对象的偏移位置 */
    inline void setPositionOffset(const Vec2& offset) { _positionOffset = offset; };
    
    /** 获取存储在字典中的属性队列 */
    inline const ValueMap& getProperties() const { return _properties; };
    inline ValueMap& getProperties() { return _properties; };
    
    /** 设置属性队列 */
    inline void setProperties(const ValueMap& properties) {
        _properties = properties;
    };
    
    /** 获取对象数组 */
    inline const ValueVector& getObjects() const { return _objects; };
    inline ValueVector& getObjects() { return _objects; };
    
    /** 设置对象数组 */
    inline void setObjects(const ValueVector& objects) {
        _objects = objects;
    };
    
protected:
    /** 组名 */
    std::string _groupName;
    /** 子对象偏移位置 */
    Vec2 _positionOffset;
    /** 存储在字典中的属性队列 */
    ValueMap _properties;
    /** 对象数组 */
    ValueVector _objects;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_OBJECT_GROUP_H__
