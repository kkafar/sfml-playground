//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_VIEWUTILS_H
#define CHESS_V2_VIEWUTILS_H

#include "View.h"

class ViewUtils {
public:
    static bool IsViewGroup(const View &view);
    static bool IsRootView(const View &view);
    static bool IsRegularView(const View &view);

private:
};


#endif //CHESS_V2_VIEWUTILS_H
