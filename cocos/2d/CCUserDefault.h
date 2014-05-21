/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#ifndef __SUPPORT_CCUSERDEFAULT_H__
#define __SUPPORT_CCUSERDEFAULT_H__

#include "base/CCPlatformMacros.h"
#include <string>
#include "base/CCData.h"

NS_CC_BEGIN

/**
 * @addtogroup data_storage
 * @{
 */

/**
 * UserDefault是一种小型数据库，可以利用它来存储或者读取基本类型的值。
 * 例如，调用setBoolForKey("played", true)，就会在数据库中增加一条布尔类型的记录，键为"played"，值为"true"。
 * 调用getBoolForKey("played")，则会得到键"played"所对应的值。
 * 支持以下几种基本类型：
 * bool, int, float, double, string
 */
class CC_DLL UserDefault
{
public:
	// 获取值的各种方法

    /**
	@brief 根据键获取bool类型值。如果键不存在，则返回默认值。
	 用户可以预设这个默认值，如果没有预设，则默认为false
    * @js NA
    */
    bool    getBoolForKey(const char* pKey);
    /**
     * @js NA
     */
    bool    getBoolForKey(const char* pKey, bool defaultValue);
    /**
	@brief 根据键获取int类型值。如果键不存在，则返回默认值。
	 用户可以预设这个默认值，如果没有预设，则默认为0。
    * @js NA
    */
    int     getIntegerForKey(const char* pKey);
    /**
     * @js NA
     */
    int     getIntegerForKey(const char* pKey, int defaultValue);
    /**
	@brief 根据键获取float类型值，如果键不存在，则返回默认值。
	用户可以预设这个默认值，如果没有预设，则默认为0.0f。
    * @js NA
    */
    float    getFloatForKey(const char* pKey);
    /**
     * @js NA
     */
    float    getFloatForKey(const char* pKey, float defaultValue);
    /**
	@brief 根据键获取double类型值。如果键不存在，则返回默认值。
	用户可以预设这个默认值，如果没有预设，则默认为0.0。
    * @js NA
    */
    double  getDoubleForKey(const char* pKey);
    /**
     * @js NA
     */
    double  getDoubleForKey(const char* pKey, double defaultValue);
    /**
	@brief 根据键获取string类型值，如果键不存在，则返回默认值。
	用户可以预设这个默认值，如果没有预设，则默认为空字符串("")。
    * @js NA
    */
    std::string getStringForKey(const char* pKey);
    /**
     * @js NA
     */
    std::string getStringForKey(const char* pKey, const std::string & defaultValue);
    /**
	 @brief 根据键获取binary类型值。如果键不存在，则返回默认值。
	 用户可以预设这个默认值，如果没有预设，则默认为空指针(null)。
     * @js NA
     * @lua NA
     */
    Data getDataForKey(const char* pKey);
    /**
     * @js NA
     * @lua NA
     */
    Data getDataForKey(const char* pKey, const Data& defaultValue);

    // set value methods

    /**
	 @brief 根据键设置其对应的bool类型值。（译者注：如果键不存在，则增加一条记录）
     * @js NA
     */
    void    setBoolForKey(const char* pKey, bool value);
    /**
	 @brief 根据键设置其对应的int类型值。（译者注：如果键不存在，则增加一条记录）
     * @js NA
     */
    void    setIntegerForKey(const char* pKey, int value);
    /**
	 @brief 根据键设置其对应的float类型值。（译者注：如果键不存在，则增加一条记录）
     * @js NA
     */
    void    setFloatForKey(const char* pKey, float value);
    /**
	 @brief 根据键设置其对应的double类型值。（译者注：如果键不存在，则增加一条记录）
     * @js NA
     */
    void    setDoubleForKey(const char* pKey, double value);
    /**
	 @breif 根据键设置其对应的string类型值。（译者注：如果键不存在，则增加一条记录）
     * @js NA
     */
    void    setStringForKey(const char* pKey, const std::string & value);
    /**
	 @brief 根据键设置其对应的binary类型值。（译者注：如果键不存在，则增加一条记录）
     * @js NA
     * @lua NA
     */
    void    setDataForKey(const char* pKey, const Data& value);
    /**
	 @brief 将数据写入XML文件。
     * @js NA
     */
    void    flush();

    /** 获取UserDefault的单例
     * @js NA
     * @lua NA
     */
    static UserDefault* getInstance();
    /**
     * @js NA
     */
    static void destroyInstance();

    /** @deprecated. 请使用getInstance()方法。 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static UserDefault* sharedUserDefault();
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedUserDefault();
    /**
     * @js NA
     */
    const static std::string& getXMLFilePath();
    /**
     * @js NA
     */
    static bool isXMLFileExist();

private:
    UserDefault();
    ~UserDefault();
    
    static bool createXMLFile();
    static void initXMLFilePath();
    
    static UserDefault* _userDefault;
    static std::string _filePath;
    static bool _isFilePathInitialized;
};

// end of data_storage group
/// @}

NS_CC_END

#endif // __SUPPORT_CCUSERDEFAULT_H__
