#pragma once
#include "../config.h"

struct HitBoxComponent
{
    unsigned int vertexCount;
    std::vector<glm::vec3> vertices;
};