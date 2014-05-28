/****************************************************************************
Copyright (c) 2010 ForzeField Studios S.L. http://forzefield.com
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
#ifndef __CCVECTOR_H__
#define __CCVECTOR_H__

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include <vector>
#include <functional>
#include <algorithm> // for std::find

NS_CC_BEGIN

template<class T>
class CC_DLL Vector
{
public:
    // ------------------------------------------
    // Iterators
    // ------------------------------------------
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    
    typedef typename std::vector<T>::reverse_iterator reverse_iterator;
    typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
    
    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    
    const_iterator cbegin() const { return _data.cbegin(); }
    const_iterator cend() const { return _data.cend(); }
    
    reverse_iterator rbegin() { return _data.rbegin(); }
    const_reverse_iterator rbegin() const { return _data.rbegin(); }
    
    reverse_iterator rend() { return _data.rend(); }
    const_reverse_iterator rend() const { return _data.rend(); }
    
    const_reverse_iterator crbegin() const { return _data.crbegin(); }
    const_reverse_iterator crend() const { return _data.crend(); }
    
    /** 构造函数 */
    Vector<T>()
    : _data()
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
    }
    
    /** 带参数容量的构造函数 */
    explicit Vector<T>(ssize_t capacity)
    : _data()
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
        CCLOGINFO("In the default constructor with capacity of Vector.");
        reserve(capacity);
    }

    /** 析构函数 */
    ~Vector<T>()
    {
        CCLOGINFO("In the destructor of Vector.");
        clear();
    }

    /** 拷贝构造函数 */
    Vector<T>(const Vector<T>& other)
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
        CCLOGINFO("In the copy constructor!");
        _data = other._data;
        addRefForAllObjects();
    }
    
    /** 转移构造函数 */
    Vector<T>(Vector<T>&& other)
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
        CCLOGINFO("In the move constructor of Vector!");
        _data = std::move(other._data);
    }
    
    /** 拷贝赋值操作符 */
    Vector<T>& operator=(const Vector<T>& other)
    {
        if (this != &other) {
            CCLOGINFO("In the copy assignment operator!");
            clear();
            _data = other._data;
            addRefForAllObjects();
        }
        return *this;
    }
    
    /** 转移赋值操作符 */
    Vector<T>& operator=(Vector<T>&& other)
    {
        if (this != &other) {
            CCLOGINFO("In the move assignment operator!");
            clear();
            _data = std::move(other._data);
        }
        return *this;
    }
    
