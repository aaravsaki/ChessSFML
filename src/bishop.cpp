#include "bishop.hpp"

Bishop::Bishop(PieceType piece_type, Team team, Coord position)
    : Slider(piece_type, team, position)
{
    directions = {Coord{-1, -1}, Coord{-1, 1}, Coord{1, -1}, Coord{1, 1}};
}

