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

#ifndef MATH_VEC2_H
#define MATH_VEC2_H

#include <algorithm>
#include <functional>
#include <math.h>
#include "math/CCMathBase.h"

NS_CC_MATH_BEGIN

/** Clamp a value between from and to.
 * 
 * 将value的大小限制在min_inclusive与max_inclusive之间
 */

inline float clampf(float value, float min_inclusive, float max_inclusive)
{
    if (min_inclusive > max_inclusive) {
        std::swap(min_inclusive, max_inclusive);
    }
    return value < min_inclusive ? min_inclusive : value < max_inclusive? value : max_inclusive;
}

class Mat4;

/**
 * Defines a 2-element floating point vector.
 * 定义一个2维浮点向量
 */
 
 
class Vec2
{
public:

    /**
     * The x coordinate.
     * 向量的x值
     */
    float x;

    /**
     * The y coordinate.
     * 向量的y值
     */
    float y;

    /**
     * Constructs a new vector initialized to all zeros.
     * 构造一个新向量初始值为0.
     */
    Vec2();

    /**
     * Constructs a new vector initialized to the specified values.
     *
     * @param xx The x coordinate.
     * @param yy The y coordinate.
     * 
     * 用指定x,y值构造一个新向量
     * 参数xx是x的值，参数yy是y的值
     */
    Vec2(float xx, float yy);

    /**
     * Constructs a new vector from the values in the specified array.
     *
     * @param array An array containing the elements of the vector in the order x, y.
     * 
     * 用指定array构造一个新的向量，array依序包含x、y的值。
     */
    Vec2(const float* array);

    /**
     * Constructs a vector that describes the direction between the specified points.
     *
     * @param p1 The first point.
     * @param p2 The second point.
     * 
     * 
     * 构造方向由点p1指向点p2的向量
     */
    Vec2(const Vec2& p1, const Vec2& p2);

    /**
     * Constructs a new vector that is a copy of the specified vector.
     *
     * @param copy The vector to copy.
     * 
     * 构造一个新向量，从一个指定向量获取值
     */
    Vec2(const Vec2& copy);

    /**
     * Destructor.
     */
    ~Vec2();

    /**
     * Indicates whether this vector contains all zeros.
     *
     * @return true if this vector contains all zeros, false otherwise.
     * 
     * 向量值是否为0
     * 如果为0则返回true，否则返回false
     */
    bool isZero() const;

    /**
     * Indicates whether this vector contains all ones.
     *
     * @return true if this vector contains all ones, false otherwise.
     * 
     * 向量的x、y值是否均为1.0f
     * 如果x、y均为1.0f，则返回true，否则返回false。
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
     * 返回两个向量之间的角度（用弧度表示）
     * 参数v1为第一个向量
     * 参数v2为第二个向量
     * 
     */
    static float angle(const Vec2& v1, const Vec2& v2);

    /**
     * Adds the elements of the specified vector to this one.
     *
     * @param v The vector to add.
     * 
     * 向量加法，加上v向量的值
     */
    void add(const Vec2& v);

    /**
     * Adds the specified vectors and stores the result in dst.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst A vector to store the result in.
     * 
     * 向量v1和v2相加，将结果保存在dst中
     * 
     */
    static void add(const Vec2& v1, const Vec2& v2, Vec2* dst);

    /**
     * Clamps this vector within the specified range.
     *
     * @param min The minimum value.
     * @param max The maximum value.
     * 
     * 将向量值限制在指定的[min,max]区间内
     * 
     * 
     */
    void clamp(const Vec2& min, const Vec2& max);

    /**
     * Clamps the specified vector within the specified range and returns it in dst.
     *
     * @param v The vector to clamp.
     * @param min The minimum value.
     * @param max The maximum value.
     * @param dst A vector to store the result in.
     * 
     * 将指定向量v限制在[min,max]区间内，并用dst保存结果。
     */
    static void clamp(const Vec2& v, const Vec2& min, const Vec2& max, Vec2* dst);

    /**
     * Returns the distance between this vector and v.
     *
     * @param v The other vector.
     * 
     * @return The distance between this vector and v.
     * 
     * @see distanceSquared
     * 
     * 返回本向量到向量v的距离
     */
    float distance(const Vec2& v) const;

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
     * 返回本向量到向量v的距离的平方值
     * 
     * 如果不需要得到两个向量之间的准确距离，例如只是比较不同向量之间的距离大小的时候，建议使用这个方法来代替distance(const Vec2& v)方法
     */
    float distanceSquared(const Vec2& v) const;

