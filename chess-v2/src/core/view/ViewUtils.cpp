//
// Created by kkafara on 6/1/24.
//

#include "ViewUtils.h"
#include "ViewType.h"

bool ViewUtils::IsViewGroup(const View &view) {
    return view.GetViewType() & ViewType::kViewGroup;
}

bool ViewUtils::IsRootView(const View &view) {
    return view.GetViewType() & ViewType::kRootView;
}

bool ViewUtils::IsRegularView(const View &view) {
    return view.GetViewType() & ViewType::kRegularView;
}

