#ifndef CHESS_V2_SCENE_H
#define CHESS_V2_SCENE_H

#include "ViewRegistry.h"
#include <cassert>
#include <core/view/View.h>
#include <core/view/ViewUtils.h>

class Scene : public sf::Drawable {
public:
    Scene();

    void AddViewHierarchy(View::Shared root);
    View::Shared &GetRootViewRef();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    /**
     * Initializes tags in given subtree with root as the root node.
     *
     * \return Last used tag
     */
    Tag InitializeViewHierarchyWithTags(const View::Shared &root, Tag current_tag);


    ViewRegistry view_registry_{};
    View::Shared root_view_{nullptr};
};


#endif //CHESS_V2_SCENE_H
