#pragma once

struct Vector2 {
	// TBA
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
	constexpr explicit Vector3(float XYZ);
	constexpr Vector3(float X, float Y, float Z);

	constexpr Vector3 operator+(Vector3 Other) const;
	constexpr Vector3 operator-(Vector3 Other) const;
	constexpr Vector3 operator*(Vector3 Other) const;
	constexpr Vector3 operator/(Vector3 Other) const;

	constexpr Vector3 operator*(float Scalar) const;
	constexpr friend Vector3 operator*(float Scalar, Vector3 Other);

	constexpr Vector3 operator/(float Scalar) const;
	constexpr friend Vector3 operator/(float Scalar, Vector3 Other);

	constexpr Vector3 operator -() const;

	constexpr float operator[](int Index) const;
	constexpr float & operator[](int Index);

	constexpr float Magnitude() const;
	constexpr float MagnitudeSquared() const;

	constexpr Vector3 Unit() const;

	constexpr float Dot(Vector3 Other) const;
	constexpr Vector3 Cross(Vector3 Other) const;

	constexpr Vector3 Lerp(Vector3 Other, float Alpha) const;
};

struct Vector4 {
	// TBA
};
