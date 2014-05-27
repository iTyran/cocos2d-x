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

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Vector3.h"
#include "Matrix.h"
//#include "Plane.h"

NS_CC_MATH_BEGIN

class Mat4;

/**
 * 在空间中定义一个四元数代码一个对象的方向
 *
 * 四元数通常用来替换欧拉角，旋转矩阵，以此来实现平滑插补，避免万向节死锁。
 *
 * 要注意四元数类(Quaternion)不会自动保持四元数归一化。因此，必要时必需通过调用归一的方法把四元数归一化。
 *
 * lerp（线性插值）:它的插补曲线给出了在四元数空间中的直线。这是简单和快速地计算。唯一的问题是，它不提供恒角速度。注意一个恒定的速度不一定是一条曲线的要求;
 * slerp（球形线性插值）：它的插补曲线构成的四元数单位球面上有很大的弧线。 Slerp提供恒定角速度;
 * squad（球形样条插值）：在使用slerp(球形线性插值)一系列的旋转进行插值时导致了以下问题：
 * - 曲线的控制点不平滑
 * - 角速度不是恒定的;
 * - 角速度的控制点不是连续的
 *
 * 由于squad（球形样条插值是连续可微的，它可以补救上面提到的第一个和第三个问题。
 * 这里提供的slerp（球形线性插值）方法用于主旋转的插值。它把+q和-q作为同一主转动，并且可以随意地输入负数。由此产生的路径总是短弧。
 *
 * 这里提供的lerp(线性插值)方法在四元数空间严格插值。需要注意的是如果一个四元数和它的确切负数之间进行插值,产生的路径可能经过原点。
 *
 * 例如，考虑下面的四元数：
 *
 * q1 = (0.6, 0.8, 0.0, 0.0),
 * q2 = (0.0, 0.6, 0.8, 0.0),
 * q3 = (0.6, 0.0, 0.8, 0.0), 和
 * q4 = (-0.8, 0.0, -0.6, 0.0).
 * For the point p = (1.0, 1.0, 1.0), the following figures show the trajectories of p using lerp, slerp, and squad.
 * 对于点p = (1.0, 1.0, 1.0), 以下数据显示了点p使用lerp（线性插值）,slerp（球形线性插值）和squad（球形样条插值）的轨迹。
 */
class Quaternion
{
    friend class Curve;
    friend class Transform;

public:

    /**
	 * 四元数的向量分量x值
     */
    float x;
    /**
	 * 四元数的向量分量y值
     */
    float y;
    /**
	 * 四元数的向量分量z值
     */
    float z;
    /**
	 * 四元数的标量分量
     */
    float w;

    /**
	 * 构造一个四元数并初始化为（0，0，0，1）。
     */
    Quaternion();

    /**
	 * 构造一个四元数并用给定的值进行初始化
     *
     * @param xx 四元数的x分量
     * @param yy 四元数的y分量
     * @param zz 四元数的z分量
     * @param ww 四元数的w分量
     */
    Quaternion(float xx, float yy, float zz, float ww);

    /**
	 * 根据指定数组的值构造一个新的四元数。
     *
     * @param array 构造四元数的数组
     */
    Quaternion(float* array);

    /**
	 * 根据指定矩阵的旋转部分构造一个四元数
     *
     * @param m The matrix.
     */
    Quaternion(const Mat4& m);

    /**
	 * 根据指定的旋转轴和角度的旋转构造一个四元数
     *
     * @param axis 描述旋转轴的矢量。
     * @param angle 旋转角度(弧度)。
     */
    Quaternion(const Vec3& axis, float angle);

    /**
	 * 根据指定的四元数复制一个新的四元数
     *
     * @param copy 要复制的四元数
     */
    Quaternion(const Quaternion& copy);

    /**
     * 析构函数.
     */
    ~Quaternion();

    /**
     * 返回单位四元数.
     *
     * @return 单位四元数。
     */
    static const Quaternion& identity();

    /**
     * 返回全是零的四元数.
     *
     * @return 全是零的四元数.
     */
    static const Quaternion& zero();

    /**
     * 判断当前四元数是否单位四元数
     *
     * @return 如果是单位四元数返回true，否则返回false。
     */
    bool isIdentity() const;

    /**
	 * 判断当前四元数是否全部为零
     *
     * @return 如果四元数全部为零返回true，否则返回false。
     */
    bool isZero() const;

    /**
	 * 根据指定矩阵的旋转部分创建一个四元数，并储存在指定的四元数中
     *
     * @param m 矩阵。
     * @param dst 储存结果的四元数。
     */
    static void createFromRotationMatrix(const Mat4& m, Quaternion* dst);

    /**
	 * 根据指定旋转轴和角度创建一个四元数，并储存在指定的四元数中
     *
     * @param axis 描述旋转轴的矢量。
     * @param angle 旋转角度(弧度)。
     * @param dst 储存结果的四元数。
     */
    static void createFromAxisAngle(const Vec3& axis, float angle, Quaternion* dst);

    /**
	 * 设置当前四元数与自身共轭.
     */
    void conjugate();

    /**
	 * 获取当前四元数的共轭.
     *
     */
    Quaternion getConjugated() const;

    /**
	 * 设置当前四元数与自身相反.
     *
	 * 需要注意的是四元数的倒数等于它的共轭时，四元数是单位长度。出于这个原因，当四元数已经单位长度时，它是使用共轭方法时更直接有效的。
     *
     * @return 如果当前四元数是可以倒置计算的返回true，否则返回false。
     */
    bool inverse();

    /**
	 * 获取四元数的倒数
     *
	 * 需要注意的是四元数的倒数等于它的共轭时，四元数是统一单位长度。出于这个原因，当四元数已经统一单位长度时，它是使用共轭方法时更直接有效的。
     * 
     * @return 获取四元数的倒数
     */
    Quaternion getInversed() const;

