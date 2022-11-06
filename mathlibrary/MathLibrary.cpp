#include "MathLibrary.h"
#include <math.h>

vec2::vec2() :
	m_X(0.f),
	m_Y(0.f)
{}

vec2::vec2(float a_X, float a_Y) :
	m_X(a_X),
	m_Y(a_Y)
{}

vec2& vec2::operator=(const vec2 &a_Rhs) {

	this->m_X = a_Rhs.m_X;
	this->m_Y = a_Rhs.m_Y;

	return *this;

}

vec2& vec2::operator+=(const vec2 &a_Rhs) {

	this->m_X += a_Rhs.m_X;
	this->m_Y += a_Rhs.m_Y;

	return *this;

}

vec2& vec2::operator-=(const vec2 &a_Rhs) {

	this->m_X -= a_Rhs.m_X;
	this->m_Y -= a_Rhs.m_Y;

	return *this;

}

vec2& vec2::operator*=(float a_Rhs) {

	this->m_X *= a_Rhs;
	this->m_Y *= a_Rhs;

	return *this;

}

vec2& vec2::operator/=(float a_Rhs) {

	this->m_X /= a_Rhs;
	this->m_Y /= a_Rhs;

	return *this;

}

float vec2::operator[](int a_Index) const { // This is a const member function. This does not change any values in the object itself.

	return v[a_Index];

}

float& vec2::operator[](int a_Index) {


	return v[a_Index];

}

vec2& vec2::normalize() {

	float length = this->length();

	this->m_X /= length;
	this->m_Y /= length;

	return *this;

}

vec2 operator+(const vec2 &a_Lhs, const vec2 &a_Rhs) {

	return vec2(a_Lhs.m_X + a_Rhs.m_X, a_Lhs.m_Y + a_Rhs.m_Y);

}

vec2 operator-(const vec2 &a_Lhs, const vec2 &a_Rhs) {

	return vec2(a_Lhs.m_X - a_Rhs.m_X, a_Lhs.m_Y - a_Rhs.m_Y);

}

vec2 operator*(const vec2 &a_Lhs, float a_Rhs) {

	return vec2(a_Lhs.m_X * a_Rhs, a_Lhs.m_Y * a_Rhs);

}

vec2 operator/(const vec2 &a_Lhs, float a_Rhs) {

	return vec2(a_Lhs.m_X / a_Rhs, a_Lhs.m_Y / a_Rhs);

}

bool operator==(const vec2 &a_Lhs, const vec2 &a_Rhs) {

	return(a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y);

}

bool operator!=(const vec2 &a_Lhs, const vec2 &a_Rhs) {

	return(a_Lhs.m_X != a_Rhs.m_X || a_Lhs.m_Y != a_Rhs.m_Y);

}



vec3::vec3() :
	m_X(0.f),
	m_Y(0.f),
	m_Z(0.f)
{}

vec3::vec3(float a_X, float a_Y, float a_Z) :
	m_X(a_X),
	m_Y(a_Y),
	m_Z(a_Z)
{}



vec3& vec3::operator=(const vec3 &a_Rhs) {

	this->m_X = a_Rhs.m_X;
	this->m_Y = a_Rhs.m_Y;
	this->m_Z = a_Rhs.m_Z;

	return *this;

}

vec3& vec3::operator+=(const vec3 &a_Rhs) {

	this->m_X += a_Rhs.m_X;
	this->m_Y += a_Rhs.m_Y;
	this->m_Z += a_Rhs.m_Z;

	return *this;

}

vec3& vec3::operator-=(const vec3 &a_Rhs) {

	this->m_X -= a_Rhs.m_X;
	this->m_Y -= a_Rhs.m_Y;
	this->m_Z -= a_Rhs.m_Z;

	return *this;

}

vec3& vec3::operator*=(float a_Rhs) {

	this->m_X *= a_Rhs;
	this->m_Y *= a_Rhs;
	this->m_Z *= a_Rhs;

	return *this;

}

