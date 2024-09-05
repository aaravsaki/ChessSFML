#pragma once
#include "slider.hpp"

class Queen : public Slider
{
public:
    Queen() = delete;
    Queen(PieceType piece_type, Team team, Coord position);
    ~Queen() override = default;
private:
    std::vector<Coord> directions{Coord{-1, -1}, Coord{-1, 1}, Coord{1, -1}, Coord{-1, -1}, Coord{-1, 0}, Coord{1, 0}, Coord{0, 1}, Coord{0, -1}};
};
