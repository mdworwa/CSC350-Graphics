#include <iostream>
using namespace std;
#include "Color.h"
#include "Model.h"
#include "Raster.h"
#include "Triangle.h"
#include "Vector.h"

#define WIDTH 100
#define HEIGHT 100


int main(int argc, const char * argv[]) {
	Raster myRaster(WIDTH, HEIGHT, White);
	
	Model teapot, bunny;
	teapot.ReadFromOBJFile("./teapot.obj", Red);
	bunny.ReadFromOBJFile("./bunny.obj", Blue);

	//Tests
	/*
	Matrix4 modelMatrixTeapot = Translate3D(50, 50, -40)*RotateZ3D(45.0)*Scale3D(0.5, 0.5, 0.5); //regular code
	Matrix4 modelMatrixTeapot = Translate3D(50, 50, -90)*RotateZ3D(45.0)*Scale3D(0.5, 0.5, 0.5); //scenario 1
	Matrix4 modelMatrixTeapot = Translate3D(50, 50, -20)*RotateZ3D(45.0)*Scale3D(0.5, 0.5, 0.5); //scenario 2
	Matrix4 viewMatrix = LookAt(Vector4(50, -20, -40, 1), Vector4(50, 50, -40, 1), Vector4(0, 0, -1, 0)); //scenario 3
	Matrix4 perspectiveMatrix = Perspective(70.0, myRaster.GetWidth() / myRaster.GetHeight(), 0.01, 1000.0); //scenario 4
	//Matrix4 viewportMatrix = Viewport(40.0, 20.0, 50, 50); //scenario 5
	//Matrix4 modelMatrixTeapot = Translate3D(50, 50, -60)*RotateZ3D(45.0)*Scale3D(0.5, 0.5, 0.5); //depth test
	*/

	//Matrix4 modelMatrixTeapot = Translate3D(50, 50, -40)*RotateZ3D(45.0)*Scale3D(0.5, 0.5, 0.5); //regular code
	//Matrix4 modelMatrixTeapot = Translate3D(50, 50, -60)*RotateZ3D(45.0)*Scale3D(0.5, 0.5, 0.5); //depth test
	Matrix4 modelMatrixTeapot = Translate3D(50, 50, -30)*RotateZ3D(45.0)*Scale3D(0.5, 0.5, 0.5);
	Vector4 eye(50, 50, 30, 1);
	Vector4 spot(50, 50, -30, 1);
	teapot.PerformBackfaceCulling(eye, spot);

	//Matrix4 modelMatrixBunny = Translate3D(70, 30, -60)*RotateZ3D(-20.0)*Scale3D(500, 500, 500);
	//Matrix4 viewMatrix = LookAt(Vector4(50, 50, 30, 1), Vector4(50, 50, -40, 1), Vector4(0, 1, 0, 0));
	Matrix4 viewMatrix = LookAt(eye, spot, Vector4(0, 1, 0, 0));
	Matrix4 perspectiveMatrix = Perspective(70.0, myRaster.GetWidth() / myRaster.GetHeight(), 0.01, 88.5);
	//Matrix4 perspectiveMatrix = Perspective(90.0, myRaster.GetWidth() / myRaster.GetHeight(), 0.01, 1000.0); 
	Matrix4 viewportMatrix = Viewport(0.0, 0.0, myRaster.GetWidth(), myRaster.GetHeight());

	teapot.Transform(perspectiveMatrix*viewMatrix*modelMatrixTeapot);
	//bunny.Transform(perspectiveMatrix*viewMatrix*modelMatrixBunny);

	teapot.Homogenize();
	//bunny.Homogenize();

	teapot.Transform(viewportMatrix);
	//bunny.Transform(viewportMatrix);

	myRaster.DrawModel(teapot);
	//myRaster.DrawModel(bunny);
	//myRaster.DrawModel(teapot); //when changing order


	myRaster.WriteToPPM();

	return 0;
}