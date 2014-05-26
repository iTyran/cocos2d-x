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
#ifndef __CCPARALLAX_NODE_H__
#define __CCPARALLAX_NODE_H__

#include "2d/CCNode.h"
/*#include "ccArray.h"*/

NS_CC_BEGIN

struct _ccArray;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** @brief 模拟视差滚动的节点
子节点根据视差比率做比父节点相对快/慢的移动。
*/
class CC_DLL ParallaxNode : public Node
{
public:
	// 创建一个视差节点。
    static ParallaxNode * create();

	// 屏蔽编译警告："Included function hides overloaded virtual functions"
    using Node::addChild;

    void addChild(Node * child, int z, const Vec2& parallaxRatio, const Vec2& positionOffset);

	/** 设置视差节点的layer数组 */
    void setParallaxArray( struct _ccArray *parallaxArray) { _parallaxArray = parallaxArray; }
	/** 获取视差节点的layer数组 */
    struct _ccArray* getParallaxArray() { return _parallaxArray; }
    const struct _ccArray* getParallaxArray() const { return _parallaxArray; }

    //
    // Overrides
    //
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void removeChild(Node* child, bool cleanup) override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;

protected:
    /** 往容器中添加一个子结点，并设置其z-order、视差比率以及位置偏移。

     @since v0.8
     * @js ctor
     */
    ParallaxNode();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParallaxNode();

    Vec2 absolutePosition();

    Vec2    _lastPosition;
    struct _ccArray* _parallaxArray;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParallaxNode);
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCPARALLAX_NODE_H__


