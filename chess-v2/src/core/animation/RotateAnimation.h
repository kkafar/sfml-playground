#ifndef CHESS_V2_ROTATEANIMATION_H
#define CHESS_V2_ROTATEANIMATION_H

#include <memory>
#include "Animation.h"


class RotateAnimation : public Animation {
public:
    using Unique = std::unique_ptr<RotateAnimation>;

    RotateAnimation() = delete;

    explicit RotateAnimation(View::Shared view);

    RotateAnimation(View::Shared view, Interpolator::Unique &&interpolator);

    void DriveAnimation(AnimationDriverVisitor &animator, float dt) override;
};


#endif //CHESS_V2_ROTATEANIMATION_H
