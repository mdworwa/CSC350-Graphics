#include "Model.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
using namespace std;


Model::Model(){
	triangles = vector<Triangle3D>();
}

int Model::NumTriangles(){
	return triangles.size();
}

Triangle3D Model::operator[ ](int i){
	return triangles[i];
}

void Model::Transform(Matrix4 m){
	for (int i = 0; i < NumTriangles(); i++){
		if (triangles[i].shouldDraw == true)
			triangles[i].Transform(m);
	}
}

void Model::ReadFromOBJFile(string filepath, Color pFillColor){
	ifstream ifile(filepath);
	string line;
	vector<string> words;
	vector<Vector4> vertices;
	vector<Triangle3D> vectriangles;

	if (ifile.is_open())
	{
		while (getline(ifile, line)){

			istringstream s(line);

			std::string sub;
			while (s >> sub){
				words.push_back(sub);
			}
			if (words.size() > 0){
				if (words[0] == "v"){
					// Vertex
					vertices.push_back(Vector4(atof(words[1].c_str()), atof(words[2].c_str()), atof(words[3].c_str()), 1.0));
				}
				else if (words[0] == "f"){
					// Face
					triangles.push_back(Triangle3D(vertices[atoi(words[1].c_str()) - 1], vertices[atoi(words[2].c_str()) - 1], vertices[atoi(words[3].c_str()) - 1], pFillColor, pFillColor, pFillColor));
				}
				words.clear();
			}
		}
	}
	ifile.close();
}

void Model::Homogenize(){
	for (int i = 0; i < NumTriangles(); i++){
		triangles[i].v0.x /= triangles[i].v0.w;
		triangles[i].v0.y /= triangles[i].v0.w;
		triangles[i].v0.z /= triangles[i].v0.w;
		triangles[i].v0.w /= triangles[i].v0.w;

		triangles[i].v1.x /= triangles[i].v1.w;
		triangles[i].v1.y /= triangles[i].v1.w;
		triangles[i].v1.z /= triangles[i].v1.w;
		triangles[i].v1.w /= triangles[i].v1.w;

		triangles[i].v2.x /= triangles[i].v2.w;
		triangles[i].v2.y /= triangles[i].v2.w;
		triangles[i].v2.z /= triangles[i].v2.w;
		triangles[i].v2.w /= triangles[i].v2.w;
	}
}
void Model::PerformBackfaceCulling(Vector4 eye, Vector4 spot){
	Vector4 view = spot - eye;
	for (int i = 0; i < NumTriangles(); i++){
		Vector4 a = triangles[i].v0 - triangles[i].v1;
		Vector4 b = triangles[i].v2 - triangles[i].v1;
		Vector4 normal = a.Cross(b);
		if (normal.Dot(view) > 0.0){
			triangles[i].c0 = White; // Blue;
			triangles[i].c1 = White; // Blue;
			triangles[i].c2 = White; // Blue;
		}
	}
}