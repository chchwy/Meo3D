#pragma once

#include <cstdint>

struct Vector2U
{
	uint32_t x = 0;
	uint32_t y = 0;

	Vector2U(uint32_t _x, uint32_t _y) { x = _x; y = _y; }
};

struct Float2
{
	float x = 0.f;
	float y = 0.f;
	Float2() {}
	Float2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

struct Float3
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	Float3() {}
	Float3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};


struct Float4
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;

	Float4() {}
	Float4(float _x, float _y, float _z, float _w = 0.f)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	Float4(Float3 f3)
	{
		x = f3.x;
		y = f3.y;
		z = f3.z;
		w = 1.f;
	}
};
