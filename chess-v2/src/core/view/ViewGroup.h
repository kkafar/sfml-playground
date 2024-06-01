//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_VIEWGROUP_H
#define CHESS_V2_VIEWGROUP_H

#include "View.h"

class ViewGroup : public View, public ViewParent {
public:
    using Ref = std::reference_wrapper<ViewGroup>;
    using Shared = std::shared_ptr<ViewGroup>;

    ViewGroup() = delete;
    explicit ViewGroup(Tag tag);
    ViewGroup(Tag tag, RenderNode::SharedDrawable drawable);


    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void AddSubview(View::Shared view);
    void AddSubviewAt(View::Shared view, std::size_t index);
    void RemoveSubviewWithTag(Tag tag);

    std::vector<View::Shared> &GetChildren();

private:
    std::vector<View::Shared> children_;

    // Currently absence of parent is modelled with nullptr.
    // Consider using std::optional here.
    Shared parent_;
};


#endif //CHESS_V2_VIEWGROUP_H
