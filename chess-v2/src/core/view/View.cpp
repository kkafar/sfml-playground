//
// Created by kkafara on 6/1/24.
//

#include "View.h"
#include "ViewType.h"

#include <utility>

void View::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (render_node_) {
        target.draw(render_node_.value(), states);
    }
}

ViewParent::Shared View::GetParent() const {
    return parent_;
}

void View::SetParent(ViewParent::Shared parent) {
    parent_ = std::move(parent);
}

ViewType View::GetViewType() const {
    return type_;
}

View::View(Tag tag, ViewType type, RenderNode::SharedDrawable drawable) :
        Tagged(tag),
        type_{type} {
    render_node_ = RenderNode(std::move(drawable));
}

View::View(Tag tag, ViewType type) :
        Tagged(tag),
        type_{type} {
    render_node_ = std::nullopt;
}

sf::Transform &View::GetTransform() {
    return render_node_->GetTransform();
}

void View::Layout(sf::Uint32 left, sf::Uint32 top, sf::Uint32 right, sf::Uint32 bottom) {
    if (!render_node_) {
        OnLayout(left, top, right, bottom);
        return;
    }

    // Holy moly, how do I set size of a view???????
    // TODO: This needs to be figured out.
    // Currently jjj

    OnLayout(left, top, right, bottom);
}

void View::OnLayout(sf::Uint32 left, sf::Uint32 top, sf::Uint32 right, sf::Uint32 bottom) {

}
