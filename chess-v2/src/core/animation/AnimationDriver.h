#ifndef CHESS_V2_ANIMATIONDRIVER_H
#define CHESS_V2_ANIMATIONDRIVER_H

#include <glog/logging.h>
#include <unordered_map>
#include <vector>
#include <concepts>
#include <core/CommonTypes.h>
#include <core/view/View.h>
#include "Interpolator.h"
#include "Animation.h"
#include "AnimationDriverVisitor.h"
#include <cmath>


class AnimationDriver {
public: // API

    void RegisterAnimation(Animation::Unique &&animation);

    void UnregisterAnimation(Tag tag);

    void StartAnimation(Tag tag);

    void CancelAnimation(Tag tag);

    void PauseAnimation(Tag tag);

    void ResumeAnimation(Tag tag);

    void RequestAnimationFrame(float dt);

private:
    std::vector<Animation::Unique> pending_registry_{};
    AnimationDriverVisitor visitor_{};
};


#endif //CHESS_V2_ANIMATIONDRIVER_H
