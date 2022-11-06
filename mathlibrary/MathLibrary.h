#pragma once

#include <cmath>
#include <ostream>

class vec2
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union {
		struct
		{
			float m_X;
			float m_Y;
		};
		float v[2];
	};
#pragma warning(pop)

public:
	vec2();
	vec2(float a_X, float a_Y);

	vec2& operator=(const vec2& rhs);

	vec2& operator+=(const vec2 &a_Rhs);
	vec2& operator-=(const vec2 &a_Rhs);
	vec2& operator*=(float a_Rhs);
	vec2& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	inline float dot(vec2 const &a_Rhs) const {

		return (this->m_X * a_Rhs.m_X + this->m_Y * a_Rhs.m_Y);

	}
	vec2& normalize();
	inline float length() const {

		return sqrtf(powf(this->m_X, 2) + powf(this->m_Y, 2));

	}
};

vec2 operator+(const vec2 &a_Lhs, const vec2 &a_Rhs);
vec2 operator-(const vec2 &a_Lhs, const vec2 &a_Rhs);
vec2 operator*(const vec2 &a_Lhs, float a_Rhs);
vec2 operator/(const vec2 &a_Lhs, float a_Rhs);
bool operator==(const vec2 &a_Lhs, const vec2 &a_Rhs);
bool operator!=(const vec2 &a_Lhs, const vec2 &a_Rhs);

class vec4;

class vec3 {
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union {
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
		};
		float v[3];
	};
#pragma warning(pop)

public:
	vec3();
	vec3(float a_X, float a_Y, float a_Z);

	vec3& operator=(const vec3& rhs);

	vec3& operator+=(const vec3 &a_Rhs);
	vec3& operator-=(const vec3 &a_Rhs);
	vec3& operator*=(float a_Rhs);
	vec3& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	inline float dot(vec3 const &a_Rhs) const {

		return (this->m_X * a_Rhs.m_X + this->m_Y * a_Rhs.m_Y + this->m_Z * a_Rhs.m_Z);

	}
	inline vec3 cross(vec3 const &a_Rhs) const {

		return vec3(this->m_Y * a_Rhs.m_Z - this->m_Z * a_Rhs.m_Y,
			this->m_Z * a_Rhs.m_X - this->m_X * a_Rhs.m_Z,
			this->m_X * a_Rhs.m_Y - this->m_Y * a_Rhs.m_X);

	}
	vec3& normalize();
	inline float length() const {

		return sqrtf(powf(this->m_X, 2) + powf(this->m_Y, 2) + powf(this->m_Z, 2));

	}

	vec4 toVec4(bool a_point);

};

vec3 operator+(const vec3 &a_Lhs, const vec3 &a_Rhs);
vec3 operator-(const vec3 &a_Lhs, const vec3 &a_Rhs);
vec3 operator*(const vec3 &a_Lhs, float a_Rhs);
vec3 operator/(const vec3 &a_Lhs, float a_Rhs);
bool operator==(const vec3 &a_Lhs, const vec3 &a_Rhs);
bool operator!=(const vec3 &a_Lhs, const vec3 &a_Rhs);

std::ostream& operator<<(std::ostream& ostream, const vec3& a_Rhs);

class vec4
{

public:
#pragma warning(push)
#pragma warning(disable: 4201)

	union
	{
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
			float m_W;
		};
		float v[4];
	};

#pragma warning(pop)

public:
	vec4();
	vec4(float a_X, float a_Y, float a_Z, float a_W);
	vec4(vec3 a_vec, float a_PorV);

	vec4& operator=(const vec4& rhs);

	vec4& operator+=(const vec4 &a_Rhs);
	vec4& operator-=(const vec4 &a_Rhs);
	vec4& operator*=(float a_Rhs);
	vec4& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	vec3 toVec3();

};

vec4 operator+(const vec4 &a_Lhs, const vec4 &a_Rhs);
vec4 operator-(const vec4 &a_Lhs, const vec4 &a_Rhs);
vec4 operator*(const vec4 &a_Lhs, float a_Rhs);
vec4 operator/(const vec4 &a_Lhs, float a_Rhs);
bool operator==(const vec4 &a_Lhs, const vec4 &a_Rhs);
bool operator!=(const vec4 &a_Lhs, const vec4 &a_Rhs);

