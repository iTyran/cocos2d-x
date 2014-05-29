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

#ifndef MATH_VEC3_H
#define MATH_VEC3_H

#include "math/CCMathBase.h"

NS_CC_MATH_BEGIN

class Mat4;
class Quaternion;

/**
 * 定义一个三维浮点向量
 * 当用作表面法向量时，该向量必须标准化。
 * 用作方向向量的时候可能会保持原向量的大小不变。
 * 当用作点时，代表了3d空间的一个位置。
 * 
 * 
 */
class Vec3
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
     * 构造一个初始值为零的向量
     */
    Vec3();

    /**
     * 构造一个新的向量并用特定值初始化
     * xx为x方向的值
     * yy为y方向的值
     * zz为z方向的值
     */
    Vec3(float xx, float yy, float zz);

    /**
     * 用特定array来构造一个新的向量
     * 该array顺序包含向量x,y,z各分量的值。
     */
    Vec3(const float* array);

    /**
     * 构造一个由p1指向p2的向量。
     * @param p1 第一个点
     * @param p2 第二个点
     */
    Vec3(const Vec3& p1, const Vec3& p2);

    /**
     * 拷贝一个已有向量
     */
    Vec3(const Vec3& copy);

    /**
     * 用一个表示RGB颜色值的整数来创建一个向量
     * 例如：Oxff0000表示红色，向量值为（1，0，0）.
     * 
     * 参数color为该RGB值
     * 返回该颜色值对应生成的向量
     */
    static Vec3 fromColor(unsigned int color);

    /**
     * 虚构函数
     */
    ~Vec3();

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
     * 返回两个给定向量之间的角度（单位为弧度）
     */
    static float angle(const Vec3& v1, const Vec3& v2);


    /**
     * 与给定向量v求和，结果保存在本向量中
     */
    void add(const Vec3& v);

    /**
     * 求向量v1与v2的和，结果保存在dst中
     */
    static void add(const Vec3& v1, const Vec3& v2, Vec3* dst);

    /**
     * 将向量限制在指定范围内，min为最小值，max为最大值。
     */
    void clamp(const Vec3& min, const Vec3& max);

    /**
     * 将给定的向量v限制在指定范围[min,max]内，结果保存在dst中。
     */
    static void clamp(const Vec3& v, const Vec3& min, const Vec3& max, Vec3* dst);

    /**
     * 计算该向量与给定向量v的叉积
     */
    void cross(const Vec3& v);

    /**
     * 计算v1与v2的叉积，结果保存在dst中
     */
    static void cross(const Vec3& v1, const Vec3& v2, Vec3* dst);

    /**
     * 计算向量与v的距离并返回
     */
    float distance(const Vec3& v) const;

    /**
     * 计算向量与v的距离的平方并返回
     * 
     *当不是必须使用精确距离的时候建议使用本方法代替distance(const Vec3& v）
     （如比较不同向量间距离大小）
     */
    float distanceSquared(const Vec3& v) const;

    /**
     * 
     * 计算向量与v的点积并返回
     */
    float dot(const Vec3& v) const;

    /**
     * 计算v1与v2的点积并返回。
     */
    static float dot(const Vec3& v1, const Vec3& v2);

    /**
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
     * 这个方法标准化一个Vec3向量为单位长度（调用这个方法后向量长度为1.0f）。如果向量已经是单位长度或者长度为零，这个方法不起任何作用。
     * 
     */
    void normalize();

    /**
     * 标准化这个向量并将结果保存在dst中
     * 
     * 如果向量已经是单位长度或者长度为零，这个方法将简单的把当前向量值拷贝到dst中。
     */
    Vec3 getNormalized() const;

    /**
     * 用指定的放缩系数scalar对向量的各分量进行放缩
     */
    void scale(float scalar);

    /**
     * 设置当前向量各分量值为指定值
     * xx是新的x分量值
     * yy是新的y分量值
     * zz是新的z分量值
     */
    void set(float xx, float yy, float zz);

    /**
     * 
     * 给定array序列，依序设置向量x,y,z各分量的值。
     */
    void set(const float* array);

    /**
     * 拷贝向量v的值到本向量中
     */
    void set(const Vec3& v);

    /**
     * 
     * 设置向量值由给定两点坐标求得。
     */
    void set(const Vec3& p1, const Vec3& p2);

    /**
     * 求与向量v的差（this-v），并将结果保存在本向量中.
     */
    void subtract(const Vec3& v);

    /**
     * 求v1-v2的值，将结果保存在dst中。
     */
    static void subtract(const Vec3& v1, const Vec3& v2, Vec3* dst);

    /**
     * 平滑更新向量的当前位置，指向目标向量target
     * responseTime定义了平滑时间量，该值越大结果越平滑，相应的延迟时间越长。如果希望向量紧跟target向量，提供一个相对elapsedTime小很多的responseTime值即可。
     */
    void smooth(const Vec3& target, float elapsedTime, float responseTime);

    /**
     * 向量加法，求向量与给定向量v的和
     * 注意：这个加法并不改变原向量的值，返回值单独定义
     */
    inline const Vec3 operator+(const Vec3& v) const;

    /**
     * 向量加法，求向量与给定向量v的和，将结果保存在该向量中，并返回。
     */
    inline Vec3& operator+=(const Vec3& v);

    /**
     * 向量减法，求向量与给定向量v的差
     * 注意：这个减法并不改变原向量的值，返回值单独定义
     */
    inline const Vec3 operator-(const Vec3& v) const;

    /**
     * 向量减法，求向量与给定向量v的差，将结果保存在该向量中，并返回。
     */
    inline Vec3& operator-=(const Vec3& v);

    /**
     * 求反向量
     * 注意：这个方法并不改变原向量的值，返回值单独定义
     */
    inline const Vec3 operator-() const;

    /**
     * 
     * 向量乘法，给定浮点数s，求向量各分量分别乘以s后的值。
     * 注意：这个方法并不改变原向量的值，返回值单独保存。
     */
    inline const Vec3 operator*(float s) const;

    /**
     * 向量乘法，给定浮点数s，求向量各分量分别乘以s后的值，将所得结果保存在原向量中。
     */
    inline Vec3& operator*=(float s);
    
    /**
     * 向量除法，给定浮点数s，求向量各分量分别除以s后的值。
     * 注意：这个方法并不改变原向量的值，返回值单独保存。
     */
    inline const Vec3 operator/(float s) const;

    /**
     * 
     * 判断该向量是否小于给定向量v，如果小于则返回true，否则返回false。
     */
    inline bool operator<(const Vec3& v) const;

    /**
     * 
     * 判断该向量是否等于给定向量v，如果等于则返回True，否则返回false。
     */
    inline bool operator==(const Vec3& v) const;

    /**
     * 判断该向量是否不等于给定向量v，如果不等则返回True，否则返回False。
     */
    inline bool operator!=(const Vec3& v) const;
    
    /** 等于 Vec3(0,0,0) */
    static const Vec3 ZERO;
    /** 等于 Vec3(1,1,1) */
    static const Vec3 ONE;
    /** 等于 Vec3(1,0,0) */
    static const Vec3 UNIT_X;
    /** 等于 Vec3(0,1,0) */
    static const Vec3 UNIT_Y;
    /** 等于 Vec3(0,0,1) */
    static const Vec3 UNIT_Z;
};

/**
 * 计算向量v与浮点数x相乘的结果。
 */
inline const Vec3 operator*(float x, const Vec3& v);

typedef Vec3 Point3;

NS_CC_MATH_END

#include "Vector3.inl"

#endif // MATH_VEC3_H
