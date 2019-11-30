#include "Color.h"
#include <cmath>


Color::Color() {
	red = 0.0;
	green = 0.0;
	blue = 0.0;
	alpha = 0.0;
}

Color::Color(float pRed, float pGreen, float pBlue, float pAlpha){
	red = pRed;
	green = pGreen;
	blue = pBlue;
	alpha = pAlpha;
	Clamp();
}

void Color::Clamp(){
	red = fmax(float(0.0), fmin(red, float(1.0)));
	green = fmax(float(0.0), fmin(green, float(1.0)));
	blue = fmax(float(0.0), fmin(blue, float(1.0)));
	alpha = fmax(float(0.0), fmin(alpha, float(1.0)));
}

Color Color::operator+(const Color c){
	Color c1(red, green, blue, alpha);
	c1.red += c.red;
	c1.green += c.green;
	c1.blue += c.blue;
	c1.alpha += c.alpha;
	c1.Clamp();
	return c1;
}


Color Color::operator-(const Color c){
	Color c1(red, green, blue, alpha);
	c1.red -= c.red;
	c1.green -= c.green;
	c1.blue -= c.blue;
	c1.alpha -= -c.alpha;
	c1.Clamp();
	return c1;
}

Color Color::operator*(float value){
	Color c1(red, green, blue, alpha);
	c1.red *= value;
	c1.green *= value;
	c1.blue *= value;
	c1.alpha *= value;
	c1.Clamp();
	return c1;
}
Color Color::operator/(float scalar){
	Color newColor(red, green, blue, alpha);
	newColor.red /= scalar;
	newColor.green /= scalar;
	newColor.blue /= scalar;
	newColor.alpha /= scalar;
	newColor.Clamp(); 
	return newColor;
}
Color Color::operator*(Color c){
	Color newColor(red, green, blue, alpha);
	newColor.red *= c.red;
	newColor.green *= c.green;
	newColor.blue *= c.blue;
	newColor.alpha *= c.alpha;
	newColor.Clamp(); // Ensure channel intensities are valid
	return newColor;
}
//-----------------------------------------------------
void Color::GetIntegerChannels(int* pRed, int* pGreen, int* pBlue, int* pAlpha){
	*pRed = red * 255;
	*pGreen = green * 255;
	*pBlue = blue * 255;
	*pAlpha = alpha * 255;
}




