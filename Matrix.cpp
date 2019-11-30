#include "Matrix.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <iostream>
using namespace std;


Matrix4::Matrix4(){
	m11 = 1.0;
	m21 = 0.0;
	m31 = 0.0;
	m41 = 0.0;

	m12 = 0.0;
	m22 = 1.0;
	m32 = 0.0;
	m42 = 0.0;

	m13 = 0.0;
	m23 = 0.0;
	m33 = 1.0;
	m43 = 0.0;

	m14 = 0.0;
	m24 = 0.0;
	m34 = 0.0;
	m44 = 1.0;
}

Matrix4::Matrix4(float p11, float p21, float p31, float p41, float p12, float p22, float p32, float p42,
	float p13, float p23, float p33, float p43, float p14, float p24, float p34, float p44){
	m11 = p11;
	m21 = p21;
	m31 = p31;
	m41 = p41;

	m12 = p12;
	m22 = p22;
	m32 = p32;
	m42 = p42;

	m13 = p13;
	m23 = p23;
	m33 = p33;
	m43 = p43;

	m14 = p14;
	m24 = p24;
	m34 = p34;
	m44 = p44;
}

Vector4 Matrix4::operator*(const Vector4 v){
	float vx = (v.x*m11) + (v.y*m21) + (v.z*m31) + (v.w*m41);
	float vy = (v.x*m12) + (v.y*m22) + (v.z*m32) + (v.w*m42);
	float vz = (v.x*m13) + (v.y*m23) + (v.z*m33) + (v.w*m43);
	float vw = (v.x*m14) + (v.y*m24) + (v.z*m34) + (v.w*m44);

	return Vector4(vx, vy, vz, vw);
}

Matrix4 Matrix4::operator*(const Matrix4 r){
	Matrix4 n;
	
	n.m11 = (r.m11*m11) + (r.m12*m21) + (r.m13*m31) + (r.m14*m41);
	n.m12 = (r.m11*m12) + (r.m12*m22) + (r.m13*m32) + (r.m14*m42);
	n.m13 = (r.m11*m13) + (r.m12*m23) + (r.m13*m33) + (r.m14*m43);
	n.m14 = (r.m11*m14) + (r.m12*m24) + (r.m13*m34) + (r.m14*m44);

	n.m21 = (r.m21*m11) + (r.m22*m21) + (r.m23*m31) + (r.m24*m41);
	n.m22 = (r.m21*m12) + (r.m22*m22) + (r.m23*m32) + (r.m24*m42);
	n.m23 = (r.m21*m13) + (r.m22*m23) + (r.m23*m33) + (r.m24*m43);
	n.m24 = (r.m21*m14) + (r.m22*m24) + (r.m23*m34) + (r.m24*m44);

	n.m31 = (r.m31*m11) + (r.m32*m21) + (r.m33*m31) + (r.m34*m41);
	n.m32 = (r.m31*m12) + (r.m32*m22) + (r.m33*m32) + (r.m34*m42);
	n.m33 = (r.m31*m13) + (r.m32*m23) + (r.m33*m33) + (r.m34*m43);
	n.m34 = (r.m31*m14) + (r.m32*m24) + (r.m33*m34) + (r.m34*m44);

	n.m41 = (r.m41*m11) + (r.m42*m21) + (r.m43*m31) + (r.m44*m41);
	n.m42 = (r.m41*m12) + (r.m42*m22) + (r.m43*m32) + (r.m44*m42);
	n.m43 = (r.m41*m13) + (r.m42*m23) + (r.m43*m33) + (r.m44*m43);
	n.m44 = (r.m41*m14) + (r.m42*m24) + (r.m43*m34) + (r.m44*m44);

	return n;
}

Matrix4 Translate3D(float tx, float ty, float tz){
	return Matrix4(1.0, 0.0, 0.0, tx,
		0.0, 1.0, 0.0, ty,
		0.0, 0.0, 1.0, tz,
		0.0, 0.0, 0.0, 1.0);
}

