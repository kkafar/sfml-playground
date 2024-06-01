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


class RenderNode : Tagged, sf::Drawable {
public:
    using Ref = std::reference_wrapper<RenderNode>;
    using Shared = std::shared_ptr<RenderNode>;

    RenderNode() = delete;

    explicit RenderNode(sf::Sprite &&sprite);

    /// Designated constructor
    RenderNode(sf::Sprite &&sprite, Tag tag);

    [[nodiscard("Pure getter")]]
    sf::Drawable &GetDrawable();

    [[nodiscard("Pure getter")]]
    const sf::Drawable &GetConstDrawable() const;

    [[nodiscard("Pure getter")]]
    sf::Transformable &GetTransformable();

    [[nodiscard("Pure getter")]]
    bool IsLeafNode() const;

    void AddChildNode(Shared child);

    void AddChildNode(RenderNode &&child);

    std::optional<Shared> RemoveChildNodeAt(std::size_t index);

    std::optional<Shared> RemoveChildWithTag(Tag tag);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite_;
    std::vector<std::shared_ptr<RenderNode>> children_;
};


#endif //CHESS_V2_RENDERNODE_H