vec3& vec3::operator/=(float a_Rhs) {

	this->m_X /= a_Rhs;
	this->m_Y /= a_Rhs;
	this->m_Z /= a_Rhs;

	return *this;

}

float vec3::operator[](int a_Index) const {

	return v[a_Index];

}

float& vec3::operator[](int a_Index) {

	return v[a_Index];

}

vec3& vec3::normalize() {

	float length = this->length();

	this->m_X /= length;
	this->m_Y /= length;
	this->m_Z /= length;

	return *this;

}

vec4 vec3::toVec4(bool a_point) {

	return vec4(*this, (a_point) ? 1.f : 0.f);

}

vec3 operator+(const vec3 &a_Lhs, const vec3 &a_Rhs) {

	return vec3(a_Lhs.m_X + a_Rhs.m_X, a_Lhs.m_Y + a_Rhs.m_Y, a_Lhs.m_Z + a_Rhs.m_Z);

}

vec3 operator-(const vec3 &a_Lhs, const vec3 &a_Rhs) {

	return vec3(a_Lhs.m_X - a_Rhs.m_X, a_Lhs.m_Y - a_Rhs.m_Y, a_Lhs.m_Z - a_Rhs.m_Z);

}

vec3 operator*(const vec3 &a_Lhs, float a_Rhs) {

	return vec3(a_Lhs.m_X * a_Rhs, a_Lhs.m_Y * a_Rhs, a_Lhs.m_Z * a_Rhs);


}

vec3 operator/(const vec3 &a_Lhs, float a_Rhs) {

	return vec3(a_Lhs.m_X / a_Rhs, a_Lhs.m_Y / a_Rhs, a_Lhs.m_Z / a_Rhs);

}

bool operator==(const vec3 &a_Lhs, const vec3 &a_Rhs) {

	return (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y && a_Lhs.m_Z == a_Rhs.m_Z);


}

bool operator!=(const vec3 &a_Lhs, const vec3 &a_Rhs) {

	return (a_Lhs.m_X != a_Rhs.m_X || a_Lhs.m_Y != a_Rhs.m_Y || a_Lhs.m_Z != a_Rhs.m_Z);


}

std::ostream& operator<<(std::ostream& ostream, const vec3& a_vec3) {

	ostream << a_vec3.m_X << ":" << a_vec3.m_Y << ":" << a_vec3.m_Z;

	return ostream;
}



vec4::vec4():
	m_X(0.f),
	m_Y(0.f),
	m_Z(0.f),
	m_W(0.f)
{}

vec4::vec4(float a_X, float a_Y, float a_Z, float a_W):
	m_X(a_X),
	m_Y(a_Y),
	m_Z(a_Z),
	m_W(a_W)
{}

vec4::vec4(vec3 a_vec, float a_PorV):
	m_X(a_vec.m_X),
	m_Y(a_vec.m_Y),
	m_Z(a_vec.m_Z),
	m_W(a_PorV)
{}

vec4& vec4::operator=(const vec4& a_Rhs) {

	this->m_X = a_Rhs.m_X;
	this->m_Y = a_Rhs.m_Y;
	this->m_Z = a_Rhs.m_Z;
	this->m_W = a_Rhs.m_W;

	return *this;

}

vec4& vec4::operator+=(const vec4& a_Rhs) {
	
	this->m_X += a_Rhs.m_X;
	this->m_Y += a_Rhs.m_Y;
	this->m_Z += a_Rhs.m_Z;
	this->m_W += a_Rhs.m_W;

	return *this;

}

vec4& vec4::operator-=(const vec4& a_Rhs) {

	this->m_X -= a_Rhs.m_X;
	this->m_Y -= a_Rhs.m_Y;
	this->m_Z -= a_Rhs.m_Z;
	this->m_W -= a_Rhs.m_W;

	return *this;

}

