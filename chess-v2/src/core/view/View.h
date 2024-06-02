#ifndef CHESS_V2_VIEW_H
#define CHESS_V2_VIEW_H

#include <optional>
#include <SFML/Graphics.hpp>
#include <core/render/RenderNode.h>
#include "ViewParent.h"
#include "ViewType.h"
#include "LayoutParams.h"

class View : public Tagged, public sf::Drawable {
public:
    using Ref = std::reference_wrapper<View>;
    using Shared = std::shared_ptr<View>;
    using Unique = std::unique_ptr<View>;
    using ChildContainer = std::vector<Shared>;

    View() = delete;
    View(ViewType type);
    View(ViewType type, Tag tag);
    View(ViewType type, Tag tag, RenderNode::SharedDrawable drawable);

public: // Drawing

    /**
     * Override of SFML Drawable draw method. You can override this in your subclass
     * to implement custom drawing logic.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public: // View hierarchy relationship management

    [[nodiscard]] ViewParent::Shared GetParent() const;

    void SetParent(ViewParent::Weak parent);

    void AddSubview(Shared subview);

    void AddSubviewAt(Shared subview, std::size_t index);

    void RemoveSubview(Tag tag);

    ChildContainer &GetChildren();

    [[nodiscard]]
    bool IsLeaf() const;

public: // Layout & Measurement

    /**
     * This method is called by the parent on given view.
     * It should position given view according to given parameters.
     * You should not attempt to override this method. Override OnLayout instead.
     */
    virtual void Layout(sf::FloatRect frame) final;

    /**
     * This method is called by Layout method implementation to notify view that it has been layouted.
     * Here you should layout all your subviews (if applicable) or run any necessary actions in reaction to layout.
     */
    virtual void OnLayout(sf::FloatRect frame);


    LayoutParams &GetLayoutParams();

public: // Misc

    [[deprecated("ViewGroup will be removed")]]
    [[nodiscard]]
    ViewType GetViewType() const;

protected:
    std::vector<Shared> children_;
    sf::FloatRect frame_{0, 0, 0, 0};
    std::optional<RenderNode> render_node_{};
    ViewParent::Shared parent_;
    ViewType type_;
    LayoutParams layoutParams_{{0, 0}, LayoutParams::Mode::kUnspecified};
};


#endif //CHESS_V2_VIEW_H