    /**
     * Returns the dot product of this vector and the specified vector.
     *
     * @param v The vector to compute the dot product with.
     * 
     * @return The dot product.
     * 
     * 返回本向量与指定向量v的点积
     */
    float dot(const Vec2& v) const;

    /**
     * Returns the dot product between the specified vectors.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * 
     * @return The dot product between the vectors.
     * 
     * 返回向量v1和v2的点积
     */
    static float dot(const Vec2& v1, const Vec2& v2);

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
     * 
     * 当不需要获取准确的向量长度时，例如只是简单比较不同向量之间的长度大小，可以使用本方法代替length()
     * 
     * 
     */
    float lengthSquared() const;

    /**
     * Negates this vector.
     * 
     * 向量求负
     */
    void negate();

    /**
     * Normalizes this vector.
     *
     * This method normalizes this Vec2 so that it is of
     * unit length (in other words, the length of the vector
     * after calling this method will be 1.0f). If the vector
     * already has unit length or if the length of the vector
     * is zero, this method does nothing.
     * 
     * @return This vector, after the normalization occurs.
     * 
     * 求向量的标准化向量
     * 
     * 这个方法标准化一个Vec2向量为单位长度（调用这个方法后向量长度为1.0f）。如果向量已经是单位长度或者长度为零，这个方法不起任何作用。
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
    Vec2 getNormalized() const;

    /**
     * Scales all elements of this vector by the specified value.
     *
     * @param scalar The scalar value.
     * 
     * 用指定的放缩系数对向量的各分量进行放缩
     */
    void scale(float scalar);

    /**
     * Scales each element of this vector by the matching component of scale.
     *
     * @param scale The vector to scale by.
     * 
     * 用scale向量的x分量来放缩本向量的x分量，用scale向量的y分量来放缩本向量的y分量。
     */
    void scale(const Vec2& scale);

    /**
     * Rotates this vector by angle (specified in radians) around the given point.
     *
     * @param point The point to rotate around.
     * @param angle The angle to rotate by (in radians).
     * 
     * 向量绕指定点point旋转angle度，其中angle的单位为弧度。
     */
    void rotate(const Vec2& point, float angle);

    /**
     * Sets the elements of this vector to the specified values.
     *
     * @param xx The new x coordinate.
     * @param yy The new y coordinate.
     * 
     * 设置向量的x分量值为xx，y分量值为yy。
     */
    void set(float xx, float yy);

    /**
     * Sets the elements of this vector from the values in the specified array.
     *
     * @param array An array containing the elements of the vector in the order x, y.
     * 
     * 给定array序列，依序设置向量各分量的值。
     */
    void set(const float* array);

    /**
     * Sets the elements of this vector to those in the specified vector.
     *
     * @param v The vector to copy.
     * 
     * 将指定向量v的值赋给本向量
     */
    void set(const Vec2& v);

    /**
     * Sets this vector to the directional vector between the specified points.
     * 
     * @param p1 The first point.
     * @param p2 The second point.
     * 
     * 得到p1指向p2的一个有向向量
     */
    void set(const Vec2& p1, const Vec2& p2);

    /**
     * Subtracts this vector and the specified vector as (this - v)
     * and stores the result in this vector.
     *
     * @param v The vector to subtract.
     * 
     * 本向量减去向量v
     */
    void subtract(const Vec2& v);

    /**
     * Subtracts the specified vectors and stores the result in dst.
     * The resulting vector is computed as (v1 - v2).
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst The destination vector.
     * 
     * 向量v1减去v2，把结果保存在dst中
     */
    static void subtract(const Vec2& v1, const Vec2& v2, Vec2* dst);

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
    void smooth(const Vec2& target, float elapsedTime, float responseTime);

    /**
     * Calculates the sum of this vector with the given vector.
     * 
     * Note: this does not modify this vector.
     * 
     * @param v The vector to add.
     * @return The vector sum.
     * 
     * 向量加法，求向量与给定向量v的和
     * 注意：这个加法并不改变原向量的值，返回值单独保存
     */
    inline const Vec2 operator+(const Vec2& v) const;

