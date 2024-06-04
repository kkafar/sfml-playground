#include "Scene.h"
#include <glog/logging.h>

Scene::Scene() {

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

    if (root->IsLeaf()) {
        return current_tag;
    }

    for (auto &child : root->GetChildren()) {
        current_tag = InitializeViewHierarchyWithTags(child, ++current_tag);
    }

    return current_tag;
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*root_view_);
}

void Scene::AddViewHierarchy(View::Shared root) {
    InitializeViewHierarchyWithTags(root, 0);
    root_view_ = std::move(root);
    LOG(INFO) << "Registered " << view_registry_.Size() << " views in view registry\n";
}

View::Shared &Scene::GetRootViewRef() {
    return root_view_;
}
