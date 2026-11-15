#pragma once

#include <string>

struct Vector2 {
	// TBA
};

struct Vector3 {
	float Data[3];

	constexpr Vector3();
	constexpr explicit Vector3(float XYZ);
	constexpr Vector3(float X, float Y, float Z);

	constexpr float X() const;
	constexpr float Y() const;
	constexpr float Z() const;
	constexpr float & X();
	constexpr float & Y();
	constexpr float & Z();
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
	float Angle(const Vector3 & Other, const Vector3 & Axis) const;
	constexpr Vector3 Lerp(const Vector3 & Target, float Alpha) const;

	constexpr Vector3 Absolute() const;
	constexpr Vector3 Round() const;
	constexpr Vector3 Floor() const;
	constexpr Vector3 Ceil() const;
	constexpr Vector3 Clamp(const Vector3 & Min, const Vector3 & Max) const;

	std::string ToString() const;
};

//

constexpr Vector3::Vector3() : Data{0.0f, 0.0f, 0.0f} {}
constexpr Vector3::Vector3(float XYZ) : Data {XYZ, XYZ, XYZ} {}
constexpr Vector3::Vector3(float X, float Y, float Z) : Data{X, Y, Z} {}

//

constexpr float Vector3::X() const { return Data[0]; }
constexpr float Vector3::Y() const { return Data[1]; }
constexpr float Vector3::Z() const { return Data[2]; }

constexpr float & Vector3::X() { return Data[0]; }
constexpr float & Vector3::Y() { return Data[1]; }
constexpr float & Vector3::Z() { return Data[2]; }

constexpr float Vector3::operator[](std::size_t Index) const { return this -> Data[Index]; }
constexpr float & Vector3::operator[](std::size_t Index) { return this -> Data[Index]; }

//

constexpr Vector3 Vector3::operator-() const {
	return Vector3(
		-this -> X(),
		-this -> Y(),
		-this -> Z()
	);
}

constexpr Vector3 Vector3::operator+(const Vector3 & Other) const {
	return Vector3(
		this -> X() + Other.X(),
		this -> Y() + Other.Y(),
		this -> Z() + Other.Z()
	);
}

constexpr Vector3 Vector3::operator-(const Vector3 & Other) const {
	return Vector3(
		this -> X() - Other.X(),
		this -> Y() - Other.Y(),
		this -> Z() - Other.Z()
	);
}

constexpr Vector3 Vector3::operator*(const Vector3 & Other) const {
	return Vector3(
		this -> X() * Other.X(),
		this -> Y() * Other.Y(),
		this -> Z() * Other.Z()
	);
}

constexpr Vector3 Vector3::operator/(const Vector3 & Other) const {
	return Vector3(
		this -> X() / Other.X(),
		this -> Y() / Other.Y(),
		this -> Z() / Other.Z()
	);
}

constexpr Vector3 Vector3::operator*(float Factor) const {
	return Vector3(
		this -> X() * Factor,
		this -> Y() * Factor,
		this -> Z() * Factor
	);
}

constexpr Vector3 Vector3::operator/(float Divisor) const {
	return Vector3(
		this -> X() / Divisor,
		this -> Y() / Divisor,
		this -> Z() / Divisor
	);
}

//

constexpr Vector3 operator*(float Factor, const Vector3 & Target) {
	return Vector3(
		Factor * Target.X(),
		Factor * Target.Y(),
		Factor * Target.Z()
	);
}

constexpr Vector3 operator/(float Divisor, const Vector3 & Target) {
	return Vector3(
		Divisor / Target.X(),
		Divisor / Target.Y(),
		Divisor / Target.Z()
	);
}

//

constexpr Vector3 & Vector3::operator+=(const Vector3 & Other) {
	this -> X() += Other.X();
	this -> Y() += Other.Y();
	this -> Z() += Other.Z();

	return *this;
}

constexpr Vector3 & Vector3::operator-=(const Vector3 & Other) {
	this -> X() -= Other.X();
	this -> Y() -= Other.Y();
	this -> Z() -= Other.Z();

	return *this;
}

