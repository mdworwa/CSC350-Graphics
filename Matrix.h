#ifndef Matrix_h
#define Matrix_h

#include <stdio.h>
#include "Vector.h"

struct Matrix4 {
	float m11, m21, m31, m41;
	float m12, m22, m32, m42;
	float m13, m23, m33, m43;
	float m14, m24, m34, m44;

	Matrix4();
	Matrix4(float p11, float p21, float p31, float p41,
		float p12, float p22, float p32, float p42,
		float p13, float p23, float p33, float p43,
		float p14, float p24, float p34, float p44);
	Vector4 operator*(const Vector4);
	Matrix4 operator*(const Matrix4);
	void print();
};

Matrix4 Translate3D(float tX, float tY, float tZ);
Matrix4 Scale3D(float sX, float sY, float sZ);
Matrix4 RotateX3D(float degrees);
Matrix4 RotateY3D(float degrees);
Matrix4 RotateZ3D(float degrees);
Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ);
Matrix4 Rotate3D(float degrees, Vector4 vec);
Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up);
Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ);
Matrix4 Viewport(float x, float y, float width, float height);

#endif
