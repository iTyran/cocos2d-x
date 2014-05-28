/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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

#ifndef __PLATFOMR_CCNS_H__
#define __PLATFOMR_CCNS_H__

#include "math/CCGeometry.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

/**
@brief 返回一个核心图形长方形结构对应于给定字符串中的数据.
@param pszContent   字符串对象，其内容形式 "{{x,y},{w, h}}",
                    x是坐标系的x,y是坐标系的y,w表示宽,h表示高
                    这些组件可以代表整型或浮点值.
                    一个有效的字串形如 "{{3,2},{4,5}}".
                    字符串没有本地化,各项总是用逗号分隔
@return 返回一个代表矩形的核心图形结构
        如果字串不是有效的格式，该方法返回Rect::ZERO.
*/
Rect CC_DLL RectFromString(const std::string& str);

/**
@brief 返回一个核心图形点结构对应于给定字符串中的数据.
@param pszContent   字符串对象，其内容形式 "{x,y}",
                    x是坐标系的x,y是坐标系的y.
                    x和y的值可以是整型或浮点型.
                    一个有效的字串形如 "{3.0,2.5}".
                    字符串没有本地化,各项总是用逗号分隔

@return 返回一个代表点(point)的核心图形结构.
        如果字串不是有效的格式，该方法返回Vec2::ZERO.
*/
Vec2 CC_DLL PointFromString(const std::string& str);

/**
@brief 返回一个核心图形的大小结构对应于给定字符串中的数据 
@param pszContent   字符串对象，其内容形式 "{w,h}",
                    w表示宽,h表示高.
                    w和h的值可以是整型或浮点型.
                    一个有效的字串形如 "{3.0,2.5}".
                    字符串没有本地化,各项总是用逗号分隔
 
@return 返回一个代表矩形大小(size)的核心图形结构.
        如果字串不是有效的格式，该方法返回Size::ZERO.

*/
Size CC_DLL SizeFromString(const std::string& str);

// end of data_structure group
/// @}

NS_CC_END

#endif // __PLATFOMR_CCNS_H__