Matrix4 Scale3D(float sx, float sy, float sz){
	return Matrix4(sx, 0.0, 0.0, 0.0,
		0.0, sy, 0.0, 0.0,
		0.0, 0.0, sz, 0.0,
		0.0, 0.0, 0.0, 1.0);
}

Matrix4 RotateX3D(float degrees){
	float radians = (degrees * M_PI) / 180.0;
	float cosine = cosf(radians);
	float sine = sinf(radians);
	Matrix4 xMatrix = { 1.0, 0.0, 0.0, 0.0,
		0.0, cosine, sine, 0.0,
		0.0, -sine, cosine, 0.0,
		0.0, 0.0, 0.0, 1.0 };
	return xMatrix;
}

Matrix4 RotateY3D(float degrees){
	float radians = (degrees * M_PI) / 180.0;
	float cosine = cosf(radians);
	float sine = sinf(radians);
	Matrix4 yMatrix = {cosine, 0.0, -sine, 0.0,
	0.0, 1.0, 0.0, 0.0,
	sine, 0.0, cosine, 0.0,
	0.0, 0.0, 0.0, 1.0};
	return yMatrix;
}

Matrix4 RotateZ3D(float degrees){
	float radians = (degrees * M_PI) / 180.0;
	float cosine = cosf(radians);
	float sine = sinf(radians);
	Matrix4 zMatrix = {cosine, sine, 0.0, 0.0, 
	-sine, cosine, 0.0, 0.0, 
	0.0, 0.0, 1.0, 0.0, 
	0.0, 0.0, 0.0, 1.0};
	return zMatrix;
}

Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ){
	Matrix4 compMatrix = RotateX3D(degreesX) * RotateY3D(degreesY) * RotateZ3D(degreesZ);
	return compMatrix;
}

Matrix4 Rotate3D(float degrees, Vector4 vec){
	float alpha = atanf(vec.x / vec.z);
	float beta = acosf(vec.y / vec.Magnitude());
	Matrix4 rotMatrix = RotateY3D(-alpha)*RotateX3D(-beta)*RotateY3D(degrees)*RotateX3D(beta)*RotateY3D(alpha);
	return rotMatrix;
}

//===================================================================================================
void Matrix4::print(){
	cout << "4x4 Matrix values" << endl;

	cout << m11 << ", " << m21 << ", " << m31 << ", " << m41 << endl;
	cout << m12 << ", " << m22 << ", " << m32 << ", " << m42 << endl;
	cout << m13 << ", " << m23 << ", " << m33 << ", " << m43 << endl;
	cout << m14 << ", " << m24 << ", " << m34 << ", " << m44 << endl;
}

//===================================================================================================
Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up){
	Vector4 look = spot - eye;
	look = look.Normalize();
	Vector4 right = look.Cross(up);
	right = right.Normalize();
	up = right.Cross(look);
	up = up.Normalize();
	
	Matrix4 m = {right.x, right.y, right.z, 0.0,
	up.x, up.y, up.z, 0.0,
	-look.x, -look.y, -look.z, 0.0,
	0.0, 0.0, 0.0, 1.0};
	
	Matrix4 m1 = m*Translate3D(-eye.x, -eye.y, -eye.z);
	return m1;
}

Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ){
	Matrix4 m = Scale3D(2 / (maxX - minX), 2 / (maxY - minY), 2 / (maxZ - minZ))*Translate3D(-((minX+maxX)/2), -((minY+maxY)/2), -((minZ+maxZ)/2));
	return m;
}

Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ){
	float radians = ((fovY/2) * M_PI) / 180.0;
	float f = 1 / tan(radians);

	Matrix4 m = {f/(aspect), 0.0, 0.0, 0.0, 
	0.0, f, 0.0, 0.0,
	0.0, 0.0, (farZ + nearZ) / (nearZ - farZ), (2 * nearZ*farZ) / (nearZ - farZ),
	0.0, 0.0, -1.0, 0.0};

	return m;
}

Matrix4 Viewport(float x, float y, float width, float height){
	Matrix4 m = Translate3D(x, y, 0.0) * Scale3D(width, height, 1.0) * Scale3D(0.5, 0.5, 0.5) * Translate3D(1.0, 1.0, -1.0);
	return m;
}