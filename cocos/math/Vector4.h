/**
 Copyright 2013 BlackBerry Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 */

#ifndef MATH_VEC4_H
#define MATH_VEC4_H

#include "math/CCMathBase.h"

NS_CC_MATH_BEGIN

class Mat4;

/**
 * 
 * 定义一个四维浮点向量
 */
class Vec4
{
public:

    /**
     * x方向分量
     */
    float x;

    /**
     * y方向分量
     */
    float y;

    /**
     * z方向分量
     */
    float z;

    /**
     * w方向分量
     */
    float w;

    /**
     * 构造一个初始值为零的向量
     */
    Vec4();

    /**
     * 
     * 构造一个新的向量并用特定值初始化
     * xx为x方向的值
     * yy为y方向的值
     * zz为z方向的值
     * ww为w方向的值
     */
    Vec4(float xx, float yy, float zz, float ww);

    /**
     * 用特定array来构造一个新的向量
     * 该array顺序包含向量x,y,z,w各分量的值。
     */
    Vec4(const float* array);

    /**
     * 构造一个由p1指向p2的向量。
     */
    Vec4(const Vec4& p1, const Vec4& p2);

    /**
     * 
     * 拷贝一个已有向量
     */
    Vec4(const Vec4& copy);

    /**
     * 
     * 用一个表示RGBA颜色值的整数来创建一个向量
     * 例如：Oxff0000ff表示不透明红色，向量值为（1，0，0，1）.
     * 
     * 参数color为该RGBA值
     * 返回该颜色值对应生成的向量
     */
    static Vec4 fromColor(unsigned int color);

    /**
     * 虚构函数
     */
    ~Vec4();

    /**
     * 该向量是否为零（每个分量都为零）
     * 如果该向量为零返回true，否则返回false
     */
    bool isZero() const;

    /**
     * 该向量是否为单位向量（每个分量都为1）
     * 如果该向量为单位向量则返回true,否则返回false
     */
    bool isOne() const;

    /**
     * 
     * 返回两个给定向量v1,v2之间的角度（单位为弧度）
     */
    static float angle(const Vec4& v1, const Vec4& v2);

    /**
     * 与给定向量v求和，结果保存在本向量中
     */
    void add(const Vec4& v);

    /**
     * 求向量v1与v2的和，结果保存在dst中
     */
    static void add(const Vec4& v1, const Vec4& v2, Vec4* dst);

    /**
     * 
     *  将向量限制在指定范围内，min为最小值，max为最大值。
     */
    void clamp(const Vec4& min, const Vec4& max);

    /**
     * 
     * 将给定的向量v限制在指定范围[min,max]内，结果保存在dst中。
     */
    static void clamp(const Vec4& v, const Vec4& min, const Vec4& max, Vec4* dst);

    /**
     * 
     * 计算向量与v的距离并返回
     */
    float distance(const Vec4& v) const;

    /**
     * 
     * 计算向量与v的距离的平方并返回
     * 
     *当不是必须使用精确距离的时候建议使用本方法代替distance(const Vec3& v）
     （如比较不同向量间距离大小）
     */
    float distanceSquared(const Vec4& v) const;

    /**
     * 计算向量与v的点积并返回
     */
    float dot(const Vec4& v) const;

    /**
     * 计算v1与v2的点积并返回。
     */
    static float dot(const Vec4& v1, const Vec4& v2);

    /**
     * 
     * 计算向量的长度并返回
     */
    float length() const;

    /**
     * 计算向量长度的平方并返回
     * 当不是必须使用精确长度的时候建议使用本方法代替length(）（如比较不同向量的长度）。
     */
    float lengthSquared() const;

    /**
     * 求反向量
     */
    void negate();

    /**
     * 求向量的标准化向量
     * 
     * 这个方法标准化一个Vec4向量为单位长度
     * （调用这个方法后向量长度为1.0f）。
     * 如果向量已经是单位长度或者长度为零，这个方法不起任何作用。
     */
     
    void normalize();

