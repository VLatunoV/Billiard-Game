#pragma once

namespace math
{
struct Vector2d {
	constexpr Vector2d() noexcept = default;
	constexpr Vector2d(float _x, float _y) noexcept: x{_x}, y{_y} {}
	constexpr Vector2d(const Vector2d&) noexcept = default;
	constexpr Vector2d(Vector2d&&) noexcept = default;

	Vector2d& operator=(const Vector2d&) noexcept = default;
	Vector2d& operator=(Vector2d&&) noexcept = default;

	inline Vector2d& operator+=(const Vector2d& other) noexcept;
	inline Vector2d& operator-=(const Vector2d& other) noexcept;
	inline Vector2d& operator*=(float scalar) noexcept;
	inline Vector2d& operator/=(float scalar);

	inline Vector2d perp() const noexcept;

	float x{};
	float y{};
};

inline Vector2d& Vector2d::operator+=(const Vector2d& other) noexcept {
	x += other.x;
	y += other.y;
	return *this;
}

inline Vector2d& Vector2d::operator-=(const Vector2d& other) noexcept {
	x -= other.x;
	y -= other.y;
	return *this;
}

inline Vector2d& Vector2d::operator*=(float scalar) noexcept {
	x *= scalar;
	y *= scalar;
	return *this;
}

inline Vector2d& Vector2d::operator/=(float scalar) {
	return *this *= (1.0f / scalar);
}

inline Vector2d Vector2d::perp() const noexcept {
	return {-y, x};
}

// =========================================================================================
// Binary operators
// =========================================================================================

[[nodiscard]] inline Vector2d operator+(Vector2d lhs, const Vector2d& rhs) noexcept {
	return lhs += rhs;
}

[[nodiscard]] inline Vector2d operator-(Vector2d lhs, const Vector2d& rhs) noexcept {
	return lhs -= rhs;
}

[[nodiscard]] inline Vector2d operator*(Vector2d lhs, float rhs) noexcept {
	return lhs *= rhs;
}

[[nodiscard]] inline Vector2d operator*(float lhs, Vector2d rhs) noexcept {
	return rhs *= lhs;
}

[[nodiscard]] inline Vector2d operator/(Vector2d lhs, float rhs) {
	return lhs /= rhs;
}

[[nodiscard]] inline Vector2d operator/(float lhs, Vector2d rhs) {
	return rhs /= lhs;
}

// =========================================================================================
// Unary operators
// =========================================================================================

[[nodiscard]] inline Vector2d operator-(Vector2d lhs) noexcept {
	return {-lhs.x, -lhs.y};
}

// =========================================================================================
// Vector functions
// =========================================================================================

[[nodiscard]] inline float dot(const Vector2d& lhs, const Vector2d& rhs) noexcept {
	return lhs.x*rhs.x + lhs.y*rhs.y;
}

[[nodiscard]] inline float cross(const Vector2d& lhs, const Vector2d& rhs) noexcept {
	return lhs.x*rhs.y - lhs.y*rhs.x;
}

[[nodiscard]] inline Vector2d perp(const Vector2d& lhs) noexcept {
	return lhs.perp();
}
} // namespace math
