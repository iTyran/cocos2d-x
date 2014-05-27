/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __cocos2dx__ccUTF8__
#define __cocos2dx__ccUTF8__

#include "base/CCPlatformMacros.h"
#include <vector>
#include <string>

NS_CC_BEGIN

namespace StringUtils {

/**
 *  @brief  utf8字符串转换为utf16字符串
 *  @param  参数utf8即需要进行转换的utf8字符串
 *  @param  参数outUtf16即转换输出的结果utf16字符串
 *  @return 如果转换成功返回true，否则返回false
 *  @note   在使用\p outUtf16之前请检查返回值
 *  e.g.
 *  @code
 *    std::u16string utf16;
 *    bool ret = StringUtils::UTF8ToUTF16("你好hello", utf16);
 *    if (ret) {
 *        do_some_thing_with_utf16(utf16);
 *    }
 *  @endcode
 */
CC_DLL bool UTF8ToUTF16(const std::string& utf8, std::u16string& outUtf16);

/**
 *  @brief  utf16字符串转换为utf8字符串
 *  @param  参数utf16即需要进行转换的utf8字符串
 *  @param  参数outUtf8即转换输出的结果utf16字符串
 *  @return 如果转换成功返回true，否则返回false
 *  @note   在使用\p outUtf8之前请检查返回值
 *  e.g.
 *  @code
 *    std::string utf8;
 *    bool ret = StringUtils::UTF16ToUTF8(u"\u4f60\u597d", utf16);
 *    if (ret) {
 *        do_some_thing_with_utf8(utf8);
 *    }
 *  @endcode
 */
CC_DLL bool UTF16ToUTF8(const std::u16string& utf16, std::string& outUtf8);

/**
 *  @brief       去掉char16_t类型容器(vector)结尾的unicode格式空格
 */
CC_DLL void trimUTF16Vector(std::vector<char16_t>& str);

/**
 *  @brief       给定字符是否是一个空白字符
 *
 *  @param ch    参数ch是unicode格式的字符
 *  @returns     返回给定字符是否是一个空白字符
 *
 *  @see http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 *
 */
CC_DLL bool isUnicodeSpace(char16_t ch);

/**
 *  @brief       给定字符是否是中文/日文/韩文字符
 *
 *  @param ch    参数ch是unicode格式字符
 *  @returns     返回给定字符是否是一个中文字符
 *
 *  @see http://www.searchtb.com/2012/04/chinese_encode.html
 *  @see http://tieba.baidu.com/p/748765987
 *
 */
CC_DLL bool isCJKUnicode(char16_t ch);

/**
 *  @brief   返回给定字符的字符串长度 .
 *
 *  @param   参数utf8是一个UTF-8编码的字符串 .
 *  @returns 返回给定字符的字符串长度
 */
CC_DLL long getCharacterCountInUTF8String(const std::string& utf8);

/**
 *  @brief   获得最后一个不同于给定字符的字符索引
 *
 *  @param   参数str即需要进行搜索的字符串 .
 *  @param   参数c即需要被寻找的字符 .
 *
 *  @returns 返回最后一个不同于c的字符索引
 *
 */
CC_DLL unsigned int getIndexOfLastNotChar16(const std::vector<char16_t>& str, char16_t c);

/**
 *  @brief  从一个给定的utf16字符串获得char16_t类型容器(vector)
 */
CC_DLL std::vector<char16_t> getChar16VectorFromUTF16String(const std::u16string& utf16);

} // namespace StringUtils {

/**
 * 返回给定字符在UTF16格式字符串中得字符个数
 * @param      参数str指向一个UTF-16编码字符串的开头， 必须是一个以NULL为终结的UTF8字符串
 * @deprecated 请使用c++11 `std::u16string::length`来代替，不要直接使用`unsigned short*`
 */
CC_DEPRECATED_ATTRIBUTE CC_DLL int cc_wcslen(const unsigned short* str);

/** 去掉UTF8字符串结尾的空格字符
 *  @deprecated 请使用`StringUtils::trimUTF16Vector`代替
 */

