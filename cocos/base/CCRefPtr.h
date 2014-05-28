/****************************************************************************
 Copyright (c) 2014     PlayFirst Inc.
 Copyright (c) 2014     Chukong Technologies Inc.
 
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

#ifndef __CC_REF_PTR_H__
#define __CC_REF_PTR_H__

#include "base/CCRef.h"
#include "base/ccMacros.h"
#include <type_traits>

NS_CC_BEGIN


/**
 *实用功能/支持宏。定义使RefPtr<T>包含类型，如'常量T'，因为我们不这样做
 *关于保留（）/释放（）为影响国家的可变性。
 */
#define CC_REF_PTR_SAFE_RETAIN(ptr)\
    \
    do\
    {\
        if (ptr)\
        {\
            const_cast<Ref*>(static_cast<const Ref*>(ptr))->retain();\
        }\
    \
    }   while (0);

#define CC_REF_PTR_SAFE_RELEASE(ptr)\
    \
    do\
    {\
        if (ptr)\
        {\
            const_cast<Ref*>(static_cast<const Ref*>(ptr))->release();\
        }\
    \
    }   while (0);

#define CC_REF_PTR_SAFE_RELEASE_NULL(ptr)\
    \
    do\
    {\
        if (ptr)\
        {\
            const_cast<Ref*>(static_cast<const Ref*>(ptr))->release();\
            ptr = nullptr;\
        }\
    \
    }   while (0);

/**
 *它保持着强劲的引用cocos2dx的cocos2d::Ref*类型的对象包装类。
 *类似的概念来提高智能指针。
 *
 *允许使用的RAII成语与Cocos2dx对象，并有助于自动一些比较
 *平凡的指针初始化和清理的任务。
 *
 *类本身是仿照C++11的std::shared_ptr的，并改掉保留一些方法
 *和功能与std::shared_ptr的一致。
 */
