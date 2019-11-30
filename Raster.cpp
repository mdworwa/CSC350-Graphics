#include "Raster.h"
#include "Color.h"
#include <stdio.h>
#include <cmath>
#include <fstream>
#include "Vector.h"
#include "Triangle.h"
#include <iostream>
#include <limits>
using namespace std;


Raster::Raster(){
	width = 0;
	height = 0;
	pixels = nullptr;
	depthPixels = nullptr;
}

Raster::Raster(int pWidth, int pHeight, Color pFillColor){
	width = pWidth;
	height = pHeight;
	int totalPixels = width*height;
	float max = numeric_limits<float>::max();
	pixels = new Color[totalPixels];
	depthPixels = new float[totalPixels];
	for (int i = 0; i < totalPixels; i++){
		pixels[i] = pFillColor;
		depthPixels[i] = max;
	}
}

Raster::~Raster(){
	delete[] pixels;
	delete[] depthPixels;
}

int Raster::GetWidth(){
	return width;
}

int Raster::GetHeight(){
	return height;
}

Color Raster::GetColorPixel(int x, int y){
	int totalPixels = width*height;
	int r = (height - 1) - y;
	int index = (r * width) + x;
	if (index >= 0 && index < totalPixels){
		return pixels[index];
	}
	else
		return Clear;
}

float Raster::GetDepthPixel(int x, int y){
	int r = (height - 1) - y;
	int index = (r*width) + x;
	return depthPixels[index];
}

void Raster::SetColorPixel(int x, int y, Color pFillColor){
	int totalPixels = width*height;
	int r = (height - 1) - y;
	int index = (r * width) + x;
	if (index >= 0 && index < totalPixels){
		pixels[index] = pFillColor;
	}
}

void Raster::SetDepthPixel(int x, int y, float depth){
	int totalDepth = width*height;
	int r = (height - 1) - y;
	int index = (r * width) + x;
	if (index >= 0 && index < totalDepth){
		depthPixels[index] = depth;
	}
}


void Raster::clear(Color pFillColor){
	int totalPixels = width*height;
	for (int i = 0; i < totalPixels; i++){
		pixels[i] = pFillColor;
	}
}

void Raster::clear(float depth){
	int totalDepth = width*height;
	for (int i = 0; i < totalDepth; i++){
		depthPixels[i] = depth;
	}
}

void Raster::WriteToPPM(){
	ofstream ppmFile;
	ppmFile.open("FRAME_BUFFER.ppm");
	ppmFile << "P3" << endl;
	ppmFile << GetWidth() << ' ' << GetHeight() << endl;
	ppmFile << 255 << endl;

	for (int row = 0; row < height; row++){
		for (int col = 0; col < width; col++){
			int r, g, b, a;
			int idx = (row * width) + col;
			pixels[idx].GetIntegerChannels(&r, &g, &b, &a);
			ppmFile << int(r) << " " << int(g) << " " << int(b) << " ";
		}
	}

	/*for (int i = 0; i < width*height; i++){
		ppmFile << (int)(pixels[i].red * 255) << " " << (int)(pixels[i].green * 255) << " " << (int)(pixels[i].blue * 255) << " ";
		}*/
	ppmFile.close();
}

void Raster::DrawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor){
	float m = (y2 - y1) / (x2 - x1);
	float m2 = (x1 - x2) / (y1 - y2);
	if (x2 == x1){ //vertical lines
		if (y2 < y1){
			swap(y2, y1);
		}
		for (int i = y1; i <= y2; i++){
			SetColorPixel(x1, i, fillColor);
		}
	}
	else if (y2 == y1){ //horizontal lines
		if (x2 < x1){
			swap(x2, x1);
		}
		for (int i = x1; i <= x2; i++){
			SetColorPixel(i, y1, fillColor);
		}
	}
	else if (m < 0 && abs(m) <= 1){ //neg. slope and less than 1 (not too steep)
		if (x2 < x1){
			swap(x2, x1);
			swap(y2, y1);
		}
		float y = y1;
		for (int x = x1; x <= x2; x++){
			SetColorPixel(x, y, fillColor);
			y += m;
		}
	}
	else if (m>0 && abs(m) <= 1){ //pos. slope and less than 1 (not too steep)
		if (x2 < x1){
			swap(x2, x1);
			swap(y2, y1);
		}
		float y = y1;
		for (int x = x1; x <= x2; x++){
			SetColorPixel(x, y, fillColor);
			y += m;
		}
	}
	else if (m<0 && abs(m)>1){ //neg. slope and more than 1 (steep)
		if (x2 < x1){
			swap(x1, x2);
			swap(y1, y2);
		}
		float x = x1;
		for (int y = y1; y >= y2; y--){
			SetColorPixel(x, y, fillColor);
			x -= m2;
		}
	}
	else if (m > 0 && abs(m) > 1){ //pos. slope and more than 1 (steep)
		if (x2 < x1){
			swap(x1, x2);
			swap(y1, y2);
		}
		float x = x2;
		for (int y = y2; y >= y1; y--){
			SetColorPixel(x, y, fillColor);
			x -= m2;
		}
	}
}

