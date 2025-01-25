#pragma once
#include "../config.h"
#include <vector>
#include <glm/vec3.hpp>
#include <array> 
struct HitBoxComponentTerrain
{
    unsigned int vertexCount;               // Number of raw vertices
    std::vector<glm::vec3> vertices;        // List of raw vertices from "v" lines

    unsigned int triangleCount;             // Number of triangles (faces with 3 vertices)
    std::vector<std::array<glm::vec3, 3>> triangles; // Each triangle has 3 glm::vec3 vertices
};
