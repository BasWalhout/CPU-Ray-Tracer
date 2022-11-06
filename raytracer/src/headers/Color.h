#pragma once
#include "../../../MathLibrary/MathLibrary.h"

enum ColorType{

	BLACK,
	WHITE,
	RED,
	GREEN,
	BLUE,
	GOLD,
	SILVER,
	SKY

};

class Color {

public:

	Color();
	Color(float r, float g, float b);
	Color(const Color& a_color);
	Color(ColorType a_color);

	Color& operator=(const Color& a_rhs);

	Color& operator+=(const Color& a_rhs);
	Color& operator-=(const Color& a_rhs);
	Color& operator*=(float a_rhs);
	Color& operator/=(float a_rhs);

	float GetComponentR() const;
	float GetComponentG() const;
	float GetComponentB() const;

	void SetComponentR(float a_r);
	void SetComponentG(float a_g);
	void SetComponentB(float a_b);

private:

	float Limit(float a_x);

	vec3 values;

};

Color operator+(const Color& a_lhs, const Color& a_rhs);
Color operator-(const Color& a_lhs, const Color& a_rhs);
Color operator*(const Color& a_lhs, const Color& a_rhs);
Color operator/(const Color& a_lhs, const Color& a_rhs);
Color operator*(const Color& a_lhs, float a_rhs);
Color operator*(float a_lhs, const Color& a_rhs);
Color operator/(const Color& a_lhs, float a_rhs);

bool operator==(const Color& a_lhs, const Color& a_rhs);
bool operator!=(const Color& a_lhs, const Color& a_rhs);

namespace ColorUtilities {

	static const float MINCOLORVALUE = 0.f;
	static const float MAXCOLORVALUE = 1.f;

}