#pragma once
#include <iostream>
#include <bitset>
#include <math.h>

template <typename V>
class Vector2
{
  public:
	V x;
	V y;

	Vector2<V>() {}
	Vector2<V>(V x, V y)
	{
		this->x = x;
		this->y = y;
	}

	template <typename U>
	Vector2<V>(Vector2<U> u) : x{(V)u.x}, y{(V)u.y} {};

	template <typename U>
	Vector2<V> &operator+=(const Vector2<U> &b)
	{
		this->x += b.x;
		this->y += b.y;
		return *this;
	}
	template <typename U>
	Vector2<V> &operator-=(const Vector2<U> &b)
	{
		this->x -= b.x;
		this->y -= b.y;
		return *this;
	}
	template <typename U>
	Vector2<V> operator+(const Vector2<U> &b) const
	{
		Vector2<V> v;
		v.x = this->x + b.x;
		v.y = this->y + b.y;
		return v;
	}
	template <typename U>
	Vector2<V> operator-(const Vector2<U> &b) const
	{
		Vector2<V> v;
		v.x = this->x - b.x;
		v.y = this->y - b.y;
		return v;
	}
	template <typename U>
	bool operator!=(const Vector2<U> &b) const
	{
		if (this->x != b.x || this->y != b.y) { return true; }
		else { return false; }
	}
	template <typename U>
	bool operator==(const Vector2<U> &b) const
	{
		if (this->x == b.x && this->y == b.y) { return true; }
		else { return false; }
	}
	Vector2<V> &operator*=(const float &b)
	{
		this->x *= b;
		this->y *= b;
		return *this;
	}
	Vector2<V> operator*(const float &b) const
	{
		Vector2<V> v;
		v.x = this->x * b;
		v.y = this->y * b;
		return v;
	}
	Vector2<V> &operator/=(const float &b)
	{
		this->x /= b;
		this->y /= b;
		return *this;
	}
	Vector2<V> operator/(const float &b) const
	{
		Vector2<V> v;
		v.x = this->x / b;
		v.y = this->y / b;
		return v;
	}

	inline void Print() const { std::cout << this->x << ", " << this->y << std::endl; }
	inline float Magnitude() const { return std::sqrt((this->x * this->x) + (this->y * this->y)); }
	inline void Normalize(float s = 1)
	{
		float m = Magnitude();
		if (m == 0)
		{
			return;
		}
		this->x /= m;
		this->y /= m;
		this->x *= s;
		this->y *= s;
	}
	inline Vector2<float> Normalized(float s = 1) const
	{
		Vector2<float> v = *this;
		if (v.Magnitude() == 0) { return v; }
		v *= s / v.Magnitude();
		return v;
	}
	inline Vector2<float> BoxNormalized(float s) const
	{
		Vector2<float> v = *this;
		if (v.Magnitude() == 0) { return v; }
		v *= s / 32768;
		return v;
	}
};

struct Vector2_Hasher
{
	inline size_t operator()(const Vector2<int> &obj) const
	{
		long h = obj.x;
		h = h << 16;
		h += obj.y;
		return h;
	}
};
struct Vector2_Comparator
{
	inline bool operator()(const Vector2<int> &obj1, const Vector2<int> &obj2) const
	{
		if (obj1.x == obj2.x && obj1.y == obj2.y) { return true; }
		return false;
	}
};