vec4& vec4::operator*=(float a_Rhs) {

	this->m_X *= a_Rhs;
	this->m_Y *= a_Rhs;
	this->m_Z *= a_Rhs;
	this->m_W *= a_Rhs;

	return *this;

}

vec4& vec4::operator/=(float a_Rhs) {

	this->m_X /= a_Rhs;
	this->m_Y /= a_Rhs;
	this->m_Z /= a_Rhs;
	this->m_W /= a_Rhs;

	return *this;

}

float vec4::operator[](int a_Index) const{

	return v[a_Index];

}

float& vec4::operator[](int a_Index) {

	return v[a_Index];

}

vec3 vec4::toVec3() {

	return vec3(m_X, m_Y, m_Z);

}

vec4 operator+(const vec4& a_Lhs, const vec4& a_Rhs) {

	return vec4(a_Lhs.m_X + a_Rhs.m_X, a_Lhs.m_Y + a_Rhs.m_Y, a_Lhs.m_Z + a_Rhs.m_Z, a_Lhs.m_W + a_Rhs.m_W);

}

vec4 operator-(const vec4& a_Lhs, const vec4& a_Rhs) {

	return vec4(a_Lhs.m_X - a_Rhs.m_X, a_Lhs.m_Y - a_Rhs.m_Y, a_Lhs.m_Z - a_Rhs.m_Z, a_Lhs.m_W - a_Rhs.m_W);

}

vec4 operator*(const vec4& a_Lhs, float a_Rhs) {

	return vec4(a_Lhs.m_X * a_Rhs, a_Lhs.m_Y * a_Rhs, a_Lhs.m_Z * a_Rhs, a_Lhs.m_W * a_Rhs);

}

vec4 operator/(const vec4& a_Lhs, float a_Rhs) {

	return vec4(a_Lhs.m_X / a_Rhs, a_Lhs.m_Y / a_Rhs, a_Lhs.m_Z / a_Rhs, a_Lhs.m_W / a_Rhs);

}

bool operator==(const vec4& a_Lhs, const vec4& a_Rhs) {

	return (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y && a_Lhs.m_Z == a_Rhs.m_Z && a_Lhs.m_W == a_Rhs.m_W);

}

bool operator!=(const vec4& a_Lhs, const vec4& a_Rhs) {

	return(a_Lhs.m_X != a_Rhs.m_X || a_Lhs.m_Y != a_Rhs.m_Y || a_Lhs.m_Z != a_Rhs.m_Z || a_Lhs.m_W != a_Rhs.m_W);

}



mat4::mat4() {

	for (int i = 0; i < 16; ++i) {
		m[i] = 0.f;

	}

}

mat4::mat4(vec3 a_Col0, float a_30,
	vec3 a_Col1, float a_31,
	vec3 a_Col2, float a_32,
	vec3 a_Col3, float a_33) :
	m_00(a_Col0.m_X), m_01(a_Col1.m_X), m_02(a_Col2.m_X), m_03(a_Col3.m_X),
	m_10(a_Col0.m_Y), m_11(a_Col1.m_Y), m_12(a_Col2.m_Y), m_13(a_Col3.m_Y),
	m_20(a_Col0.m_Z), m_21(a_Col1.m_Z), m_22(a_Col2.m_Z), m_23(a_Col3.m_Z),
	m_30(a_30), m_31(a_31), m_32(a_32), m_33(a_33)
{}

mat4::mat4(vec4 a_Col0,
	vec4 a_Col1,
	vec4 a_Col2,
	vec4 a_Col3):
	m_00(a_Col0.m_X), m_01(a_Col1.m_X), m_02(a_Col2.m_X), m_03(a_Col3.m_X),
	m_10(a_Col0.m_Y), m_11(a_Col1.m_Y), m_12(a_Col2.m_Y), m_13(a_Col3.m_Y),
	m_20(a_Col0.m_Z), m_21(a_Col1.m_Z), m_22(a_Col2.m_Z), m_23(a_Col3.m_Z),
	m_30(a_Col0.m_W), m_31(a_Col1.m_W), m_32(a_Col2.m_W), m_33(a_Col3.m_W)
{}

