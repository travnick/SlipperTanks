#include "emptymodel3d.hpp"

EmptyModel3D &EmptyModel3D::getStaticGlobalInstance()
{
    static EmptyModel3D model;

    return model;
}
