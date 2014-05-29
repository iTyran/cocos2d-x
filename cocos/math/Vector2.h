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

/**
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
 * 定义一个2维浮点向量
 */
 
 
class Vec2
{
public:

    /**
     * 向量的x值
     */
    float x;

    /**
     * 向量的y值
     */
    float y;

    /**
     * 构造一个新向量初始值为0.
     */
    Vec2();

    /**
     * 用指定x,y值构造一个新向量
     * 参数xx是x的值，参数yy是y的值
     *
     * @param xx x坐标
     * @param yy y坐标
     */
    Vec2(float xx, float yy);

    /**
     * 用指定array构造一个新的向量，array依序包含x、y的值。
     *
     * @param array 包含x，y坐标向量的数组。
     * 
     */
    Vec2(const float* array);

    /**
     * 构造方向由点p1指向点p2的向量
     *
     * @param p1 第一个点
     * @param p2 第二个点
     * 
     */
    Vec2(const Vec2& p1, const Vec2& p2);

    /**
     * 构造一个新向量，从一个指定向量获取值
     *
     * @param copy 将被拷贝的向量
     * 
     */
    Vec2(const Vec2& copy);

    /**
     * 虚构函数
     */
    ~Vec2();

    /**
     * 向量值是否为0
     *
     * @return 如果为0则返回true，否则返回false
     * 
     */
    bool isZero() const;

    /**
     * 向量的x、y值是否均为1.0f
     *
     * @return 如果x、y均为1.0f，则返回true，否则返回false。
     * 
     */
    bool isOne() const;

    /**
     * 返回两个向量之间的角度（用弧度表示）
     *
     * @param v1 第一个向量
     * @param v2 第二个向量
     * 
     * @return 夹角弧度
     * 
     */
    static float angle(const Vec2& v1, const Vec2& v2);

    /**
     * 向量加法，加上v向量的值
     *
     * @param v 将被添加的向量
     * 
     */
    void add(const Vec2& v);

    /**
     * 向量v1和v2相加，将结果保存在dst中
     *
     * @param v1 第一向量
     * @param v2 第二向量
     * @param dst 相加的结果
     * 
     */
    static void add(const Vec2& v1, const Vec2& v2, Vec2* dst);

    /**
     * 将向量值限制在指定的[min,max]区间内
     *
     * @param min 最小值
     * @param max 最大值
     * 
     */
    void clamp(const Vec2& min, const Vec2& max);

    /**
     * 将指定向量v限制在[min,max]区间内，并用dst保存结果。
     *
     * @param v 将被限定的向量
     * @param min 最小值
     * @param max 最大值
     * @param dst 结果
     * 
     */
    static void clamp(const Vec2& v, const Vec2& min, const Vec2& max, Vec2* dst);

    /**
     * 返回本向量到向量v的距离
     *
     * @param v 另一个向量
     * 
     * @see distanceSquared
     * 
     */
    float distance(const Vec2& v) const;

    /**
     * 返回本向量到向量v的距离的平方值
     *
     * 如果不需要得到两个向量之间的准确距离，
     * 例如只是比较不同向量之间的距离大小的时候，
     * 建议使用这个方法来代替distance(const Vec2& v)方法
     *
     * @param v 另一个向量
     * 
     * @see distance
     * 
     */
    float distanceSquared(const Vec2& v) const;

    /**
     * 返回本向量与指定向量v的点积
     *
     * @param v 用来计算点积的另一个向量
     * 
     */
    float dot(const Vec2& v) const;

    /**
     * 返回向量v1和v2的点积
     *
     * @param v1 第一个向量
     * @param v2 第二个向量
     * 
     */
    static float dot(const Vec2& v1, const Vec2& v2);

    /**
     * 计算向量的长度并返回
     *
     * @see lengthSquared
     * 
     */
    float length() const;

    /**
     * 计算向量长度的平方并返回
     *
     * 当不需要获取准确的向量长度时，
     * 例如只是简单比较不同向量之间的长度大小，
     * 可以使用本方法代替length()
     *
     * 
     * @see length
     * 
     */
    float lengthSquared() const;

    /**
     * 向量求负
     */
    void negate();

