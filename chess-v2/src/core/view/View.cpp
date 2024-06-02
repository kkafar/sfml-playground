#include "View.h"
#include "ViewType.h"

#include <utility>

void View::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // First draw myself
    if (render_node_) {
        target.draw(render_node_.value(), states);
    }

    // Draw children
    for (auto &child : children_) {
        child->draw(target, states);
    }
}

ViewParent::Shared View::GetParent() const {
    return parent_;
}

void View::SetParent(ViewParent::Weak parent) {
    parent_ = std::move(parent);
}

ViewType View::GetViewType() const {
    return type_;
}

View::View(ViewType type, Tag tag, RenderNode::SharedDrawable drawable) :
        Tagged(tag),
        type_{type} {
    render_node_ = RenderNode(std::move(drawable));
}

View::View(ViewType type, Tag tag) :
        Tagged(tag),
        type_{type} {
    render_node_ = std::nullopt;
}

//sf::Transform &View::GetTransform() {
//    return render_node_->getTransform();
//}

void View::Layout(const sf::FloatRect frame) {
    if (frame_ == frame) {
        return;
    }
    frame_ = frame;

    if (!render_node_) {
        OnLayout(frame);
        return;
    }

    // Holy moly, how do I set size of a view???????
    // TODO: This needs to be figured out.
    // Currently jjj

    auto &render_node = render_node_.value();
    render_node.setPosition(frame_.left, frame_.top);

    OnLayout(frame);
}

void View::OnLayout(sf::FloatRect frame) {

}

View::View(ViewType type) : type_{type} {

}

LayoutParams &View::GetLayoutParams() {
    return layoutParams_;
}


// View hierarchy relationship management

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
