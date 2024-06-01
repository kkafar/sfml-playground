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

inline bool RenderNode::IsLeafNode() const {
    return children_.empty();
}

void RenderNode::AddChildNode(RenderNode::Shared child) {
    children_.push_back(std::move(child));
}

void RenderNode::AddChildNode(RenderNode &&child) {
    auto pointer = std::make_shared<RenderNode>(std::move(child));
    children_.emplace_back(pointer);
}

std::optional<RenderNode::Shared> RenderNode::RemoveChildNodeAt(std::size_t index) {
    if (index < children_.size()) {
        RenderNode::Shared removed_node = std::move(children_[index]);
        children_.erase(std::begin(children_) + index);
        return std::make_optional<RenderNode::Shared>(std::move(removed_node));
    }
    return {};
}

std::optional<RenderNode::Shared> RenderNode::RemoveChildWithTag(Tag tag) {
    auto iter = std::find_if(std::begin(children_), std::end(children_), [tag](const RenderNode::Shared &node) -> bool {
        return node->GetTag() == tag;
    });
    if (iter != std::end(children_)) {
        RenderNode::Shared removed_node = std::move(*iter);
        children_.erase(iter);
        return std::make_optional<RenderNode::Shared>(std::move(removed_node));
    }
    return {};
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

