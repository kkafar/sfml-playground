//
// Created by kkafara on 6/1/24.
//

#include "RenderNode.h"
#include <algorithm>

RenderNode::RenderNode(sf::Sprite &&sprite, Tag tag) :
        Tagged{tag},
        sprite_{std::move(sprite)} {

}

RenderNode::RenderNode(sf::Sprite &&sprite) :
        RenderNode(std::move(sprite), Tagged::kTagUnset) {

}

inline sf::Drawable &RenderNode::GetDrawable() {
    return sprite_;
}

inline sf::Transformable &RenderNode::GetTransformable() {
    return sprite_;
}

void RenderNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->GetConstDrawable(), states);

    for (const auto &child: children_) {
        target.draw(child->GetConstDrawable(), states);
    }
}

const sf::Drawable &RenderNode::GetConstDrawable() const {
    return sprite_;
}

