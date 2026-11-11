#pragma once

struct Vector2 {

};

struct Vector3 {
	union {
		struct {
			float X;
			float Y;
			float Z;
		};

		float Data[3];
	};

	constexpr Vector3();
	constexpr explicit Vector3(float);
	constexpr Vector3(float, float, float);

	constexpr Vector3 operator+(Vector3) const;
	constexpr Vector3 operator-(Vector3) const;
	constexpr Vector3 operator*(Vector3) const;
	constexpr Vector3 operator/(Vector3) const;

	constexpr Vector3 operator*(float) const;
	constexpr friend Vector3 operator*(float, Vector3);

	constexpr Vector3 operator/(float) const;
	constexpr friend Vector3 operator/(float, Vector3);

	constexpr Vector3 operator -() const;

	constexpr float operator[](int) const;
	constexpr float & operator[](int);

	constexpr float Magnitude() const;
	constexpr float MagnitudeSquared() const;

	constexpr Vector3 Unit() const;

	constexpr float Dot(Vector3) const;
	constexpr Vector3 Cross(Vector3) const;
};

struct Vector4 {

};