mat4::mat4(float a_00, float a_01, float a_02, float a_03,
	float a_10, float a_11, float a_12, float a_13,
	float a_20, float a_21, float a_22, float a_23,
	float a_30, float a_31, float a_32, float a_33) :
	m_00(a_00), m_01(a_01), m_02(a_02), m_03(a_03),
	m_10(a_10), m_11(a_11), m_12(a_12), m_13(a_13),
	m_20(a_20), m_21(a_21), m_22(a_22), m_23(a_23),
	m_30(a_30), m_31(a_31), m_32(a_32), m_33(a_33)
{}

mat4& mat4::operator=(const mat4 &a_Rhs) {

	this->m[0] = a_Rhs.m[0];
	this->m[1] = a_Rhs.m[1];
	this->m[2] = a_Rhs.m[2];
	this->m[3] = a_Rhs.m[3];
	this->m[4] = a_Rhs.m[4];
	this->m[5] = a_Rhs.m[5];
	this->m[6] = a_Rhs.m[6];
	this->m[7] = a_Rhs.m[7];
	this->m[8] = a_Rhs.m[8];
	this->m[9] = a_Rhs.m[9];
	this->m[10] = a_Rhs.m[10];
	this->m[11] = a_Rhs.m[11];
	this->m[12] = a_Rhs.m[12];
	this->m[13] = a_Rhs.m[13];
	this->m[14] = a_Rhs.m[14];
	this->m[15] = a_Rhs.m[15];

	return *this;

}

mat4& mat4::operator+=(const mat4 &a_Rhs) {

	//since this is already the same size for both row and column we do no need to check if the 2 matrices are the same size.

	for (int i = 0; i < 16; ++i) {

		this->m[i] += a_Rhs.m[i];

	}

	return *this;
}

mat4& mat4::operator-=(const mat4 &a_Rhs) {

	//since this is already the same size for both row and column we do no need to check if the 2 matrices are the same size.

	for (int i = 0; i < 16; ++i) {

		this->m[i] -= a_Rhs.m[i];

	}

	return *this;

}

