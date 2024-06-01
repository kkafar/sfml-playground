//
// Created by kkafara on 6/1/24.
//

#include "ViewUtils.h"
#include "ViewType.h"

inline bool ViewUtils::IsViewGroup(const View &view) {
//    return view.GetViewType() & ViewType::kViewGroup;
    return false;
}

bool ViewUtils::IsRootView(const View &view) {
//    return view.GetViewType() & ViewType::kRootView;
    return true;
}
