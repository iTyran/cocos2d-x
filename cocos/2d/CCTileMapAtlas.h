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
#ifndef __CCTILE_MAP_ATLAS__
#define __CCTILE_MAP_ATLAS__

#include "CCAtlasNode.h"
#include "base/CCValue.h"

NS_CC_BEGIN

struct sImageTGA;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** @brief CCTileMapAtlas 是一个 CCAtlasNode的子类.
 
 它知道如何基于瓦片渲染地图
 瓦片必须是.PNG格式，地图必须是.TGA文件
 
 了解更多关于格式的信息，请看这个地址:
 http://www.cocos2d-iphone.org/archives/27
 
 所有CCAtlasNode的特性在CCTileMapAtlas都是有效的
 
 重要提示:
 这个类不赞成使用，它的存在只是为了保持一致性
 你不应该使用这个类
 作为代替，请使用更新的TMX文件格式: CCTMXTiledMap
 */

class CC_DLL TileMapAtlas : public AtlasNode 
{
public:
    /** 用一个在地图文件里指定宽、高的瓦片文件（贴图集）来初始化CCTileMap
     * 通过使用TextureMgr，瓦片文件将被加载
     */
    static TileMapAtlas * create(const std::string& tile, const std::string& mapFile, int tileWidth, int tileHeight);
    /**
     * @js ctor
     */
    TileMapAtlas();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TileMapAtlas();
    
    /** 用一个在地图文件里指定宽、高的瓦片文件（贴图集）来初始化CCTileMap
     * 通过使用TextureMgr，文件将被加载
     */
    bool initWithTileFile(const std::string& tile, const std::string& mapFile, int tileWidth, int tileHeight);

    /** 从x,y位置返回一个瓦片
     * 此时只有R通道被使用
     */
    Color3B getTileAt(const Vec2& position) const;
    CC_DEPRECATED_ATTRIBUTE Color3B tileAt(const Vec2& position) const { return getTileAt(position); };
    /** 在x,y位置设置一个瓦片
     * 此时只有R通道被使用
     */
    void setTile(const Color3B& tile, const Vec2& position);
    /** 从内存里dealloc地图 */
    void releaseMap();
    
    inline struct sImageTGA* getTGAInfo() const { return _TGAInfo; };
    inline void setTGAInfo(struct sImageTGA* TGAInfo) { _TGAInfo = TGAInfo; };

protected:
    void loadTGAfile(const std::string& file);
    void calculateItemsToRender();
    void updateAtlasValueAt(const Vec2& pos, const Color3B& value, int index);
    void updateAtlasValues();


    //! x,y到贴图集字典
    ValueMap _posToAtlasIndex;
    //! 渲染的瓦片地图
    int _itemsToRender;
    /** TileMap 信息 */
    struct sImageTGA* _TGAInfo;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTILE_MAP_ATLAS__

