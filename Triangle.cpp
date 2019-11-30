#include "Triangle.h"
#include <cmath>
#include <iostream>
using namespace std;

#include "Triangle.h"
#include <math.h>


Triangle2D::Triangle2D(){
	v0 = Vector3(0.0, 0.0, 1.0);
	v1 = Vector3(0.0, 0.0, 1.0);
	v2 = Vector3(0.0, 0.0, 1.0);
	c0 = Clear;
	c1 = Clear;
	c2 = Clear;
}

Triangle2D::Triangle2D(Vector3 vec0, Vector3 vec1, Vector3 vec2, Color col0, Color col1, Color col2){
	v0 = vec0;
	v1 = vec1;
	v2 = vec2;
	c0 = col0;
	c1 = col1;
	c2 = col2;
}

void Triangle2D::CalculateBarycentricCoordinates(Vector2 P, float &lambda1, float &lambda2, float &lambda3){
	float areaFull = Determinant(v1 - v2, v0 - v2);
	float area0 = Determinant(v1 - v2, P - v2);
	float area1 = Determinant(P - v2, v0 - v2);

	lambda1 = area0 / areaFull;
	lambda2 = area1 / areaFull;
	lambda3 = 1.0 - (lambda1 + lambda2);
}

//==================================================================================
Triangle3D::Triangle3D(){
	shouldDraw = true;
	v0 = Vector4(0.0, 0.0, 0.0, 1.0);
	v1 = Vector4(0.0, 0.0, 0.0, 1.0);
	v2 = Vector4(0.0, 0.0, 0.0, 1.0);
	c0 = Clear;
	c1 = Clear;
	c2 = Clear;
}

Triangle3D::Triangle3D(Vector4 pV0, Vector4 pV1, Vector4 pV2, Color pC0, Color pC1, Color pC2){
	shouldDraw = true;
	v0 = pV0;
	v1 = pV1;
	v2 = pV2;
	c0 = pC0;
	c1 = pC1;
	c2 = pC2;
}

void Triangle3D::Transform(Matrix4 matrix){
	v0 = matrix*v0;
	v1 = matrix*v1;
	v2 = matrix*v2;
}

//==================================================================================
Triangle2D::Triangle2D(Triangle3D t){
	v0 = Vector3(t.v0.x, t.v0.y, 1);
	v1 = Vector3(t.v1.x, t.v1.y, 1);
	v2 = Vector3(t.v2.x, t.v2.y, 1);
	c0 = t.c0;
	c1 = t.c1;
	c2 = t.c2;
}
