// PauseAnimation.h

#pragma once
#include <glm/glm.hpp>
#include "Object3D.h"
#include "Animation.h"

class PauseAnimation : public Animation {
public:
    PauseAnimation(Object3D& object, float duration)
        : Animation(object, duration) {}

    void applyAnimation(float dt) override {
        // Do nothing
    }
};