void Raster::DrawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1, Color color2){
	float m = (y2 - y1) / (x2 - x1);
	float m2 = (x1 - x2) / (y1 - y2);
	Vector2 v1;
	Vector2 v2;
	Vector2 p;
	float fullLength = 0.0;
	float length = 0.0;
	float ratio = 0.0;
	Color fillColor;
	if (x2 == x1){ //vertical lines
		if (y2 < y1){
			swap(y2, y1);
		}
		v1 = Vector2(x1, y1);
		v2 = Vector2(x2, y2);
		fullLength = (v2 - v1).Magnitude();
		for (int i = y1; i <= y2; i++){
			p = Vector2(x1, i);
			length = (p - v1).Magnitude();
			ratio = length / fullLength;
			fillColor = (color2*ratio) + (color1*(1 - ratio));
			SetColorPixel(x1, i, fillColor);
		}
	}
	else if (y2 == y1){ //horizontal lines
		if (x2 < x1){
			swap(x2, x1);
		}
		v1 = Vector2(x1, y1);
		v2 = Vector2(x2, y2);
		fullLength = (v2 - v1).Magnitude();
		for (int i = x1; i <= x2; i++){
			p = Vector2(i, y1);
			length = (p - v1).Magnitude();
			ratio = length / fullLength;
			fillColor = (color2 * ratio) + (color1 * (1 - ratio));
			SetColorPixel(i, y1, fillColor);
		}
	}
	else if (m < 0 && abs(m) <= 1){ //neg. slope and less than 1 (not too steep)
		if (x2 < x1){
			swap(x2, x1);
			swap(y2, y1);
		}
		v1 = Vector2(x1, y1);
		v2 = Vector2(x2, y2);
		fullLength = (v2 - v1).Magnitude();
		float y = y1;
		for (int x = x1; x <= x2; x++){
			p = Vector2(x, round(y));
			length = (p - v1).Magnitude();
			ratio = length / fullLength;
			fillColor = (color2 * ratio) + (color1 * (1 - ratio));
			SetColorPixel(x, round(y), fillColor);
			y += m;
		}
	}
	else if (m > 0 && abs(m) <= 1){ //pos. slope and less than 1 (not too steep)
		if (x2 < x1){
			swap(x2, x1);
			swap(y2, y1);
		}
		float y = y1;
		v1 = Vector2(x1, y1);
		v2 = Vector2(x2, y2);
		fullLength = (v2 - v1).Magnitude();
		for (int x = x1; x <= x2; x++){
			p = Vector2(x, y);
			length = (p - v1).Magnitude();
			ratio = length / fullLength;
			fillColor = (color2 * ratio) + (color1 * (1 - ratio));
			SetColorPixel(x, y, fillColor);
			y += m;
		}
	}
	else if (m<0 && abs(m)>1){ //neg. slope and more than 1 (steep)
		if (x2 < x1){
			swap(x1, x2);
			swap(y1, y2);
		}
		float x = x1;
		v1 = Vector2(x1, y1);
		v2 = Vector2(x2, y2);
		fullLength = (v2 - v1).Magnitude();
		for (int y = y1; y >= y2; y--){
			p = Vector2(x, y);
			length = (p - v1).Magnitude();
			ratio = length / fullLength;
			fillColor = (color2 * ratio) + (color1 * (1 - ratio));
			SetColorPixel(x, y, fillColor);
			x -= m2;
		}
	}
	else if (m > 0 && abs(m) > 1){ //pos. slope and more than 1 (steep)
		if (x2 < x1){
			swap(x1, x2);
			swap(y1, y2);
		}
		float x = x2;
		v1 = Vector2(x1, y1);
		v2 = Vector2(x2, y2);
		fullLength = (v2 - v1).Magnitude();
		for (int y = y2; y >= y1; y--){
			p = Vector2(x, y);
			length = (p - v1).Magnitude();
			ratio = length / fullLength;
			fillColor = (color2 * ratio) + (color1 * (1 - ratio));
			SetColorPixel(x, y, fillColor);
			x -= m2;
		}
	}
}

