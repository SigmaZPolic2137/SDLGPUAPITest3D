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

	constexpr Vector3 operator+(const Vector3 & Other) const;
	constexpr Vector3 operator-(const Vector3 & Other) const;
	constexpr Vector3 operator*(const Vector3 & Other) const;
	constexpr Vector3 operator/(const Vector3 & Other) const;

	constexpr Vector3 operator*(float Factor) const;
	friend constexpr Vector3 operator*(float Factor, const Vector3 & Target);

	constexpr Vector3 operator/(float Divisor) const;
	friend constexpr Vector3 operator/(float Divisor, const Vector3 & Target);

	constexpr Vector3 operator-() const;

	constexpr float operator[](std::size_t Index) const;
	constexpr float & operator[](std::size_t Index);

	float Magnitude() const;
	constexpr float MagnitudeSquared() const;

	Vector3 Unit() const;

	constexpr float Dot(const Vector3 & Other) const;
	constexpr Vector3 Cross(const Vector3 & Other) const;

	constexpr Vector3 Lerp(const Vector3 & Target, float Alpha) const;
	constexpr Vector3 Clamp(const Vector3 & Min, const Vector3 & Max) const;

	std::string ToString() const;
};

constexpr Vector3::Vector3() : Data{0.0f, 0.0f, 0.0f} {}
constexpr Vector3::Vector3(float XYZ) : Data {XYZ, XYZ, XYZ} {}
constexpr Vector3::Vector3(float X, float Y, float Z) : Data{X, Y, Z} {}

constexpr float Vector3::X() const {
	return Data[0];
}

constexpr float Vector3::Y() const {
	return Data[1];
}

constexpr float Vector3::Z() const {
	return Data[2];
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

constexpr Vector3 operator*(float Factor, const Vector3 & Target) {
	return Vector3(
		Factor * Target.X(),
		Factor * Target.Y(),
		Factor * Target.Z()
	);
}

constexpr Vector3 Vector3::operator/(float Divisor) const {
	return Vector3(
		this -> X() / Divisor,
		this -> Y() / Divisor,
		this -> Z() / Divisor
	);
}

constexpr Vector3 operator/(float Divisor, const Vector3 & Target) {
	return Vector3(
		Divisor / Target.X(),
		Divisor / Target.Y(),
		Divisor / Target.Z()
	);
}

constexpr Vector3 Vector3::operator-() const {
	return Vector3(
		-this -> X(),
		-this -> Y(),
		-this -> Z()
	);
}

constexpr float Vector3::operator[](std::size_t Index) const {
	return this -> Data[Index];
}

constexpr float & Vector3::operator[](std::size_t Index) {
	return this -> Data[Index];
}

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

constexpr Vector3 Vector3::Clamp(const Vector3 & Min, const Vector3 & Max) const {
	return Vector3(
		this -> X() < Min.X() ? Min.X() : (this -> X() > Max.X() ? Max.X() : this -> X()),
		this -> Y() < Min.Y() ? Min.Y() : (this -> Y() > Max.Y() ? Max.Y() : this -> Y()),
		this -> Z() < Min.Z() ? Min.Z() : (this -> Z() > Max.Z() ? Max.Z() : this -> Z())
	);
}

void Vector3Test();
