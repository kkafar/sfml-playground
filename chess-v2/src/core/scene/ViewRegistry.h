//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_VIEWREGISTRY_H
#define CHESS_V2_VIEWREGISTRY_H

#include <unordered_map>
#include <memory>
#include <core/CommonTypes.h>
#include <core/view/View.h>

class ViewRegistry {
public:
    ViewRegistry();

    bool InsertView(Tag tag, View &&view);
    bool InsertView(Tag tag, View::Shared view);
    bool RemoveView(Tag tag);

    [[nodiscard]]
    View::Shared GetView(Tag tag) const;

    [[nodiscard]]
    std::size_t Size() const;

private:
    std::unordered_map<Tag, View::Shared> registry_;
};


#endif //CHESS_V2_VIEWREGISTRY_H
