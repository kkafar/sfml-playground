//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_VIEWTYPE_H
#define CHESS_V2_VIEWTYPE_H


enum ViewType {
    kView = 0,
    kViewGroup = 1 << 0,
    kRootView = (1 << 1) | (kViewGroup),
};


#endif //CHESS_V2_VIEWTYPE_H