    /**
     * Adds the given vector to this vector.
     * 
     * @param v The vector to add.
     * @return This vector, after the addition occurs.
     * 
     * 向量加法，求向量与给定向量v的和，将结果保存在该向量中，并返回。
     */
    inline Vec2& operator+=(const Vec2& v);

    /**
     * Calculates the sum of this vector with the given vector.
     * 
     * Note: this does not modify this vector.
     * 
     * @param v The vector to add.
     * @return The vector sum.
     * 
     * 向量减法，求向量与给定向量v的差
     * 注意：这个减法并不改变原向量的值，返回值单独保存
     */
    inline const Vec2 operator-(const Vec2& v) const;

    /**
     * Subtracts the given vector from this vector.
     * 
     * @param v The vector to subtract.
     * @return This vector, after the subtraction occurs.
     * 
     * 向量减法，求向量与给定向量v的差，将结果保存在该向量中，并返回。
     */
    inline Vec2& operator-=(const Vec2& v);

    /**
     * Calculates the negation of this vector.
     * 
     * Note: this does not modify this vector.
     * 
     * @return The negation of this vector.
     * 
     * 求反向量
     * 注意：这个方法并不改变原向量的值，返回值单独保存
     */
    inline const Vec2 operator-() const;

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
    inline const Vec2 operator*(float s) const;

    /**
     * Scales this vector by the given value.
     * 
     * @param s The value to scale by.
     * @return This vector, after the scale occurs.
     * 
     * 向量乘法，给定浮点数s，求向量各分量分别乘以s后的值，将所得结果保存在原向量中。
     */
    inline Vec2& operator*=(float s);
    
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
    inline const Vec2 operator/(float s) const;

    /**
     * Determines if this vector is less than the given vector.
     * 
     * @param v The vector to compare against.
     * 
     * @return True if this vector is less than the given vector, false otherwise.
     * 
     * 判断该向量是否小于给定向量v，如果小于则返回true，否则返回false。
     * 
     */
    inline bool operator<(const Vec2& v) const;

    /**
     * Determines if this vector is equal to the given vector.
     * 
     * @param v The vector to compare against.
     * 
     * @return True if this vector is equal to the given vector, false otherwise.
     * 
     * 判断该向量是否等于给定向量v，如果等于则返回True，否则返回false。
     */
    inline bool operator==(const Vec2& v) const;

    /**
     * Determines if this vector is not equal to the given vector.
     * 
     * @param v The vector to compare against.
     * 
     * @return True if this vector is not equal to the given vector, false otherwise.
     * 
     * 判断该向量是否不等于给定向量v，如果不等则返回True，否则返回False。
     */
    inline bool operator!=(const Vec2& v) const;

    //code added compatible for Point
    //增加的一些与点相关的代码
public:
      /**
     * @js NA
     * @lua NA
     */
    void setPoint(float xx, float yy);
    /**
     * @js NA
     */
    bool equals(const Vec2& target) const;
    
    /** @returns if points have fuzzy equality which means equal with some degree of variance.
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 如果点有fuzzy equality意味着与某种方差是相等的。
     */
    bool fuzzyEquals(const Vec2& target, float variance) const;

    /** Calculates distance between point an origin
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 计算点到原点的距离，返回一个浮点数
     */
    inline float getLength() const {
        return sqrtf(x*x + y*y);
    };

    /** Calculates the square length of a Vec2 (not calling sqrt() )
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 计算该向量长度的平方，不调用sqrt().
     */
    inline float getLengthSq() const {
        return dot(*this); //x*x + y*y;
    };

    /** Calculates the square distance between two points (not calling sqrt() )
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     * 计算到另一个向量的长度的平方，不调用sqrt().
     */
    inline float getDistanceSq(const Vec2& other) const {
        return (*this - other).getLengthSq();
    };

    /** Calculates the distance between two points
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 计算两点之间的距离
     */
    inline float getDistance(const Vec2& other) const {
        return (*this - other).getLength();
    };

    /** @returns the angle in radians between this vector and the x axis
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 返回向量与x轴夹角，单位是弧度。
     */
    inline float getAngle() const {
        return atan2f(y, x);
    };