    /**
     * 与指定的四元数相乘，并把结果储存到指定传入的四元数中。
     *
     * @param q 相乘的四元数。
     */
    void multiply(const Quaternion& q);

    /**
	 * 把两个指定的四元数相乘，并把结果储存到dst（指定的四元数引用）
     *
     * @param q1 第一个四元数。
     * @param q2 第二个四元数。
     * @param dst 储存结果的四元数引用。
     */
    static void multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst);

    /**
	 * 归一化四元数有利于它有统一的单位长度
     *
     * 如果四元数已经有单位长度或者四元数的长度为零，则此方法不执行任何操作。
     */
    void normalize();

    /**
     * 获取归一处理的四元数
     *
     * 如果这个四元数是有单位长度或者为零，只是返回该四元数.
     *
     */
    Quaternion getNormalized() const;

    /**
     * 根据指定的值设置四元数的元素
     *
     * @param xx 新的x值
     * @param yy 新的y值
     * @param zz 新的z值
     * @param ww 新的w值
     */
    void set(float xx, float yy, float zz, float ww);

    /**
     * 根据指定的数组设置四元数的元素
     *
     * @param array 一个包含四元数x,y,z,w分量的数组
     */
    void set(float* array);

    /**
     * 设置四元数等于指定矩阵的旋转部分
     *
     * @param m 矩阵。
     */
    void set(const Mat4& m);

    /**
     * 设置四元数等于指定指定旋转轴和角度的旋转
     * 
     * @param axis 旋转轴。
     * @param angle 旋转的角度（以弧度为单位）。
     */
    void set(const Vec3& axis, float angle);

    /**
     * 复制四元数的元素到指定的四元数的副本。
     *
     * @param q 四元数的副本。
     */
    void set(const Quaternion& q);

    /**
     * 设置四元数为该单位四元数
     */
    void setIdentity();

    /**
     * 把四元数转换为转角符号。该轴是归一化的。
     *
     * @param e 储存该轴的Vec3f。
     * 
     * @return 角度（以弧度为单位）
     */
    float toAxisAngle(Vec3* e) const;

    /**
     * 把两个四元数使用线性插值进行插值。
     *
     * 四元数之间线性插值的插值曲线给出了在四元数空间中的直线。
     *
     * @param q1 第一个四元数。
     * @param q2 第二个四元数。
     * @param t 内插系数。
     * @param dst 储存结果的四元数。
     */
    static void lerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
    /**
     * 把两个四元数使用球形线性插值进行插值。
     *
     * 球形线性插值提供不同方向的平滑过渡往往在动画的三维模型或摄像机非常有用。
     *
     * 注：为了精确插值，输入四元数必须在（或接近）单位长度。此方法不会自动归一化牏输入的四元数，如有必要，它是由调用者来确保他们都归一化。
     *
     * @param q1 第一个四元数。
     * @param q2 第二个四元数。
     * @param t 内插系数。
     * @param dst 储存结果的四元数。
     */
    static void slerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
    /**
     * 使用球形样条插值修改一系列的四元数。
     *
     * 球形样条插值提供不同方向平滑的过渡往往在动画的三维模型或摄像机非常有用。
     *
     * 注：为了精确插值，输入四元数必须是单位。
     * 此方法不会自动归一化处理输入的四元数，如果必要，它是由调用者来确保他们都归一化。
     *
     * @param q1 第一个四元数。
     * @param q2 第二个四元数。
     * @param s1 第一个控制点。
     * @param s2 第丙个控制点。
     * @param t 内插系数。
     * @param dst 储存结果的四元数。
     */
    static void squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2, float t, Quaternion* dst);

    /**
     * 计算当前四元数与指定四元数的乘积的四元数。
     *
     * 注意：该方法不修改当此四元数。
     * 
     * @param q 要相乘的四元数。
     * @return 两个四元数的乘积的四元数。
     */
    inline const Quaternion operator*(const Quaternion& q) const;

    /**
     * 计算当前四元数与指定四元数的乘积。
     * 
     * @param q 要相乘的四元数。
     * @return 相乘之后的四元数。
     */
    inline Quaternion& operator*=(const Quaternion& q);

private:

    /**
     * 把两个四元数使用球形线性插值进行插值。
     *
     * 球形线性插值提供不同方向平滑的过渡往往在动画的三维模型或摄像机非常有用。
     *
     * 注：为了精确插值，输入四元数必须在（或接近）单位长度。此方法不会自动归一化牏输入的四元数，如有必要，它是由调用者来确保他们都归一化。
     *
     * @param q1x 第一个四元数的x分量。
     * @param q1y 第一个四元数的y分量。
     * @param q1z 第一个四元数的z分量。
     * @param q1w 第一个四元数的w分量。
     * @param q2x 第二个四元数的x分量。
     * @param q2y 第二个四元数的y分量。
     * @param q2z 第二个四元数的z分量。
     * @param q2w 第二个四元数的w分量。
     * @param t 内插系数。slerp（球形线性插值）
     * @param dstx 指向储存slerp（球形线性插值）x分量的指针。
     * @param dsty 指向储存slerp（球形线性插值）y分量的指针。
     * @param dstz 指向储存slerp（球形线性插值）z分量的指针。
     * @param dstw 指向储存slerp（球形线性插值）w分量的指针。
     */
    static void slerp(float q1x, float q1y, float q1z, float q1w, float q2x, float q2y, float q2z, float q2w, float t, float* dstx, float* dsty, float* dstz, float* dstw);

    static void slerpForSquad(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
};

NS_CC_MATH_END

#include "Quaternion.inl"

#endif
