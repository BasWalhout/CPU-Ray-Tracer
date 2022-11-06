#include "stdafx.h"
#include "CppUnitTest.h"
#include "../MathLibrary/MathLibrary.h"

#include <chrono>
#include <limits>
#include <random>
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MathTest
{		
	TEST_CLASS(Vec3Test)
	{
	public:
		void TestEqual(float a_Lhs, float a_Rhs, float a_Tolerance)
		{
			const float diff = a_Lhs - a_Rhs;
			Assert::IsTrue((diff <= a_Tolerance && -diff <= a_Tolerance));
		}

		void TestEqual(const vec3 &a_Lhs, const vec3 &a_Rhs)
		{
			for (size_t i = 0; i < 3; ++i)
			{
				Assert::AreEqual(a_Lhs.v[i], a_Rhs.v[i]);
			}
		}

		TEST_METHOD(Vec3Construction)
		{
			const vec3 vecEmpty;
			Assert::AreEqual(vecEmpty.v[0], 0.0f);
			Assert::AreEqual(vecEmpty.v[1], 0.0f);
			Assert::AreEqual(vecEmpty.v[2], 0.0f);

			const vec3 vecValues(1.0f, 4.0f, 5.0f);
			Assert::AreEqual(vecValues.v[0], 1.0f);
			Assert::AreEqual(vecValues.v[1], 4.0f);
			Assert::AreEqual(vecValues.v[2], 5.0f);
		}

		TEST_METHOD(Vec3Assignment)
		{
			const vec3 vecOriginal(5.0f, 7.0f, 2.0f);
			vec3 vecEqual = vecOriginal;
			TestEqual(vecEqual, vecOriginal);
		}

		TEST_METHOD(Vec3Operators)
		{
			const vec3 vecOriginal(5.0f, 7.0f, 2.0f);
			const vec3 vecOperand(6.0f, 3.0f, 1.0f);
			{
				vec3 vecSum = vecOriginal;
				vecSum += vecOperand;
				TestEqual(vecSum, vec3(11.0f, 10.0f, 3.0f));

				vec3 vecDiff = vecOriginal;
				vecDiff -= vecOperand;
				TestEqual(vecDiff, vec3(-1.0f, 4.0f, 1.0f));
			}

			{
				const vec3 vecSum = vecOriginal + vecOperand;
				TestEqual(vecSum, vec3(11.0f, 10.0f, 3.0f));

				const vec3 vecDiff = vecOriginal - vecOperand;
				TestEqual(vecDiff, vec3(-1.0f, 4.0f, 1.0f));
			}

			{
				vec3 vecDiv = vec3(6.0f, 27.0f, 3.0f);
				vecDiv /= 3.0f;
				TestEqual(vecDiv, vec3(2.0f, 9.0f, 1.0f));

				vec3 vecMult = vecDiv;
				vecMult *= 2.5f;
				TestEqual(vecMult, vec3(5.0f, 22.5f, 2.5f));
			}

			{
				vec3 vecDiv = vec3(6.0f, 27.0f, 3.0f) / 3.0f;
				TestEqual(vecDiv, vec3(2.0f, 9.0f, 1.0f));

				vec3 vecMult = vecDiv * 2.5f;
				TestEqual(vecMult, vec3(5.0f, 22.5f, 2.5f));
			}
		}

		TEST_METHOD(Vec3Equality)
		{
			std::mt19937 generator(std::time(0));
			const float x = generator();
			const float y = generator();
			const float z = generator();
			const vec3 lhs(x, y, z);

			Assert::IsTrue(lhs == vec3(x, y, z));
			Assert::IsFalse(lhs == vec3(y, x, z));

			Assert::IsFalse(lhs != vec3(x, y, z));
			Assert::IsTrue(lhs != vec3(y, x, z));
		}

		TEST_METHOD(Vec3DotProduct)
		{
			const vec3 lhs(2.0f, 3.0f, 6.0f);
			const vec3 rhs(5.0f, 4.0f, 1.0f);

			const float dotProduct = 28.0f;
			Assert::AreEqual(lhs.dot(rhs), dotProduct);
		}

		TEST_METHOD(Vec3CrossProduct)
		{
			vec3 lhs(1.0f, 2.0f, 3.0f);
			vec3 rhs(4.0f, 5.0f, 6.0f);
			Assert::IsTrue(vec3(-3.0f, 6.0f, -3.0f) == lhs.cross(rhs));
		}

		TEST_METHOD(Vec3Normalize)
		{
			vec3 vector(3.0f, 4.0f, 5.0f);
			vector.normalize();
			Assert::AreEqual(vector.length(), 1.0f);
		}

		TEST_METHOD(Vec3Length)
		{
			const vec3 vector(3.0f, 4.0f, 5.0f);
			TestEqual(vector.length(), sqrtf(50.0f), 3 * std::numeric_limits<float>::epsilon());
		}

		TEST_METHOD(Reflection) {

			const vec3 incomingDirection = vec3(5.f, -5.f, 5.f).normalize();
			const vec3 normal = vec3(0.f, 1.f, 0.f);

			const vec3 reflectionDirection = vec3(5.f, 5.f, 5.f).normalize();

			vec3 R = incomingDirection - (normal * normal.dot(incomingDirection)) * 2.f;

			TestEqual(reflectionDirection, R);

		}

		TEST_METHOD(Refraction) {

			const vec3 incomingDirection = vec3(1.f, 1.f, 1.f).normalize();
			vec3 normal = vec3(0.f, 0.f, -1.f).normalize();

			vec3 refractionDirection = vec3();

			float NdotI = normal.dot(incomingDirection);
			float iorCurrentMedium = 1.f;
			float iorEnteringMedium = 1.8f;

			if (NdotI < 0.f) { // the ray comes from outside the surface. The cosine returns negative, we want to make it positive.
				NdotI = -NdotI;
			}
			else { //the ray comes from the inside. The cosine is already positive, we want to swap the refraction indices and reverse the normal.

				normal *= -1.f;
				std::swap(iorCurrentMedium, iorEnteringMedium);

			}

			float ior = iorCurrentMedium / iorEnteringMedium;
			float c2 = 1 - (ior * ior) * (1 - (NdotI * NdotI));

			if (c2 < 0) {
				//total internal reflection. There is no refraction in this case.
				
			}
			else {

				refractionDirection = incomingDirection * ior + normal * (ior * NdotI - sqrtf(c2));
				printf("%f, %f, %f \n", refractionDirection.m_X, refractionDirection.m_Y, refractionDirection.m_Z);

			}

			float NdotR = -normal.dot(refractionDirection);
			float Angle = std::cosf(26.97706 * MathUtilities::DEG2RAD);
			//https://www.omnicalculator.com/physics/snells-law used this calculator to calculte the angle between 2 different directions.

			Assert::AreEqual(Angle, NdotR, MathUtilities::EPSILON);


		}

		TEST_METHOD(Fresnel) {

			const vec3 incomingDirection = vec3(1.f, 1.f, 1.f).normalize();
			vec3 normal = vec3(0.f, 0.f, -1.f).normalize();

			float NdotI = normal.dot(incomingDirection);
			float iorCurrentMedium = 1.f;
			float iorEnteringMedium = 1.8f;

			float Rreflection = 0.f;

			if (NdotI > 0.f) { // The ray comes from the inside of the object. We want to swap the refractive indices.
				std::swap(iorCurrentMedium, iorEnteringMedium);
			}

			float ior = iorCurrentMedium / iorEnteringMedium;
			float c2 = 1 - (ior * ior) * (1 - (NdotI * NdotI));

			if (c2 < 0.f) { // There is total internal refraction. We want to reflect all light.
				Rreflection = 1.f;
			}
			else {

				float cosRefractionAngle = sqrt(c2);
				NdotI = fabsf(NdotI);

				float Rparallel =	((iorEnteringMedium * NdotI) - (iorCurrentMedium * cosRefractionAngle)) / 
									((iorEnteringMedium * NdotI) + (iorCurrentMedium * cosRefractionAngle));

				float Rperpendicular = ((iorCurrentMedium * NdotI) - (iorEnteringMedium * cosRefractionAngle)) / 
										((iorCurrentMedium * NdotI) + (iorEnteringMedium * cosRefractionAngle));

				Rreflection = 0.5f * (Rparallel * Rparallel + Rperpendicular * Rperpendicular);

			}

			float expectedValue = 0.5f * (0.221581620868f + 0.00587297770615f);

			Assert::AreEqual(expectedValue, Rreflection, MathUtilities::EPSILON);

		}

	};
}