    /**
     * 求向量的标准化向量
     *
     * 这个方法标准化一个Vec2向量为单位长度
     * （调用这个方法后向量长度为1.0f）。
     * 如果向量已经是单位长度或者长度为零，
     * 这个方法不起任何作用。
     * 
     */
    void normalize();

    /**
     * 标准化这个向量并将结果保存在dst中
     *
     * 如果向量已经是单位长度或者长度为零，
     * 这个方法将简单的把当前向量值拷贝到dst中。
     *
     */
    Vec2 getNormalized() const;

    /**
     * 用指定的放缩系数对向量的各分量进行放缩
     *
     * @param scalar 缩放因子
     * 
     */
    void scale(float scalar);

    /**
     * 用scale向量的x分量来放缩本向量的x分量，用scale向量的y分量来放缩本向量的y分量。
     *
     * @param scale 缩放因子
     */
    void scale(const Vec2& scale);

    /**
     * 向量绕指定点point旋转angle度，其中angle的单位为弧度。
     *
     * @param point 旋转锚点
     * @param angle 旋转角度
     * 
     */
    void rotate(const Vec2& point, float angle);

    /**
     * 设置向量的x分量值为xx，y分量值为yy。
     *
     * @param xx 新的X坐标
     * @param yy 新的Y坐标
     * 
     */
    void set(float xx, float yy);

    /**
     * 给定array序列，依序设置向量各分量的值。
     *
     * @param array 包含x，y向量的数组
     * 
     */
    void set(const float* array);

    /**
     * 将指定向量v的值赋给本向量
     *
     * @param v 被拷贝的向量
     * 
     */
    void set(const Vec2& v);

    /**
     * 得到p1指向p2的一个有向向量
     * 
     * @param p1 第一个点
     * @param p2 第二个点
     * 
     */
    void set(const Vec2& p1, const Vec2& p2);

    /**
     * 本向量减去向量v
     *
     */
    void subtract(const Vec2& v);

    /**
     * 向量v1减去v2，把结果保存在dst中
     *
     * @param v1 第一向量
     * @param v2 第二向量
     * @param dst 结果
     * 
     */
    static void subtract(const Vec2& v1, const Vec2& v2, Vec2* dst);

    /**
     * 平滑更新向量的当前位置，指向目标向量target
     * responseTime定义了平滑时间量，该值越大结果越平滑，
     * 相应的延迟时间越长。如果希望向量紧跟target向量，
     * 提供一个相对elapsedTime小很多的responseTime值即可。
     *
     * @param target 目标值
     * @param elapsedTime 消逝时间
     * @param responseTime 响应时间
     * 
     */
    void smooth(const Vec2& target, float elapsedTime, float responseTime);

    /**
     * 向量加法，求向量与给定向量v的和
     * 
     * 注意：这个加法并不改变原向量的值，返回值单独保存
     * 
     * @param v 被加的向量
     * 
     */
    inline const Vec2 operator+(const Vec2& v) const;

    /**
     * 向量加法，求向量与给定向量v的和，将结果保存在该向量中，并返回。
     * 
     * @param v 被加的向量
     * 
     */
    inline Vec2& operator+=(const Vec2& v);

    /**
     * 向量减法，求向量与给定向量v的差
     * 注意：这个减法并不改变原向量的值，返回值单独保存
     * 
     * @param v 被加的向量
     * 
     */
    inline const Vec2 operator-(const Vec2& v) const;

    /**
     * 向量减法，求向量与给定向量v的差，将结果保存在该向量中，并返回。
     * 
     * @param v 减的向量
     * 
     */
    inline Vec2& operator-=(const Vec2& v);

    /**
     * 求反向量
     * 注意：这个方法并不改变原向量的值，返回值单独保存
     * 
     */
    inline const Vec2 operator-() const;

    /**
     * 向量乘法，给定浮点数s，求向量各分量分别乘以s后的值。
     * 注意：这个方法并不改变原向量的值，返回值单独保存。
     * 
     * @param s 缩放因子
     * 
     */
    inline const Vec2 operator*(float s) const;

    /**
     * 向量乘法，给定浮点数s，求向量各分量分别乘以s后的值，将所得结果保存在原向量中。
     * 
     * @param s 缩放因子.
     * 
     */
    inline Vec2& operator*=(float s);
    
