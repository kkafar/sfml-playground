//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_RENDERNODE_H
#define CHESS_V2_RENDERNODE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cstdint>
#include <optional>
#include <core/Tagged.h>
#include <core/CommonTypes.h>


class RenderNode : public Tagged, public sf::Drawable {
public:
    using Ref = std::reference_wrapper<RenderNode>;
    using Shared = std::shared_ptr<RenderNode>;
    using SharedDrawable = std::shared_ptr<sf::Drawable>;

    RenderNode() = delete;

    explicit RenderNode(SharedDrawable drawable);

    /// Designated constructor
    RenderNode(SharedDrawable drawable, Tag tag);

    [[nodiscard("Pure getter")]]
    SharedDrawable &GetDrawable();

    [[nodiscard("Pure getter")]]
    const SharedDrawable &GetConstDrawable() const;

    [[nodiscard]]
    sf::Transform &GetTransform();

//    [[nodiscard("Pure getter")]]
//    sf::Transformable &GetTransformable();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    SharedDrawable drawable_;
    sf::Transform transform_{sf::Transform::Identity};
};


#endif //CHESS_V2_RENDERNODE_H
