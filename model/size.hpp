#pragma once

template <typename T>
struct Size
{
    typedef Size<T> MyType;

    Size(const T &width = T(), const T &height = T()):
        _width(width),
        _height(height)
    {
    }

    T getAspectRatio() const
    {
        T aspectRatio = _width  / _height;
        return aspectRatio;
    }

    T _width;
    T _height;
};