    /** @returns the angle in radians between two vector directions
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 返回两个向量的夹角，单位是弧度。
     */
    float getAngle(const Vec2& other) const;

    /** Calculates cross product of two points.
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 计算两个二维向量的叉乘
     */
    inline float cross(const Vec2& other) const {
        return x*other.y - y*other.x;
    };

    /** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
     @return Vec2
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 计算v逆时针旋转90度的垂线--cross(v,perp(v))>=0
     */
    inline Vec2 getPerp() const {
        return Vec2(-y, x);
    };
    
    /** Calculates midpoint between two points.
     @return Vec2
     @since v3.0
     * @js NA
     * @lua NA
     * 
     * 用向量计算两点间的中点
     */
    inline Vec2 getMidpoint(const Vec2& other) const
    {
        return Vec2((x + other.x) / 2.0f, (y + other.y) / 2.0f);
    }
    
    /** Clamp a point between from and to.
     @since v3.0
     * @js NA
     * @lua NA
     * 
     * 将一个点限制在min_inclusive和max_inclusive之间，返回该点的二维向量形式
     */
    inline Vec2 getClampPoint(const Vec2& min_inclusive, const Vec2& max_inclusive) const
    {
        return Vec2(clampf(x,min_inclusive.x,max_inclusive.x), clampf(y, min_inclusive.y, max_inclusive.y));
    }
    
    /** Run a math operation function on each point component
     * absf, fllorf, ceilf, roundf
     * any function that has the signature: float func(float);
     * For example: let's try to take the floor of x,y
     * p.compOp(floorf);
     @since v3.0
     * @js NA
     * @lua NA
     * 
     * 对该点向量形式的各分量进行function参数来指定的运算，如absf,floorf,ceilf,roundf等，任何函数拥有如下形式：float func(float)均可。
     * 例如：我们对x,y进行floor运算，则调用方法为p.compOp(floorf);
     */
    inline Vec2 compOp(std::function<float(float)> function) const
    {
        return Vec2(function(x), function(y));
    }

    /** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
     @return Vec2
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 计算向量v顺时针旋转90度后的值---cross(v,rperp(v))<=0
     */
    inline Vec2 getRPerp() const {
        return Vec2(y, -x);
    };

    /** Calculates the projection of this over other.
     @return Vec2
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 计算该向量在另一向量other上的投影。
     */
    inline Vec2 project(const Vec2& other) const {
        return other * (dot(other)/other.dot(other));
    };