mat4& mat4::operator*=(const mat4 &a_Rhs) {

	mat4 result = mat4();

	result.m_00 = this->m_00 * a_Rhs.m_00 + this->m_01 * a_Rhs.m_10 + this->m_02 * a_Rhs.m_20 + this->m_03 * a_Rhs.m_30;
	result.m_01 = this->m_00 * a_Rhs.m_01 + this->m_01 * a_Rhs.m_11 + this->m_02 * a_Rhs.m_21 + this->m_03 * a_Rhs.m_31;
	result.m_02 = this->m_00 * a_Rhs.m_02 + this->m_01 * a_Rhs.m_12 + this->m_02 * a_Rhs.m_22 + this->m_03 * a_Rhs.m_32;
	result.m_03 = this->m_00 * a_Rhs.m_03 + this->m_01 * a_Rhs.m_13 + this->m_02 * a_Rhs.m_23 + this->m_03 * a_Rhs.m_33;

	result.m_10 = this->m_10 * a_Rhs.m_00 + this->m_11 * a_Rhs.m_10 + this->m_12 * a_Rhs.m_20 + this->m_13 * a_Rhs.m_30;
	result.m_11 = this->m_10 * a_Rhs.m_01 + this->m_11 * a_Rhs.m_11 + this->m_12 * a_Rhs.m_21 + this->m_13 * a_Rhs.m_31;
	result.m_12 = this->m_10 * a_Rhs.m_02 + this->m_11 * a_Rhs.m_12 + this->m_12 * a_Rhs.m_22 + this->m_13 * a_Rhs.m_32;
	result.m_13 = this->m_10 * a_Rhs.m_03 + this->m_11 * a_Rhs.m_13 + this->m_12 * a_Rhs.m_23 + this->m_13 * a_Rhs.m_33;

	result.m_20 = this->m_20 * a_Rhs.m_00 + this->m_21 * a_Rhs.m_10 + this->m_22 * a_Rhs.m_20 + this->m_23 * a_Rhs.m_30;
	result.m_21 = this->m_20 * a_Rhs.m_01 + this->m_21 * a_Rhs.m_11 + this->m_22 * a_Rhs.m_21 + this->m_23 * a_Rhs.m_31;
	result.m_22 = this->m_20 * a_Rhs.m_02 + this->m_21 * a_Rhs.m_12 + this->m_22 * a_Rhs.m_22 + this->m_23 * a_Rhs.m_32;
	result.m_23 = this->m_20 * a_Rhs.m_03 + this->m_21 * a_Rhs.m_13 + this->m_22 * a_Rhs.m_23 + this->m_23 * a_Rhs.m_33;

	result.m_30 = this->m_30 * a_Rhs.m_00 + this->m_31 * a_Rhs.m_10 + this->m_32 * a_Rhs.m_20 + this->m_33 * a_Rhs.m_30;
	result.m_31 = this->m_30 * a_Rhs.m_01 + this->m_31 * a_Rhs.m_11 + this->m_32 * a_Rhs.m_21 + this->m_33 * a_Rhs.m_31;
	result.m_32 = this->m_30 * a_Rhs.m_02 + this->m_31 * a_Rhs.m_12 + this->m_32 * a_Rhs.m_22 + this->m_33 * a_Rhs.m_32;
	result.m_33 = this->m_30 * a_Rhs.m_03 + this->m_31 * a_Rhs.m_13 + this->m_32 * a_Rhs.m_23 + this->m_33 * a_Rhs.m_33;

	*this = result;
	return *this;

}

float mat4::determinant() const {

	return

		m_00 * (
			m_11 * (m_22 * m_33 - m_23 * m_32) +
			m_12 * (m_23 * m_31 - m_21 * m_33) +
			m_13 * (m_21 * m_32 - m_22 * m_31)) -

		m_01 * (
			m_10 * (m_22 * m_33 - m_23 * m_32) +
			m_12 * (m_23 * m_30 - m_20 * m_33) +
			m_13 * (m_20 * m_32 - m_22 * m_30)) +

		m_02 * (
			m_10 * (m_21 * m_33 - m_23 * m_31) +
			m_11 * (m_23 * m_30 - m_20 * m_33) +
			m_13 * (m_20 * m_31 - m_21 * m_30)) -

		m_03 * (
			m_10 * (m_21 * m_32 - m_22 * m_31) +
			m_11 * (m_22 * m_30 - m_20 * m_32) +
			m_12 * (m_20 * m_31 - m_21 * m_30));

}



mat4 mat4::rotateX(float a_Radians) {

	return mat4(1.f, 0.f, 0.f, 0.f,
		0.f, cosf(a_Radians), -sinf(a_Radians), 0.f,
		0.f, sinf(a_Radians), cosf(a_Radians), 0.f,
		0.f, 0.f, 0.f, 1.f);

}

mat4 mat4::rotateY(float a_Radians) {

	return mat4(cosf(a_Radians), 0.f, sinf(a_Radians), 0.f,
				0.f, 1.f, 0.f, 0.f,
				-sinf(a_Radians), 0.f, cosf(a_Radians), 0.f,
				0.f, 0.f, 0.f, 1.f);

}

mat4 mat4::rotateZ(float a_Radians) {

	return mat4(cosf(a_Radians), -sinf(a_Radians), 0.f, 0.f,
				sinf(a_Radians), cosf(a_Radians), 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f);

}

mat4 mat4::translate(const vec3 &a_Translation) {

	return mat4(1, 0, 0, a_Translation.m_X,
				0, 1, 0, a_Translation.m_Y,
				0, 0, 1, a_Translation.m_Z,
				0, 0, 0, 1);

}

