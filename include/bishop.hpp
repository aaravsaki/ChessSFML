#pragma once
#include "slider.hpp"

class Bishop : public Slider
{
public:
    Bishop() = delete;
    Bishop(PieceType piece_type, Team team, Coord position);
    ~Bishop() override = default;
};
