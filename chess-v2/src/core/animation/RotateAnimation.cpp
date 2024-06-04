#include "RotateAnimation.h"

RotateAnimation::RotateAnimation(View::Shared view) : Animation(std::move(view)) {

}

RotateAnimation::RotateAnimation(View::Shared view, Interpolator::Unique &&interpolator) : Animation(std::move(view),
                                                                                                     std::move(interpolator)) {

}

void RotateAnimation::DriveAnimation(AnimationDriverVisitor &visitor, float dt) {
    float new_time = progress_ * duration_ms_ + dt;
    float progress = std::clamp(new_time / duration_ms_, 0.0f, 1.0f);
    float interpolated_progress = interpolator_->Interpolate(progress);

    float from = 0;
    float to = 360;

    float current_value = (1 - interpolated_progress) * from + (interpolated_progress) * to;
    view_->setRotation(current_value);

    progress_ = progress;
}
