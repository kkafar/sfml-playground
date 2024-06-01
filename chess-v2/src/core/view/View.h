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
    View(Tag tag, ViewType type, sf::Sprite &&sprite);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ViewParent::Shared GetParent() const;
    void SetParent(ViewParent::Shared parent);
    [[nodiscard]] ViewType GetViewType() const;


protected:
    std::optional<RenderNode> render_node_;
    ViewParent::Shared parent_;
    ViewType type_;
};


#endif //CHESS_V2_VIEW_H
