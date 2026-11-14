#include "vector.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

float Vector3::Magnitude() const {
	return std::sqrt(this -> MagnitudeSquared());
}

Vector3 Vector3::Unit() const {
	const float Magnitude = this -> Magnitude();

	return Vector3(
		this -> X() / Magnitude,
		this -> Y() / Magnitude,
		this -> Z() / Magnitude
	);
}


std::string Vector3::ToString() const {
	char Buffer[64];
	std::snprintf(Buffer, sizeof(Buffer), "(%.3f, %.3f, %.3f)", this -> X(), this -> Y(), this -> Z());
	return std::string(Buffer);
}

static constexpr bool Near(float A, float B, float Epsilon = 1e-5f) {
    float Diff = A - B;
    return (Diff < 0.0f ? -Diff : Diff) < Epsilon;
}

void Vector3Test() {
    // Constructors & Data Access
    constexpr Vector3 DefaultVec;
    static_assert(DefaultVec.X() == 0.0f && DefaultVec.Y() == 0.0f && DefaultVec.Z() == 0.0f, "Default constructor failed");

    constexpr Vector3 UniformVec(5.5f);
    static_assert(UniformVec.X() == 5.5f && UniformVec.Y() == 5.5f && UniformVec.Z() == 5.5f, "Uniform constructor failed");

    constexpr Vector3 ExplicitVec(1.0f, 2.0f, 3.0f);
    static_assert(ExplicitVec.X() == 1.0f && ExplicitVec.Y() == 2.0f && ExplicitVec.Z() == 3.0f, "Explicit constructor failed");

    // Union / Array access check
    assert(ExplicitVec.Data[0] == 1.0f && ExplicitVec.Data[1] == 2.0f && ExplicitVec.Data[2] == 3.0f);

    // Subscript Operators
    constexpr Vector3 ConstSubscript(10.0f, 20.0f, 30.0f);
    static_assert(ConstSubscript[0] == 10.0f && ConstSubscript[1] == 20.0f && ConstSubscript[2] == 30.0f, "Const subscript failed");

    Vector3 MutableSubscript;
    MutableSubscript[0] = 4.0f;
    MutableSubscript[1] = 5.0f;
    MutableSubscript[2] = 6.0f;
    assert(MutableSubscript.X() == 4.0f && MutableSubscript.Y() == 5.0f && MutableSubscript.Z() == 6.0f);

    // Vector Arithmetic Operators
    constexpr Vector3 A(2.0f, 4.0f, 6.0f);
    constexpr Vector3 B(1.0f, 3.0f, 5.0f);

    constexpr Vector3 AddResult = A + B;
    static_assert(AddResult.X() == 3.0f && AddResult.Y() == 7.0f && AddResult.Z() == 11.0f, "Addition failed");

    constexpr Vector3 SubResult = A - B;
    static_assert(SubResult.X() == 1.0f && SubResult.Y() == 1.0f && SubResult.Z() == 1.0f, "Subtraction failed");

    constexpr Vector3 MulResult = A * B;
    static_assert(MulResult.X() == 2.0f && MulResult.Y() == 12.0f && MulResult.Z() == 30.0f, "Component multiplication failed");

    constexpr Vector3 DivResult = A / B;
    static_assert(DivResult.X() == 2.0f && Near(DivResult.Y(), 4.0f / 3.0f) && Near(DivResult.Z(), 6.0f / 5.0f), "Component division failed");

    constexpr Vector3 NegResult = -A;
    static_assert(NegResult.X() == -2.0f && NegResult.Y() == -4.0f && NegResult.Z() == -6.0f, "Negation failed");

    constexpr Vector3 V(1.0f, 2.0f, 3.0f);

    // Vector * Scalar & Scalar * Vector
    constexpr Vector3 MulScalar1 = V * 2.0f;
    static_assert(MulScalar1.X() == 2.0f && MulScalar1.Y() == 4.0f && MulScalar1.Z() == 6.0f, "Vector * Scalar failed");

    constexpr Vector3 MulScalar2 = 2.0f * V;
    static_assert(MulScalar2.X() == 2.0f && MulScalar2.Y() == 4.0f && MulScalar2.Z() == 6.0f, "Scalar * Vector failed");

    // Vector / Scalar & Scalar / Vector
    constexpr Vector3 DivScalar1 = V / 2.0f;
    static_assert(DivScalar1.X() == 0.5f && DivScalar1.Y() == 1.0f && DivScalar1.Z() == 1.5f, "Vector / Scalar failed");

    constexpr Vector3 DivScalar2 = 6.0f / V;
    static_assert(DivScalar2.X() == 6.0f && DivScalar2.Y() == 3.0f && DivScalar2.Z() == 2.0f, "Scalar / Vector failed");

    // Length, Dot, and Cross Products
    constexpr Vector3 LengthVec(3.0f, 4.0f, 0.0f);

    constexpr float MagSq = LengthVec.MagnitudeSquared();
    static_assert(MagSq == 25.0f, "MagnitudeSquared failed");

    float Mag = LengthVec.Magnitude();
    assert(Near(Mag, 5.0f));

    Vector3 UnitVec = LengthVec.Unit();
    assert(Near(UnitVec.X(), 0.6f) && Near(UnitVec.Y(), 0.8f) && Near(UnitVec.Z(), 0.0f));

    // Dot Product
    constexpr Vector3 Dot1(1.0f, 2.0f, 3.0f);
    constexpr Vector3 Dot2(4.0f, -5.0f, 6.0f);
    constexpr float DotResult = Dot1.Dot(Dot2); // (4) + (-10) + (18) = 12
    static_assert(DotResult == 12.0f, "Dot product failed");

    // Cross Product
    constexpr Vector3 Right(1.0f, 0.0f, 0.0f);
    constexpr Vector3 Up(0.0f, 1.0f, 0.0f);
    constexpr Vector3 Forward = Right.Cross(Up);
    static_assert(Forward.X() == 0.0f && Forward.Y() == 0.0f && Forward.Z() == 1.0f, "Cross product failed");

    // Lerp
    constexpr Vector3 LerpStart(0.0f, 10.0f, 20.0f);
    constexpr Vector3 LerpEnd(10.0f, 20.0f, 40.0f);
    constexpr Vector3 LerpHalf = LerpStart.Lerp(LerpEnd, 0.5f);
    static_assert(LerpHalf.X() == 5.0f && LerpHalf.Y() == 15.0f && LerpHalf.Z() == 30.0f, "Lerp failed");

    // Clamp
    constexpr Vector3 Unclamped(15.0f, -5.0f, 4.0f);
    constexpr Vector3 MinBound(0.0f, 0.0f, 0.0f);
    constexpr Vector3 MaxBound(10.0f, 10.0f, 10.0f);
    constexpr Vector3 Clamped = Unclamped.Clamp(MinBound, MaxBound);
    static_assert(Clamped.X() == 10.0f && Clamped.Y() == 0.0f && Clamped.Z() == 4.0f, "Clamp failed");

    // ToString
    Vector3 StringVec(1.5f, 2.0f, -3.75f);
    std::string Str = StringVec.ToString();
    assert(!Str.empty());

    std::cout << "All Vector3 tests passed successfully!\n";
}
