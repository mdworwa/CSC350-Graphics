#include "Vector.h"
#include <cmath>

Vector2::Vector2(){
	x = 0.0;
	y = 0.0;
}

Vector2::Vector2(float pX, float pY){
	x = pX;
	y = pY;
}

Vector2::Vector2(Vector3 other){
	x = other.x;
	y = other.y;
}

Vector2 Vector2::operator*(float value){
	return Vector2(x*value, y*value);
}

Vector2 Vector2::operator+(const Vector2 v){
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 v){
	return Vector2(x - v.x, y - v.y);
}

float Vector2::Magnitude(){
	float length = sqrt((x*x) + (y*y));
	return length;
}

float Vector2::Dot(Vector2 v){
	float product = (x * v.x) + (y * v.y);
	return product;
}

Vector2 Vector2::Normalize(){
	Vector2 v1(x, y);
	float mag = Magnitude();
	return v1*(1 / mag);
}

Vector2 Vector2::Perpendicular(){
	return Vector2(-y, x);
}

float Determinant(Vector2 a, Vector2 b){
	float deter = (b.x * a.y) - (a.x * b.y);
	return deter;
}
//================================================================================
Vector3::Vector3(){
	x = 0.0;
	y = 0.0;
	w = 0.0;
}

Vector3::Vector3(float pX, float pY, float pW){
	x = pX;
	y = pY;
	w = pW;
}

Vector3 Vector3::operator*(float scalar){
	return Vector3(x * scalar, y * scalar, w * scalar);
}

Vector3 Vector3::operator+(Vector3 other){
	return Vector3(x + other.x, y + other.y, w + other.w);
}

Vector3 Vector3::operator-(Vector3 other){
	return Vector3(x - other.x, y - other.y, w - other.w);
}

float Vector3::Magnitude(){
	return sqrt((x*x) + (y*y) + (w * w));
}

float Vector3::Dot(Vector3 other){
	return (x*other.x) + (y*other.y) + (w*other.w);
}

Vector3 Vector3::Normalize(){
	float mag = Magnitude();
	return Vector3(x / mag, y / mag, w / mag);
}
//================================================================================
Vector4::Vector4(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;
}

Vector4::Vector4(float pX, float pY, float pZ, float pW){
	x = pX;
	y = pY;
	z = pZ;
	w = pW;
}

Vector4 Vector4::operator*(float value){
	return Vector4(x*value, y*value, z*value, w*value);
}

Vector4 Vector4::operator+(const Vector4 v){
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator-(const Vector4 v){
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

float Vector4::Magnitude(){
	float length = sqrt((x*x) + (y*y) + (z*z));
	return length;
}

float Vector4::Dot(Vector4 vector){
	float product = (x * vector.x) + (y * vector.y) + (z * vector.z) + (w * vector.w);
	return product;
}

Vector4 Vector4::Normalize(){
	float mag = Magnitude();
	return Vector4(x / mag, y / mag, z / mag, w / mag);
}

Vector4 Vector4::Cross(Vector4 b){
	return Vector4(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x, 0.0);
}