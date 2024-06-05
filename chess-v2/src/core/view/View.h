#ifndef CHESS_V2_VIEW_H
#define CHESS_V2_VIEW_H

#include <optional>
#include <SFML/Graphics.hpp>
#include <core/render/RenderNode.h>
#include "LayoutCommons.h"

class View : public Tagged, public sf::Drawable, public sf::Transformable {
public:
    using Ref = std::reference_wrapper<View>;
    using Shared = std::shared_ptr<View>;
    using Unique = std::unique_ptr<View>;
    using Weak = std::weak_ptr<View>;
    using ChildContainer = std::vector<Shared>;

    View();
    explicit View(LayoutParams params);
    View(LayoutParams params, RenderNode::SharedDrawable drawable);

public: // Drawing

    /**
     * Override of SFML Drawable draw method. You can override this in your subclass
     * to implement custom drawing logic.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public: // View hierarchy relationship management

    [[nodiscard]]
    View::Shared GetParent() const;

    void SetParent(View::Weak parent);

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
    virtual void Layout(Frame frame) final;

    /**
     * This method is called by Layout method implementation to notify view that it has been layouted.
     * Here you should layout all your subviews (if applicable) or run any necessary actions in reaction to layout.
     * Base implementation does forward Layout call that it received to all of the subviews.
     */
    virtual void OnLayout(Frame frame);

    LayoutParams &GetLayoutParams();

    void InvalidateLayout();

public: // API for animations

protected: // Subclass flexibility

//    [[nodiscard]]
//    RenderNode &GetRenderNode();

    void SetRenderNode(RenderNode &&node);

protected:
    std::vector<Shared> children_{};
    Frame frame_{0, 0, 0, 0};
    RenderNode render_node_{};
    View::Shared parent_{nullptr};
    LayoutParams layoutParams_{};
    bool layout_invalidated_{true};
};


#endif //CHESS_V2_VIEW_H
