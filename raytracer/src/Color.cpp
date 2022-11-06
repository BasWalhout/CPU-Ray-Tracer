#include "headers/Color.h"

Color::Color() {

	this->values = vec3();

}

Color::Color(float r, float g, float b)
{

	this->values = vec3(r, g, b);

}

Color::Color(const Color& a_color) {

	this->values = a_color.values;

}

Color::Color(ColorType a_color) {

	float MAX_UINT8 = 255.f;

	switch (a_color)
	{
	case BLACK:
		this->values = vec3();
		break;
	case WHITE:
		this->values = vec3(1.f, 1.f, 1.f);
		break;
	case RED:
		this->values = vec3(1.f, 0.f, 0.f);
		break;
	case GREEN:
		this->values = vec3(0.f, 1.f, 0.f);
		break;
	case BLUE:
		this->values = vec3(0.f, 0.f, 1.f);
		break;
	case GOLD:
		this->values = vec3(255.f / MAX_UINT8, 215.f / MAX_UINT8, 0.f);
		break;
	case SILVER:
		this->values = vec3(192.f / MAX_UINT8, 192.f / MAX_UINT8, 192.f / MAX_UINT8);
		break;
	case SKY:
		this->values = vec3(101.f / MAX_UINT8, 197.f / MAX_UINT8, 255.f / MAX_UINT8);
	default:
		this->values = vec3();
		break;
	}

}

float Color::GetComponentR() const{

	return this->values.m_X;

}

float Color::GetComponentG() const {

	return this->values.m_Y;

}

float Color::GetComponentB() const {

	return this->values.m_Z;

}

void Color::SetComponentR(float a_r) {

	this->values.m_X = this->Limit(a_r);

}

void Color::SetComponentG(float a_g) {

	this->values.m_Y = this->Limit(a_g);

}

void Color::SetComponentB(float a_b) {

	this->values.m_Z = this->Limit(a_b);

}

float Color::Limit(float a_x) {

	return MathUtilities::Clampf(a_x, ColorUtilities::MINCOLORVALUE, ColorUtilities::MAXCOLORVALUE);

}

Color& Color::operator=(const Color& a_rhs) {

	this->values = a_rhs.values;

	return *this;

}

Color& Color::operator+=(const Color& a_rhs) {

	this->values.m_X = this->Limit(this->values.m_X + a_rhs.values.m_X);
	this->values.m_Y = this->Limit(this->values.m_Y + a_rhs.values.m_Y);
	this->values.m_Z = this->Limit(this->values.m_Z + a_rhs.values.m_Z);
	
	return *this;

}

Color& Color::operator-=(const Color& a_rhs) {

	this->values.m_X += this->Limit(this->values.m_X - a_rhs.values.m_X);
	this->values.m_Y += this->Limit(this->values.m_Y - a_rhs.values.m_Y);
	this->values.m_Z += this->Limit(this->values.m_Z - a_rhs.values.m_Z);

	return *this;

}

Color& Color::operator*=(float a_rhs) {

	this->values.m_X = this->Limit(this->values.m_X * a_rhs);
	this->values.m_Y = this->Limit(this->values.m_Y * a_rhs);
	this->values.m_Z = this->Limit(this->values.m_Z * a_rhs);

	return *this;

}

Color& Color::operator/=(float a_rhs) {

	this->values.m_X = this->Limit(this->values.m_X / a_rhs);
	this->values.m_Y = this->Limit(this->values.m_Y / a_rhs);
	this->values.m_Z = this->Limit(this->values.m_Z / a_rhs);

	return *this;

}

Color operator+(const Color& a_lhs, const Color& a_rhs) {

	Color result = Color(a_lhs);
	result += a_rhs;

	return result;

}

Color operator-(const Color& a_lhs, const Color& a_rhs) {

	Color result = Color(a_lhs);
	result -= a_rhs;

	return result;

}

Color operator*(const Color& a_lhs, const Color& a_rhs) {

	Color result = Color(a_lhs.GetComponentR() * a_rhs.GetComponentR(), a_lhs.GetComponentG() * a_rhs.GetComponentG(), a_lhs.GetComponentB() * a_rhs.GetComponentB());

	return result;

}

Color operator/(const Color& a_lhs, const Color& a_rhs) {

	Color result = Color(a_lhs.GetComponentR() / a_rhs.GetComponentR(), a_lhs.GetComponentG() / a_rhs.GetComponentG(), a_lhs.GetComponentB() / a_rhs.GetComponentB());

	return result;

}

Color operator*(const Color& a_lhs, float a_rhs) {

	Color result = Color(a_lhs);
	result *= a_rhs;

	return result;

}

Color operator*(float a_lhs, const Color& a_rhs) {

	return a_rhs * a_lhs;

}

Color operator/(const Color& a_lhs, float a_rhs) {

	Color result = Color(a_lhs);
	result /= a_rhs;

	return result;

}

bool operator==(const Color& a_lhs, const Color& a_rhs) {

	return(	a_lhs.GetComponentR() == a_rhs.GetComponentR() &&
			a_lhs.GetComponentG() == a_rhs.GetComponentG() &&
			a_lhs.GetComponentB() == a_rhs.GetComponentB());

}

bool operator!=(const Color& a_lhs, const Color& a_rhs) {

	return (a_lhs.GetComponentR() != a_rhs.GetComponentR() ||
			a_lhs.GetComponentG() != a_rhs.GetComponentG() ||
			a_lhs.GetComponentB() != a_rhs.GetComponentB());

}