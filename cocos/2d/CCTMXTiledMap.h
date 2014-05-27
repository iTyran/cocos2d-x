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
#ifndef __CCTMX_TILE_MAP_H__
#define __CCTMX_TILE_MAP_H__

#include "2d/CCNode.h"
#include "CCTMXObjectGroup.h"
#include "base/CCValue.h"

NS_CC_BEGIN

class TMXObjectGroup;
class TMXLayer;
class TMXLayerInfo;
class TMXTilesetInfo;
class TMXMapInfo;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** TMXmap的方位 */
enum
{
    /** 直角鸟瞰定向(orientation) */
    TMXOrientationOrtho,

    /** 六边形定向(orientation) */
    TMXOrientationHex,

    /** 持等距斜视定向(orientation) */
    TMXOrientationIso,
};

/** @brief TMXTiledMap知道如何解析和渲染TMX地图

http://www.mapeditor.org官网将其加入支持TMX tiled地图格式
其支持等距斜视(isometric),六边形(hexagonal),直角鸟瞰(orthogonal)tiles
也支持对象组,多对象以及多属性

特点如下:
- 每个TMXTiledMap都被当作一个精灵
- 这些精灵需要时被创建而且仅当调用layer->tileAt(position)时才会被创建
- 每个tile继承了精灵的特点，可以旋转/移动/缩放/着色/透明化
- Tiles可以在运行时添加或删除
- Tiles的z-order亦可在运行时修改
- 每个tile的锚点是(0,0)
- TMXTileMap的锚点是(0,0)
- TMX layers可以当作子节点添加
- TXM layers默认会设置一个别名
- Tileset图片可以在使用TextureCache时加入
- 每个tile都有一个唯一的tag
- 每个tile都有一个唯一的z值.左上(top-left): z=1, 右下(bottom-right): z=max z
- 每个对象组(object group)可以用作可变数组(MutaleArray)
- 对象类包含的属性都存储在一个字典(dictionary)中
- 属性可以赋值给地图(Map),层(Layer),对象属性(Object Group)以及对象(Object)

受限点:
- 每个layer只支持一个tileset
- 不支持嵌入式图片(Embedded images)
- 只支持XML格式(不支持JSON格式)

技术描述:
每个layer被创建成TMXLayer(继承自SpriteBatchNode)。
如果layer是可视的,那么如果你有5个layer,则5个TMXLayer被创建.
如果不可视,则layer根本不会被创建。
在运行时,可通过如下获取layers(TMXLayer objects):
- map->getChildByTag(tag_number);  // 0=1st layer, 1=2nd layer, 2=3rd layer, etc...
- map->getLayer(name_of_the_layer); //name_of_the_layer layer名

每个对象组被创建成一个继承自MutableArray的TMXObjectGroup
运行时,可通过如下获取该对象组:
- map->getObjectGroup(name_of_the_object_group);//name_of_the_object_group 对象组名

每个object都是一个TMXObject

每个属性都通过key-value对存储在一个MutableDictionary里
运行时,可通过如下获取属性:
map->getProperty(name_of_the_property);//name_of_the_property 属性名
layer->getProperty(name_of_the_property);
objectGroup->getProperty(name_of_the_property);
object->getProperty(name_of_the_property);

@since v0.8.1
*/
class CC_DLL TMXTiledMap : public Node
{
public:
    /** 通过指定TMX文件创建一个TMX Tiled地图*/
    static TMXTiledMap* create(const std::string& tmxFile);

    /** 通过一个指定的TMX格式的XML和TMX资源路径创建一个TMX Tiled地图 */
    static TMXTiledMap* createWithXML(const std::string& tmxString, const std::string& resourcePath);

    /** 通过layerName获取对应的TMXLayer */
    TMXLayer* getLayer(const std::string& layerName) const;
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE TMXLayer* layerNamed(const std::string& layerName) const { return getLayer(layerName); };

    /** 通过groupName获取对应的TMXObjectGroup */
    TMXObjectGroup* getObjectGroup(const std::string& groupName) const;
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE TMXObjectGroup* objectGroupNamed(const std::string& groupName) const { return getObjectGroup(groupName); };

    /** 通过propertyName获取对应的Property */
    Value getProperty(const std::string& propertyName) const;
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Value propertyNamed(const char *propertyName) const { return getProperty(propertyName); };

    /** 通过GID获取对应的属性字典(properties dictionary) */
    Value getPropertiesForGID(int GID) const;
    CC_DEPRECATED_ATTRIBUTE Value propertiesForGID(int GID) const { return getPropertiesForGID(GID); };

    /** 通过指定GID查找其对应的属性变量,并赋予属性值value,如成功查找到并赋值成功,则返回true,反之则为false*/
    bool getPropertiesForGID(int GID, Value** value);

    /** 以tiles数量为基准的地图尺寸 */
    inline const Size& getMapSize() const { return _mapSize; };
    inline void setMapSize(const Size& mapSize) { _mapSize = mapSize; };

    /** 以像素点为基准的tile尺寸属性 */
    inline const Size& getTileSize() const { return _tileSize; };
    inline void setTileSize(const Size& tileSize) { _tileSize = tileSize; };

    /** 地图定向(orientation) */
    inline int getMapOrientation() const { return _mapOrientation; };
    inline void setMapOrientation(int mapOrientation) { _mapOrientation = mapOrientation; };

    /** 对象组 */
    inline const Vector<TMXObjectGroup*>& getObjectGroups() const { return _objectGroups; };
    inline Vector<TMXObjectGroup*>& getObjectGroups() { return _objectGroups; };
    inline void setObjectGroups(const Vector<TMXObjectGroup*>& groups) {
        _objectGroups = groups;
    };
    
    /** 属性 */
    inline ValueMap& getProperties() { return _properties; };
    inline void setProperties(const ValueMap& properties) {
        _properties = properties;
    };

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    TMXTiledMap();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXTiledMap();
    
    /** 通过指定的TMX文件初始化一个TMX Tiled地图 */
    bool initWithTMXFile(const std::string& tmxFile);
    
    /** 通过一个指定的TMX格式的XML和TMX资源路径初始化一个TMX Tiled地图 */
    bool initWithXML(const std::string& tmxString, const std::string& resourcePath);

protected:
    TMXLayer * parseLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    TMXTilesetInfo * tilesetForLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    void buildWithMapInfo(TMXMapInfo* mapInfo);

    /** 以tiles数量为基准的地图尺寸 */
    Size _mapSize;
    /** 以像素点为基准的tile尺寸属性 */
    Size _tileSize;
    /** 地图定向(orientation) */
    int _mapOrientation;
    /** 对象组 */
    Vector<TMXObjectGroup*> _objectGroups;
    /** 属性 */
    ValueMap _properties;
    
    //! tile属性
    ValueMapIntKey _tileProperties;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TMXTiledMap);

};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_TILE_MAP_H__


