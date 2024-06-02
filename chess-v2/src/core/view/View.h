//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_VIEW_H
#define CHESS_V2_VIEW_H

#include <optional>
#include <SFML/Graphics.hpp>
#include <core/render/RenderNode.h>
#include "ViewParent.h"
#include "ViewType.h"


class View : public Tagged, public sf::Drawable {
public:
    using Ref = std::reference_wrapper<View>;
    using Shared = std::shared_ptr<View>;
    using Unique = std::unique_ptr<View>;

    View() = delete;
    View(Tag tag, ViewType type);
    View(Tag tag, ViewType type, RenderNode::SharedDrawable drawable);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    [[nodiscard]] ViewParent::Shared GetParent() const;
    void SetParent(ViewParent::Shared parent);
    [[nodiscard]] ViewType GetViewType() const;

//    [[nodiscard]] sf::Transform &GetTransform();

    /**
     * This method is called by the parent on given view.
     * It should position given view according to given parameters.
     * You should not attempt to override this method. Override OnLayout instead.
     */
    virtual void Layout(sf::Uint32 left, sf::Uint32 top, sf::Uint32 right, sf::Uint32 bottom) final;

    /**
     * This method is called by Layout method implementation to notify view that it has been layouted.
     * Here you should layout all your subviews (if applicable) or run any necessary actions in reaction to layout.
     */
    virtual void OnLayout(sf::Uint32 left, sf::Uint32 top, sf::Uint32 right, sf::Uint32 bottom);


protected:
    sf::Uint32 left_{0};
    sf::Uint32 right_{0};
    sf::Uint32 width_{0};
    sf::Uint32 height_{0};

    std::optional<RenderNode> render_node_;
    ViewParent::Shared parent_;
    ViewType type_;
};


#endif //CHESS_V2_VIEW_H