void Raster::DrawTriangle2D_DotProduct(Triangle2D triangle){
	Vector2 edge0 = triangle.v1 - triangle.v0;
	Vector2 perp0 = edge0.Perpendicular();

	Vector2 edge1 = triangle.v2 - triangle.v1;
	Vector2 perp1 = edge1.Perpendicular();

	Vector2 edge2 = triangle.v0 - triangle.v2;
	Vector2 perp2 = edge2.Perpendicular();

	float xMax = fmax(fmax(triangle.v0.x, triangle.v1.x), triangle.v2.x);
	float xMin = fmin(fmin(triangle.v0.x, triangle.v1.x), triangle.v2.x);
	float yMax = fmax(fmax(triangle.v0.y, triangle.v1.y), triangle.v2.y);
	float yMin = fmin(fmin(triangle.v0.y, triangle.v1.y), triangle.v2.y);

	xMax = fmin(fmax(0, xMax), width);
	xMin = fmax(fmin(width, xMin), 0);
	yMax = fmin(fmax(0, yMax), height);
	yMin = fmax(fmin(height, yMin), 0);

	for (int x = xMin; x < xMax; x++){
		for (int y = yMin; y < yMax; y++){

			Vector2 p = Vector2(x, y);

			Vector2 g0 = p - triangle.v0;
			float result0 = perp0.Dot(g0);

			Vector2 g1 = p - triangle.v1;
			float result1 = perp1.Dot(g1);

			Vector2 g2 = p - triangle.v2;
			float result2 = perp2.Dot(g2);

			if (result0 >= 0 && result1 >= 0 && result2 >= 0){
				SetColorPixel(x, y, triangle.c0);
			}
		}
	}
}

void Raster::DrawTriangle3D_Barycentric(Triangle3D T){
	if (T.shouldDraw == true){
		Triangle2D myTri(T);

		float xMax = fmax(fmax(T.v0.x, T.v1.x), T.v2.x);
		float xMin = fmin(fmin(T.v0.x, T.v1.x), T.v2.x);
		float yMax = fmax(fmax(T.v0.y, T.v1.y), T.v2.y);
		float yMin = fmin(fmin(T.v0.y, T.v1.y), T.v2.y);

		xMax = fmin(fmax(0, xMax), width);
		xMin = fmax(fmin(width, xMin), 0);
		yMax = fmin(fmax(0, yMax), height);
		yMin = fmax(fmin(height, yMin), 0);

		float lambda1 = 0.0;
		float lambda2 = 0.0;
		float lambda3 = 0.0;

		for (int x = xMin; x < xMax; x++){
			for (int y = yMin; y < yMax; y++){
				myTri.CalculateBarycentricCoordinates(Vector2(float(x) + 0.5, float(y) + 0.5), lambda1, lambda2, lambda3);
				if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0){
					if (GetDepthPixel(x, y) >((T.v0.z*(lambda1)) + (T.v1.z*(lambda2)) + (T.v2.z*(lambda3))))
					{
						SetDepthPixel(x, y, ((T.v0.z*(lambda1)) + (T.v1.z*(lambda2)) + (T.v2.z*(lambda3)))); //need to fix this part
						SetColorPixel(x, y, ((T.c0*(lambda1)) + (T.c1*(lambda2)) + (T.c2*(lambda3))));
					}
				}
			}
		}
	}
}

void Raster::DrawModel(Model m){
	for (int i = 0; i < m.NumTriangles(); i++){
		DrawTriangle3D_Barycentric(m[i]);
	}
}
