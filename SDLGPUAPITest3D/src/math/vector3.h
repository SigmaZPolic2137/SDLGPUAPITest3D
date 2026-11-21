#pragma once

#include <cassert>
#include <string>

struct Vector3 {
	float X{0.0f};
	float Y{0.0f};
	float Z{0.0f};

	constexpr Vector3() = default;
	constexpr explicit Vector3(float XYZ);
	constexpr Vector3(float X, float Y, float Z);

	static constexpr Vector3 Zero() { return Vector3{0.0f, 0.0f, 0.0f}; }
	static constexpr Vector3 One() { return Vector3{1.0f, 1.0f, 1.0f}; }
	static constexpr Vector3 Right() { return Vector3{1.0f, 0.0f, 0.0f}; }
	static constexpr Vector3 Left() { return Vector3{-1.0f, 0.0f, 0.0f}; }
	static constexpr Vector3 Up() { return Vector3{0.0f, 1.0f, 0.0f}; }
	static constexpr Vector3 Down() { return Vector3{0.0f, -1.0f, 0.0f}; }
	static constexpr Vector3 Front() { return Vector3{0.0f, 0.0f, 1.0f}; }
	static constexpr Vector3 Back() { return Vector3{0.0f, 0.0f, -1.0f}; }

	constexpr float * Data();
	constexpr const float * Data() const;

	constexpr float operator[](std::size_t Index) const;
	constexpr float & operator[](std::size_t Index);

	constexpr Vector3 operator-() const;
	constexpr Vector3 operator+(const Vector3 & Other) const;
	constexpr Vector3 operator-(const Vector3 & Other) const;
	constexpr Vector3 operator*(const Vector3 & Other) const;
	constexpr Vector3 operator/(const Vector3 & Other) const;
	constexpr Vector3 operator*(float Factor) const;
	constexpr Vector3 operator/(float Divisor) const;

	friend constexpr Vector3 operator*(float Factor, const Vector3 & Target);
	friend constexpr Vector3 operator/(float Divisor, const Vector3 & Target);

	constexpr Vector3 & operator+=(const Vector3 & Other);
	constexpr Vector3 & operator-=(const Vector3 & Other);
	constexpr Vector3 & operator*=(const Vector3 & Other);
	constexpr Vector3 & operator/=(const Vector3 & Other);
	constexpr Vector3 & operator*=(float Factor);
	constexpr Vector3 & operator/=(float Divisor);

	constexpr bool operator==(const Vector3 & Other) const = default;
	constexpr bool Near(const Vector3 & Other, float Epsilon = 1e-5f) const;

	float Magnitude() const;
	constexpr float MagnitudeSquared() const;
	Vector3 Unit() const;
	constexpr float Dot(const Vector3 & Other) const;
	constexpr Vector3 Cross(const Vector3 & Other) const;
	float Angle(const Vector3 & Other) const;
	float Angle(const Vector3 & Other, const Vector3 & Axis) const;
	constexpr Vector3 Lerp(const Vector3 & Target, float Alpha) const;

	constexpr Vector3 Absolute() const;
	constexpr Vector3 Sign() const;
	constexpr Vector3 Round() const;
	constexpr Vector3 Floor() const;
	constexpr Vector3 Ceil() const;
	constexpr Vector3 Clamp(const Vector3 & Min, const Vector3 & Max) const;

	std::string ToString() const;
	static void Test();
};

//

constexpr Vector3::Vector3(float XYZ) : X{XYZ}, Y{XYZ}, Z{XYZ} {}
constexpr Vector3::Vector3(float X, float Y, float Z) : X{X}, Y{Y}, Z{Z} {}

//



//

constexpr float Vector3::operator[](std::size_t Index) const {
	assert(Index < 3 && "Vector3 index out of bounds!");
	switch (Index % 3) {
		case 2:  return this -> Z;
		case 1:  return this -> Y;
		case 0:
		default: return this -> X;
	}
}

constexpr float & Vector3::operator[](std::size_t Index) {
	assert(Index < 3 && "Vector3 index out of bounds!");
	switch (Index % 3) {
		case 2:  return this -> Z;
		case 1:  return this -> Y;
		case 0:
		default: return this -> X;
	}
}

//

constexpr Vector3 Vector3::operator-() const {
	return Vector3{
		-this -> X,
		-this -> Y,
		-this -> Z
	};
}

constexpr Vector3 Vector3::operator+(const Vector3 & Other) const {
	return Vector3{
		this -> X + Other.X,
		this -> Y + Other.Y,
		this -> Z + Other.Z
	};
}

constexpr Vector3 Vector3::operator-(const Vector3 & Other) const {
	return Vector3{
		this -> X - Other.X,
		this -> Y - Other.Y,
		this -> Z - Other.Z
	};
}

constexpr Vector3 Vector3::operator*(const Vector3 & Other) const {
	return Vector3{
		this -> X * Other.X,
		this -> Y * Other.Y,
		this -> Z * Other.Z
	};
}

constexpr Vector3 Vector3::operator/(const Vector3 & Other) const {
	return Vector3{
		this -> X / Other.X,
		this -> Y / Other.Y,
		this -> Z / Other.Z
	};
}

constexpr Vector3 Vector3::operator*(float Factor) const {
	return Vector3{
		this -> X * Factor,
		this -> Y * Factor,
		this -> Z * Factor
	};
}

