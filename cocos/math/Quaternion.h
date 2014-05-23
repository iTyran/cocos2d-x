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
 * Defines a 4-element quaternion that represents the orientation of an object in space.
 * 在空间中定义一个四元数代码一个对象的方向
 *
 * Quaternions are typically used as a replacement for euler angles and rotation matrices as a way to achieve smooth interpolation and avoid gimbal lock.
 * 四元数通常用来替换欧拉角，旋转矩阵，以此来实现平滑插补，避免万向节死锁。
 *
 * Note that this quaternion class does not automatically keep the quaternion normalized. Therefore, care must be taken to normalize the quaternion when necessary, by calling the normalize method.
 * 要注意四元数类(Quaternion)不会自动保持四元数归一化。因此，必要时必需通过调用归一的方法把四元数归一化。
 * This class provides three methods for doing quaternion interpolation: lerp, slerp, and squad.
 *
 * lerp (linear interpolation): the interpolation curve gives a straight line in quaternion space. It is simple and fast to compute. The only problem is that it does not provide constant angular velocity. Note that a constant velocity is not necessarily a requirement for a curve;
 * lerp（线性插值）:它的插补曲线给出了在四元数空间中的直线。这是简单和快速地计算。唯一的问题是，它不提供恒角速度。注意一个恒定的速度不一定是一条曲线的要求;
 * slerp (spherical linear interpolation): the interpolation curve forms a great arc on the quaternion unit sphere. Slerp provides constant angular velocity;
 * slerp（球形线性插值）：它的插补曲线构成的四元数单位球面上有很大的弧线。 Slerp提供恒定角速度;
 * squad (spherical spline interpolation): interpolating between a series of rotations using slerp leads to the following problems:
 * squad（球形样条插值）：在使用slerp(球形线性插值)一系列的旋转进行插值时导致了以下问题：
 * - the curve is not smooth at the control points;
 * - 曲线的控制点不平滑
 * - the angular velocity is not constant;
 * - 角速度不是恒定的;
 * - the angular velocity is not continuous at the control points.
 * - 角速度的控制点不是连续的
 *
 * Since squad is continuously differentiable, it remedies the first and third problems mentioned above.
 * 由于squad（球形样条插值是连续可微的，它可以补救上面提到的第一个和第三个问题。
 * The slerp method provided here is intended for interpolation of principal rotations. It treats +q and -q as the same principal rotation and is at liberty to use the negative of either input. The resulting path is always the shorter arc.
 * 这里提供的slerp（球形线性插值）方法用于主旋转的插值。它把+q和-q作为同一主转动，并且可以随意地输入负数。由此产生的路径总是短弧。
 *
 * The lerp method provided here interpolates strictly in quaternion space. Note that the resulting path may pass through the origin if interpolating between a quaternion and its exact negative.
 * 这里提供的lerp(线性插值)方法在四元数空间严格插值。需要注意的是如果一个四元数和它的确切负数之间进行插值,产生的路径可能经过原点。
 *
 * As an example, consider the following quaternions:
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
     * The x-value of the quaternion's vector component.
	 * 四元数的向量分量x值
     */
    float x;
    /**
     * The y-value of the quaternion's vector component.
	 * 四元数的向量分量y值
     */
    float y;
    /**
     * The z-value of the quaternion's vector component.
	 * 四元数的向量分量z值
     */
    float z;
    /**
     * The scalar component of the quaternion.
	 * 四元数的标量分量
     */
    float w;

    /**
     * Constructs a quaternion initialized to (0, 0, 0, 1).
	 * 构造一个四元数并初始化为（0，0，0，1）。
     */
    Quaternion();

    /**
     * Constructs a quaternion initialized to (0, 0, 0, 1).
	 * 构造一个四元数并用给定的值进行初始化
     *
     * @param xx 四元数的x分量
     * @param yy 四元数的y分量
     * @param zz 四元数的z分量
     * @param ww 四元数的w分量
     */
    Quaternion(float xx, float yy, float zz, float ww);

    /**
     * Constructs a new quaternion from the values in the specified array.
	 * 根据指定数组的值构造一个新的四元数。
     *
     * @param array 构造四元数的数组
     */
    Quaternion(float* array);

    /**
     * Constructs a quaternion equal to the rotational part of the specified matrix.
	 * 根据指定矩阵的旋转部分构造一个四元数
     *
     * @param m The matrix.
     */
    Quaternion(const Mat4& m);

    /**
     * Constructs a quaternion equal to the rotation from the specified axis and angle.
	 * 根据指定的旋转轴和角度的旋转构造一个四元数
     *
     * @param axis 描述旋转轴的矢量。
     * @param angle 旋转角度(弧度)。
     */
    Quaternion(const Vec3& axis, float angle);

    /**
     * Constructs a new quaternion that is a copy of the specified one.
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
     * Creates a quaternion equal to the rotational part of the specified matrix
     * and stores the result in dst.
	 * 根据指定矩阵的旋转部分创建一个四元数，并储存在指定的四元数中
     *
     * @param m 矩阵。
     * @param dst 储存结果的四元数。
     */
    static void createFromRotationMatrix(const Mat4& m, Quaternion* dst);

    /**
     * Creates this quaternion equal to the rotation from the specified axis and angle
     * and stores the result in dst.
	 * 根据指定旋转轴和角度创建一个四元数，并储存在指定的四元数中
     *
     * @param axis 描述旋转轴的矢量。
     * @param angle 旋转角度(弧度)。
     * @param dst 储存结果的四元数。
     */
    static void createFromAxisAngle(const Vec3& axis, float angle, Quaternion* dst);

    /**
     * Sets this quaternion to the conjugate of itself.
	 * 设置当前四元数与自身共轭
     */
    void conjugate();

    /**
     * Gets the conjugate of this quaternion in dst.
	 * 获取当前四元数的共轭
     *
     * @param dst A quaternion to store the conjugate in.
     */
    Quaternion getConjugated() const;

    /**
     * Sets this quaternion to the inverse of itself.
	 * 设置当前四元数与自身相反
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
	 * 需要注意的是四元数的倒数等于它的共轭时，四元数是单位长度。出于这个原因，当四元数已经单位长度时，它是使用共轭方法时更直接有效的，。
     *
     * @return true if the inverse can be computed, false otherwise.如果当前四元数是可以倒置计算的返回true，否则返回false。
     */
    bool inverse();

    /**
     * Gets the inverse of this quaternion in dst.
	 * 获取四元数的倒数
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
	 * 需要注意的是四元数的倒数等于它的共轭时，四元数是统一单位长度。出于这个原因，当四元数已经统一单位长度时，它是使用共轭方法时更直接有效的，。
     *
     * @param dst A quaternion to store the inverse in.
     * 
     * @return 获取四元数的倒数
     */
    Quaternion getInversed() const;

    /**
     * Multiplies this quaternion by the specified one and stores the result in this quaternion.
     *
     * @param q The quaternion to multiply.
     */
    void multiply(const Quaternion& q);

    /**
     * Multiplies the specified quaternions and stores the result in dst.
	 * 把两个指定的四元数相乘，并把结果储存到dst（指定的四元数引用）
     *
     * @param q1 第一个四元数。
     * @param q2 第二个四元数。
     * @param dst 储存结果的四元数引用。
     */
    static void multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst);

    /**
     * Normalizes this quaternion to have unit length.
	 * 归一化四元数便利它有统一的单位长度
     *
     * 如果四元数已经有单位长度或者四元数的长度为零，则此方法不执行任何操作。
     */
    void normalize();

    /**
     * Normalizes this quaternion and stores the result in dst.
     *
     * If the quaternion already has unit length or if the length
     * of the quaternion is zero, this method simply copies
     * this vector into dst.
     *
     * @param dst A quaternion to store the result in.
     */
    Quaternion getNormalized() const;

    /**
     * Sets the elements of the quaternion to the specified values.
     *
     * @param xx The new x-value.
     * @param yy The new y-value.
     * @param zz The new z-value.
     * @param ww The new w-value.
     */
    void set(float xx, float yy, float zz, float ww);

    /**
     * Sets the elements of the quaternion from the values in the specified array.
     *
     * @param array An array containing the elements of the quaternion in the order x, y, z, w.
     */
    void set(float* array);

    /**
     * Sets the quaternion equal to the rotational part of the specified matrix.
     *
     * @param m The matrix.
     */
    void set(const Mat4& m);

    /**
     * Sets the quaternion equal to the rotation from the specified axis and angle.
     * 
     * @param axis The axis of rotation.
     * @param angle The angle of rotation (in radians).
     */
    void set(const Vec3& axis, float angle);

    /**
     * Sets the elements of this quaternion to a copy of the specified quaternion.
     *
     * @param q The quaternion to copy.
     */
    void set(const Quaternion& q);

    /**
     * Sets this quaternion to be equal to the identity quaternion.
     */
    void setIdentity();

    /**
     * Converts this Quaternion4f to axis-angle notation. The axis is normalized.
     *
     * @param e The Vec3f which stores the axis.
     * 
     * @return The angle (in radians).
     */
    float toAxisAngle(Vec3* e) const;

    /**
     * Interpolates between two quaternions using linear interpolation.
     *
     * The interpolation curve for linear interpolation between
     * quaternions gives a straight line in quaternion space.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param t The interpolation coefficient.
     * @param dst A quaternion to store the result in.
     */
    static void lerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
    /**
     * Interpolates between two quaternions using spherical linear interpolation.
     *
     * Spherical linear interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be at (or close to) unit length.
     * This method does not automatically normalize the input quaternions, so it is up to the
     * caller to ensure they call normalize beforehand, if necessary.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param t The interpolation coefficient.
     * @param dst A quaternion to store the result in.
     */
    static void slerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
    /**
     * Interpolates over a series of quaternions using spherical spline interpolation.
     *
     * Spherical spline interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be unit.
     * This method does not automatically normalize the input quaternions,
     * so it is up to the caller to ensure they call normalize beforehand, if necessary.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param s1 The first control point.
     * @param s2 The second control point.
     * @param t The interpolation coefficient.
     * @param dst A quaternion to store the result in.
     */
    static void squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2, float t, Quaternion* dst);

    /**
     * Calculates the quaternion product of this quaternion with the given quaternion.
     * 
     * Note: this does not modify this quaternion.
     * 
     * @param q The quaternion to multiply.
     * @return The quaternion product.
     */
    inline const Quaternion operator*(const Quaternion& q) const;

    /**
     * Multiplies this quaternion with the given quaternion.
     * 
     * @param q The quaternion to multiply.
     * @return This quaternion, after the multiplication occurs.
     */
    inline Quaternion& operator*=(const Quaternion& q);

private:

    /**
     * Interpolates between two quaternions using spherical linear interpolation.
     *
     * Spherical linear interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be at (or close to) unit length.
     * This method does not automatically normalize the input quaternions, so it is up to the
     * caller to ensure they call normalize beforehand, if necessary.
     *
     * @param q1x The x component of the first quaternion.
     * @param q1y The y component of the first quaternion.
     * @param q1z The z component of the first quaternion.
     * @param q1w The w component of the first quaternion.
     * @param q2x The x component of the second quaternion.
     * @param q2y The y component of the second quaternion.
     * @param q2z The z component of the second quaternion.
     * @param q2w The w component of the second quaternion.
     * @param t The interpolation coefficient.
     * @param dstx A pointer to store the x component of the slerp in.
     * @param dsty A pointer to store the y component of the slerp in.
     * @param dstz A pointer to store the z component of the slerp in.
     * @param dstw A pointer to store the w component of the slerp in.
     */
    static void slerp(float q1x, float q1y, float q1z, float q1w, float q2x, float q2y, float q2z, float q2w, float t, float* dstx, float* dsty, float* dstz, float* dstw);

    static void slerpForSquad(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
};

NS_CC_MATH_END

#include "Quaternion.inl"

#endif
