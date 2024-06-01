//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_VIEWPARENT_H
#define CHESS_V2_VIEWPARENT_H

#include <memory>

class ViewParent {
public:
    using Shared = std::shared_ptr<ViewParent>;
    using Ref = std::reference_wrapper<ViewParent>;

    ViewParent();
    explicit ViewParent(Shared parent);

    Shared GetParent();

    // Abstract class
    virtual ~ViewParent() = default;
private:
    Shared parent_;
};


#endif //CHESS_V2_VIEWPARENT_H
