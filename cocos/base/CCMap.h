/****************************************************************************
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

#ifndef __CCMAP_H__
#define __CCMAP_H__

#define USE_STD_UNORDERED_MAP 1

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include <vector>

#if USE_STD_UNORDERED_MAP
#include <unordered_map>
#else
#include <map>
#endif

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

template <class K, class V>
class CC_DLL Map
{
public:
    // ------------------------------------------
    // 迭代器(Iterators)
    // ------------------------------------------
#if USE_STD_UNORDERED_MAP
    typedef std::unordered_map<K, V> RefMap;
#else
    typedef std::map<K, V> RefMap;
#endif
    
    typedef typename RefMap::iterator iterator;
    typedef typename RefMap::const_iterator const_iterator;
    
    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    
    const_iterator cbegin() const { return _data.cbegin(); }
    const_iterator cend() const { return _data.cend(); }
    
    /** Default constructor */
    Map<K, V>()
    : _data()
    {
        static_assert(std::is_convertible<V, Ref*>::value, "Invalid Type for cocos2d::Map<K, V>!");
        CCLOGINFO("In the default constructor of Map!");
    }
    
    /** 指定容量构造 */
    explicit Map<K, V>(ssize_t capacity)
    : _data()
    {
        static_assert(std::is_convertible<V, Ref*>::value, "Invalid Type for cocos2d::Map<K, V>!");
        CCLOGINFO("In the constructor with capacity of Map!");
        _data.reserve(capacity);
    }
    
    /** 拷贝构造函数 */
    Map<K, V>(const Map<K, V>& other)
    {
        static_assert(std::is_convertible<V, Ref*>::value, "Invalid Type for cocos2d::Map<K, V>!");
        CCLOGINFO("In the copy constructor of Map!");
        _data = other._data;
        addRefForAllObjects();
    }
    
    /** 移动构造函数（Move constructor） */
    Map<K, V>(Map<K, V>&& other)
    {
        static_assert(std::is_convertible<V, Ref*>::value, "Invalid Type for cocos2d::Map<K, V>!");
        CCLOGINFO("In the move constructor of Map!");
        _data = std::move(other._data);
    }
    
    /** 虚构函数
     *  它会释放map中的所有对象.
     */
    ~Map<K, V>()
    {
        CCLOGINFO("In the destructor of Map!");
        clear();
    }
    
    /** 设置map的容量 */
    void reserve(ssize_t capacity)
    {
#if USE_STD_UNORDERED_MAP
        _data.reserve(capacity);
#endif
    }
    
    /** 返回 Map容器中桶的容量. */
    ssize_t bucketCount() const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket_count();
#else
        return 0;
#endif
    }
    
    /** 返回n桶中元素的数量 . */
    ssize_t bucketSize(ssize_t n) const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket_size(n);
#else
        return 0;
#endif
    }
    
    /** 返回关键字k所在位置桶的数量. */
    ssize_t bucket(const K& k) const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket(k);
#else
        return 0;
