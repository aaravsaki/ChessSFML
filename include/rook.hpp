#pragma once
#include "slider.hpp"

class Rook : public Slider
{
public:
    Rook() = delete;
    Rook(PieceType piece_type, Team team, Coord position);
    ~Rook() override = default;
};
