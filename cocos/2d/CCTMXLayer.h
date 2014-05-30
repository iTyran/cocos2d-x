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
#ifndef __CCTMX_LAYER_H__
#define __CCTMX_LAYER_H__

#include "CCTMXObjectGroup.h"
#include "CCAtlasNode.h"
#include "2d/CCSpriteBatchNode.h"
#include "CCTMXXMLParser.h"
#include "2d/ccCArray.h"
NS_CC_BEGIN

class TMXMapInfo;
class TMXLayerInfo;
class TMXTilesetInfo;
struct _ccCArray;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** @brief TMXLayer用来表示TMX layer，继承自SpriteBatchNode。tiles使用TextureAtlas进行渲染。
如果运行时修改一个tile，那么tile将变成一个Sprite，反之，则不会有Sprite对象被创建。
使用Sprite对象作为tiles有如下好处：
- tiles(即Sprite)可以通过完善的API进行旋转/缩放/移动

如果layer包含一个属性名为"cc_vertexz"的整数(整数/负数)，那么属于layer的tiles将使用该属性值作为它们OpenGL用来渲染显示层次的Z值。

在另一方面，如果"cc_vertexz"属性拥有 "automatic"值，那么这些tiles将使用一个自分配的Z值。
同样，在绘制这些tiles时，在绘制前，必须设置GL_ALPHA_TEST为可用，绘制后设置为禁用。使用的Alpha函数如下：
glAlphaFunc( GL_GREATER, value )

"value"默认值是0，也可通过添加"cc_alpha_func"属性给转换成tile的layer来进行改变。
大多数情况是value的值是0，但如果有些tiles是半透明的，那么这值则可能会有不同，如是0.5
进一步的信息，请查看相关说明(注：此链接已不可用)：
http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:tiled_maps

@since v0.8.1
Tiles可以有额外属性tile flags，这些属性只当水平翻转和垂直翻转时使用，它们的bit flags定义在TMXXMLParser.h头文件中。

@since 1.1
*/

class CC_DLL TMXLayer : public SpriteBatchNode
{
public:
    /** 通过指定TMXTilesetInfo,TMXLayerInfo和TMXMapInfo创建一个TMXLayer */
    static TMXLayer * create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    /**
     * @js ctor
     */
    TMXLayer();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXLayer();

