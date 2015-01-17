#pragma once

#include "model3d.hpp"

class EmptyModel3D : public Model3D
{
public:
    void initialize() override
    {
    }

    void render() override
    {
    }

    static EmptyModel3D &getStaticGlobalInstance();
};
