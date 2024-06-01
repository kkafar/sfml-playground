//
// Created by kkafara on 6/1/24.
//

#include "ViewParent.h"

inline ViewParent::Shared ViewParent::GetParent() {
    return parent_;
}

ViewParent::ViewParent() : parent_(nullptr) {
}

ViewParent::ViewParent(ViewParent::Shared parent) : parent_(std::move(parent)) {

}
