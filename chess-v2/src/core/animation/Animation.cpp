#include "Animation.h"

View::Shared &Animation::GetView() {
    return view_;
}

void Animation::Pause() {
    running_ = false;
}

void Animation::Resume() {
    running_ = true;
}

void Animation::Start() {
    running_ = true;
}

void Animation::Cancel() {
    running_ = false;
}

float Animation::GetProgress() const noexcept {
    return progress_;
}

sf::Int32 Animation::GetDurationMs() const noexcept {
    return duration_ms_;
}

Interpolator::Unique &Animation::GetInterpolator() {
    return interpolator_;
}

Animation::Animation(View::Shared view) : view_{std::move(view)},
                                          interpolator_{std::move(std::make_unique<LinearInterpolator>())} {


}

Animation::Animation(View::Shared view, Interpolator::Unique &&interpolator) : view_{std::move(view)},
                                                                               interpolator_{std::move(interpolator)} {

}

void Animation::SetProgress(float progress) noexcept {
    // We do not use clamp here as some animation might want to overshoot
    progress_ = progress;
}

bool Animation::SetDurationMs(sf::Int32 duration) noexcept {
    duration_ms_ = duration;
    return true;
}
