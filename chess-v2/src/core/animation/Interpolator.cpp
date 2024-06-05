#include "Interpolator.h"

float LinearInterpolator::Interpolate(float progress) {
    return progress;
}

float AccelerateInterpolator::Interpolate(float progress) {
    return progress * progress;
}