class mat4
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union {
		struct
		{
			float m_00; float m_10; float m_20; float m_30;
			float m_01; float m_11; float m_21; float m_31;
			float m_02; float m_12; float m_22; float m_32;
			float m_03; float m_13; float m_23; float m_33;
		};
		struct
		{

			vec3 axis_X3; float w_X;
			vec3 axis_Y3; float w_Y;
			vec3 axis_Z3; float w_Z;
			vec3 translation3; float w_T;

		};
		struct
		{

			vec4 axis_X4;
			vec4 axis_Y4;
			vec4 axis_Z4;
			vec4 translation4;

		};
		vec4 axes[4];
		float m[16];
	};
#pragma warning(pop)

public:
	mat4();
	//Makes a matrix using the vectors to fill in the columns of the matrix.
	mat4(vec3 a_Col0, float a_03,
		vec3 a_Col1, float a_13,
		vec3 a_Col2, float a_23,
		vec3 a_Col3, float a_33);
	mat4(vec4 a_Col0,
		vec4 a_Col1,
		vec4 a_Col2,
		vec4 a_Col3);
	mat4(float a_00, float a_01, float a_02, float a_03,
		float a_10, float a_11, float a_12, float a_13,
		float a_20, float a_21, float a_22, float a_23,
		float a_30, float a_31, float a_32, float a_33 = 1.f);

	mat4& operator=(const mat4& rhs);

	mat4& operator+=(const mat4 &a_Rhs);
	mat4& operator-=(const mat4 &a_Rhs);
	mat4& operator*=(const mat4 &a_Rhs);

	float determinant() const;
	inline mat4 inverse() {

		float determinant = this->determinant();

		if (determinant == 0.f) {
			mat4();
		}

		float minor_00 = this->m_11 * (this->m_22 * this->m_33 - this->m_23 * this->m_32) -
			this->m_12 * (this->m_21 * this->m_33 - this->m_23 * this->m_31) +
			this->m_13 * (this->m_21 * this->m_32 - this->m_22 * this->m_31);

		float minor_01 = this->m_10 * (this->m_22 * this->m_33 - this->m_23 * this->m_32) -
			this->m_12 * (this->m_20 * this->m_33 - this->m_23 * this->m_30) +
			this->m_13 * (this->m_20 * this->m_32 - this->m_22 * this->m_30);

		float minor_02 = this->m_10 * (this->m_21 * this->m_33 - this->m_23 * this->m_31) -
			this->m_11 * (this->m_20 * this->m_33 - this->m_23 * this->m_31) +
			this->m_13 * (this->m_20 * this->m_31 - this->m_21 * this->m_30);

		float minor_03 = this->m_10 * (this->m_21 * this->m_32 - this->m_22 * this->m_31) -
			this->m_11 * (this->m_20 * this->m_32 - this->m_22 * this->m_30) +
			this->m_12 * (this->m_20 * this->m_31 - this->m_21 * this->m_30);



		float minor_10 = this->m_01 * (this->m_22 * this->m_33 - this->m_23 * this->m_32) -
			this->m_02 * (this->m_21 * this->m_33 - this->m_23 * this->m_31) +
			this->m_03 * (this->m_21 * this->m_32 - this->m_31 * this->m_22);

		float minor_11 = this->m_00 * (this->m_22 * this->m_33 - this->m_23 * this->m_32) -
			this->m_02 * (this->m_20 * this->m_33 - this->m_23 * this->m_30) +
			this->m_03 * (this->m_20 * this->m_32 - this->m_22 * this->m_30);

		float minor_12 = this->m_00 * (this->m_21 * this->m_33 - this->m_23 * this->m_31) -
			this->m_01 * (this->m_20 * this->m_33 - this->m_23 * this->m_30) +
			this->m_03 * (this->m_20 * this->m_31 - this->m_21 * this->m_30);

		float minor_13 = this->m_00 * (this->m_21 * this->m_32 - this->m_22 * this->m_31) -
			this->m_01 * (this->m_20 * this->m_32 - this->m_22 * this->m_30) +
			this->m_02 * (this->m_20 * this->m_31 - this->m_21 * this->m_30);



		float minor_20 = this->m_01 * (this->m_12 * this->m_33 - this->m_13 * this->m_32) -
			this->m_02 * (this->m_11 * this->m_33 - this->m_13 * this->m_31) +
			this->m_03 * (this->m_11 * this->m_32 - this->m_12 * this->m_31);

		float minor_21 = this->m_00 * (this->m_12 * this->m_33 - this->m_13 * this->m_32) -
			this->m_02 * (this->m_10 * this->m_33 - this->m_13 * this->m_30) +
			this->m_03 * (this->m_10 * this->m_32 - this->m_12 * this->m_30);

		float minor_22 = this->m_00 * (this->m_11 * this->m_33 - this->m_13 * this->m_31) -
			this->m_01 * (this->m_10 * this->m_33 - this->m_13 * this->m_30) +
			this->m_03 * (this->m_10 * this->m_31 - this->m_11 * this->m_30);

		float minor_23 = this->m_00 * (this->m_11 * this->m_32 - this->m_12 * this->m_31) -
			this->m_01 * (this->m_10 * this->m_32 - this->m_12 * this->m_30) +
			this->m_02 * (this->m_10 * this->m_31 - this->m_11 * this->m_30);



		float minor_30 = this->m_01 * (this->m_12 * this->m_23 - this->m_13 * this->m_22) -
			this->m_02 * (this->m_11 * this->m_23 - this->m_13 * this->m_21) +
			this->m_03 * (this->m_11 * this->m_22 - this->m_12 * this->m_21);

		float minor_31 = this->m_00 * (this->m_12 * this->m_23 - this->m_13 * this->m_22) -
			this->m_02 * (this->m_10 * this->m_23 - this->m_13 * this->m_20) +
			this->m_03 * (this->m_10 * this->m_22 - this->m_12 * this->m_20);

		float minor_32 = this->m_00 * (this->m_11 * this->m_23 - this->m_13 * this->m_21) -
			this->m_01 * (this->m_10 * this->m_23 - this->m_13 * this->m_20) +
			this->m_03 * (this->m_10 * this->m_21 - this->m_11 * this->m_20);

		float minor_33 = this->m_00 * (this->m_11 * this->m_22 - this->m_12 * this->m_21) -
			this->m_01 * (this->m_10 * this->m_22 - this->m_12 * this->m_20) +
			this->m_02 * (this->m_10 * this->m_21 - this->m_11 * this->m_20);

		mat4 adjoint = mat4(minor_00, -minor_10, minor_20, -minor_30,
			-minor_01, minor_11, -minor_21, minor_31,
			minor_02, -minor_12, minor_22, -minor_32,
			-minor_03, minor_13, -minor_23, minor_33);

		for (int i = 0; i < 16; ++i) {

			this->m[i] = adjoint.m[i] / determinant;

		}

		return *this;

	};

	static mat4 identity();
	static mat4 rotateX(float a_Radians);
	static mat4 rotateY(float a_Radians);
	static mat4 rotateZ(float a_Radians);
	static mat4 translate(const vec3 &a_Translation);
	static mat4 scale(const vec3& a_Scale);

	static mat4 lookat(const vec3 &a_Eye, const vec3 &a_Center, const vec3 &a_Up);
	static mat4 projection(float a_FovY, float a_AspectRatio, float a_Near, float a_Far);
};

mat4 operator+(const mat4 &a_Lhs, const mat4 &a_Rhs);
mat4 operator-(const mat4 &a_Lhs, const mat4 &a_Rhs);
mat4 operator*(const mat4 &a_Lhs, const mat4 &a_Rhs);
vec3 operator*(const mat4 &a_Lhs, const vec3 &a_Rhs);
vec4 operator*(const mat4 &a_Lhs, const vec4 &a_Rhs);

namespace MathUtilities {

	const float PI = 3.14159265359f;
	const float RAD2DEG = 180.f / PI;
	const float DEG2RAD = PI / 180.f;

	const float EPSILON = 0.0001f;

	inline float Clampf(float a_x, float a_min, float a_max) {

		return(a_x < a_min) ? a_min : (a_x > a_max) ? a_max : a_x;

	}

}