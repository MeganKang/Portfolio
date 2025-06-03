#pragma once
#include "Object3D.h"
#include "Animation.h"
#include <glm/glm.hpp>

/**
 * @brief Rotates an object at a continuous rate over an interval and loops forever.
 */
class LoopingRotationAnimation : public Animation {
private:
    glm::vec3 m_perSecond;  // How much to increment the orientation per second
    float_t m_duration;     // Duration of one full rotation
    float_t m_elapsedTime = 0.0f;  // Tracks elapsed time

    /**
     * @brief Advance the animation by the given time interval.
     */
    void applyAnimation(float_t dt) override {
        m_elapsedTime += dt;

        // Rotate the object based on the per-second increment
        object().rotate(m_perSecond * dt);

        // Check if the current cycle has completed
        if (m_elapsedTime >= m_duration) {
            m_elapsedTime = 0.0f;  // Reset elapsed time for the next loop
        }
    }

public:
    /**
     * @brief Constructs a looping rotation animation with the given total rotation angle
     * and interpolates across the specified duration.
     */
    LoopingRotationAnimation(Object3D& object, float_t duration, const glm::vec3& totalRotation)
        : Animation(object, duration), m_perSecond(totalRotation / duration), m_duration(duration) {}
};