    /**
     * 
     * 标准化这个向量并将结果保存在dst中
     * 
     * 如果向量已经是单位长度或者长度为零，这个方法将简单的把当前向量值拷贝到dst中。
     */
    Vec4 getNormalized() const;

    /**
     * 用指定的放缩系数scalar对向量的各分量进行放缩
     */
    void scale(float scalar);

    /**
     * 
     * 设置当前向量各分量值为指定值
     * xx是新的x分量值
     * yy是新的y分量值
     * zz是新的z分量值
     * ww是新的w分量值
     */
    void set(float xx, float yy, float zz, float ww);

    /**
     * 
     * 给定array序列，依序设置向量x,y,z，w各分量的值。
     */
    void set(const float* array);

    /**
     * 
     * 拷贝向量v的值到本向量中
     */
    void set(const Vec4& v);

    /**
     * 
     * 设置向量值由给定两点求得。
     */
    void set(const Vec4& p1, const Vec4& p2);

    /**
     * 
     * 求与向量v的差（this-v），并将结果保存在本向量中.
     */
    void subtract(const Vec4& v);

    /**
     * 
     * 求v1-v2的值，将结果保存在dst中。
     */
    static void subtract(const Vec4& v1, const Vec4& v2, Vec4* dst);

    /**
     * 
     * 向量加法，求向量与给定向量v的和
     * 注意：这个加法并不改变原向量的值，返回值单独定义。
     */
    inline const Vec4 operator+(const Vec4& v) const;

    /**
     * 
     * 向量加法，求向量与给定向量v的和，将结果保存在该向量中，并返回。
     */
    inline Vec4& operator+=(const Vec4& v);

    /**
     * 
     * 向量减法，求向量与给定向量v的差
     * 注意：这个减法并不改变原向量的值，返回值单独定义
     */
    inline const Vec4 operator-(const Vec4& v) const;

    /**
     * 
     * 向量减法，求向量与给定向量v的差，将结果保存在该向量中，并返回。
     */
    inline Vec4& operator-=(const Vec4& v);

    /**
     * 
     *  求反向量
     * 注意：这个方法并不改变原向量的值，返回值单独定义
     */
    inline const Vec4 operator-() const;

    /**
     * 
     * 向量乘法，给定浮点数s，求向量各分量分别乘以s后的值。
     * 注意：这个方法并不改变原向量的值，返回值单独保存。
     */
    inline const Vec4 operator*(float s) const;

    /**
     * 向量乘法，给定浮点数s，求向量各分量分别乘以s后的值，将所得结果保存在原向量中。
     */
    inline Vec4& operator*=(float s);
    
    /**
     * 向量除法，给定浮点数s，求向量各分量分别除以s后的值。
     * 注意：这个方法并不改变原向量的值，返回值单独保存。
     */
    inline const Vec4 operator/(float s) const;

    /**
     * 
     * 判断该向量是否小于给定向量v，如果小于则返回true，否则返回false。
     */
    inline bool operator<(const Vec4& v) const;

    /**
     * 
     * 判断该向量是否等于给定向量v，如果等于则返回True，否则返回false。
     */
    inline bool operator==(const Vec4& v) const;

    /**
     * 判断该向量是否不等于给定向量v，如果不等则返回True，否则返回False。
     */
    inline bool operator!=(const Vec4& v) const;
    
    /** 等于 Vec4(0,0,0,0) */
    static const Vec4 ZERO;
    /** 等于 Vec4(1,1,1,1) */
    static const Vec4 ONE;
    /** 等于 Vec4(1,0,0,0) */
    static const Vec4 UNIT_X;
    /** 等于 Vec4(0,1,0,0) */
    static const Vec4 UNIT_Y;
    /** 等于 Vec4(0,0,1,0) */
    static const Vec4 UNIT_Z;
    /** 等于 Vec4(0,0,0,1) */
    static const Vec4 UNIT_W;
};

/**
 * 计算向量v与浮点数x相乘的结果。
 */
inline const Vec4 operator*(float x, const Vec4& v);

NS_CC_MATH_END

#include "Vector4.inl"

#endif // MATH_VEC4_H
