#include "vector.h"

#include <SDL3/SDL_log.h>

#include <cassert>
#include <cmath>
#include <cstdio>
#include <string>

float Vector3::Magnitude() const {
	return std::sqrt(this -> MagnitudeSquared());
}

Vector3 Vector3::Unit() const {
	const float Magnitude = this -> Magnitude();
    if (Magnitude == 0.0f) return Vector3(0.0f);

	return Vector3(
		this -> X() / Magnitude,
		this -> Y() / Magnitude,
		this -> Z() / Magnitude
	);
}

float Vector3::Angle(const Vector3 & Other) const {
    const float MagnitudeProduct = this -> Magnitude() * Other.Magnitude();
    if (MagnitudeProduct == 0.0f) return 0.0f;

    float DotValue = this -> Dot(Other) / MagnitudeProduct;
    DotValue = DotValue < -1.0f ? -1.0f : (DotValue > 1.0f ? 1.0f : DotValue);

    return std::acosf(DotValue);
}

float Vector3::Angle(const Vector3 & Other, const Vector3 & Axis) const {
    const float AxisMagnitude = Axis.Magnitude();
    if (AxisMagnitude == 0.0f) return 0.0f;

    const Vector3 NormalizedAxis = Axis / AxisMagnitude;

    const Vector3 A = *this - NormalizedAxis * this -> Dot(NormalizedAxis);
    const Vector3 B = Other - NormalizedAxis * Other.Dot(NormalizedAxis);

    const float MagnitudeProduct = A.Magnitude() * B.Magnitude();
    if (MagnitudeProduct == 0.0f) return 0.0f;

    float DotValue = A.Dot(B) / MagnitudeProduct;
    DotValue = DotValue < -1.0f ? -1.0f : (DotValue > 1.0f ? 1.0f : DotValue);

    const float AngleRadians = std::acosf(DotValue);

    return A.Cross(B).Dot(NormalizedAxis) < 0.0f
        ? -AngleRadians
        : AngleRadians;
}

std::string Vector3::ToString() const {
	char Buffer[64];
	std::snprintf(Buffer, sizeof(Buffer), "(%.3f, %.3f, %.3f)", this -> X(), this -> Y(), this -> Z());
	return std::string(Buffer);
}

static constexpr bool NearFloat(float A, float B, float Epsilon = 1e-5f) {
    float Diff = A - B;
    return (Diff < 0.0f ? -Diff : Diff) < Epsilon;
}