    /**
     * 向量除法，给定浮点数s，求向量各分量分别除以s后的值。
     * 注意：这个方法并不改变原向量的值，返回值单独保存。
     *
     */
    inline const Vec2 operator/(float s) const;

    /**
     * 
     * 判断该向量是否小于给定向量v，如果小于则返回true，否则返回false。
     * 
     */
    inline bool operator<(const Vec2& v) const;

    /**
     * 
     * 判断该向量是否等于给定向量v，如果等于则返回True，否则返回false。
     */
    inline bool operator==(const Vec2& v) const;

    /**
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
    
    /** 
     * @returns 如果点有fuzzy equality意味着与某种方差是相等的
     * @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    bool fuzzyEquals(const Vec2& target, float variance) const;

    /** 计算点到原点的距离，返回一个浮点数
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline float getLength() const {
        return sqrtf(x*x + y*y);
    };

    /** 计算该向量长度的平方，不调用sqrt().
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline float getLengthSq() const {
        return dot(*this); //x*x + y*y;
    };

    /** 计算到另一个向量的长度的平方，不调用sqrt().
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getDistanceSq(const Vec2& other) const {
        return (*this - other).getLengthSq();
    };

    /** 计算两点之间的距离
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline float getDistance(const Vec2& other) const {
        return (*this - other).getLength();
    };

    /** @returns 返回向量与x轴夹角，单位是弧度。
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline float getAngle() const {
        return atan2f(y, x);
    };

    /** @returns 返回两个向量的夹角，单位是弧度。
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    float getAngle(const Vec2& other) const;

    /** 计算两个二维向量的叉乘
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline float cross(const Vec2& other) const {
        return x*other.y - y*other.x;
    };

    /** 计算v逆时针旋转90度的垂线--cross(v,perp(v))>=0
     @return Vec2
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline Vec2 getPerp() const {
        return Vec2(-y, x);
    };
    
    /** 用向量计算两点间的中点
     @return Vec2
     @since v3.0
     * @js NA
     * @lua NA
     * 
     */
    inline Vec2 getMidpoint(const Vec2& other) const
    {
        return Vec2((x + other.x) / 2.0f, (y + other.y) / 2.0f);
    }
    
    /** 将一个点限制在min_inclusive和max_inclusive之间，返回该点的二维向量形式
     @since v3.0
     * @js NA
     * @lua NA
     * 
     */
    inline Vec2 getClampPoint(const Vec2& min_inclusive, const Vec2& max_inclusive) const
    {
        return Vec2(clampf(x,min_inclusive.x,max_inclusive.x), clampf(y, min_inclusive.y, max_inclusive.y));
    }
    
    /** 对该点向量形式的各分量进行function参数来指定的运算，
     * 如absf,floorf,ceilf,roundf等，
     * 任何函数拥有如下形式：float func(float)均可。
     * 例如：我们对x,y进行floor运算，则调用方法为p.compOp(floorf);
     @since v3.0
     * @js NA
     * @lua NA
     * 
     */
    inline Vec2 compOp(std::function<float(float)> function) const
    {
        return Vec2(function(x), function(y));
    }

