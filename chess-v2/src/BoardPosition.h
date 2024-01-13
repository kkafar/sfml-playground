//
// Created by kkafara on 1/13/24.
//

#ifndef CHESS_V2_BOARDPOSITION_H
#define CHESS_V2_BOARDPOSITION_H

#include <SFML/Main.hpp>
#include <ostream>

namespace chess {

struct BoardPosition {
    sf::Uint32 row;
    sf::Uint32 col;

    friend std::ostream &operator<<(std::ostream &stream, const BoardPosition &pos);

    [[nodiscard]] BoardPosition operator+(const BoardPosition &other) const noexcept;
    [[nodiscard]] bool operator==(const BoardPosition &other) const noexcept;
    [[nodiscard]] bool operator!=(const BoardPosition &other) const noexcept;
    BoardPosition& operator+=(const BoardPosition &other) noexcept;
    BoardPosition& operator-=(const BoardPosition &other) noexcept;
};

}



#endif //CHESS_V2_BOARDPOSITION_H
