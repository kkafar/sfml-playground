//
// Created by kkafara on 6/2/24.
//

#ifndef CHESS_V2_LAYOUTPARAMS_H
#define CHESS_V2_LAYOUTPARAMS_H

#include <SFML/System/Vector2.hpp>

class LayoutParams {
public:
    enum class Mode {
        kUnspecified = 0,
        kExactly = 1,
        kWrapContent = 2,
    };

    sf::Vector2<float> size{0, 0};
    Mode mode{Mode::kUnspecified};

private:
};


#endif //CHESS_V2_LAYOUTPARAMS_H
