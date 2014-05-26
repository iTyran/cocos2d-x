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

#ifndef MATH_MAT4_H
#define MATH_MAT4_H

#include "math/Vector3.h"
#include "math/Vector4.h"

NS_CC_MATH_BEGIN

//class Plane;

/**
 * 定义一个4*4的浮点矩阵来表示一个3D转换。
 *
 * 用向量作为列，结果一个矩阵表示如下，x,y,z作为矩阵的转换部件。
 *
 * 1  0  0  x
 * 0  1  0  y
 * 0  0  1  z
 * 0  0  0  1
 *
 * 由于这个矩阵类(Mat4)的元素是在内存的形式正如OpenGL盼望的一样，所以这个矩阵类(Mat4)是直接兼容OpenGL的。
 * 该矩阵使用列为主(column-major)的格式，以致数组下标优先往下增长。
 * 由于矩阵乘法是不可交换的，所以乘法必须在合并时进行正序转换。
 * 假设我们有一个转换矩阵T和一个旋转矩阵R。首先把对象围绕原点旋转然后再转换它，你可以使两个矩阵相乘得到TR。
 *
 * 同样，首先转换那对象然后再旋转它，你会得到一个RT。
 *
 * 所以通常，矩阵转换发生时必须进行倒序转换。(这也适用于缩放，旋转和平移方法；这些方法都是处理矩阵缩放，旋转和转换的便利方法)
 *
 * 在多次局部转换的情况下（围绕z轴旋转0.76弧度，然后没x轴平移2.1,然后...）,这比使用转换类处理更好（这是对那种用法的优化）。
 *
 * @see Transform
 */

class Mat4
{
public:
    // //temp add conversion
    // operator kmMat4() const
    // {
    //     kmMat4 result;
    //     kmMat4Fill(&result, m);
    //     return result;
    // }
    
    // Mat4(const kmMat4& mat)
    // {
    //     set(mat.mat);
    // }
    /**
	 * 储存这个4*4的矩阵
     * */
    float m[16];

    /**
	 * 构造一个矩阵并初始化为单位矩阵
     *
     * 1  0  0  0
     * 0  1  0  0
     * 0  0  1  0
     * 0  0  0  1
     */
    Mat4();

    /**
	 * 构造一个矩阵并使用给定的值初始化
     *
     * @param m11 第一行的第一个元素.
     * @param m12 第一行的第二个元素.
     * @param m13 第一行的第三个元素.
     * @param m14 第一行的第四个元素.
     * @param m21 第二行的第一个元素.
     * @param m22 第二行的第二个元素.
     * @param m23 第二行的第三个元素.
     * @param m24 第二行的第四个元素.
     * @param m31 第三行的第一个元素.
     * @param m32 第三行的第二个元素.
     * @param m33 第三行的第三个元素.
     * @param m34 第三行的第四个元素.
     * @param m41 第四行的第一个元素.
     * @param m42 第四行的第二个元素.
     * @param m43 第四行的第三个元素.
     * @param m44 第四行的第四个元素.
     */
    Mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

    /**
	 * 创建一个矩阵并使用指定的列优先数组时行初始化。
     *
	 * 传入的​​数组是列优先的顺序，所以数组的储存布局如下所示：
     *
     *     0   4   8   12
     *     1   5   9   13
     *     2   6   10  14
     *     3   7   11  15
     *
     * @param mat 一个含有16个元素并且以列优先的数组。
     */
    Mat4(const float* mat);

    /**
	 * 复制指定的矩阵构造一个新的矩阵。
     *
     * @param copy 要复制的矩阵。
     */
    Mat4(const Mat4& copy);

    /**
	 * 析构函数
     */
    ~Mat4();

    /**
	 * 根据输入参数的创建一个视图矩阵。
     *
     * @param eyePosition 视点。
     * @param targetPosition 目标的中心点。
     * @param up 向上向量。
     * @param dst 储存结果的矩阵。
     */
    static void createLookAt(const Vec3& eyePosition, const Vec3& targetPosition, const Vec3& up, Mat4* dst);

