#include "View.h"
#include <utility>
#include <glog/logging.h>

///////////////////////////////////////////////////////////////
/// Ctors
///////////////////////////////////////////////////////////////

View::View(LayoutParams params) : Tagged(Tagged::kTagUnset), layoutParams_(params) {
}

View::View(LayoutParams params, RenderNode::SharedDrawable drawable) : Tagged(Tagged::kTagUnset),
                                                                       layoutParams_(params),
                                                                       render_node_{std::make_shared<RenderNode>(
                                                                               std::move(drawable))} {
}

///////////////////////////////////////////////////////////////
/// Drawing
///////////////////////////////////////////////////////////////

void View::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // First draw myself
    states.transform *= getTransform();
    target.draw(render_node_, states);

    // Draw children
    for (auto &child: children_) {
        child->draw(target, states);
    }
}

///////////////////////////////////////////////////////////////
/// Layout
///////////////////////////////////////////////////////////////

void View::Layout(const Frame frame) {
    if (!layout_invalidated_ || frame_ == frame) {
        return;
    }

    LOG(INFO) << "LAYOUT";
    frame_ = frame;

//    if (!render_node_) {
//        OnLayout(frame);
//        return;
//    }

    // Holy moly, how do I set size of a view???????
    // TODO: This needs to be figured out.
    // Currently jjj

    auto &render_node = render_node_;
    render_node.setPosition(frame_.left, frame_.top);

    OnLayout(frame);
    layout_invalidated_ = false;
}

void View::OnLayout(sf::FloatRect frame) {
    for (auto &child : children_) {
        child->Layout(frame);
    }
}

View::View() {

}

LayoutParams &View::GetLayoutParams() {
    return layoutParams_;
}

void View::InvalidateLayout() {
    layout_invalidated_ = true;
}

///////////////////////////////////////////////////////////////
/// View hierarchy relationship management
///////////////////////////////////////////////////////////////

void View::AddSubview(View::Shared subview) {
    children_.push_back(std::move(subview));
}

void View::AddSubviewAt(View::Shared subview, std::size_t index) {
    if (index > children_.size()) {
        return;
    }
    if (index == children_.size()) {
        children_.push_back(std::move(subview));
        return;
    }
    children_.insert(std::begin(children_) + index, std::move(subview));
}

void View::RemoveSubview(Tag tag) {
    auto iter = std::find_if(std::begin(children_), std::end(children_), [tag](const View::Shared &view) {
        return view->GetTag() == tag;
    });

    if (iter != std::end(children_)) {
        children_.erase(iter);
    }
}

View::ChildContainer &View::GetChildren() {
    return children_;
}

bool View::IsLeaf() const {
    return children_.empty();
}

View::Shared View::GetParent() const {
    return parent_;
}

void View::SetParent(View::Weak parent) {
    parent_ = parent.lock();
}

void View::SetRenderNode(RenderNode &&node) {
    render_node_ = {std::move(node)};
}


//RenderNode &View::GetRenderNode() {
//    return render_node_;
//}

