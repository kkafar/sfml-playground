//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_TAGGED_H
#define CHESS_V2_TAGGED_H

#include "CommonTypes.h"

class Tagged {
public:
    static constexpr Tag kTagUnset = -1;

    Tagged();
    explicit Tagged(Tag tag);

    [[nodiscard]] Tag GetTag() const;
    void SetTag(Tag tag);
    [[nodiscard]] bool HasTag() const;

private:
    Tag tag_;
};


#endif //CHESS_V2_TAGGED_H