mat4 mat4::scale(const vec3& a_scale) {

	return mat4(a_scale.m_X, 0, 0, 0,
				0, a_scale.m_Y, 0, 0,
				0, 0, a_scale.m_Z, 0,
				0, 0, 0, 1.f);

}

mat4 mat4::identity() {

	return mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

}

mat4 mat4::lookat(const vec3 &a_Eye, const vec3 &a_Center, const vec3 &a_Up) {

	a_Eye;
	a_Center;
	a_Up;

	return mat4();
}

mat4 mat4::projection(float a_FovY, float a_AspectRatio, float a_Near, float a_Far) {

	a_FovY = a_FovY;
	a_AspectRatio = a_AspectRatio;
	a_Near = a_Near;
	a_Far = a_Far;

	return mat4();

}

mat4 operator+(const mat4 &a_Lhs, const mat4 &a_Rhs) {

	mat4 returnMatrix = a_Lhs;

	for (int i = 0; i < 16; ++i) {

		returnMatrix.m[i] += a_Rhs.m[i];

	}

	return returnMatrix;

}

mat4 operator-(const mat4 &a_Lhs, const mat4 &a_Rhs) {

	mat4 returnMatrix = a_Lhs;

	for (int i = 0; i < 16; ++i) {

		returnMatrix.m[i] -= a_Rhs.m[i];

	}

	return returnMatrix;

}

mat4 operator*(const mat4 &a_Lhs, const mat4 &a_Rhs) {

	return mat4(
		(a_Lhs.m_00 * a_Rhs.m_00) + (a_Lhs.m_01 * a_Rhs.m_10) + (a_Lhs.m_02 * a_Rhs.m_20) + (a_Lhs.m_03 * a_Rhs.m_30),
		(a_Lhs.m_00 * a_Rhs.m_01) + (a_Lhs.m_01 * a_Rhs.m_11) + (a_Lhs.m_02 * a_Rhs.m_21) + (a_Lhs.m_03 * a_Rhs.m_31),
		(a_Lhs.m_00 * a_Rhs.m_02) + (a_Lhs.m_01 * a_Rhs.m_12) + (a_Lhs.m_02 * a_Rhs.m_22) + (a_Lhs.m_03 * a_Rhs.m_32),
		(a_Lhs.m_00 * a_Rhs.m_03) + (a_Lhs.m_01 * a_Rhs.m_13) + (a_Lhs.m_02 * a_Rhs.m_23) + (a_Lhs.m_03 * a_Rhs.m_33),

		(a_Lhs.m_10 * a_Rhs.m_00) + (a_Lhs.m_11 * a_Rhs.m_10) + (a_Lhs.m_12 * a_Rhs.m_20) + (a_Lhs.m_13 * a_Rhs.m_30),
		(a_Lhs.m_10 * a_Rhs.m_01) + (a_Lhs.m_11 * a_Rhs.m_11) + (a_Lhs.m_12 * a_Rhs.m_21) + (a_Lhs.m_13 * a_Rhs.m_31),
		(a_Lhs.m_10 * a_Rhs.m_02) + (a_Lhs.m_11 * a_Rhs.m_12) + (a_Lhs.m_12 * a_Rhs.m_22) + (a_Lhs.m_13 * a_Rhs.m_32),
		(a_Lhs.m_10 * a_Rhs.m_03) + (a_Lhs.m_11 * a_Rhs.m_13) + (a_Lhs.m_12 * a_Rhs.m_23) + (a_Lhs.m_13 * a_Rhs.m_33),

		(a_Lhs.m_20 * a_Rhs.m_00) + (a_Lhs.m_21 * a_Rhs.m_10) + (a_Lhs.m_22 * a_Rhs.m_20) + (a_Lhs.m_23 * a_Rhs.m_30),
		(a_Lhs.m_20 * a_Rhs.m_01) + (a_Lhs.m_21 * a_Rhs.m_11) + (a_Lhs.m_22 * a_Rhs.m_21) + (a_Lhs.m_23 * a_Rhs.m_31),
		(a_Lhs.m_20 * a_Rhs.m_02) + (a_Lhs.m_21 * a_Rhs.m_12) + (a_Lhs.m_22 * a_Rhs.m_22) + (a_Lhs.m_23 * a_Rhs.m_32),
		(a_Lhs.m_20 * a_Rhs.m_03) + (a_Lhs.m_21 * a_Rhs.m_13) + (a_Lhs.m_22 * a_Rhs.m_23) + (a_Lhs.m_23 * a_Rhs.m_33),

		(a_Lhs.m_30 * a_Rhs.m_00) + (a_Lhs.m_31 * a_Rhs.m_10) + (a_Lhs.m_32 * a_Rhs.m_20) + (a_Lhs.m_33 * a_Rhs.m_30),
		(a_Lhs.m_30 * a_Rhs.m_01) + (a_Lhs.m_31 * a_Rhs.m_11) + (a_Lhs.m_32 * a_Rhs.m_21) + (a_Lhs.m_33 * a_Rhs.m_31),
		(a_Lhs.m_30 * a_Rhs.m_02) + (a_Lhs.m_31 * a_Rhs.m_12) + (a_Lhs.m_32 * a_Rhs.m_22) + (a_Lhs.m_33 * a_Rhs.m_32),
		(a_Lhs.m_30 * a_Rhs.m_03) + (a_Lhs.m_31 * a_Rhs.m_13) + (a_Lhs.m_32 * a_Rhs.m_23) + (a_Lhs.m_33 * a_Rhs.m_33)
	);

}

