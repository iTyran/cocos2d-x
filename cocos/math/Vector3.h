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
 * Defines a 3-element floating point vector.
 *
 * When using a vector to represent a surface normal,
 * the vector should typically be normalized.
 * Other uses of directional vectors may wish to leave
 * the magnitude of the vector intact. When used as a point,
 * the elements of the vector represent a position in 3D space.
 * 
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
     * The x-coordinate.
     * x方向分量
     */
    float x;

    /**
     * The y-coordinate.
     * y方向分量
     */
    float y;

    /**
     * The z-coordinate.
     * z方向分量
     */
    float z;

    /**
     * Constructs a new vector initialized to all zeros.
     * 构造一个初始值为零的向量
     */
    Vec3();

    /**
     * Constructs a new vector initialized to the specified values.
     *
     * @param xx The x coordinate.
     * @param yy The y coordinate.
     * @param zz The z coordinate.
     * 
     * 构造一个新的向量并用特定值初始化
     * xx为x方向的值
     * yy为y方向的值
     * zz为z方向的值
     */
    Vec3(float xx, float yy, float zz);

    /**
     * Constructs a new vector from the values in the specified array.
     *
     * @param array An array containing the elements of the vector in the order x, y, z.
     * 
     * 用特定array来构造一个新的向量
     * 该array顺序包含向量x,y,z各分量的值。
     */
    Vec3(const float* array);

    /**
     * Constructs a vector that describes the direction between the specified points.
     *
     * @param p1 The first point.
     * @param p2 The second point.
     * 
     * 构造一个由p1指向p2的向量。
     */
    Vec3(const Vec3& p1, const Vec3& p2);

    /**
     * Constructs a new vector that is a copy of the specified vector.
     *
     * @param copy The vector to copy.
     * 
     * 拷贝一个已有向量
     */
    Vec3(const Vec3& copy);

    /**
     * Creates a new vector from an integer interpreted as an RGB value.
     * E.g. 0xff0000 represents red or the vector (1, 0, 0).
     *
     * @param color The integer to interpret as an RGB value.
     *
     * @return A vector corresponding to the interpreted RGB color.
     * 
     * 用一个表示RGB颜色值的整数来创建一个向量
     * 例如：Oxff0000表示红色，向量值为（1，0，0）.
     * 
     * 参数color为该RGB值
     * 返回该颜色值对应生成的向量
     */
    static Vec3 fromColor(unsigned int color);

    /**
     * Destructor.
     */
    ~Vec3();

    /**
     * Indicates whether this vector contains all zeros.
     *
     * @return true if this vector contains all zeros, false otherwise.
     * 
     * 该向量是否为零（每个分量都为零）
     * 如果该向量为零返回true，否则返回false
     */
    bool isZero() const;

    /**
     * Indicates whether this vector contains all ones.
     *
     * @return true if this vector contains all ones, false otherwise.
     * 
     * 该向量是否为单位向量（每个分量都为1）
     * 如果该向量为单位向量则返回true,否则返回false
     */
    bool isOne() const;

    /**
     * Returns the angle (in radians) between the specified vectors.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * 
     * @return The angle between the two vectors (in radians).
     * 
     * 返回两个给定向量之间的角度（单位为弧度）
     */
    static float angle(const Vec3& v1, const Vec3& v2);


    /**
     * Adds the elements of the specified vector to this one.
     *
     * @param v The vector to add.
     * 
     * 与给定向量v求和，结果保存在本向量中
     */
    void add(const Vec3& v);

    /**
     * Adds the specified vectors and stores the result in dst.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst A vector to store the result in.
     * 
     * 求向量v1与v2的和，结果保存在dst中
     */
    static void add(const Vec3& v1, const Vec3& v2, Vec3* dst);

    /**
     * Clamps this vector within the specified range.
     *
     * @param min The minimum value.
     * @param max The maximum value.
     * 
     * 将向量限制在指定范围内，min为最小值，max为最大值。
     */
    void clamp(const Vec3& min, const Vec3& max);

    /**
     * Clamps the specified vector within the specified range and returns it in dst.
     *
     * @param v The vector to clamp.
     * @param min The minimum value.
     * @param max The maximum value.
     * @param dst A vector to store the result in.
     * 
     * 将给定的向量v限制在指定范围[min,max]内，结果保存在dst中。
     */
    static void clamp(const Vec3& v, const Vec3& min, const Vec3& max, Vec3* dst);

    /**
     * Sets this vector to the cross product between itself and the specified vector.
     *
     * @param v The vector to compute the cross product with.
     * 
     * 计算该向量与给定向量v的叉积
     */
    void cross(const Vec3& v);

    /**
     * Computes the cross product of the specified vectors and stores the result in dst.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst A vector to store the result in.
     * 
     * 计算v1与v2的叉积，结果保存在dst中
     */
    static void cross(const Vec3& v1, const Vec3& v2, Vec3* dst);

    /**
     * Returns the distance between this vector and v.
     *
     * @param v The other vector.
     * 
     * @return The distance between this vector and v.
     * 
     * @see distanceSquared
     * 
     * 计算向量与v的距离并返回
     */
    float distance(const Vec3& v) const;

    /**
     * Returns the squared distance between this vector and v.
     *
     * When it is not necessary to get the exact distance between
     * two vectors (for example, when simply comparing the
     * distance between different vectors), it is advised to use
     * this method instead of distance.
     *
     * @param v The other vector.
     * 
     * @return The squared distance between this vector and v.
     * 
     * @see distance
     * 
     * 计算向量与v的距离的平方并返回
     * 
     *当不是必须使用精确距离的时候建议使用本方法代替distance(const Vec3& v）（如比较不同向量间距离大小）
     */
    float distanceSquared(const Vec3& v) const;

    /**
     * Returns the dot product of this vector and the specified vector.
     *
     * @param v The vector to compute the dot product with.
     * 
     * @return The dot product.
     * 
     * 计算向量与v的点积并返回
     */
    float dot(const Vec3& v) const;

    /**
     * Returns the dot product between the specified vectors.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * 
     * @return The dot product between the vectors.
     * 
     * 计算v1与v2的点积并返回。
     */
    static float dot(const Vec3& v1, const Vec3& v2);

    /**
     * Computes the length of this vector.
     *
     * @return The length of the vector.
     * 
     * @see lengthSquared
     * 
     * 计算向量的长度并返回
     */
    float length() const;

    /**
     * Returns the squared length of this vector.
     *
     * When it is not necessary to get the exact length of a
     * vector (for example, when simply comparing the lengths of
     * different vectors), it is advised to use this method
     * instead of length.
     *
     * @return The squared length of the vector.
     * 
     * @see length
     * 
     * 计算向量长度的平方并返回
     * 当不是必须使用精确长度的时候建议使用本方法代替length(）（如比较不同向量的长度）。
     */
    float lengthSquared() const;

    /**
     * Negates this vector.
     * 
     * 求反向量
     */
    void negate();

    /**
     * Normalizes this vector.
     *
     * This method normalizes this Vect3 so that it is of
     * unit length (in other words, the length of the vector
     * after calling this method will be 1.0f). If the vector
     * already has unit length or if the length of the vector
     * is zero, this method does nothing.
     * 
     * @return This vector, after the normalization occurs.
     * 
     * 求向量的标准化向量
     * 
     * 这个方法标准化一个Vec3向量为单位长度（调用这个方法后向量长度为1.0f）。如果向量已经是单位长度或者长度为零，这个方法不起任何作用。
     * 
     */
    void normalize();

    /**
     * Normalizes this vector and stores the result in dst.
     *
     * If the vector already has unit length or if the length
     * of the vector is zero, this method simply copies the
     * current vector into dst.
     *
     * @param dst The destination vector.
     * 
     * 标准化这个向量并将结果保存在dst中
     * 
     * 如果向量已经是单位长度或者长度为零，这个方法将简单的把当前向量值拷贝到dst中。
     */
    Vec3 getNormalized() const;

    /**
     * Scales all elements of this vector by the specified value.
     *
     * @param scalar The scalar value.
     * 
     * 用指定的放缩系数scalar对向量的各分量进行放缩
     */
    void scale(float scalar);

    /**
     * Sets the elements of this vector to the specified values.
     *
     * @param xx The new x coordinate.
     * @param yy The new y coordinate.
     * @param zz The new z coordinate.
     * 
     * 设置当前向量各分量值为指定值
     * xx是新的x分量值
     * yy是新的y分量值
     * zz是新的z分量值
     */
    void set(float xx, float yy, float zz);

    /**
     * Sets the elements of this vector from the values in the specified array.
     *
     * @param array An array containing the elements of the vector in the order x, y, z.
     * 
     * 给定array序列，依序设置向量x,y,z各分量的值。
     */
    void set(const float* array);

    /**
     * Sets the elements of this vector to those in the specified vector.
     *
     * @param v The vector to copy.
     * 
     * 拷贝向量v的值到本向量中
     */
    void set(const Vec3& v);

    /**
     * Sets this vector to the directional vector between the specified points.
     * 
     * 设置向量值由给定两点坐标求得。
     */
    void set(const Vec3& p1, const Vec3& p2);

    /**
     * Subtracts this vector and the specified vector as (this - v)
     * and stores the result in this vector.
     *
     * @param v The vector to subtract.
     * 
     * 求与向量v的差（this-v），并将结果保存在本向量中.
     */
    void subtract(const Vec3& v);

    /**
     * Subtracts the specified vectors and stores the result in dst.
     * The resulting vector is computed as (v1 - v2).
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst The destination vector.
     * 
     * 求v1-v2的值，将结果保存在dst中。
     */
    static void subtract(const Vec3& v1, const Vec3& v2, Vec3* dst);

    /**
     * Updates this vector towards the given target using a smoothing function.
     * The given response time determines the amount of smoothing (lag). A longer
     * response time yields a smoother result and more lag. To force this vector to
     * follow the target closely, provide a response time that is very small relative
     * to the given elapsed time.
     *
     * @param target target value.
     * @param elapsedTime elapsed time between calls.
     * @param responseTime response time (in the same units as elapsedTime).
     * 
     * 平滑更新向量的当前位置，指向目标向量target
     * responseTime定义了平滑时间量，该值越大结果越平滑，相应的延迟时间越长。如果希望向量紧跟target向量，提供一个相对elapsedTime小很多的responseTime值即可。
     */
     */
    void smooth(const Vec3& target, float elapsedTime, float responseTime);

    /**
     * Calculates the sum of this vector with the given vector.
     * 
     * Note: this does not modify this vector.
     * 
     * @param v The vector to add.
     * @return The vector sum.
     * 
     * 向量加法，求向量与给定向量v的和
     * 注意：这个加法并不改变原向量的值，返回值单独定义
     */
    inline const Vec3 operator+(const Vec3& v) const;

    /**
     * Adds the given vector to this vector.
     * 
     * @param v The vector to add.
     * @return This vector, after the addition occurs.
     * 
     * 向量加法，求向量与给定向量v的和，将结果保存在该向量中，并返回。
     */
    inline Vec3& operator+=(const Vec3& v);

    /**
     * Calculates the difference of this vector with the given vector.
     * 
     * Note: this does not modify this vector.
     * 
     * @param v The vector to subtract.
     * @return The vector difference.
     * 
     * 向量减法，求向量与给定向量v的差
     * 注意：这个减法并不改变原向量的值，返回值单独定义
     */
    inline const Vec3 operator-(const Vec3& v) const;

    /**
     * Subtracts the given vector from this vector.
     * 
     * @param v The vector to subtract.
     * @return This vector, after the subtraction occurs.
     * 
     * 向量减法，求向量与给定向量v的差，将结果保存在该向量中，并返回。
     */
    inline Vec3& operator-=(const Vec3& v);

    /**
     * Calculates the negation of this vector.
     * 
     * Note: this does not modify this vector.
     * 
     * @return The negation of this vector.
     * 
     * 求反向量
     * 注意：这个方法并不改变原向量的值，返回值单独定义
     */
    inline const Vec3 operator-() const;

    /**
     * Calculates the scalar product of this vector with the given value.
     * 
     * Note: this does not modify this vector.
     * 
     * @param s The value to scale by.
     * @return The scaled vector.
     * 
     * 向量乘法，给定浮点数s，求向量各分量分别乘以s后的值。
     * 注意：这个方法并不改变原向量的值，返回值单独保存。
     */
    inline const Vec3 operator*(float s) const;

    /**
     * Scales this vector by the given value.
     * 
     * @param s The value to scale by.
     * @return This vector, after the scale occurs.
     * 
     * 向量乘法，给定浮点数s，求向量各分量分别乘以s后的值，将所得结果保存在原向量中。
     */
    inline Vec3& operator*=(float s);
    
    /**
     * Returns the components of this vector divided by the given constant
     *
     * Note: this does not modify this vector.
     *
     * @param s the constant to divide this vector with
     * @return a smaller vector
     * 
     * 向量除法，给定浮点数s，求向量各分量分别除以s后的值。
     * 注意：这个方法并不改变原向量的值，返回值单独保存。
     */
    inline const Vec3 operator/(float s) const;

    /**
     * Determines if this vector is less than the given vector.
     * 
     * @param v The vector to compare against.
     * 
     * @return True if this vector is less than the given vector, false otherwise.
     * 
     * 判断该向量是否小于给定向量v，如果小于则返回true，否则返回false。
     */
    inline bool operator<(const Vec3& v) const;

    /**
     * Determines if this vector is equal to the given vector.
     * 
     * @param v The vector to compare against.
     * 
     * @return True if this vector is equal to the given vector, false otherwise.
     * 
     * 判断该向量是否等于给定向量v，如果等于则返回True，否则返回false。
     */
    inline bool operator==(const Vec3& v) const;

    /**
     * Determines if this vector is not equal to the given vector.
     * 
     * @param v The vector to compare against.
     * 
     * @return True if this vector is not equal to the given vector, false otherwise.
     * 判断该向量是否不等于给定向量v，如果不等则返回True，否则返回False。
     */
    inline bool operator!=(const Vec3& v) const;
    
    /** equals to Vec3(0,0,0) */
    static const Vec3 ZERO;
    /** equals to Vec3(1,1,1) */
    static const Vec3 ONE;
    /** equals to Vec3(1,0,0) */
    static const Vec3 UNIT_X;
    /** equals to Vec3(0,1,0) */
    static const Vec3 UNIT_Y;
    /** equals to Vec3(0,0,1) */
    static const Vec3 UNIT_Z;
};

/**
 * Calculates the scalar product of the given vector with the given value.
 * 
 * @param x The value to scale by.
 * @param v The vector to scale.
 * @return The scaled vector.
 * 
 * 计算向量v与浮点数x相乘的结果。
 */
inline const Vec3 operator*(float x, const Vec3& v);

typedef Vec3 Point3;

NS_CC_MATH_END

#include "Vector3.inl"

#endif // MATH_VEC3_H
