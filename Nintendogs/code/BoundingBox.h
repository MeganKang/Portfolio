#pragma once
#include <glm/glm.hpp>
#include <limits>

/**
 * @brief Represents an axis-aligned bounding box (AABB) in 3D space.
 */
struct BoundingBox {
    glm::vec3 min;
    glm::vec3 max;

    BoundingBox() :
        min(glm::vec3(std::numeric_limits<float>::max())),
        max(glm::vec3(std::numeric_limits<float>::lowest())) {}
};