    /** 计算向量v顺时针旋转90度后的值---cross(v,rperp(v))<=0
     @return Vec2
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline Vec2 getRPerp() const {
        return Vec2(y, -x);
    };

    /** 计算该向量在另一向量other上的投影。
     @return Vec2
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline Vec2 project(const Vec2& other) const {
        return other * (dot(other)/other.dot(other));
    };

    /** 绕other向量旋转。
     * 返回向量的角度为this.getAngle()+other.getAngle(),
     * 长度为this.getLength()*other.getLength()
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline Vec2 rotate(const Vec2& other) const {
        return Vec2(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    /** 绕other向量旋转前的向量值
     * 返回向量的角度为this.getAngle()-other.getAngle(),
     * 长度为this.getLength()*other.getLength().
     * (这里是不是有点问题，难道不应该是this.getLength()/other.getLength()么？)
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline Vec2 unrotate(const Vec2& other) const {
        return Vec2(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    /** 两个点a和b之间的线性插值
     @returns
        alpha ==0 ? a
        alpha ==1 ? b
        否则为a和b之间的一个值
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
     */
    inline Vec2 lerp(const Vec2& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    /** 以pivot为轴逆时针旋转angle度（单位为弧度），返回结果向量
     @since v2.1.4
     * @js NA
     * @lua NA
     * 
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
    
    /** 一个通用的线段相交检测
     @param A   为线段L1起点 L1 = (A - B)
     @param B   为L1终点 L1 = (A - B)
     @param C   为线段L2起点 L2 = (C - D)
     @param D   为L2终点 L2 = (C - D)
     @param S   为L1上计算各点的插值参数，计算方法为：p = A + S*(B - A)
     @param T   为L2上计算各点的插值参数，计算方法为：p = C + T*(D - C)
     @returns   whether these two lines interects.

     注意要准确测试出线段是否相交我们需要确保S&T的值在[0..1]区间范围内 
     @since 3.0
     * @js NA
     * @lua NA
     * 
     */
    static bool isLineIntersect(const Vec2& A, const Vec2& B,
                                 const Vec2& C, const Vec2& D,
                                 float *S = nullptr, float *T = nullptr);
    
    /**
     如果直线AB与线段CD重叠，返回True。
     @since v3.0
     * @js NA
     * @lua NA
     * 
     */
    static bool isLineOverlap(const Vec2& A, const Vec2& B,
                                const Vec2& C, const Vec2& D);
    
    /**
     如果直线AB与线段CD平行，返回True。
     @since v3.0
     * @js NA
     * @lua NA
     * 
     */
    static bool isLineParallel(const Vec2& A, const Vec2& B,
                   const Vec2& C, const Vec2& D);
    
    /**
     如果线段AB与线段CD重叠，返回True。
     @since v3.0
     * @js NA
     * @lua NA
     * 
     */
    static bool isSegmentOverlap(const Vec2& A, const Vec2& B,
                                 const Vec2& C, const Vec2& D,
                                 Vec2* S = nullptr, Vec2* E = nullptr);
    
    /**
     如果线段AB与线段CD交叉，返回True。
     @since v3.0
     * @js NA
     * @lua NA
     * 
     */
    static bool isSegmentIntersect(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D);
    
    /**
     返回直线AB，CD的交叉点。
     @since v3.0
     * @js NA
     * @lua NA
     * 
     */
    static Vec2 getIntersectPoint(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D);
    
    /** 等于 Vec2(0,0) */
    static const Vec2 ZERO;
    /** 等于 Vec2(1,1) */
    static const Vec2 ONE;
    /** 等于 Vec2(1,0) */
    static const Vec2 UNIT_X;
    /** 等于 Vec2(0,1) */
    static const Vec2 UNIT_Y;
    /** 等于 Vec2(0.5, 0.5) */
    static const Vec2 ANCHOR_MIDDLE;
    /** 等于 Vec2(0, 0) */
    static const Vec2 ANCHOR_BOTTOM_LEFT;
    /** 等于 Vec2(0, 1) */
    static const Vec2 ANCHOR_TOP_LEFT;
    /** 等于 Vec2(1, 0) */
    static const Vec2 ANCHOR_BOTTOM_RIGHT;
    /** 等于 Vec2(1, 1) */
    static const Vec2 ANCHOR_TOP_RIGHT;
    /** 等于 Vec2(1, 0.5) */
    static const Vec2 ANCHOR_MIDDLE_RIGHT;
    /** 等于 Vec2(0, 0.5) */
    static const Vec2 ANCHOR_MIDDLE_LEFT;
    /** 等于 Vec2(0.5, 1) */
    static const Vec2 ANCHOR_MIDDLE_TOP;
    /** 等于 Vec2(0.5, 0) */
    static const Vec2 ANCHOR_MIDDLE_BOTTOM;
};

/**
 * 计算向量与给定浮点数的乘积。
 * 
 * @param x 缩放因子
 * @param v 被缩放的向量
 * @return 缩放后的值
 * 
 */
inline const Vec2 operator*(float x, const Vec2& v);

typedef Vec2 Point2;

NS_CC_MATH_END

#include "Vector2.inl"

#endif // MATH_VEC2_H
