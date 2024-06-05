#ifndef CHESS_V2_POSITIONANIMATION_H
#define CHESS_V2_POSITIONANIMATION_H

#include <memory>
#include <core/view/View.h>
#include <core/animation/Animation.h>
#include <core/animation/Interpolator.h>
#include <core/animation/AnimationDriverVisitor.h>

class PositionAnimation : public Animation {
public:
    using Unique = std::unique_ptr<PositionAnimation>;

    PositionAnimation() = delete;

    explicit PositionAnimation(View::Shared view, sf::Vector2f target_position);

    PositionAnimation(View::Shared view, Interpolator::Unique &&interpolator, sf::Vector2f target_position);

    void DriveAnimation(AnimationDriverVisitor &animator, float dt) override;

private:
    sf::Vector2f initial_position_{0, 0};
    sf::Vector2f target_position_{0, 0};
};


#endif //CHESS_V2_POSITIONANIMATION_H
