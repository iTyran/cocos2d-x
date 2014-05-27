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


#ifndef __CC_TM_XML_PARSER__
#define __CC_TM_XML_PARSER__

#include "math/CCGeometry.h"
#include "2d/platform/CCSAXParser.h"
#include "base/CCVector.h"
#include "base/CCValue.h"

#include <string>

NS_CC_BEGIN

class TMXLayerInfo;
class TMXObjectGroup;
class TMXTilesetInfo;

/** @file
* 内部的TMX解析器
*
* 重要: 用户不需要关心这些
*
*/

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

enum {
    TMXLayerAttribNone = 1 << 0,
    TMXLayerAttribBase64 = 1 << 1,
    TMXLayerAttribGzip = 1 << 2,
    TMXLayerAttribZlib = 1 << 3,
};

enum {
    TMXPropertyNone,
    TMXPropertyMap,
    TMXPropertyLayer,
    TMXPropertyObjectGroup,
    TMXPropertyObject,
    TMXPropertyTile
};

typedef enum TMXTileFlags_ {
    kTMXTileHorizontalFlag  = 0x80000000,
    kTMXTileVerticalFlag    = 0x40000000,
    kTMXTileDiagonalFlag    = 0x20000000,
    kTMXFlipedAll           = (kTMXTileHorizontalFlag|kTMXTileVerticalFlag|kTMXTileDiagonalFlag),
    kTMXFlippedMask         = ~(kTMXFlipedAll)
} TMXTileFlags;

// 当前32位全局tile标识符的最后部分被用来表示tile标记

/** @brief TMXLayerInfo所包含的一些layers信息:
- Layer名字
- Layer尺寸
- 创建时的Layer opacity(不能在运行时修改)
- layer可视化(如不可视,CocosNode则不会被创建)

这些信息均可从TMX文件中获取
*/
class CC_DLL TMXLayerInfo : public Ref
{
public:
    /**
     * @js ctor
     */
    TMXLayerInfo();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXLayerInfo();

    void setProperties(ValueMap properties);
    ValueMap& getProperties();

    ValueMap            _properties;
    std::string         _name;
    Size                _layerSize;
    uint32_t            *_tiles;
    bool                _visible;
    unsigned char       _opacity;
    bool                _ownTiles;
    Vec2               _offset;
};

/** @brief TMXTilesetInfo所包含的一些tilesets信息:
- Tileset名字
- Tileset间隔
- Tileset外边距
- tiles尺寸
- tiles图片
- 图片尺寸

这些信息均可从TMX文件中读取 
*/
class CC_DLL TMXTilesetInfo : public Ref
{
public:
    std::string     _name;
    int             _firstGid;
    Size            _tileSize;
    int             _spacing;
    int             _margin;
    //! 包含tiles(spritesheet/texture atlas)的文件
    std::string     _sourceImage;
    //! 图片像素尺寸
    Size            _imageSize;
public:
    /**
     * @js ctor
     */
    TMXTilesetInfo();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXTilesetInfo();
    Rect getRectForGID(uint32_t gid);
};

/** @brief TMXMapInfo所包含的一些map的信息:
- 地图定向(orientation):六边形(hexagonal),等距斜视(isometric),直角鸟瞰(orthogonal)
- Tile尺寸
- 地图尺寸

以及如下:
- Layers (一组TMXLayerInfo对象)
- Tilesets (一组TMXTilesetInfo对象)
- ObjectGroups (一组TMXObjectGroupInfo对象)

这些信息均可从TMX文件中读取

*/
class CC_DLL TMXMapInfo : public Ref, public SAXDelegator
{    
public:    
    /** 创建一个指定tmx文件格式的TMX */
    static TMXMapInfo * create(const std::string& tmxFile);
    /** 创建一个指定XML字符串和TMX资源路径(TMX resource path)格式的TMX */
    static TMXMapInfo * createWithXML(const std::string& tmxString, const std::string& resourcePath);
    
    /** 创建一个指定tmx文件格式的TMX */
    CC_DEPRECATED_ATTRIBUTE static TMXMapInfo * formatWithTMXFile(const char *tmxFile) { return TMXMapInfo::create(tmxFile); };
    /** 创建一个指定XML字符串和TMX资源路径(TMX resource path)格式的TMX */
    CC_DEPRECATED_ATTRIBUTE static TMXMapInfo * formatWithXML(const char* tmxString, const char* resourcePath) { return TMXMapInfo::createWithXML(tmxString, resourcePath); };
    /**
     * @js ctor
     */
    TMXMapInfo();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXMapInfo();
    
    /** 使用指定tmx文件格式初始化一个TMX */
    bool initWithTMXFile(const std::string& tmxFile);
    /** 使用指定XML字符串和TMX资源路径(TMX resource path)格式初始化一个TMX */
    bool initWithXML(const std::string& tmxString, const std::string& resourcePath);
    /** 通过解析一个XML文件,tmx(Map)文件或tsx(Tileset)文件初始化一个TMX */
    bool parseXMLFile(const std::string& xmlFilename);
    /* 通过解析一个XML字符串,tmx(Map)字符串或tsx(Tileset)字符串初始化一个TMX */
    bool parseXMLString(const std::string& xmlString);

