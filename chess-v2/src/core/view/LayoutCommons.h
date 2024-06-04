#ifndef CHESS_V2_LAYOUTCOMMONS_H
#define CHESS_V2_LAYOUTCOMMONS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

using Size = sf::Vector2f;
using Frame = sf::FloatRect;

struct LayoutParams {
    enum class Mode {
        kExactly = 0,
        kWrapContent = 1,
    };

    Size size{0, 0};
    Mode width_mode{Mode::kExactly};
    Mode height_mode{Mode::kExactly};
};

struct MeasureSpec {
    enum class Mode {
        kExactly = 0,
        kWrapContent = 1,
    };

    Size size{0, 0};
    Mode width_mode{Mode::kExactly};
    Mode height_mode{Mode::kExactly};
};



#endif //CHESS_V2_LAYOUTCOMMONS_H