void Vector3::Test() {
    // Constructors & Data Access
    constexpr Vector3 DefaultVec;
    static_assert(DefaultVec.X() == 0.0f && DefaultVec.Y() == 0.0f && DefaultVec.Z() == 0.0f);

    constexpr Vector3 UniformVec(5.5f);
    static_assert(UniformVec.X() == 5.5f && UniformVec.Y() == 5.5f && UniformVec.Z() == 5.5f);

    constexpr Vector3 ExplicitVec(1.0f, 2.0f, 3.0f);
    static_assert(ExplicitVec.X() == 1.0f && ExplicitVec.Y() == 2.0f && ExplicitVec.Z() == 3.0f);

    assert(ExplicitVec.Data[0] == 1.0f);
    assert(ExplicitVec.Data[1] == 2.0f);
    assert(ExplicitVec.Data[2] == 3.0f);

    // Static Utility Instantiations
    static_assert(Vector3::Zero() == Vector3(0.0f, 0.0f, 0.0f));
    static_assert(Vector3::One() == Vector3(1.0f, 1.0f, 1.0f));
    static_assert(Vector3::Right() == Vector3(1.0f, 0.0f, 0.0f));
    static_assert(Vector3::Left() == Vector3(-1.0f, 0.0f, 0.0f));
    static_assert(Vector3::Up() == Vector3(0.0f, 1.0f, 0.0f));
    static_assert(Vector3::Down() == Vector3(0.0f, -1.0f, 0.0f));
    static_assert(Vector3::Front() == Vector3(0.0f, 0.0f, 1.0f));
    static_assert(Vector3::Back() == Vector3(0.0f, 0.0f, -1.0f));

    // Component Accessors & Subscript Operators
    Vector3 MutableVec;
    MutableVec.X() = 1.0f;
    MutableVec.Y() = 2.0f;
    MutableVec.Z() = 3.0f;

    assert(MutableVec.X() == 1.0f);
    assert(MutableVec.Y() == 2.0f);
    assert(MutableVec.Z() == 3.0f);

    constexpr Vector3 ConstSubscript(10.0f, 20.0f, 30.0f);
    static_assert(ConstSubscript[0] == 10.0f);
    static_assert(ConstSubscript[1] == 20.0f);
    static_assert(ConstSubscript[2] == 30.0f);

    MutableVec[0] = 4.0f;
    MutableVec[1] = 5.0f;
    MutableVec[2] = 6.0f;
    assert(MutableVec.X() == 4.0f);
    assert(MutableVec.Y() == 5.0f);
    assert(MutableVec.Z() == 6.0f);

    // Arithmetic Operators
    constexpr Vector3 A(2.0f, 4.0f, 6.0f);
    constexpr Vector3 B(1.0f, 3.0f, 5.0f);

    constexpr Vector3 AddResult = A + B;
    static_assert(AddResult == Vector3(3.0f, 7.0f, 11.0f));

    constexpr Vector3 SubResult = A - B;
    static_assert(SubResult == Vector3(1.0f, 1.0f, 1.0f));

    constexpr Vector3 MulResult = A * B;
    static_assert(MulResult == Vector3(2.0f, 12.0f, 30.0f));

    constexpr Vector3 DivResult = A / B;
    static_assert(DivResult.X() == 2.0f);
    static_assert(NearFloat(DivResult.Y(), 4.0f / 3.0f));
    static_assert(NearFloat(DivResult.Z(), 6.0f / 5.0f));

    constexpr Vector3 NegResult = -A;
    static_assert(NegResult == Vector3(-2.0f, -4.0f, -6.0f));

    // Scalar Arithmetic
    constexpr Vector3 V(1.0f, 2.0f, 3.0f);

    constexpr Vector3 MulScalar1 = V * 2.0f;
    static_assert(MulScalar1 == Vector3(2.0f, 4.0f, 6.0f));

    constexpr Vector3 MulScalar2 = 2.0f * V;
    static_assert(MulScalar2 == Vector3(2.0f, 4.0f, 6.0f));

    constexpr Vector3 DivScalar1 = V / 2.0f;
    static_assert(DivScalar1 == Vector3(0.5f, 1.0f, 1.5f));

    constexpr Vector3 DivScalar2 = 6.0f / V;
    static_assert(DivScalar2 == Vector3(6.0f, 3.0f, 2.0f));

    // Compound Assignment Operators
    Vector3 Compound(1.0f, 2.0f, 3.0f);

    Compound += Vector3(2.0f, 3.0f, 4.0f);
    assert(Compound == Vector3(3.0f, 5.0f, 7.0f));

    Compound -= Vector3(1.0f, 2.0f, 3.0f);
    assert(Compound == Vector3(2.0f, 3.0f, 4.0f));

    Compound *= Vector3(2.0f, 3.0f, 4.0f);
    assert(Compound == Vector3(4.0f, 9.0f, 16.0f));

    Compound /= Vector3(2.0f, 3.0f, 4.0f);
    assert(Compound == Vector3(2.0f, 3.0f, 4.0f));

    Compound *= 2.0f;
    assert(Compound == Vector3(4.0f, 6.0f, 8.0f));

    Compound /= 2.0f;
    assert(Compound == Vector3(2.0f, 3.0f, 4.0f));

    // Equality & Near
    constexpr Vector3 EqualA(1.0f, 2.0f, 3.0f);
    constexpr Vector3 EqualB(1.0f, 2.0f, 3.0f);
    constexpr Vector3 Different(1.0f, 2.0f, 4.0f);

    static_assert(EqualA == EqualB);
    static_assert(!(EqualA == Different));

    constexpr Vector3 AlmostEqual(1.000001f, 2.000001f, 3.000001f);
    static_assert(EqualA.Near(AlmostEqual));

    constexpr Vector3 NotNear(1.0f, 2.0f, 3.1f);
    static_assert(!EqualA.Near(NotNear));

    // Magnitude & Normalization
    constexpr Vector3 LengthVec(3.0f, 4.0f, 0.0f);

    constexpr float MagSq = LengthVec.MagnitudeSquared();
    static_assert(MagSq == 25.0f);

    assert(NearFloat(LengthVec.Magnitude(), 5.0f));

    Vector3 UnitVec = LengthVec.Unit();
    assert(NearFloat(UnitVec.X(), 0.6f));
    assert(NearFloat(UnitVec.Y(), 0.8f));
    assert(NearFloat(UnitVec.Z(), 0.0f));
    assert(NearFloat(UnitVec.Magnitude(), 1.0f));

    // Check division-by-zero protection in Unit()
    assert(Vector3::Zero().Unit() == Vector3::Zero());

    // Dot & Cross Products
    constexpr Vector3 Dot1(1.0f, 2.0f, 3.0f);
    constexpr Vector3 Dot2(4.0f, -5.0f, 6.0f);

    constexpr float DotResult = Dot1.Dot(Dot2);
    static_assert(DotResult == 12.0f);

    static_assert(Vector3::Right().Cross(Vector3::Up()) == Vector3::Front());
    static_assert(Vector3::Up().Cross(Vector3::Right()) == Vector3::Back());

    // Angles
    constexpr float HalfPi = 1.57079632679f;
    constexpr float Pi = 3.14159265359f;

    assert(NearFloat(Vector3::Right().Angle(Vector3::Up()), HalfPi));
    assert(NearFloat(Vector3::Up().Angle(Vector3::Right()), HalfPi));
    assert(NearFloat(Vector3::Right().Angle(Vector3::Left()), Pi));
    assert(NearFloat(Vector3::Right().Angle(Vector3::Right()), 0.0f));
    assert(NearFloat(Vector3::Zero().Angle(Vector3::Right()), 0.0f));

    assert(NearFloat(Vector3::Right().Angle(Vector3::Up(), Vector3::Front()), HalfPi));
    assert(NearFloat(Vector3::Up().Angle(Vector3::Right(), Vector3::Front()), -HalfPi));
    assert(NearFloat(Vector3::Right().Angle(Vector3::Left(), Vector3::Front()), Pi));
    assert(NearFloat(Vector3::Right().Angle(Vector3::Right(), Vector3::Front()), 0.0f));
    assert(NearFloat(Vector3::Right().Angle(Vector3::Front(), Vector3::Up()), -HalfPi));

    // Lerp
    constexpr Vector3 LerpStart(0.0f, 10.0f, 20.0f);
    constexpr Vector3 LerpEnd(10.0f, 20.0f, 40.0f);

    constexpr Vector3 LerpZero = LerpStart.Lerp(LerpEnd, 0.0f);
    static_assert(LerpZero == LerpStart);

    constexpr Vector3 LerpHalf = LerpStart.Lerp(LerpEnd, 0.5f);
    static_assert(LerpHalf == Vector3(5.0f, 15.0f, 30.0f));

    constexpr Vector3 LerpFull = LerpStart.Lerp(LerpEnd, 1.0f);
    static_assert(LerpFull == LerpEnd);

    constexpr Vector3 LerpExtrapolated = LerpStart.Lerp(LerpEnd, 2.0f);
    static_assert(LerpExtrapolated == Vector3(20.0f, 30.0f, 60.0f));

    // Absolute & Sign
    constexpr Vector3 NegativeVec(-1.5f, 0.0f, 3.5f);
    constexpr Vector3 AbsoluteResult = NegativeVec.Absolute();
    static_assert(AbsoluteResult == Vector3(1.5f, 0.0f, 3.5f));

    constexpr Vector3 SignResult = NegativeVec.Sign();
    static_assert(SignResult == Vector3(-1.0f, 0.0f, 1.0f));

    // Round, Floor & Ceil
    constexpr Vector3 RoundingVec(1.4f, 2.5f, -3.6f);

    constexpr Vector3 RoundResult = RoundingVec.Round();
    static_assert(RoundResult == Vector3(1.0f, 3.0f, -4.0f));

    constexpr Vector3 FloorResult = RoundingVec.Floor();
    static_assert(FloorResult == Vector3(1.0f, 2.0f, -4.0f));

    constexpr Vector3 CeilResult = RoundingVec.Ceil();
    static_assert(CeilResult == Vector3(2.0f, 3.0f, -3.0f));

    // Clamp
    constexpr Vector3 Unclamped(15.0f, -5.0f, 4.0f);
    constexpr Vector3 MinBound(0.0f, 0.0f, 0.0f);
    constexpr Vector3 MaxBound(10.0f, 10.0f, 10.0f);

    constexpr Vector3 Clamped = Unclamped.Clamp(MinBound, MaxBound);
    static_assert(Clamped == Vector3(10.0f, 0.0f, 4.0f));

    // ToString
    Vector3 StringVec(1.5f, 2.0f, -3.75f);
    std::string Str = StringVec.ToString();
    assert(!Str.empty());

    SDL_Log("All Vector3 tests passed successfully!");
}
