//
// Created by kkafara on 6/1/24.
//

#include "ViewRegistry.h"

ViewRegistry::ViewRegistry() : registry_{} {

}

bool ViewRegistry::InsertView(View &&view, Tag tag) {
    auto res = registry_.insert({tag, std::make_shared<View>(std::move(view))});
    // Whether the insertion took place or not
    return res.second;
}

bool ViewRegistry::RemoveView(Tag tag) {
    // This can return either 0 or 1.
    return registry_.erase(tag) == 1;
}

View::Shared ViewRegistry::GetView(Tag tag) const {
    auto entry = registry_.find(tag);
    if (entry == std::end(registry_)) {
        return {};
    }
    return entry->second;
}