constexpr Vector3 & Vector3::operator*=(const Vector3 & Other) {
	this -> X() *= Other.X();
	this -> Y() *= Other.Y();
	this -> Z() *= Other.Z();

	return *this;
}

constexpr Vector3 & Vector3::operator/=(const Vector3 & Other) {
	this -> X() /= Other.X();
	this -> Y() /= Other.Y();
	this -> Z() /= Other.Z();

	return *this;
}

constexpr Vector3 & Vector3::operator*=(float Factor) {
	this -> X() *= Factor;
	this -> Y() *= Factor;
	this -> Z() *= Factor;

	return *this;
}

constexpr Vector3 & Vector3::operator/=(float Divisor) {
	this -> X() /= Divisor;
	this -> Y() /= Divisor;
	this -> Z() /= Divisor;

	return *this;
}

//

constexpr bool Vector3::Near(const Vector3 & Other, float Epsilon) const {
	const auto AbsoluteValue = [] (float Value) constexpr {
		return Value < 0.0f ? -Value : Value;
	};

	return
		AbsoluteValue(X() - Other.X()) <= Epsilon &&
		AbsoluteValue(Y() - Other.Y()) <= Epsilon &&
		AbsoluteValue(Z() - Other.Z()) <= Epsilon;
}

//

constexpr float Vector3::MagnitudeSquared() const {
	return this -> X() * this -> X() + this -> Y() * this -> Y() + this -> Z() * this -> Z();
}

constexpr float Vector3::Dot(const Vector3 & Other) const {
	return this -> X() * Other.X() + this -> Y() * Other.Y() + this -> Z() * Other.Z();
}

constexpr Vector3 Vector3::Cross(const Vector3 & Other) const {
	return Vector3(
		(this -> Y() * Other.Z()) - (this -> Z() * Other.Y()),
		(this -> Z() * Other.X()) - (this -> X() * Other.Z()),
		(this -> X() * Other.Y()) - (this -> Y() * Other.X())
	);
}

constexpr Vector3 Vector3::Lerp(const Vector3 & Target, float Alpha) const {
	return *this + (Target - *this) * Alpha;
}

//

constexpr Vector3 Vector3::Absolute() const {
	const auto AbsoluteValue = [] (float Value) constexpr {
		return Value < 0.0f ? -Value : Value;
	};

	return Vector3(
		AbsoluteValue(X()),
		AbsoluteValue(Y()),
		AbsoluteValue(Z())
	);
}

constexpr Vector3 Vector3::Round() const {
	const auto RoundValue = [] (float Value) constexpr {
		return static_cast <float> (Value >= 0.0f ? static_cast <int> (Value + 0.5f) : static_cast <int> (Value - 0.5f));
	};

	return Vector3(
		RoundValue(X()),
		RoundValue(Y()),
		RoundValue(Z())
	);
}

constexpr Vector3 Vector3::Floor() const {
	const auto FloorValue = [] (float Value) constexpr {
		const int Integer = static_cast <int> (Value);
		return static_cast <float> (Value < 0.0f && Value != static_cast <float> (Integer) ? Integer - 1 : Integer);
	};

	return Vector3(
		FloorValue(X()),
		FloorValue(Y()),
		FloorValue(Z())
	);
}

constexpr Vector3 Vector3::Ceil() const {
	const auto CeilValue = [] (float Value) constexpr {
		const int Integer = static_cast <int> (Value);
		return static_cast <float> (Value > 0.0f && Value != static_cast <float> (Integer) ? Integer + 1 : Integer);
	};

	return Vector3(
		CeilValue(X()),
		CeilValue(Y()),
		CeilValue(Z())
	);
}

constexpr Vector3 Vector3::Clamp(const Vector3 & Min, const Vector3 & Max) const {
	const auto ClampValue = [] (float Value, float Min, float Max) constexpr {
		return Value < Min ? Min : (Value > Max ? Max : Value);
	};

	return Vector3(
		ClampValue(this -> X(), Min.X(), Max.X()),
		ClampValue(this -> Y(), Min.Y(), Max.Y()),
		ClampValue(this -> Z(), Min.Z(), Max.Z())
	);
}

//

void Vector3Test();
