#pragma once

#include <cstdint>

struct Vector2U
{
	uint32_t x = 0;
	uint32_t y = 0;

	Vector2U(uint32_t _x, uint32_t _y) { x = _x; y = _y; }
};