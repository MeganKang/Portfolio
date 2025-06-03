#include "Animation.h"
#include "Object3D.h"
#include <glm/glm.hpp>
#include <cmath>

/**
 * @brief An animation that tilts an object from side to side in a graceful manner.
 */
class TiltAnimation : public Animation {
private:
    float_t m_duration;      // Total duration of the tilt animation
    float_t m_elapsedTime;   // Time passed since animation started
    float_t m_angle;         // Maximum tilt angle in degrees
    float_t m_frequency;     // How many tilts per second
    glm::vec3 m_originalOrientation;  // Original orientation of the object

    /**
     * @brief Advance the animation by the given time interval.
     */
    void applyAnimation(float_t dt) override {
        m_elapsedTime += dt;

        // Calculate the tilt angle using a sine wave
        float_t tiltAngle = m_angle * std::sin(m_frequency * m_elapsedTime * glm::two_pi<float>());

        // Apply the tilt by rotating around the Z-axis (yaw)
        glm::vec3 newOrientation = m_originalOrientation;
        newOrientation.z += tiltAngle;

        object().setOrientation(newOrientation);

        // Reset the object's orientation to the original after the animation ends
        if (m_elapsedTime >= m_duration) {
            object().setOrientation(m_originalOrientation);
            m_elapsedTime = 0.0f;  // Reset elapsed time to enable looping or continuation
        }
    }

public:
    /**
     * @brief Constructs a tilt animation.
     * @param object The object to animate.
     * @param duration Total duration of the animation.
     * @param angle Maximum tilt angle in degrees.
     * @param frequency Number of tilts per second.
     */
    TiltAnimation(Object3D& object, float_t duration, float_t angle, float_t frequency)
        : Animation(object, duration), m_duration(duration), m_elapsedTime(0.0f),
        m_angle(angle), m_frequency(frequency) {
        m_originalOrientation = object.getOrientation();  // Store the object's initial orientation
    }
};