    /** 使用指定TMXTilesetInfo,TMXLayerInfo和TMXMapInfo初始化一个TMXLayer */
    bool initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);

    /** 从内存中释放包含tile位置信息的地图。
    除知道在运行时知道tiles的位置信息外，你都可安全的调用此方法。
    如果即将调用layer->tileGIDAt()，那么不能释放地图。
    */
    void releaseMap();

    /** 通过指定的tile坐标获取对应的tile(Sprite)。
    返回的tile(Sprite)应是已经添加到TMXLayer，不能被重复添加。
    这个tile(Sprite)如同其他的Sprite一样，可以旋转、缩放、翻转、透明化、设置颜色等。
    可通过调用如下对其进行删除：
    - layer->removeChild(sprite, cleanup);
    - 或 layer->removeTileAt(Vec2(x,y));
    */
    Sprite* getTileAt(const Vec2& tileCoordinate);
    CC_DEPRECATED_ATTRIBUTE Sprite* tileAt(const Vec2& tileCoordinate) { return getTileAt(tileCoordinate); };
    
    /** 通过指定的tile坐标获取对应的tile grid，也返回对应的tile flags
     这个方法要求tile地图之前没有被释放掉(如，不能调用layer->releaseMap())
     */
    uint32_t getTileGIDAt(const Vec2& tileCoordinate, TMXTileFlags* flags = nullptr);
    CC_DEPRECATED_ATTRIBUTE uint32_t tileGIDAt(const Vec2& tileCoordinate, TMXTileFlags* flags = nullptr){
        return getTileGIDAt(tileCoordinate, flags);
    };

    /** 设置一个指定坐标的tile的grid(gid = tile global id)。
    Tile GID可以通过调用tileGIDAt方法或使用TMX editor -> Tileset Mgr +1得到。
    如果该位置上已有一个tile，那么该位置上已有的tile将会被移除。
    */
    void setTileGID(uint32_t gid, const Vec2& tileCoordinate);

    /** 设置一个指定坐标的tile的grid(gid = tile global id)。
      Tile GID可以通过调用tileGIDAt方法或使用TMX editor -> Tileset Mgr +1得到。
     如果该位置上已有一个tile，那么该位置上已有的tile将会被移除。
     
     如果tile flags也需要改变，则使用withFlags。
     */

    void setTileGID(uint32_t gid, const Vec2& tileCoordinate, TMXTileFlags flags);

    /** 移除指定坐标上的tile */
    void removeTileAt(const Vec2& tileCoordinate);

    /** 获取指定坐标的位置(以点为单位) */
    Vec2 getPositionAt(const Vec2& tileCoordinate);
    CC_DEPRECATED_ATTRIBUTE Vec2 positionAt(const Vec2& tileCoordinate) { return getPositionAt(tileCoordinate); };

    /** 获取指定属性名(propertyName)的value */
    Value getProperty(const std::string& propertyName) const;
    CC_DEPRECATED_ATTRIBUTE Value propertyNamed(const std::string& propertyName) const { return getProperty(propertyName); };

    /** 创建tiles */
    void setupTiles();

    inline const std::string& getLayerName(){ return _layerName; }
    inline void setLayerName(const std::string& layerName){ _layerName = layerName; }

    /** 获取在tiles中layer的尺寸 */
    inline const Size& getLayerSize() const { return _layerSize; };
    inline void setLayerSize(const Size& size) { _layerSize = size; };
    
    /** 获取地图tile的尺寸(与tile尺寸不同) */
    inline const Size& getMapTileSize() const { return _mapTileSize; };
    inline void setMapTileSize(const Size& size) { _mapTileSize = size; };
    
    /** 指针:指向tiles地图 
     * @js NA
     * @lua NA
     */
    uint32_t* getTiles() const { return _tiles; };
    void setTiles(uint32_t* tiles) { _tiles = tiles; };
    
    /** 获取layer的Tileset信息 */
    inline TMXTilesetInfo* getTileSet() const { return _tileSet; };
    inline void setTileSet(TMXTilesetInfo* info) {
        CC_SAFE_RETAIN(info);
        CC_SAFE_RELEASE(_tileSet);
        _tileSet = info;
    };
    
    /** Layer定向(同地图定向) */
    inline int getLayerOrientation() const { return _layerOrientation; };
    inline void setLayerOrientation(int orientation) { _layerOrientation = orientation; };
    
    /** layer的属性，可以被当作Tile添加 */
    inline const ValueMap& getProperties() const { return _properties; };
    inline ValueMap& getProperties() { return _properties; };
    inline void setProperties(const ValueMap& properties) {
        _properties = properties;
    };
    //
    // Override
    //
    /** TMXLayer不支持手动添加
     @warning addchild(z, tag); 不能在TMXLayer中使用，用setTileGID代替
     */
    using SpriteBatchNode::addChild;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    // 父方法
    void removeChild(Node* child, bool cleanup) override;
    virtual std::string getDescription() const override;

private:
    Vec2 getPositionForIsoAt(const Vec2& pos);
    Vec2 getPositionForOrthoAt(const Vec2& pos);
    Vec2 getPositionForHexAt(const Vec2& pos);

    Vec2 calculateLayerOffset(const Vec2& offset);

    /* 优化的方法 */
    Sprite* appendTileForGID(uint32_t gid, const Vec2& pos);
    Sprite* insertTileForGID(uint32_t gid, const Vec2& pos);
    Sprite* updateTileForGID(uint32_t gid, const Vec2& pos);

    /* layer所用到的一些属性，如cc_vertez */
    void parseInternalProperties();
    void setupTileSprite(Sprite* sprite, Vec2 pos, int gid);
    Sprite* reusedTileWithRect(Rect rect);
    int getVertexZForPos(const Vec2& pos);

    // index
    ssize_t atlasIndexForExistantZ(int z);
    ssize_t atlasIndexForNewZ(int z);
    
protected:
    //! layer名
    std::string _layerName;
    //! 透明度(TMX Layer支持该属性)
    unsigned char        _opacity;
    
    //! 当且仅当vertexZ被使用时使用
    int                    _vertexZvalue;
    bool                _useAutomaticVertexZ;

    //! 用于优化
    Sprite            *_reusedTile;
    ccCArray            *_atlasIndexArray;
    
    // 用于Retina屏的显示
    float               _contentScaleFactor;
    
    /** tiles中的layer尺寸 */
    Size _layerSize;
    /** 地图tile的尺寸(与tile尺寸不同) */
    Size _mapTileSize;
    /** tiles地图指针 */
    uint32_t* _tiles;
    /** layer的Tileset信息 */
    TMXTilesetInfo* _tileSet;
    /** Layer定向(同地图定向) */
    int _layerOrientation;
    /** layer的属性，可以被当作Tile添加 */
    ValueMap _properties;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_LAYER_H__

