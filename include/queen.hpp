#pragma once
#include "slider.hpp"

class Queen : public Slider
{
public:
    Queen() = delete;
    Queen(PieceType piece_type, Team team, Coord position);
    ~Queen() override = default;
};
