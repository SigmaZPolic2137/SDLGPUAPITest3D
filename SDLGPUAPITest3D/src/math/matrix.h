#pragma once

#include "vector4.h"

struct alignas(16) Matrix {
	Vector4 Columns[4];
};
