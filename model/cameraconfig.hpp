#pragma once

#include "size.hpp"

struct CameraConfig
{
    SizeGL _nearSize = {1.f, 1.f};
    float _frustumDepth = 1000.f;
    float _speed = 15.f;
    uint16_t FOV = 90;
};
