//
// Created by kkafara on 6/1/24.
//

#include "ViewGroup.h"

void ViewGroup::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // First draw myself
    View::draw(target, states);

    // Draw all the children
    for (const auto &child : children_) {
        child->draw(target, states);
    }
}

void ViewGroup::AddSubview(View::Shared view) {
    // TODO: Find how to handle this! (Maybe pass a reference?)
//    view->SetParent(std::make_shared<ViewParent>());
    children_.push_back(std::move(view));
}

void ViewGroup::RemoveSubviewWithTag(Tag tag) {
//    auto iter = std::find_if(std::begin(children_), std::end(children_), [tag](const View::Shared &view) {
//        return view->GetTag() == tag;
//    });
//
//    if (iter != std::end(children_)) {
//        children_.erase(iter);
//    }
}

void ViewGroup::AddSubviewAt(View::Shared view, std::size_t index) {
    if (index > children_.size()) {
        return;
    }
    if (index == children_.size()) {
        children_.push_back(std::move(view));
        return;
    }
    children_.insert(std::begin(children_) + index, std::move(view));
}

ViewGroup::ViewGroup(Tag tag) : View(tag, ViewType::kViewGroup), ViewParent() {

}

ViewGroup::ViewGroup(Tag tag, RenderNode::SharedDrawable drawable) :
        View(tag, ViewType::kViewGroup, std::move(drawable)),
        ViewParent() {

}

std::vector<View::Shared> &ViewGroup::GetChildren() {
    return children_;
}

void ViewGroup::OnLayout(sf::Uint32 left, sf::Uint32 top, sf::Uint32 right, sf::Uint32 bottom) {
    for (auto &child : children_) {
        child->Layout(left, top, right, bottom);
    }
}
