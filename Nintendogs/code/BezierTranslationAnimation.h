#pragma once

#include <glm/glm.hpp>
#include "Object3D.h"
#include "Animation.h"

class BezierTranslationAnimation : public Animation {
private:
    glm::vec3 m_start;
    glm::vec3 m_control;
    glm::vec3 m_end;

    glm::vec3 calcPoint(float_t t) const {
        float time_left = 1.0f - t;
        return m_start * (time_left * time_left) +
            m_control * (2 * time_left * t) +
            m_end * (t * t);
    }

    void applyAnimation(float_t dt) override {
        float t = currentTime() / duration();
        if (t > 1.0f) {
            t = 1.0f;
            object().setPosition(m_end);
        }
        glm::vec3 newPosition = calcPoint(t);
        object().setPosition(newPosition);
    }
public:
    BezierTranslationAnimation(Object3D& object, float_t duration,
        const glm::vec3& start,
        const glm::vec3& control,
        const glm::vec3& end) : Animation(object, duration),
        m_start(start),
        m_control(control),
        m_end(end) {}
};