template <typename T> class RefPtr
{
public:
    
    inline RefPtr()
    :
        _ptr(nullptr)
    {
        
    }
    
    inline RefPtr(RefPtr<T> && other)
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    inline RefPtr(T * ptr)
    :
        _ptr(const_cast<typename std::remove_const<T>::type*>(ptr))     // Const cast allows RefPtr<T> to reference objects marked const too.
    {
        CC_REF_PTR_SAFE_RETAIN(_ptr);
    }
    
    inline RefPtr(std::nullptr_t ptr)
    :
        _ptr(nullptr)
    {
        
    }
    
    inline RefPtr(const RefPtr<T> & other)
    :
        _ptr(other._ptr)
    {
        CC_REF_PTR_SAFE_RETAIN(_ptr);
    }
    
    inline ~RefPtr()
    {
        CC_REF_PTR_SAFE_RELEASE_NULL(_ptr);
    }
    
    inline RefPtr<T> & operator = (const RefPtr<T> & other)
    {
        if (other._ptr != _ptr)
        {
            CC_REF_PTR_SAFE_RETAIN(other._ptr);
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = other._ptr;
        }
        
        return *this;
    }
    
    inline RefPtr<T> & operator = (RefPtr<T> && other)
    {
        if (&other != this)
        {
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        
        return *this;
    }
    
    inline RefPtr<T> & operator = (T * other)
    {
        if (other != _ptr)
        {
            CC_REF_PTR_SAFE_RETAIN(other);
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = const_cast<typename std::remove_const<T>::type*>(other);     //常量转换(Const cast)允许RefPtr<T>引用的对象也标记为const的.
        }
        
        return *this;
    }
    
    inline RefPtr<T> & operator = (std::nullptr_t other)
    {
        CC_REF_PTR_SAFE_RELEASE_NULL(_ptr);
        return *this;
    }
    
    //注意：在使用reinterpret_cast<>代替static_cast<>，因为它不需要类型信息。
    //因为在编译时我们核实正确的类型转换，construction/assign并不需要知道类型信息
    //这里不需要的类型信息，使我们能够在头文件中的内联函数使用这些操作时，
    //这个类指向的类型是唯一的向前引用。
    inline operator T * () const { return reinterpret_cast<T*>(_ptr); }
    
    inline T & operator * () const
    {
        CCASSERT(_ptr, "Attempt to dereference a null pointer!");
        return reinterpret_cast<T&>(*_ptr);
    }
    
    inline T * operator->() const
    {
        CCASSERT(_ptr, "Attempt to dereference a null pointer!");
        return reinterpret_cast<T*>(_ptr);
    }
    
    inline T * get() const { return reinterpret_cast<T*>(_ptr); }
    
    
    inline bool operator == (const RefPtr<T> & other) const { return _ptr == other._ptr; }
    
    inline bool operator == (const T * other) const { return _ptr == other; }
    
    inline bool operator == (typename std::remove_const<T>::type * other) const { return _ptr == other; }
    
    inline bool operator == (const std::nullptr_t other) const { return _ptr == other; }
    
    
    inline bool operator != (const RefPtr<T> & other) const { return _ptr != other._ptr; }
    
    inline bool operator != (const T * other) const { return _ptr != other; }
    
    inline bool operator != (typename std::remove_const<T>::type * other) const { return _ptr != other; }
    
    inline bool operator != (const std::nullptr_t other) const { return _ptr != other; }
    
    
    inline bool operator > (const RefPtr<T> & other) const { return _ptr > other._ptr; }
    
    inline bool operator > (const T * other) const { return _ptr > other; }
    
    inline bool operator > (typename std::remove_const<T>::type * other) const { return _ptr > other; }
    
    inline bool operator > (const std::nullptr_t other) const { return _ptr > other; }
    
    
    inline bool operator < (const RefPtr<T> & other) const { return _ptr < other._ptr; }
    
    inline bool operator < (const T * other) const { return _ptr < other; }
    
    inline bool operator < (typename std::remove_const<T>::type * other) const { return _ptr < other; }
    
    inline bool operator < (const std::nullptr_t other) const { return _ptr < other; }
    
        
    inline bool operator >= (const RefPtr<T> & other) const { return _ptr >= other._ptr; }
    
    inline bool operator >= (const T * other) const { return _ptr >= other; }
    
    inline bool operator >= (typename std::remove_const<T>::type * other) const { return _ptr >= other; }
    
    inline bool operator >= (const std::nullptr_t other) const { return _ptr >= other; }
    
        
    inline bool operator <= (const RefPtr<T> & other) const { return _ptr <= other._ptr; }
    
    inline bool operator <= (const T * other) const { return _ptr <= other; }
    
    inline bool operator <= (typename std::remove_const<T>::type * other) const { return _ptr <= other; }
    
    inline bool operator <= (const std::nullptr_t other) const { return _ptr <= other; }
    
        
    inline operator bool() const { return _ptr != nullptr; }
        
    inline void reset()
    {
        CC_REF_PTR_SAFE_RELEASE_NULL(_ptr);
    }
        
    inline void swap(RefPtr<T> & other)
    {
        if (&other != this)
        {
            Ref * tmp = _ptr;
            _ptr = other._ptr;
            other._ptr = tmp;
        }
    }
    
    /**
     *此函数分配给这个RefPtr<T>但不增加指向对象的引用计数。
     *有用的分配通过new操作符的RefPtr<T>创建的对象。基本上是在场景用来
     *其中RefPtr<T>有对象的初始所有权。
     *
     * 例如：
     * RefPtr<cocos2d::Image>image;
     * image.weakAssign（new cocos2d::Image());
     *
     代替：
     *      RefPtr<cocos2d::Image> image;
     *      image = new cocos2d::Image();
     *      image->release(); //必需的，因为new创建的对象已经具有'1引用计数“。
     */
    inline void weakAssign(const RefPtr<T> & other)
    {
        CC_REF_PTR_SAFE_RELEASE(_ptr);
        _ptr = other._ptr;
    }
    
private:
    Ref * _ptr;
};
    
/**
 *静态转换RefPtr之间类型。
 */
template<class T, class U> RefPtr<T> static_pointer_cast(const RefPtr<U> & r)
{
    return RefPtr<T>(static_cast<T*>(r.get()));
}


/**
 *动态转换RefPtr之间的类型。
 */
template<class T, class U> RefPtr<T> dynamic_pointer_cast(const RefPtr<U> & r)
{
    return RefPtr<T>(dynamic_cast<T*>(r.get()));
}

/**
 * Done with these macros.
 */
/**
 *用这些宏完成。
 */
#undef CC_REF_PTR_SAFE_RETAIN
#undef CC_REF_PTR_SAFE_RELEASE
#undef CC_REF_PTR_SAFE_RELEASE_NULL

NS_CC_END

#endif  // __CC_REF_PTR_H__