// Don't uses operator since we could not decide whether it needs 'retain'/'release'.
//    T& operator[](int index)
//    {
//        return _data[index];
//    }
//    
//    const T& operator[](int index) const
//    {
//        return _data[index];
//    }
    
	/** @brief 请求改变向量(vector)的容量 
     *  @param capacity 向量(vector)的最小容量.
     *         如果n比当前向量(vector)的容量大, 
     *         这个函数会重新分配向量(vector)的存储空间，将容量提升到n(或者更大).
     */
    void reserve(ssize_t n)
    {
        _data.reserve(n);
    }
    
	 /** @brief 返回当前分配给容器的存储空间的大小，按照容器中的元素个数来表示.
     *  @note 这个容量没必要和向量(vector)的size相等. 
     *        它可以相等或者更大。如果更大的话，就会有额外的空间来适应其增长，这样就不必要在每次插入操作时都重新分配空间
     *  @return 当前分配给向量(vector)的存储容量的大小，这个大小是按照它能够存放的元素的个数计算的
     */
    ssize_t capacity() const
    {
        return _data.capacity();
    }
    
	 /** @brief 返回向量(vector)中元素的数目.
     *  @note 这是向量(vector)中存储的实际对象的数目, 不必要和它的存储容量相等.
     *  @return 容器中元素的实际数目.
     */
    ssize_t size() const
    {
        return  _data.size();
    }

	 /** @brief 返回向量(vector)是否是空的 (比如，他的size是否是0).
     *  @note 这个函数不会以任何方式改变容器。如果想清除向量(vector)的内容，请参考 Vector<T>::clear
     */
    bool empty() const
    {
        return _data.empty();
    }
    
    /** 返回向量(vector)可以容纳的最大元素数目. */
    ssize_t max_size() const
    {
        return _data.max_size();
    }
    
    /** 返回特定对象的索引, 如果向量(vector)中不包含此对象，则返回UINT_MAX */
    ssize_t getIndex(T object) const
    {
        auto iter = std::find(_data.begin(), _data.end(), object);
        if (iter != _data.end())
            return iter - _data.begin();

        return -1;
    }

    /** @brief Find the object in the vector.
     *  @return Returns an iterator to the first element in the range [first,last) that compares equal to val. 
     *          If no such element is found, the function returns last.
     */
	 /** @brief 在向量(vector)中查找对象.
     *  @return 返回一个指向区间[first, last)中的第一个与要查找的值相等元素的迭代器. 
     *          如果没有找到这个元素，函数返回迭代器last.
     */
    const_iterator find(T object) const
    {
        return std::find(_data.begin(), _data.end(), object);
    }
    
    iterator find(T object)
    {
        return std::find(_data.begin(), _data.end(), object);
    }
    
    /** 返回向量(vector)中位置为'index'的元素 */
    T at(ssize_t index) const
    {
        CCASSERT( index >= 0 && index < size(), "index out of range in getObjectAtIndex()");
        return _data[index];
    }
	
    /** 返回向量(vector)中的第一个元素. */
    T front() const
    {
        return _data.front();
    }
    
    /** 返回向量(vector)中的最后一个元素. */
    T back() const
    {
        return _data.back();
    }

    /** 返回向量(vector)中的一个随机元素. */
    T getRandomObject() const
    {
        if (!_data.empty())
        {
            ssize_t randIdx = rand() % _data.size();
            return *(_data.begin() + randIdx);
        }
        return nullptr;
    }

    /** 返回一个Boolean值以指示对象object是否在向量(vector)中. */
    bool contains(T object) const
    {
        return( std::find(_data.begin(), _data.end(), object) != _data.end() );
    }

    /** 如果两个向量(vector)相等，则返回true */
    bool equals(const Vector<T> &other)
    {
        ssize_t s = this->size();
        if (s != other.size())
            return false;
        
        for (ssize_t i = 0; i < s; i++)
        {
            if (this->at(i) != other.at(i))
            {
                return false;
            }
        }
        return true;
    }

    // Adds objects
    
	/** @brief 在向量(vector)的末尾添加一个新的元素，位于当前最后一个元素之后
     *  @note 这个函数会将容器的size增加1,
     *        当且仅当新的向量(vector)的size超过当前的容量时
     *        此函数会引起自动为已分配的存储空间重新分配.
     */
    void pushBack(T object)
    {
        CCASSERT(object != nullptr, "The object should not be nullptr");
        _data.push_back( object );
        object->retain();
    }
    
    /** 将一个已存在的向量(vector)的所有元素加到当前向量(vector)的末尾. */
    void pushBack(const Vector<T>& other)
    {
        for(const auto &obj : other) {
            _data.push_back(obj);
            obj->retain();
        }
    }
	
	/** @brief 在特定索引位置插入一个特定元素 
     *  @note 通过在指定索引'index'前插入一个新元素,向量(vector)会被扩展
     *        这会使得容器的size变大,增加的数目等于插入元素的数目.
     *        当且仅当新的向量(vector)的size超过当前的容量时 
     *        此函数会引起自动为已分配的存储空间重新分配..
     */
    void insert(ssize_t index, T object)
    {
        CCASSERT(index >= 0 && index <= size(), "Invalid index!");
        CCASSERT(object != nullptr, "The object should not be nullptr");
        _data.insert((std::begin(_data) + index), object);
        object->retain();
    }
    
    // Removes Objects

	 /** 删除向量(vector)最后一个元素, 
     *  有效地将容器的size减小1. 同时减小被删除对象的引用计数
     */
    void popBack()
    {
        CCASSERT(!_data.empty(), "no objects added");
        auto last = _data.back();
        _data.pop_back();
        last->release();
    }
    
	/** @brief 删除向量(vector)中的特定对象 .
     *  @param object 要被删除的对象.
     *  @param removeAll 是否要删除与指定对象的值相同的所有元素
     *                   如果值为'false', 函数会删除查找到的第一个元素.
     */
    void eraseObject(T object, bool removeAll = false)
    {
        CCASSERT(object != nullptr, "The object should not be nullptr");
        
        if (removeAll)
        {
            for (auto iter = _data.begin(); iter != _data.end();)
            {
                if ((*iter) == object)
                {
                    iter = _data.erase(iter);
                    object->release();
                }
                else
                {
                    ++iter;
                }
            }
        }
        else
        {
            auto iter = std::find(_data.begin(), _data.end(), object);
            if (iter != _data.end())
            {
                _data.erase(iter);
                object->release();
            }
        }
    }
	
	/** @brief 通过迭代器在向量(vector)中删除对象. 
     *  @param position 指向向量(vector)中要被删除的单个元素的迭代器.
     *  @return 一个指向新位置的元素的迭代器，这个元素紧跟在由此函数调用删除的对象之后
     *          如果这个操作删除的是序列最后一个元素，那么返回的是指向容器最后一个元素之后的迭代器.
     */
    iterator erase(iterator position)
    {
        CCASSERT(position >= _data.begin() && position < _data.end(), "Invalid position!");
        (*position)->release();
        return _data.erase(position);
    }
    
	/** @brief 删除向量(vector)中在一个区间内的元素 (  [first, last)  ).
     *  @param first 区间的起始
     *  @param last 区间的结束, 'last' 不会被使用, 只是用来指示区间的末尾.
     *  @return 一个指向新位置的元素的迭代器，这个元素紧跟在由此函数调用删除的对象之后.
     *          如果这个操作删除的是序列最后一个元素，那么返回的是指向容器最后一个元素之后的迭代器.
     */
    iterator erase(iterator first, iterator last)
    {
        for (auto iter = first; iter != last; ++iter)
        {
            (*iter)->release();
        }
        
        return _data.erase(first, last);
    }
    
    /** @brief 删除向量(vector)中给定索引的元素.
     *  @param index 向量(vector)中要被删除的元素的索引.
     *  @return  一个指向新位置的元素的迭代器，这个元素紧跟在由此函数调用删除的对象之后.
     *          如果这个操作删除的是序列最后一个元素，那么返回的是指向容器最后一个元素之后的迭代器.
     */
    iterator erase(ssize_t index)
    {
        CCASSERT(!_data.empty() && index >=0 && index < size(), "Invalid index!");
        auto it = std::next( begin(), index );
        (*it)->release();
        return _data.erase(it);
    }

	/** @brief 删除向量(vector)中的所有元素 (这些元素被销毁), 只留下一个size为0的容器.
     *  @note 在向量(vector)中的所有元素都会被释放 (减小引用计数).
     */
    void clear()
    {
        for( auto it = std::begin(_data); it != std::end(_data); ++it ) {
            (*it)->release();
        }
        _data.clear();
    }

    // Rearranging Content

    /** 交换两个元素 */
    void swap(T object1, T object2)
    {
        ssize_t idx1 = getIndex(object1);
        ssize_t idx2 = getIndex(object2);

        CCASSERT(idx1>=0 && idx2>=0, "invalid object index");

        std::swap( _data[idx1], _data[idx2] );
    }

    /** 交换两个指定索引处的元素 */
    void swap(ssize_t index1, ssize_t index2)
    {
        CCASSERT(index1 >=0 && index1 < size() && index2 >= 0 && index2 < size(), "Invalid indices");

        std::swap( _data[index1], _data[index2] );
    }

    /** 将指定索引处的对象替换为另一个对象. */
    void replace(ssize_t index, T object)
    {
        CCASSERT(index >= 0 && index < size(), "Invalid index!");
        CCASSERT(object != nullptr, "The object should not be nullptr");
        
        _data[index]->release();
        _data[index] = object;
        object->retain();
    }

    /** 将向量(vector)逆序 */
    void reverse()
    {
        std::reverse( std::begin(_data), std::end(_data) );
    }
    
    /** 收缩向量(vector)使得分配的内存大小与元素的数目保持一致 */
    void shrinkToFit()
    {
        _data.shrink_to_fit();
    }
    
protected:
    
    /** 对向量(vector)中的所有对象增加引用 */
    void addRefForAllObjects()
    {
        for(const auto &obj : _data) {
            obj->retain();
        }
    }
    
    std::vector<T> _data;
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCVECTOR_H__
