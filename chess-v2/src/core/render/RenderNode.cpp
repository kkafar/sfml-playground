//
// Created by kkafara on 6/1/24.
//

#include "RenderNode.h"
#include <algorithm>

RenderNode::RenderNode(RenderNode::SharedDrawable drawable) :
        drawable_{std::move(drawable)} {

}

inline RenderNode::SharedDrawable &RenderNode::GetDrawable() {
    return drawable_;
}

//inline sf::Transformable &RenderNode::GetTransformable() {
//    return drawable_;
//}

void RenderNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*GetConstDrawable(), states.transform * getTransform());
}

const RenderNode::SharedDrawable &RenderNode::GetConstDrawable() const {
    return drawable_;
}

//sf::Transform &RenderNode::GetTransform() {
//    return transform_;
//}

