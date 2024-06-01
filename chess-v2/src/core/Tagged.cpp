//
// Created by kkafara on 6/1/24.
//

#include "Tagged.h"

Tagged::Tagged() : tag_{Tagged::kTagUnset} {
}

Tagged::Tagged(Tag tag) : tag_{tag} {
}

inline Tag Tagged::GetTag() const {
    return tag_;
}

void Tagged::SetTag(Tag tag) {
    tag_ = tag;
}

bool Tagged::HasTag() const {
    return tag_ != Tagged::kTagUnset;
}