CC_DEPRECATED_ATTRIBUTE void cc_utf8_trim_ws(std::vector<unsigned short>* str);

/**
 * 给定字符是否是一个空白字符.
 *
 * @param ch    参数ch是unicode格式的字符
 * @returns     返回给定字符是否一个空白字符
 * @deprecated  请使用`StringUtils::isUnicodeSpace`代替
 *
 * @see http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 * */
CC_DEPRECATED_ATTRIBUTE bool isspace_unicode(unsigned short ch);

/**
 * 给定字符是否是中文/日文/韩文字符
 *
 * @param ch    参数ch是unicode格式的字符
 * @returns     返回指定字符是否是一个中文字符
 * @deprecated  请使用`StringUtils::isCJKUnicode`代替
 *
 * @see http://www.searchtb.com/2012/04/chinese_encode.html
 * @see http://tieba.baidu.com/p/748765987
 * */
CC_DEPRECATED_ATTRIBUTE bool iscjk_unicode(unsigned short ch);

/**
 * 返回给定字符的字符串长度.
 *
 * @param p      参数p指向一个UTF-8编码字符串的开头，必须是一个以NULL为终结的UTF8字符串
 * @param max    参数max从3.1起不再使用，保留它只是为了向后兼容
 * @deprecated   请使用`StringUtils::getCharacterCountInUTF8String`代替
 * @returns      返回值是给定字符的字符串长度
 **/
CC_DEPRECATED_ATTRIBUTE long cc_utf8_strlen (const char * p, int max = -1);

/**
 * 寻找最后一个不同于给定字符的字符 .
 *
 * @param str    参数str即需要进行搜索的字符串 .
 * @param c      参数c即需要被寻找的字符 .
 * @deprecated   请使用`StringUtils::getIndexOfLastNotChar16`代替
 * @returns      返回值是最后一个不同于c的字符的索引  .
 * */
CC_DEPRECATED_ATTRIBUTE unsigned int cc_utf8_find_last_not_char(const std::vector<unsigned short>& str, unsigned short c);

/**
 *  @brief      从给定的utf16格式字符串得到一个`unsigned short`类型的容器(vector)
 *  @deprecated 请使用`StringUtils::getChar16VectorFromUTF16String`代替
 */
CC_DEPRECATED_ATTRIBUTE std::vector<unsigned short> cc_utf16_vec_from_utf16_str(const unsigned short* str);

/**
 * 从一个c字符串创建一个utf8字符串，当结果为空是转换结束.
 *
 * @param      参数str_old指向一个c字符串的开头，必须是一个以NULL为终结的UTF8字符串
 * @param      参数length从3.1起不再使用，，保留它只是为了向后兼容
 * @param      参数rUtf16Size即返回的UTF16字符串的字符个数
 * @deprecated 请使用`StringUtils::UTF8ToUTF16`代替
 * @returns    返回值是新创建的utf16格式字符串，必须用`delete[]`释放。如果有错误发生，返回%NULL
 * */
CC_DEPRECATED_ATTRIBUTE unsigned short* cc_utf8_to_utf16(const char* str_old, int length = -1, int* rUtf16Size = nullptr);

/**
 * 转换一个UTF-16字符串为UTF-8格式。当结果为空是转换结束
 *
 * @param      参数utf16是一个utf16编码的字符串，必须是一个以NULL为终结的UTF16字符串
 * @param      参数len从3.1起不再使用，保留它只是为了向后兼容
 * @param      参数items_read从3.1起不再使用， 保留它只是为了向后兼容
 * @param      参数items_written从3.1起不再使用， 保留它只是为了向后兼容
 * @deprecated 请使用`StringUtils::UTF16ToUTF8`来代替
 * @returns    返回值是一个指针，指向新分配的UTF-8格式字符串。这个值必须用`delete[]`释放。如果有错误发生，返回%NULL
 **/
CC_DEPRECATED_ATTRIBUTE char * cc_utf16_to_utf8 (const unsigned short  *str,
                  int             len = -1,
                  long            *items_read = nullptr,
                  long            *items_written = nullptr);


NS_CC_END

#endif /* defined(__cocos2dx__ccUTF8__) */