#endif
    }
    
    /** map中元素的数量. */
    ssize_t size() const
    {
        return _data.size();
    }
    
    /** 返回一个布尔值表示该map容器是否为空，如果为空它的大小为0.
     *  @note 此方法不会以任何方式修改容器的内容.
     *        已存在成员函数nordered_map::clear 清理数组对象的内容.
     */
    bool empty() const
    {
        return _data.empty();
    }
    
    /** 返回map中所有关键字key的集合 */
    std::vector<K> keys() const
    {
        std::vector<K> keys;

        if (!_data.empty())
        {
            keys.reserve(_data.size());
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                keys.push_back(iter->first);
            }
        }
        return keys;
    }
    
    /** 返回所有匹配该对象的key */
    std::vector<K> keys(V object) const
    {
        std::vector<K> keys;
        
        if (!_data.empty())
        {
            keys.reserve(_data.size() / 10);
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                if (iter->second == object)
                {
                    keys.push_back(iter->first);
                }
            }
        }
        
        keys.shrink_to_fit();
        
        return keys;
    }
    
    /** @brief 返回map中key映射的元素的值 .
     *  @note 如果容器中没有匹配的该key的元素，此方法返回 nullptr.
     *  @param key 传人Key的值是元素的键值映射的值.
     *       成员类型K 是容器中元素的keys. Map < K、V >中定义的别名,它的第一个模板参数(键).
     */
    const V at(const K& key) const
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
        return nullptr;
    }
    
    V at(const K& key)
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
        return nullptr;
    }
    
    /** @brief 用参数key搜索容器的一个元素，如果找到返回iterator，相反返回 Map<K, V>::end 的iterator（容器中的最后一个元素）
     *  @param key 用于搜索的Key.
     *       成员类型K 是容器中元素的keys. Map < K、V >中定义的别名,它的第一个模板参数(键).
     */
    const_iterator find(const K& key) const
    {
        return _data.find(key);
    }
    
    iterator find(const K& key)
    {
        return _data.find(key);
    }
    
    /** @brief 插入新元素到map.
     *  @note 如果容器中已经包含该key,此方法将移除容器中旧的键值对(key, object)然后插入.
     *  @param key 插入的Key键.
     *  @param object 插入的对象.
     */
    void insert(const K& key, V object)
    {
        CCASSERT(object != nullptr, "Object is nullptr!");
        erase(key);
        _data.insert(std::make_pair(key, object));
        object->retain();
    }
    
    /** @brief 指定 iterator 从 Map<K, V> 容器中移除元素.
     *  @param position Iterator 指向的单个元素被从 Map<K, V> 移除.
     *         成员类型 const_iterator 是一个前向 iterator 类型.
     */
    iterator erase(const_iterator position)
    {
        CCASSERT(position != _data.cend(), "Invalid iterator!");
        position->second->release();
        return _data.erase(position);
    }
    
    /** @brief  从Map<K, V> 容器中移除元素.
     *  @param k key对应的元素被移除.
     *       成员类型K 是容器中元素的keys. Map < K、V >中定义的别名,它的第一个模板参数(键).
     */
    size_t erase(const K& k)
    {
        auto iter = _data.find(k);
        if (iter != _data.end())
        {
            iter->second->release();
            _data.erase(iter);
            return 1;
        }
        
        return 0;
    }
    
    /** @brief 移除map中vector集合键值key相关的一些元素.
     *  @param keys 键值相关的元素被移除.
     */
    void erase(const std::vector<K>& keys)
    {
        for(const auto &key : keys) {
            this->erase(key);
        }
    }
    
    /** Map<K,V>容器中的所有元素被丢弃:
     * 他们的引用计数会减1, 且被从容器中移除,直到容器大小为0
     */
    void clear()
    {
        for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
        {
            iter->second->release();
        }
        
        _data.clear();
    }
    
    /** @brief 获取 map中的一个随机对象
     *  @return 返回非空map中的一个随机对象, 相反返回nullptr.
     */
    V getRandomObject() const
    {
        if (!_data.empty())
        {
            ssize_t randIdx = rand() % _data.size();
            const_iterator randIter = _data.begin();
            std::advance(randIter , randIdx);
            return randIter->second;
        }
        return nullptr;
    }
    
    // Don't uses operator since we could not decide whether it needs 'retain'/'release'.
    //    V& operator[] ( const K& key )
    //    {
    //        CCLOG("copy: [] ref");
    //        return _data[key];
    //    }
    //
    //    V& operator[] ( K&& key )
    //    {
    //        CCLOG("move [] ref");
    //        return _data[key];
    //    }
    
    //    const V& operator[] ( const K& key ) const
    //    {
    //        CCLOG("const copy []");
    //        return _data.at(key);
    //    }
    //
    //    const V& operator[] ( K&& key ) const
    //    {
    //        CCLOG("const move []");
    //        return _data.at(key);
    //    }
    
    /** 拷贝赋值运算符 */
    Map<K, V>& operator= ( const Map<K, V>& other )
    {
        if (this != &other) {
            CCLOGINFO("In the copy assignment operator of Map!");
            clear();
            _data = other._data;
            addRefForAllObjects();
        }
        return *this;
    }
    
    /** 移动赋值运算符 */
    Map<K, V>& operator= ( Map<K, V>&& other )
    {
        if (this != &other) {
            CCLOGINFO("In the move assignment operator of Map!");
            clear();
            _data = std::move(other._data);
        }
        return *this;
    }
    
protected:
    
    /** 对map中的所有元素执行retain操作 */
    void addRefForAllObjects()
    {
        for (auto iter = _data.begin(); iter != _data.end(); ++iter)
        {
            iter->second->retain();
        }
    }
    
    RefMap _data;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCMAP_H__ */
