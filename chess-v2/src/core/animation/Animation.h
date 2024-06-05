#ifndef CHESS_V2_ANIMATION_H
#define CHESS_V2_ANIMATION_H

#include <memory>
#include <core/view/View.h>
#include "Interpolator.h"
#include "AnimationDriverVisitor.h"

class AnimationDriver;

class Animation {
public: // Interface
    using Unique = std::unique_ptr<Animation>;
    using Shared = std::shared_ptr<Animation>;
    using RefWrap = std::reference_wrapper<Animation>;
    using Ref = Animation &;

    Animation() = delete;

    explicit Animation(View::Shared view);

    Animation(View::Shared view, Interpolator::Unique &&interpolator);

    virtual Animation &operator =(const Animation &) = delete;

    virtual ~Animation() = default;

public: // Animation management

    /**
     * Override this method to implement your animation type;
     */
    virtual void DriveAnimation(AnimationDriverVisitor &animator, float dt) = 0;

    virtual void Start();

    virtual void Cancel();

    virtual void Pause();

    virtual void Resume();

public: // Accessors

    [[nodiscard]]
    View::Shared &GetView();

    Interpolator::Unique &GetInterpolator();

    [[nodiscard]]
    float GetProgress() const noexcept;

    /**
     * Can be used to manually drive the animation
     */
    void SetProgress(float progress) noexcept;

    [[nodiscard]]
    sf::Int32 GetDurationMs() const noexcept;

    /**
     * Sets duration of the animation. Note that this can not be done when animation is in running state.
     */
    bool SetDurationMs(sf::Int32 duration) noexcept;

protected:
    View::Shared view_{nullptr};
    Interpolator::Unique interpolator_{nullptr};
    sf::Int32 duration_ms_{0};
    float progress_{0};
    bool running_{false};
};

#endif //CHESS_V2_ANIMATION_H
