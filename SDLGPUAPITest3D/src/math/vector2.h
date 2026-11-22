#pragma once

#include <cassert>
#include <string>

struct alignas(8) Vector2 {
	float X{0.0f};
	float Y{0.0f};

	constexpr Vector2() = default;
	constexpr explicit Vector2(float XY);
	constexpr Vector2(float X, float Y);

	static constexpr Vector2 Zero() { return Vector2 {0.0f, 0.0f}; }
	static constexpr Vector2 One() { return Vector2 {1.0f, 1.0f}; }
	static constexpr Vector2 Right() { return Vector2 {1.0f, 0.0f}; }
	static constexpr Vector2 Left() { return Vector2 {-1.0f, 0.0f}; }
	static constexpr Vector2 Up() { return Vector2 {0.0f, 1.0f}; }
	static constexpr Vector2 Down() { return Vector2 {0.0f, -1.0f}; }

	constexpr float operator[](std::size_t Index) const;
	constexpr float & operator[](std::size_t Index);

	constexpr const float * Data() const;
	constexpr float * Data();

	constexpr Vector2 operator-() const;
	constexpr Vector2 operator+(const Vector2 & Other) const;
	constexpr Vector2 operator-(const Vector2 & Other) const;
	constexpr Vector2 operator*(const Vector2 & Other) const;
	constexpr Vector2 operator/(const Vector2 & Other) const;
	constexpr Vector2 operator*(float Factor) const;
	constexpr Vector2 operator/(float Divisor) const;

	friend constexpr Vector2 operator*(float Factor, const Vector2 & Target);
	friend constexpr Vector2 operator/(float Divisor, const Vector2 & Target);

	constexpr Vector2 & operator+=(const Vector2 & Other);
	constexpr Vector2 & operator-=(const Vector2 & Other);
	constexpr Vector2 & operator*=(const Vector2 & Other);
	constexpr Vector2 & operator/=(const Vector2 & Other);
	constexpr Vector2 & operator*=(float Factor);
	constexpr Vector2 & operator/=(float Divisor);

	constexpr bool operator==(const Vector2 & Other) const = default;
	constexpr bool Near(const Vector2 & Other, float Epsilon = 1e-5f) const;

	float Magnitude() const;
	constexpr float MagnitudeSquared() const;
	Vector2 Unit() const;
	constexpr float Dot(const Vector2 & Other) const;
	constexpr float Cross(const Vector2 & Other) const;
	float Angle(const Vector2 & Other, bool Sign = false) const;
	constexpr Vector2 Lerp(const Vector2 & Target, float Alpha) const;

	constexpr Vector2 Absolute() const;
	constexpr Vector2 Sign() const;
	constexpr Vector2 Round() const;
	constexpr Vector2 Floor() const;
	constexpr Vector2 Ceil() const;
	constexpr Vector2 Clamp(const Vector2 & Min, const Vector2 & Max) const;

	std::string ToString() const;
	static void Test();
};

//

constexpr Vector2::Vector2(float XY) : X {XY}, Y {XY} {}
constexpr Vector2::Vector2(float X, float Y) : X {X}, Y {Y} {}

//

constexpr const float * Vector2::Data() const {
	return &this -> X;
}

constexpr float * Vector2::Data() {
	return &this -> X;
}

//

constexpr float Vector2::operator[](std::size_t Index) const {
	assert(Index < 2 && "Vector2 index out of bounds!");

	switch (Index % 2) {
		case 1:  return this -> Y;
		case 0:
		default: return this -> X;
	}
}

constexpr float & Vector2::operator[](std::size_t Index) {
	assert(Index < 2 && "Vector2 index out of bounds!");

	switch (Index % 2) {
		case 1:  return this -> Y;
		case 0:
		default: return this -> X;
	}
}

//

constexpr Vector2 Vector2::operator-() const {
	return Vector2{
		-this -> X,
		-this -> Y
	};
}

constexpr Vector2 Vector2::operator+(const Vector2 & Other) const {
	return Vector2{
		this -> X + Other.X,
		this -> Y + Other.Y
	};
}

constexpr Vector2 Vector2::operator-(const Vector2 & Other) const {
	return Vector2{
		this -> X - Other.X,
		this -> Y - Other.Y
	};
}

constexpr Vector2 Vector2::operator*(const Vector2 & Other) const {
	return Vector2{
		this -> X * Other.X,
		this -> Y * Other.Y
	};
}

constexpr Vector2 Vector2::operator/(const Vector2 & Other) const {
	return Vector2{
		this -> X / Other.X,
		this -> Y / Other.Y
	};
}

constexpr Vector2 Vector2::operator*(float Factor) const {
	return Vector2{
		this -> X * Factor,
		this -> Y * Factor
	};
}

constexpr Vector2 Vector2::operator/(float Divisor) const {
	return Vector2{
		this -> X / Divisor,
		this -> Y / Divisor
	};
}

//

constexpr Vector2 operator*(float Factor, const Vector2 & Target) {
	return Vector2{
		Factor * Target.X,
		Factor * Target.Y
	};
}

constexpr Vector2 operator/(float Divisor, const Vector2 & Target) {
	return Vector2{
		Divisor / Target.X,
		Divisor / Target.Y
	};
}

//

constexpr Vector2 & Vector2::operator+=(const Vector2 & Other) {
	this -> X += Other.X;
	this -> Y += Other.Y;

	return *this;
}

constexpr Vector2 & Vector2::operator-=(const Vector2 & Other) {
	this -> X -= Other.X;
	this -> Y -= Other.Y;
	
	return *this;
}

constexpr Vector2 & Vector2::operator*=(const Vector2 & Other) {
	this -> X *= Other.X;
	this -> Y *= Other.Y;

	return *this;
}

constexpr Vector2 & Vector2::operator/=(const Vector2 & Other) {
	this -> X /= Other.X;
	this -> Y /= Other.Y;

	return *this;
}

constexpr Vector2 & Vector2::operator*=(float Factor) {
	this -> X *= Factor;
	this -> Y *= Factor;

	return *this;
}

constexpr Vector2 & Vector2::operator/=(float Divisor) {
	this -> X /= Divisor;
	this -> Y /= Divisor;

	return *this;
}

//

constexpr bool Vector2::Near(const Vector2 & Other, float Epsilon) const {
	const auto AbsoluteValue = [] (float Value) constexpr {
		return Value < 0.0f ? -Value : Value;
	};

	return
		AbsoluteValue(this -> X - Other.X) <= Epsilon &&
		AbsoluteValue(this -> Y - Other.Y) <= Epsilon;
}

//

constexpr float Vector2::MagnitudeSquared() const {
	return this -> X * this -> X + this -> Y * this -> Y;
}
