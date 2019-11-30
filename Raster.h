#ifndef Raster_h
#define Raster_h
#include "Color.h"
#include "Triangle.h"
#include "Model.h"


class Raster {
private:
	int width;
	int height;
	Color* pixels;
	float* depthPixels;
public:
	Raster();
	Raster(int pWidth, int pHeight, Color pFillColor);
	~Raster();
	int GetWidth();
	int GetHeight();
	Color GetColorPixel(int x, int y);
	float GetDepthPixel(int x, int y);
	void SetColorPixel(int x, int y, Color pFillColor);
	void SetDepthPixel(int x, int y, float depth);
	void clear(Color pFillColor);
	void clear(float depth);
	void WriteToPPM();
	void DrawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor);
	void DrawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1, Color color2);
	void DrawTriangle2D_DotProduct(Triangle2D triangle);
	void DrawTriangle3D_Barycentric(Triangle3D T);
	void DrawModel(Model m);
};

#endif