    /** Complex multiplication of two points ("rotates" two points).
     @return Vec2 vector with an angle of this.getAngle() + other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 绕other向量旋转。
     * 返回向量的角度为this.getAngle()+other.getAngle(),长度为this.getLength()*other.getLength().
     */
    inline Vec2 rotate(const Vec2& other) const {
        return Vec2(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    /** Unrotates two points.
     @return Vec2 vector with an angle of this.getAngle() - other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 绕other向量旋转前的向量值
     * 返回向量的角度为this.getAngle()-other.getAngle(),长度为this.getLength()*other.getLength().(这里是不是有点问题，难道不应该是this.getLength()/other.getLength()么？)
     */
    inline Vec2 unrotate(const Vec2& other) const {
        return Vec2(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    /** Linear Interpolation between two points a and b
     @returns
        alpha == 0 ? a
        alpha == 1 ? b
        otherwise a value between a..b
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 两个点a和b之间的线性插值
     * 返回 alpha ==0 ? a
     *      alpha ==1 ? b
     *      否则为a和b之间的一个值
     */
    inline Vec2 lerp(const Vec2& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    /** Rotates a point counter clockwise by the angle around a pivot
     @param pivot is the pivot, naturally
     @param angle is the angle of rotation ccw in radians
     @returns the rotated point
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     * 以pivot为轴逆时针旋转angle度（单位为弧度），返回结果向量
     */
    Vec2 rotateByAngle(const Vec2& pivot, float angle) const;

    /**
     * @js NA
     * @lua NA
     */
    static inline Vec2 forAngle(const float a)
    {
        return Vec2(cosf(a), sinf(a));
    }
    
    /** A general line-line intersection test
     @param A   the startpoint for the first line L1 = (A - B)
     @param B   the endpoint for the first line L1 = (A - B)
     @param C   the startpoint for the second line L2 = (C - D)
     @param D   the endpoint for the second line L2 = (C - D)
     @param S   the range for a hitpoint in L1 (p = A + S*(B - A))
     @param T   the range for a hitpoint in L2 (p = C + T*(D - C))
     @returns   whether these two lines interects.

     Note that to truly test intersection for segments we have to make
     sure that S & T lie within [0..1] and for rays, make sure S & T > 0
     the hit point is        C + T * (D - C);
     the hit point also is   A + S * (B - A);
     @since 3.0
     * @js NA
     * @lua NA
     * 
     * 
     * 一个通用的线段相交检测
     * A为线段L1起点，B为L1终点
     * C为线段L2起点，D为L2终点
     * 
     * S为L1上计算各点的插值参数，计算方法为：p = A + S*(B - A)
     * T为L2上计算各点的插值参数，计算方法为：p = C + T*(D - C)
     * 
     * 注意要准确测试出线段是否相交我们需要确保S&T的值在[0..1]区间范围内
     */
    static bool isLineIntersect(const Vec2& A, const Vec2& B,
                                 const Vec2& C, const Vec2& D,
                                 float *S = nullptr, float *T = nullptr);
    
    /**
     returns true if Line A-B overlap with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     * 
     * 如果直线AB与线段CD重叠，返回True。
     */
    static bool isLineOverlap(const Vec2& A, const Vec2& B,
                                const Vec2& C, const Vec2& D);
    
    /**
     returns true if Line A-B parallel with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     * 
     * 如果直线AB与线段CD平行，返回True。
     */
    static bool isLineParallel(const Vec2& A, const Vec2& B,
                   const Vec2& C, const Vec2& D);
    
    /**
     returns true if Segment A-B overlap with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     * 
     * 如果线段AB与线段CD重叠，返回True。
     */
    static bool isSegmentOverlap(const Vec2& A, const Vec2& B,
                                 const Vec2& C, const Vec2& D,
                                 Vec2* S = nullptr, Vec2* E = nullptr);
    
    /**
     returns true if Segment A-B intersects with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     * 
     * 如果线段AB与线段CD交叉，返回True。
     */
    static bool isSegmentIntersect(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D);
    
    /**
     returns the intersection point of line A-B, C-D
     @since v3.0
     * @js NA
     * @lua NA
     * 
     * 返回直线AB，CD的交叉点。
     */
    static Vec2 getIntersectPoint(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D);
    
    /** equals to Vec2(0,0) */
    static const Vec2 ZERO;
    /** equals to Vec2(1,1) */
    static const Vec2 ONE;
    /** equals to Vec2(1,0) */
    static const Vec2 UNIT_X;
    /** equals to Vec2(0,1) */
    static const Vec2 UNIT_Y;
    /** equals to Vec2(0.5, 0.5) */
    static const Vec2 ANCHOR_MIDDLE;
    /** equals to Vec2(0, 0) */
    static const Vec2 ANCHOR_BOTTOM_LEFT;
    /** equals to Vec2(0, 1) */
    static const Vec2 ANCHOR_TOP_LEFT;
    /** equals to Vec2(1, 0) */
    static const Vec2 ANCHOR_BOTTOM_RIGHT;
    /** equals to Vec2(1, 1) */
    static const Vec2 ANCHOR_TOP_RIGHT;
    /** equals to Vec2(1, 0.5) */
    static const Vec2 ANCHOR_MIDDLE_RIGHT;
    /** equals to Vec2(0, 0.5) */
    static const Vec2 ANCHOR_MIDDLE_LEFT;
    /** equals to Vec2(0.5, 1) */
    static const Vec2 ANCHOR_MIDDLE_TOP;
    /** equals to Vec2(0.5, 0) */
    static const Vec2 ANCHOR_MIDDLE_BOTTOM;
};

/**
 * Calculates the scalar product of the given vector with the given value.
 * 
 * @param x The value to scale by.
 * @param v The vector to scale.
 * @return The scaled vector.
 * 
 * 计算向量与给定浮点数的乘积。
 */
inline const Vec2 operator*(float x, const Vec2& v);

typedef Vec2 Point2;

NS_CC_MATH_END

#include "Vector2.inl"

#endif // MATH_VEC2_H
