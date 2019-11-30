#ifndef Model_h
#define Model_h

#include <stdio.h>
#include "Triangle.h"
#include "Vector.h"
#include "Matrix.h"
#include "Color.h"
#include <vector>
using namespace std;

class Model
{
private:
	vector<Triangle3D> triangles;
public:
	Model();
	int NumTriangles();
	Triangle3D operator[](int i);
	void Transform(Matrix4 m);
	void ReadFromOBJFile(string filepath, Color pFillColor);
	void Homogenize();
	void PerformBackfaceCulling(Vector4 eye, Vector4 spot);
};

#endif
