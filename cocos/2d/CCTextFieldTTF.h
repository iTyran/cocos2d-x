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

#ifndef __CC_TEXT_FIELD_H__
#define __CC_TEXT_FIELD_H__

#include "2d/CCLabel.h"
#include "2d/CCIMEDelegate.h"

NS_CC_BEGIN

class TextFieldTTF;

/**
 * @addtogroup input
 * @{
 */

class CC_DLL TextFieldDelegate
{
public:
    virtual ~TextFieldDelegate() {}

    /**
    @brief 如果sender不想附加到IME，返回true
    */
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
    @brief 如果sender不想解除IME，返回true
    */
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }

    /**
    @brief 如果sender不想插入文本，返回true
    */
    virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(text);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
    @brief 如何sender不想删除delText，返回true
    */
    virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen)
    {
        CC_UNUSED_PARAM(sender);
        CC_UNUSED_PARAM(delText);
        CC_UNUSED_PARAM(nLen);
        return false;
    }

    /**
    @brief 如何sender不想绘图，返回true.
    */
    virtual bool onVisit(TextFieldTTF * sender,Renderer *renderer, const Mat4 &transform, bool transformUpdated)
    {
        CC_UNUSED_PARAM(sender);
        return false;
    }
};

/**
@brief 一个简单的TTF文本输入框  A simple text input field with TTF font.
*/
class CC_DLL TextFieldTTF : public Label, public IMEDelegate
{
public:
    /**
     * @js ctor
     */
    TextFieldTTF();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TextFieldTTF();

    //char * description();

    /** 由字体名称、对齐方式、, 字体大小、尺寸创建一个TextFieldTTF */
    static TextFieldTTF * textFieldWithPlaceHolder(const std::string& placeholder, const Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize);
    /** 由字体名称和大小创建一个TextFieldTTF */
    static TextFieldTTF * textFieldWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize);
    /** 由字体名称、对齐方式、, 字体大小、尺寸 初始化TextFieldTTF */
    bool initWithPlaceHolder(const std::string& placeholder, const Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize);
    /** 由字体名称和大小初始化TextFieldTTF */
    bool initWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize);

    /**
    @brief 打开键盘并接收输入
    */
    virtual bool attachWithIME();

    /**
    @brief 输入技术并关闭键盘
    */
    virtual bool detachWithIME();

    //////////////////////////////////////////////////////////////////////////
    // properties
    //////////////////////////////////////////////////////////////////////////
    /**
     * @js NA
     * @lua NA
     */
    inline TextFieldDelegate* getDelegate() const { return _delegate; };
    /**
     * @js NA
     * @lua NA
     */
    inline void setDelegate(TextFieldDelegate* delegate) { _delegate = delegate; };

    inline int getCharCount() const { return _charCount; };
    
    virtual const Color4B& getColorSpaceHolder();

    virtual void setColorSpaceHolder(const Color3B& color);
    virtual void setColorSpaceHolder(const Color4B& color);

    virtual void setTextColor(const Color4B& textColor) override;

    // input text property
    virtual void setString(const std::string& text) override;
    virtual const std::string& getString() const override;

    // place holder text property
    // place holder text displayed when there is no text in the text field.
    virtual void setPlaceHolder(const std::string& text);
    virtual const std::string& getPlaceHolder(void) const;

    virtual void setSecureTextEntry(bool value);
    virtual bool isSecureTextEntry();

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;

protected:
    //////////////////////////////////////////////////////////////////////////
    // IMEDelegate interface
    //////////////////////////////////////////////////////////////////////////

    virtual bool canAttachWithIME() override;
    virtual bool canDetachWithIME() override;
    virtual void insertText(const char * text, size_t len) override;
    virtual void deleteBackward() override;
    virtual const std::string& getContentText() override;

    TextFieldDelegate * _delegate;
    int _charCount;

    std::string _inputText;

    std::string _placeHolder;
    Color4B _colorSpaceHolder;
    Color4B _colorText;

    bool _secureTextEntry;

private:
    class LengthStack;
    LengthStack * _lens;
};

// end of input group
/// @}

NS_CC_END

#endif    // __CC_TEXT_FIELD_H__
