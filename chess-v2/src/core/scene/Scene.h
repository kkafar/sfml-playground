//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_SCENE_H
#define CHESS_V2_SCENE_H

#include "ViewRegistry.h"
#include <cassert>
#include <core/view/ViewGroup.h>
#include <core/view/ViewUtils.h>

class Scene : public sf::Drawable {
public:
    Scene();

    void AddViewHierarchy(ViewGroup::Shared root);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    /**
     * Initializes tags in given subtree with root as the root node.
     *
     * \return Last used tag
     */
    Tag InitializeViewHierarchyWithTags(const View::Shared &root, Tag current_tag);


    ViewRegistry view_registry_;
    ViewGroup::Shared root_view_{nullptr};
};


#endif //CHESS_V2_SCENE_H
