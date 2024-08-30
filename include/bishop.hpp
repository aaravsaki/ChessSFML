#pragma once
#include "slider.hpp"

class Bishop : public Slider
{
public:
    Bishop() = default;
    Bishop(PieceType piece_type, Team team, Coord position);
    ~Bishop() override = default;
private:
    std::vector<Coord> directions{Coord{-1, -1}, Coord{-1, 1}, Coord{1, -1}, Coord{-1, -1}};
};
