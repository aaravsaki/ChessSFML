#pragma once
#include "slider.hpp"

class Rook : public Slider
{
public:
    Rook() = default;
    Rook(PieceType piece_type, Team team, Coord position);
    ~Rook() override = default;
private:
    std::vector<Coord> directions{Coord{-1, 0}, Coord{1, 0}, Coord{0, 1}, Coord{0, -1}};
};