vec3 operator*(const mat4 &a_Lhs, const vec3 &a_Rhs) {

	float x, y, z;

	// The reason that I did not take in account the fourth column from the matrix and the imaginary 4th column of the vector which does not exist is
	// that it the fourth columns values would all be zero. Also than I had to make up a number for the fourth value of the vector. Which would be 0 because
	// the vector would be a direction. The value added to the dot product would always be zero so leaving this calculation out does not change the value in
	// the end.

	x = a_Lhs.m_00 * a_Rhs.m_X + a_Lhs.m_01 * a_Rhs.m_Y + a_Lhs.m_02 * a_Rhs.m_Z;
	y = a_Lhs.m_10 * a_Rhs.m_X + a_Lhs.m_11 * a_Rhs.m_Y + a_Lhs.m_12 * a_Rhs.m_Z;
	z = a_Lhs.m_20 * a_Rhs.m_X + a_Lhs.m_21 * a_Rhs.m_Y + a_Lhs.m_22 * a_Rhs.m_Z;

	return vec3(x, y, z);

}

vec4 operator*(const mat4& a_Lhs, const vec4& a_Rhs) {

	float x, y, z, w;

	x = a_Lhs.m_00 * a_Rhs.m_X + a_Lhs.m_01 * a_Rhs.m_Y + a_Lhs.m_02 * a_Rhs.m_Z + a_Lhs.m_03 * a_Rhs.m_W;
	y = a_Lhs.m_10 * a_Rhs.m_X + a_Lhs.m_11 * a_Rhs.m_Y + a_Lhs.m_12 * a_Rhs.m_Z + a_Lhs.m_13 * a_Rhs.m_W;
	z = a_Lhs.m_20 * a_Rhs.m_X + a_Lhs.m_21 * a_Rhs.m_Y + a_Lhs.m_22 * a_Rhs.m_Z + a_Lhs.m_23 * a_Rhs.m_W;
	w = a_Lhs.m_30 * a_Rhs.m_X + a_Lhs.m_31 * a_Rhs.m_Y + a_Lhs.m_32 * a_Rhs.m_Z + a_Lhs.m_33 * a_Rhs.m_W;

	return vec4(x, y, z, w);

}