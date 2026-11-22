#include "vector2.h"

#include <cmath>

float Vector2::Magnitude() const {
	return std::sqrtf(this -> MagnitudeSquared());
}
