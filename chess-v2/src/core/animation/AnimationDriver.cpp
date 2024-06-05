#include "AnimationDriver.h"


//void AnimationDriver::DriveAnimation(Animation &animation, float dt) {
//    auto &view = animation.GetView();
//
//    // We need to know:
//    // 1. current state of animation (animation should hold it),
//    // 2. time delta (we assume that animations are time driven right now),
//    // 3. range of animation (from & to values),
//    // 4. interpolator, that maps current animation progress to a value in animation range,
//
//    animation.DriveAnimation(*this, dt);
//}

void AnimationDriver::RegisterAnimation(Animation::Unique &&animation) {
//    pending_registry_.insert({animation->GetView()->GetTag(), std::move(animation)});
    pending_registry_.push_back(std::move(animation));
}

void AnimationDriver::UnregisterAnimation(Tag tag) {
//    auto find_iter = pending_registry_.find(tag);
//
//    if (find_iter == std::end(pending_registry_)) {
//        return;
//    }
//
//    auto &animation = find_iter->second;
//    animation->Cancel();
//
//    pending_registry_.erase(find_iter);
}

void AnimationDriver::StartAnimation(Tag tag) {
//    auto find_iter = pending_registry_.find(tag);
//
//    if (find_iter == std::end(pending_registry_)) {
//        return;
//    }
//
//    find_iter->second->Start();
}

void AnimationDriver::CancelAnimation(Tag tag) {
    auto find_iter = std::find_if(pending_registry_.begin(), pending_registry_.end(), [tag](Animation::Unique &anim) {
        return anim->GetView()->GetTag() == tag;
    });

    if (find_iter == std::end(pending_registry_)) {
        return;
    }

//    *find_iter->Pause();
}

void AnimationDriver::PauseAnimation(Tag tag) {
    auto find_iter = std::find_if(pending_registry_.begin(), pending_registry_.end(), [tag](const Animation::Unique &anim) {
        return anim->GetView()->GetTag() == tag;
    });

    if (find_iter == std::end(pending_registry_)) {
        return;
    }

    find_iter->get()->Pause();
}

void AnimationDriver::ResumeAnimation(Tag tag) {
//    auto find_iter = pending_registry_.find(tag);
//
//    if (find_iter == std::end(pending_registry_)) {
//        return;
//    }
//
//    find_iter->second->Resume();
}

void AnimationDriver::RequestAnimationFrame(float dt) {
    for (auto &entry: pending_registry_) {
        auto &animation = entry;
        animation->DriveAnimation(visitor_, dt);
    }
}
