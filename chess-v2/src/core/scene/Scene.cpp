//
// Created by kkafara on 6/1/24.
//

#include "Scene.h"
#include <glog/logging.h>

Scene::Scene() : view_registry_{} {

}

Tag Scene::InitializeViewHierarchyWithTags(const View::Shared &root, Tag current_tag) {
    if (root == nullptr) {
        LOG(ERROR) << "Attempted to initialize null node with tag " << current_tag << '\n';
        assert(false);
    }
    root->SetTag(current_tag);
    if (!view_registry_.InsertView(current_tag, root)) {
        LOG(ERROR) << "View with given tag: " << current_tag << " already exists in registry!\n";
        assert(false);
    }

    if (ViewUtils::IsRegularView(*root)) {
        return current_tag;
    }

    // Now it should be safe to downcast this, assuming that the views have correct
    // types assigned.
    // TODO: Consider removing ViewType && ViewGroup all together, and instead
    // having just single class View.

    auto view_group = std::static_pointer_cast<ViewGroup>(root);

    for (auto &child : view_group->GetChildren()) {
        current_tag = InitializeViewHierarchyWithTags(child, ++current_tag);
    }

    return current_tag;
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*root_view_);
}

void Scene::AddViewHierarchy(ViewGroup::Shared root) {
    assert(ViewUtils::IsRootView(*root));

    InitializeViewHierarchyWithTags(root, 0);
    root_view_ = std::move(root);
    LOG(INFO) << "Registered " << view_registry_.Size() << " views in view registry\n";
}