constexpr Vector3 Vector3::operator/(float Divisor) const {
	return Vector3{
		this -> X / Divisor,
		this -> Y / Divisor,
		this -> Z / Divisor
	};
}

//

constexpr Vector3 operator*(float Factor, const Vector3 & Target) {
	return Vector3{
		Factor * Target.X,
		Factor * Target.Y,
		Factor * Target.Z
	};
}

constexpr Vector3 operator/(float Divisor, const Vector3 & Target) {
	return Vector3{
		Divisor / Target.X,
		Divisor / Target.Y,
		Divisor / Target.Z
	};
}

//

constexpr Vector3 & Vector3::operator+=(const Vector3 & Other) {
	this -> X += Other.X;
	this -> Y += Other.Y;
	this -> Z += Other.Z;

	return *this;
}

constexpr Vector3 & Vector3::operator-=(const Vector3 & Other) {
	this -> X -= Other.X;
	this -> Y -= Other.Y;
	this -> Z -= Other.Z;

	return *this;
}

constexpr Vector3 & Vector3::operator*=(const Vector3 & Other) {
	this -> X *= Other.X;
	this -> Y *= Other.Y;
	this -> Z *= Other.Z;

	return *this;
}

constexpr Vector3 & Vector3::operator/=(const Vector3 & Other) {
	this -> X /= Other.X;
	this -> Y /= Other.Y;
	this -> Z /= Other.Z;

	return *this;
}

constexpr Vector3 & Vector3::operator*=(float Factor) {
	this -> X *= Factor;
	this -> Y *= Factor;
	this -> Z *= Factor;

	return *this;
}

constexpr Vector3 & Vector3::operator/=(float Divisor) {
	this -> X /= Divisor;
	this -> Y /= Divisor;
	this -> Z /= Divisor;

	return *this;
}

//

constexpr bool Vector3::Near(const Vector3 & Other, float Epsilon) const {
	const auto AbsoluteValue = [] (float Value) constexpr {
		return Value < 0.0f ? -Value : Value;
	};

	return
		AbsoluteValue(this -> X - Other.X) <= Epsilon &&
		AbsoluteValue(this -> Y - Other.Y) <= Epsilon &&
		AbsoluteValue(this -> Z - Other.Z) <= Epsilon;
}

//

constexpr float Vector3::MagnitudeSquared() const {
	return this -> X * this -> X + this -> Y * this -> Y + this -> Z * this -> Z;
}

constexpr float Vector3::Dot(const Vector3 & Other) const {
	return this -> X * Other.X + this -> Y * Other.Y + this -> Z * Other.Z;
}

constexpr Vector3 Vector3::Cross(const Vector3 & Other) const {
	return Vector3{
		(this -> Y * Other.Z) - (this -> Z * Other.Y),
		(this -> Z * Other.X) - (this -> X * Other.Z),
		(this -> X * Other.Y) - (this -> Y * Other.X)
	};
}

constexpr Vector3 Vector3::Lerp(const Vector3 & Target, float Alpha) const {
	return *this + (Target - *this) * Alpha;
}

//

constexpr Vector3 Vector3::Absolute() const {
	const auto AbsoluteValue = [] (float Value) constexpr {
		return Value < 0.0f ? -Value : Value;
	};

	return Vector3{
		AbsoluteValue(this -> X),
		AbsoluteValue(this -> Y),
		AbsoluteValue(this -> Z)
	};
}

constexpr Vector3 Vector3::Sign() const {
	const auto SignValue = [] (float Value) constexpr {
		return static_cast <float> ((Value > 0) - (Value < 0));
	};

	return Vector3{
		SignValue(this -> X),
		SignValue(this -> Y),
		SignValue(this -> Z)
	};
}

constexpr Vector3 Vector3::Round() const {
	const auto RoundValue = [] (float Value) constexpr {
		return static_cast <float> (Value >= 0.0f ? static_cast <int> (Value + 0.5f) : static_cast <int> (Value - 0.5f));
	};

	return Vector3{
		RoundValue(this -> X),
		RoundValue(this -> Y),
		RoundValue(this -> Z)
	};
}

constexpr Vector3 Vector3::Floor() const {
	const auto FloorValue = [] (float Value) constexpr {
		const int Integer = static_cast <int> (Value);
		return static_cast <float> (Value < 0.0f && Value != static_cast <float>(Integer) ? Integer - 1 : Integer);
	};

	return Vector3{
		FloorValue(this -> X),
		FloorValue(this -> Y),
		FloorValue(this -> Z)
	};
}

constexpr Vector3 Vector3::Ceil() const {
	const auto CeilValue = [] (float Value) constexpr {
		const int Integer = static_cast <int> (Value);
		return static_cast <float> (Value > 0.0f && Value != static_cast <float> (Integer) ? Integer + 1 : Integer);
	};

	return Vector3{
		CeilValue(this -> X),
		CeilValue(this -> Y),
		CeilValue(this -> Z)
	};
}

constexpr Vector3 Vector3::Clamp(const Vector3 & Min, const Vector3 & Max) const {
	const auto ClampValue = [] (float Value, float Min, float Max) constexpr {
		return Value < Min ? Min : (Value > Max ? Max : Value);
	};

	return Vector3{
		ClampValue(this -> X, Min.X, Max.X),
		ClampValue(this -> Y, Min.Y, Max.Y),
		ClampValue(this -> Z, Min.Z, Max.Z)
	};
}
