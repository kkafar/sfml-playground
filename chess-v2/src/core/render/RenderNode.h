#ifndef CHESS_V2_RENDERNODE_H
#define CHESS_V2_RENDERNODE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cstdint>
#include <optional>
#include <core/Tagged.h>
#include <core/CommonTypes.h>


class RenderNode : public sf::Drawable, public sf::Transformable {
public:
    using Ref = std::reference_wrapper<RenderNode>;
    using Shared = std::shared_ptr<RenderNode>;
    using SharedDrawable = std::shared_ptr<sf::Drawable>;

    RenderNode() = default;

    explicit RenderNode(SharedDrawable drawable);

    [[nodiscard("Pure getter")]]
    SharedDrawable &GetDrawable();

    [[nodiscard("Pure getter")]]
    const SharedDrawable &GetConstDrawable() const;

//    [[nodiscard]]
//    sf::Transform &GetTransform();

//    [[nodiscard("Pure getter")]]
//    sf::Transformable &GetTransformable();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    SharedDrawable drawable_{nullptr};
    sf::FloatRect frame_{0, 0, 0, 0};
};


#endif //CHESS_V2_RENDERNODE_H