    /**
	 * 根据输入参数的创建一个视图矩阵。
     *
     * @param eyePositionX x坐标视点。
     * @param eyePositionY y坐标视点。
     * @param eyePositionZ z坐标视点。
     * @param targetCenterX 目标在x坐标的中心点。
     * @param targetCenterY 目标在y坐标的中心点。
     * @param targetCenterZ 目标在z坐标的中心点。
     * @param upX 向上向量在x坐标的值。
     * @param upY 向上向量在y坐标的值。
     * @param upZ 向上向量在z坐标的值。
     * @param dst 储存结果的矩阵。
     */
    static void createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                             float targetCenterX, float targetCenterY, float targetCenterZ,
                             float upX, float upY, float upZ, Mat4* dst);

    /**
     * 根据视野和返回的值构建一个透视投影矩阵
     *
     *
     * 投影空间指的是空间应用的视图空间投影变换后。
     * 投影变换后，可见内容具有范围都是从-1到1的x和y坐标的，范围从0到1的和z坐标的。
     * 为了获得一个场景的可视区域（在世界空间中）中，创建一个BoundingFrustum和通过组合视图和投影矩阵的构造函数。
     *
     * @param fieldOfView 视图在y方向的值（度为单位）。
     * @param aspectRatio 宽高比，定义为视图空间宽度除以高度。
     * @param zNearPlane 离视图平面最近的距离。
     * @param zFarPlane 离视图平面最远的距离。
     * @param dst 储存结果的矩阵。
     */
    static void createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane, Mat4* dst);

    /**
     * 创建一个正交投影矩阵。
     *
     * @param width 视图的宽度。
     * @param height 视图的高度。
     * @param zNearPlane 视图的最小z值。
     * @param zFarPlane 视图的最大z值。
     * @param dst 储存结果的矩阵。
     */
    static void createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Mat4* dst);

    /**
     * 创建一个正交投影矩阵。
     *
     * 投影空间指的是空间从视图应用投影变换后的空间。
     * 投影变换后,可见内容有x和y坐标的范围为1至-1,和z坐标的范围为0至1。
     *
     * 在正射投影和透视投影没有视角透视收缩。
     *
     * 正投影的可视区域的范围是从左至右的x轴，从下到上的y轴，和zNearPlane到zFarPlane于z轴。
     * 这些值是相对于所述位置以及x，y和视图的z轴。
     * 为了获得场景的可视区域（在世界空间中），创建一个BoundingFrustum，并通过组合视图和投影矩阵的构造函数。
     *
     * @param left 视体的最小x值。
     * @param right 视体的最大x值。
     * @param bottom 视体的最小y值。
     * @param top 视体的最大y值。
     * @param zNearPlane 视体的最小z值。
     * @param zFarPlane 视体的最大z值。
     * @param dst 储存结果的矩阵。
     */
    static void createOrthographicOffCenter(float left, float right, float bottom, float top,
                                            float zNearPlane, float zFarPlane, Mat4* dst);

    /**
     * 创建一个围绕指定对象的位置旋转的球形广告牌(Billboard)。
     *
     * 该方法计算广告牌(Billboard)从对象位置和摄像机的位置的面对方向。
     * 当对象和摄像机位置太近,矩阵将不准确。为了避免这个问题,如果位置太近该方法默认单位旋转处理。(见createBillboard重载的另一种方法)。
     *
     * @param objectPosition 广告牌(Billboard)围绕旋转的对象位置。
     * @param cameraPosition 相机的位置。
     * @param cameraUpVector 相机的向量。
     * @param dst 储存结果的矩阵。
     */
    static void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
                                const Vec3& cameraUpVector, Mat4* dst);

    /**
     * 创建一个球形的广告牌(Billboard),并围绕提供的安全默认指定对象的位置旋转。
     *
     * This method computes the facing direction of the billboard from the object position
     * and camera position. When the object and camera positions are too close, the matrix
     * will not be accurate. To avoid this problem, this method uses the specified camera
     * forward vector if the positions are too close. (See the other overload of createBillboard
     * for an alternative approach).
     * 该方法计算广告牌(Billboard)从对象位置和摄像机的位置的面对方向。
     * 当对象和摄像机位置太近,矩阵将不准确。为了避免这个问题,这种方法使用指定的相机向前向量是否太近的位置。(见createBillboard重载的另一种方法)。
     *
     * @param objectPosition The position of the object the billboard will rotate around.
     * @param cameraPosition The position of the camera.
     * @param cameraUpVector The up vector of the camera.
     * @param cameraForwardVector The forward vector of the camera, used if the positions are too close.
     * @param dst A matrix to store the result in.
     */
    static void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
                                const Vec3& cameraUpVector, const Vec3& cameraForwardVector,
                                Mat4* dst);

    /**
     * Fills in an existing Mat4 so that it reflects the coordinate system about a specified Plane.
     * 填补了现有MAT4（矩阵），以便反映对特定平面的坐标系。
     *
     * @param plane 反射平面。
     * @param dst 储存结果的矩阵。
     */
    //static void createReflection(const Plane& plane, Mat4* dst);

    /**
     * 创建一个缩放矩阵。
     *
     * @param scale 缩放量。
     * @param dst 储存结果的矩阵。
     */
    static void createScale(const Vec3& scale, Mat4* dst);

    /**
     * 创建一个缩放矩阵。
     *
     * @param xScale x轴上的缩放量。
     * @param yScale y轴上的缩放量。
     * @param zScale z轴上的缩放量。
     * @param dst 储存结果的矩阵。
     */
    static void createScale(float xScale, float yScale, float zScale, Mat4* dst);

    /**
     * 根据指定的四元数创建一个旋转矩阵。
     *
     * @param quat 描述三给方向的四元数。
     * @param dst 储存结果的矩阵。
     */
    static void createRotation(const Quaternion& quat, Mat4* dst);

    /**
     * 根据指定的旋转轴和角度创建一个旋转矩阵。
     *
     * @param axis 矢量描述的旋转轴。
     * @param angle 角度（以弧度为单位）。
     * @param dst 储存结果的矩阵。
     */
    static void createRotation(const Vec3& axis, float angle, Mat4* dst);

    /**
     * 根据指定的角度围绕x轴旋转创建一个矩阵。
     *
     * @param angle 旋转角度（以弧度为单位）。
     * @param dst 储存结果的矩阵。
     */
    static void createRotationX(float angle, Mat4* dst);

    /**
     * 根据指定角度矩阵围绕y轴旋转创建一个矩阵。
     *
     * @param angle 旋转角度（以弧度为单位）。
     * @param dst 储存结果的矩阵。
     */
    static void createRotationY(float angle, Mat4* dst);

    /**
     * Creates a matrix describing a rotation around the z-axis.
     *
     * @param angle The angle of rotation (in radians).
     * @param dst A matrix to store the result in.
     */
    static void createRotationZ(float angle, Mat4* dst);

    /**
     * Creates a translation matrix.
     *
     * @param translation The translation.
     * @param dst A matrix to store the result in.
     */
    static void createTranslation(const Vec3& translation, Mat4* dst);

    /**
     * Creates a translation matrix.
     *
     * @param xTranslation The translation on the x-axis.
     * @param yTranslation The translation on the y-axis.
     * @param zTranslation The translation on the z-axis.
     * @param dst A matrix to store the result in.
     */
    static void createTranslation(float xTranslation, float yTranslation, float zTranslation, Mat4* dst);

    /**
     * Adds a scalar value to each component of this matrix.
     *
     * @param scalar The scalar to add.
     */
    void add(float scalar);

    /**
     * Adds a scalar value to each component of this matrix and stores the result in dst.
     *
     * @param scalar The scalar value to add.
     * @param dst A matrix to store the result in.
     */
    void add(float scalar, Mat4* dst);

    /**
     * Adds the specified matrix to this matrix.
     *
     * @param mat The matrix to add.
     */
    void add(const Mat4& mat);

    /**
     * Adds the specified matrices and stores the result in dst.
     *
     * @param m1 The first matrix.
     * @param m2 The second matrix.
     * @param dst The destination matrix to add to.
     */
    static void add(const Mat4& m1, const Mat4& m2, Mat4* dst);

    /**
     * Decomposes the scale, rotation and translation components of this matrix.
     *
     * @param scale The scale.
     * @param rotation The rotation.
     * @param translation The translation.
     */
    bool decompose(Vec3* scale, Quaternion* rotation, Vec3* translation) const;

    /**
     * Computes the determinant of this matrix.
     *
     * @return The determinant.
     */
    float determinant() const;

    /**
     * Gets the scalar component of this matrix in the specified vector.
     *
     * If the scalar component of this matrix has negative parts,
     * it is not possible to always extract the exact scalar component;
     * instead, a scale vector that is mathematically equivalent to the
     * original scale vector is extracted and returned.
     *
     * @param scale A vector to receive the scale.
     */
    void getScale(Vec3* scale) const;

    /**
     * Gets the rotational component of this matrix in the specified quaternion.
     *
     * @param rotation A quaternion to receive the rotation.
     * 
     * @return true if the rotation is successfully extracted, false otherwise.
     */
    bool getRotation(Quaternion* rotation) const;

    /**
     * Gets the translational component of this matrix in the specified vector.
     *
     * @param translation A vector to receive the translation.
     */
    void getTranslation(Vec3* translation) const;

    /**
     * Gets the up vector of this matrix.
     *
     * @param dst The destination vector.
     */
    void getUpVector(Vec3* dst) const;

    /**
     * Gets the down vector of this matrix.
     *
     * @param dst The destination vector.
     */
    void getDownVector(Vec3* dst) const;

    /**
     * Gets the left vector of this matrix.
     *
     * @param dst The destination vector.
     */
    void getLeftVector(Vec3* dst) const;

    /**
     * Gets the right vector of this matrix.
     *
     * @param dst The destination vector.
     */
    void getRightVector(Vec3* dst) const;

    /**
     * Gets the forward vector of this matrix.
     *
     * @param dst The destination vector.
     */
    void getForwardVector(Vec3* dst) const;

    /**
     * Gets the backward vector of this matrix.
     *
     * @param dst The destination vector.
     */
    void getBackVector(Vec3* dst) const;

    /**
     * Inverts this matrix.
     *
     * @return true if the the matrix can be inverted, false otherwise.
     */
    bool inverse();

    /**
     * Stores the inverse of this matrix in the specified matrix.
     *
     * @param dst A matrix to store the invert of this matrix in.
     * 
     * @return true if the the matrix can be inverted, false otherwise.
     */
    Mat4 getInversed() const;

    /**
     * Determines if this matrix is equal to the identity matrix.
     *
     * @return true if the matrix is an identity matrix, false otherwise.
     */
    bool isIdentity() const;

    /**
     * Multiplies the components of this matrix by the specified scalar.
     *
     * @param scalar The scalar value.
     */
    void multiply(float scalar);

    /**
     * Multiplies the components of this matrix by a scalar and stores the result in dst.
     *
     * @param scalar The scalar value.
     * @param dst A matrix to store the result in.
     */
    void multiply(float scalar, Mat4* dst) const;

    /**
     * Multiplies the components of the specified matrix by a scalar and stores the result in dst.
     *
     * @param mat The matrix.
     * @param scalar The scalar value.
     * @param dst A matrix to store the result in.
     */
    static void multiply(const Mat4& mat, float scalar, Mat4* dst);

    /**
     * Multiplies this matrix by the specified one.
     *
     * @param mat The matrix to multiply.
     */
    void multiply(const Mat4& mat);

    /**
     * Multiplies m1 by m2 and stores the result in dst.
     *
     * @param m1 The first matrix to multiply.
     * @param m2 The second matrix to multiply.
     * @param dst A matrix to store the result in.
     */
    static void multiply(const Mat4& m1, const Mat4& m2, Mat4* dst);

    /**
     * Negates this matrix.
     */
    void negate();

    /**
     * Negates this matrix and stores the result in dst.
     *
     * @param dst A matrix to store the result in.
     */
    Mat4 getNegated() const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified quaternion rotation.
     *
     * @param q The quaternion to rotate by.
     */
    void rotate(const Quaternion& q);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified quaternion rotation and stores the result in dst.
     *
     * @param q The quaternion to rotate by.
     * @param dst A matrix to store the result in.
     */
    void rotate(const Quaternion& q, Mat4* dst) const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation about the specified axis.
     *
     * @param axis The axis to rotate about.
     * @param angle The angle (in radians).
     */
    void rotate(const Vec3& axis, float angle);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the specified
     * rotation about the specified axis and stores the result in dst.
     *
     * @param axis The axis to rotate about.
     * @param angle The angle (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotate(const Vec3& axis, float angle, Mat4* dst) const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the x-axis.
     *
     * @param angle The angle (in radians).
     */
    void rotateX(float angle);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the x-axis and stores the result in dst.
     *
     * @param angle The angle (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotateX(float angle, Mat4* dst) const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the y-axis.
     *
     * @param angle The angle (in radians).
     */
    void rotateY(float angle);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the y-axis and stores the result in dst.
     *
     * @param angle The angle (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotateY(float angle, Mat4* dst) const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the z-axis.
     *
     * @param angle The angle (in radians).
     */
    void rotateZ(float angle);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified rotation around the z-axis and stores the result in dst.
     *
     * @param angle The angle (in radians).
     * @param dst A matrix to store the result in.
     */
    void rotateZ(float angle, Mat4* dst) const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation.
     *
     * @param value The amount to scale along all axes.
     */
    void scale(float value);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation and stores the result in dst.
     *
     * @param value The amount to scale along all axes.
     * @param dst A matrix to store the result in.
     */
    void scale(float value, Mat4* dst) const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation.
     *
     * @param xScale The amount to scale along the x-axis.
     * @param yScale The amount to scale along the y-axis.
     * @param zScale The amount to scale along the z-axis.
     */
    void scale(float xScale, float yScale, float zScale);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation and stores the result in dst.
     *
     * @param xScale The amount to scale along the x-axis.
     * @param yScale The amount to scale along the y-axis.
     * @param zScale The amount to scale along the z-axis.
     * @param dst A matrix to store the result in.
     */
    void scale(float xScale, float yScale, float zScale, Mat4* dst) const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation.
     *
     * @param s The scale values along the x, y and z axes.
     */
    void scale(const Vec3& s);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified scale transformation and stores the result in dst.
     *
     * @param s The scale values along the x, y and z axes.
     * @param dst A matrix to store the result in.
     */
    void scale(const Vec3& s, Mat4* dst) const;

    /**
     * Sets the values of this matrix.
     *
     * @param m11 The first element of the first row.
     * @param m12 The second element of the first row.
     * @param m13 The third element of the first row.
     * @param m14 The fourth element of the first row.
     * @param m21 The first element of the second row.
     * @param m22 The second element of the second row.
     * @param m23 The third element of the second row.
     * @param m24 The fourth element of the second row.
     * @param m31 The first element of the third row.
     * @param m32 The second element of the third row.
     * @param m33 The third element of the third row.
     * @param m34 The fourth element of the third row.
     * @param m41 The first element of the fourth row.
     * @param m42 The second element of the fourth row.
     * @param m43 The third element of the fourth row.
     * @param m44 The fourth element of the fourth row.
     */
    void set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
             float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

    /**
     * Sets the values of this matrix to those in the specified column-major array.
     *
     * @param mat An array containing 16 elements in column-major format.
     */
    void set(const float* mat);

    /**
     * Sets the values of this matrix to those of the specified matrix.
     *
     * @param mat The source matrix.
     */
    void set(const Mat4& mat);

    /**
     * Sets this matrix to the identity matrix.
     */
    void setIdentity();

    /**
     * Sets all elements of the current matrix to zero.
     */
    void setZero();

    /**
     * Subtracts the specified matrix from the current matrix.
     *
     * @param mat The matrix to subtract.
     */
    void subtract(const Mat4& mat);

    /**
     * Subtracts the specified matrix from the current matrix.
     *
     * @param m1 The first matrix.
     * @param m2 The second matrix.
     * @param dst A matrix to store the result in.
     */
    static void subtract(const Mat4& m1, const Mat4& m2, Mat4* dst);

    /**
     * Transforms the specified point by this matrix.
     *
     * The result of the transformation is stored directly into point.
     *
     * @param point The point to transform and also a vector to hold the result in.
     */
    void transformPoint(Vec3* point) const;

    /**
     * Transforms the specified point by this matrix, and stores
     * the result in dst.
     *
     * @param point The point to transform.
     * @param dst A vector to store the transformed point in.
     */
    void transformPoint(const Vec3& point, Vec3* dst) const;

    /**
     * Transforms the specified vector by this matrix by
     * treating the fourth (w) coordinate as zero.
     *
     * The result of the transformation is stored directly into vector.
     *
     * @param vector The vector to transform and also a vector to hold the result in.
     */
    void transformVector(Vec3* vector) const;

    /**
     * Transforms the specified vector by this matrix by
     * treating the fourth (w) coordinate as zero, and stores the
     * result in dst.
     *
     * @param vector The vector to transform.
     * @param dst A vector to store the transformed vector in.
     */
    void transformVector(const Vec3& vector, Vec3* dst) const;

    /**
     * Transforms the specified vector by this matrix.
     *
     * @param x The vector x-coordinate to transform by.
     * @param y The vector y-coordinate to transform by.
     * @param z The vector z-coordinate to transform by.
     * @param w The vector w-coordinate to transform by.
     * @param dst A vector to store the transformed point in.
     */
    void transformVector(float x, float y, float z, float w, Vec3* dst) const;

    /**
     * Transforms the specified vector by this matrix.
     *
     * The result of the transformation is stored directly into vector.
     *
     * @param vector The vector to transform.
     */
    void transformVector(Vec4* vector) const;

    /**
     * Transforms the specified vector by this matrix.
     *
     * @param vector The vector to transform.
     * @param dst A vector to store the transformed point in.
     */
    void transformVector(const Vec4& vector, Vec4* dst) const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation.
     *
     * @param x The amount to translate along the x-axis.
     * @param y The amount to translate along the y-axis.
     * @param z The amount to translate along the z-axis.
     */
    void translate(float x, float y, float z);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation and stores the result in dst.
     *
     * @param x The amount to translate along the x-axis.
     * @param y The amount to translate along the y-axis.
     * @param z The amount to translate along the z-axis.
     * @param dst A matrix to store the result in.
     */
    void translate(float x, float y, float z, Mat4* dst) const;

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation.
     *
     * @param t The translation values along the x, y and z axes.
     */
    void translate(const Vec3& t);

    /**
     * Post-multiplies this matrix by the matrix corresponding to the
     * specified translation and stores the result in dst.
     *
     * @param t The translation values along the x, y and z axes.
     * @param dst A matrix to store the result in.
     */
    void translate(const Vec3& t, Mat4* dst) const;

    /**
     * Transposes this matrix.
     */
    void transpose();

    /**
     * Transposes this matrix and stores the result in dst.
     *
     * @param dst A matrix to store the result in.
     */
    Mat4 getTransposed() const;

    /**
     * Calculates the sum of this matrix with the given matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @param mat The matrix to add.
     * @return The matrix sum.
     */
    inline const Mat4 operator+(const Mat4& mat) const;
    
    /**
     * Adds the given matrix to this matrix.
     * 
     * @param mat The matrix to add.
     * @return This matrix, after the addition occurs.
     */
    inline Mat4& operator+=(const Mat4& mat);

    /**
     * Calculates the difference of this matrix with the given matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @param mat The matrix to subtract.
     * @return The matrix difference.
     */
    inline const Mat4 operator-(const Mat4& mat) const;

    /**
     * Subtracts the given matrix from this matrix.
     * 
     * @param mat The matrix to subtract.
     * @return This matrix, after the subtraction occurs.
     */
    inline Mat4& operator-=(const Mat4& mat);

    /**
     * Calculates the negation of this matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @return The negation of this matrix.
     */
    inline const Mat4 operator-() const;

    /**
     * Calculates the matrix product of this matrix with the given matrix.
     * 
     * Note: this does not modify this matrix.
     * 
     * @param mat The matrix to multiply by.
     * @return The matrix product.
     */
    inline const Mat4 operator*(const Mat4& mat) const;

    /**
     * Right-multiplies this matrix by the given matrix.
     * 
     * @param mat The matrix to multiply by.
     * @return This matrix, after the multiplication occurs.
     */
    inline Mat4& operator*=(const Mat4& mat);

    /** equals to a matrix full of zeros */
    static const Mat4 ZERO;
    /** equals to the identity matrix */
    static const Mat4 IDENTITY;

private:

    static void createBillboardHelper(const Vec3& objectPosition, const Vec3& cameraPosition,
                                      const Vec3& cameraUpVector, const Vec3* cameraForwardVector,
                                      Mat4* dst);
};

/**
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @param v The vector to transform.
 * @param m The matrix to transform by.
 * @return This vector, after the transformation occurs.
 */
inline Vec3& operator*=(Vec3& v, const Mat4& m);

/**
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @param m The matrix to transform by.
 * @param v The vector to transform.
 * @return The resulting transformed vector.
 */
inline const Vec3 operator*(const Mat4& m, const Vec3& v);

/**
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @param v The vector to transform.
 * @param m The matrix to transform by.
 * @return This vector, after the transformation occurs.
 */
inline Vec4& operator*=(Vec4& v, const Mat4& m);

/**
 * Transforms the given vector by the given matrix.
 * 
 * Note: this treats the given vector as a vector and not as a point.
 * 
 * @param m The matrix to transform by.
 * @param v The vector to transform.
 * @return The resulting transformed vector.
 */
inline const Vec4 operator*(const Mat4& m, const Vec4& v);

NS_CC_MATH_END

#include "Matrix.inl"

#endif // MATH_MAT4_H
