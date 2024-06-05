//
// Created by kkafara on 6/5/24.
//

#include <cmath>
#include "PositionAnimation.h"

PositionAnimation::PositionAnimation(View::Shared view, sf::Vector2f target_position) : Animation(std::move(view)),
                                                                                        target_position_{
                                                                                                target_position} {
    initial_position_ = GetView()->getPosition();
}

PositionAnimation::PositionAnimation(View::Shared view, Interpolator::Unique &&interpolator,
                                     sf::Vector2f target_position) : Animation(std::move(view),
                                                                               std::move(interpolator)),
                                                                     target_position_(target_position) {
    initial_position_ = GetView()->getPosition();
}

void PositionAnimation::DriveAnimation(AnimationDriverVisitor &animator, float dt) {
    float new_time = progress_ * duration_ms_ + dt;
    float progress = std::clamp(new_time / duration_ms_, 0.0f, 1.0f);
    float interpolated_progress = interpolator_->Interpolate(progress);

    float new_x = std::lerp(initial_position_.x, target_position_.x, interpolated_progress);
    float new_y = std::lerp(initial_position_.y, target_position_.y, interpolated_progress);

    view_->setPosition(new_x, new_y);
    progress_ = progress;
}
