#pragma once
#include <algorithm>

template <typename T>
struct Rect {
    Rect() noexcept = default;
    Rect(T _x0, T _y0, T _x1, T _y1) noexcept
        : x0{std::min<T>(_x0, _x1)}
        , y0{std::min<T>(_y0, _y1)}
        , x1{std::max<T>(_x0, _x1)}
        , y1{std::max<T>(_y0, _y1)}
    {}
    Rect(const Rect&) noexcept = default;
    Rect(Rect&&) noexcept = default;

    Rect& operator=(const Rect&) = default;
    Rect& operator=(Rect&&) = default;

    T Width() const noexcept { return x1-x0; }
    T Height() const noexcept { return y1-y0; }

    Rect& Union(const Rect& other) noexcept {
        if (other.x0 < x0) x0 = other.x0;
        if (other.y0 < y0) y0 = other.y0;
        if (other.x1 > x1) x1 = other.x1;
        if (other.y1 > y1) y1 = other.y1;
        return *this;
    }

    T x0{};
    T y0{};
    T x1{};
    T y1{};
};

using RectInt = Rect<int>;
using RectFloat = Rect<float>;