    ValueMapIntKey& getTileProperties() { return _tileProperties; };
    void setTileProperties(const ValueMapIntKey& tileProperties) {
        _tileProperties = tileProperties;
    };

    /// 地图定向(orientation)
    inline int getOrientation() const { return _orientation; };
    inline void setOrientation(int orientation) { _orientation = orientation; };

    /// 地图尺寸(宽和高)
    inline const Size& getMapSize() const { return _mapSize; };
    inline void setMapSize(const Size& mapSize) { _mapSize = mapSize; };

    /// tiles尺寸(宽和高)
    inline const Size& getTileSize() const { return _tileSize; };
    inline void setTileSize(const Size& tileSize) { _tileSize = tileSize; };
    
    /// Layers
    inline const Vector<TMXLayerInfo*>& getLayers() const { return _layers; };
    inline Vector<TMXLayerInfo*>& getLayers() { return _layers; };
    inline void setLayers(const Vector<TMXLayerInfo*>& layers) {
        _layers = layers;
    };

    /// tilesets
    inline const Vector<TMXTilesetInfo*>& getTilesets() const { return _tilesets; };
    inline Vector<TMXTilesetInfo*>& getTilesets() { return _tilesets; };
    inline void setTilesets(const Vector<TMXTilesetInfo*>& tilesets) {
        _tilesets = tilesets;
    };

    /// 对象组(ObjectGroups)
    inline const Vector<TMXObjectGroup*>& getObjectGroups() const { return _objectGroups; };
    inline Vector<TMXObjectGroup*>& getObjectGroups() { return _objectGroups; };
    inline void setObjectGroups(const Vector<TMXObjectGroup*>& groups) {
        _objectGroups = groups;
    };

    /// 父元素
    inline int getParentElement() const { return _parentElement; };
    inline void setParentElement(int element) { _parentElement = element; };

    /// 父全局标识(GID)
    inline int getParentGID() const { return _parentGID; };
    inline void setParentGID(int gid) { _parentGID = gid; };

    /// layer属性
    inline int getLayerAttribs() const { return _layerAttribs; };
    inline void setLayerAttribs(int layerAttribs) { _layerAttribs = layerAttribs; };

    /// TMX文件中data元素内容是否为base64字符(TMX文件中data元素是否以base64字符信息保存)
    inline bool isStoringCharacters() const { return _storingCharacters; };
    CC_DEPRECATED_ATTRIBUTE inline bool getStoringCharacters() const { return isStoringCharacters(); };
    inline void setStoringCharacters(bool storingCharacters) { _storingCharacters = storingCharacters; };

    /// 属性
    inline const ValueMap& getProperties() const { return _properties; }
    inline ValueMap& getProperties() { return _properties; }
    inline void setProperties(const ValueMap& properties) {
        _properties = properties;
    };
    
    // 实现SAXDelegator的纯虚函数
    /**
     * @js NA
     * @lua NA
     */
    void startElement(void *ctx, const char *name, const char **atts);
    /**
     * @js NA
     * @lua NA
     */
    void endElement(void *ctx, const char *name);
    /**
     * @js NA
     * @lua NA
     */
    void textHandler(void *ctx, const char *ch, int len);
    
    inline const std::string& getCurrentString() const { return _currentString; }
    inline void setCurrentString(const std::string& currentString){ _currentString = currentString; }
    inline const std::string& getTMXFileName() const { return _TMXFileName; }
    inline void setTMXFileName(const std::string& fileName){ _TMXFileName = fileName; }

protected:
    void internalInit(const std::string& tmxFileName, const std::string& resourcePath);

    /// 地图定向(orientation)
    int    _orientation;
    /// 地图尺寸(宽和高)
    Size _mapSize;
    /// tiles尺寸(宽和高)
    Size _tileSize;
    /// Layers
    Vector<TMXLayerInfo*> _layers;
    /// tilesets
    Vector<TMXTilesetInfo*> _tilesets;
    /// 对象组(ObjectGroups)
    Vector<TMXObjectGroup*> _objectGroups;
    /// 父元素
    int _parentElement;
    /// 父全局标识(GID)
    int _parentGID;
    /// layer属性
    int _layerAttribs;
    /// TMX文件中data元素内容是否为base64字符(TMX文件中data元素是否以base64字符信息保存)
    bool _storingCharacters;
    /// 属性
    ValueMap _properties;
    //! xml格式的tile索引
    int _xmlTileIndex;
    
    //! tmx文件名
    std::string _TMXFileName;
    // tmx资源路径
    std::string _resources;
    //! 当前所处理的字符信息
    std::string _currentString;
    //! tile属性
    ValueMapIntKey _tileProperties;
    int _currentFirstGID;
    bool _recordFirstGID;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif

