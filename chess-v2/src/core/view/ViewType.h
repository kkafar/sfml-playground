//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_VIEWTYPE_H
#define CHESS_V2_VIEWTYPE_H


enum ViewType {
    kRegularView = 1 << 1,
    kViewGroup = 1 << 2,
    kRootView = (1 << 2) | (kViewGroup),
};


#endif //CHESS_V2_VIEWTYPE_H
