#ifndef Vector_h
#define Vector_h

#include <stdio.h>

struct Vector3;

struct Vector2 {
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);
	Vector2 operator*(float value);
	Vector2 operator+(const Vector2);
	Vector2 operator-(const Vector2);
	float Magnitude();
	float Dot(Vector2 vector);
	Vector2 Normalize();
	Vector2 Perpendicular();
	Vector2(Vector3 other);
};

float Determinant(Vector2 a, Vector2 b);

struct Vector3{
	float x;
	float y;
	float w; // Homogeneous coordinate

	Vector3();
	Vector3(float pX, float pY, float pW);
	Vector3 operator*(float scalar);
	Vector3 operator+(Vector3 other);
	Vector3 operator-(Vector3 other);
	float Magnitude();
	float Dot(Vector3 other);
	Vector3 Normalize();

};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;

	Vector4();
	Vector4(float pX, float pY, float pZ, float pW);
	Vector4 operator*(float value);
	Vector4 operator+(Vector4 other);
	Vector4 operator-(Vector4 other);
	float Magnitude();
	float Dot(Vector4 vector);
	Vector4 Normalize();
	Vector4 Cross(Vector4 b);
};

#endif
