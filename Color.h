#ifndef Color_h
#define Color_h

#define Red Color(1.0, 0.0, 0.0, 1.0)
#define Green Color(0.0, 1.0, 0.0, 1.0)
#define Blue Color(0.0, 0.0, 1.0, 1.0)
#define Black Color(0.0, 0.0, 0.0, 1.0)
#define White Color(1.0, 1.0, 1.0, 1.0)
#define Clear Color(0.0, 0.0, 0.0, 0.0)

#include <stdio.h>

struct Color {
	float red;
	float green;
	float blue;
	float alpha;

	Color();
	Color(float pRed, float pGreen, float pBlue, float pAlpha);
	void Clamp();
	Color operator+(const Color);
	Color operator-(const Color);
	Color operator*(float value);
	Color operator/(float scalar);
	Color operator*(Color c);
	void GetIntegerChannels(int* pRed, int* pGreen, int* pBlue, int* pAlpha);
};

#endif
