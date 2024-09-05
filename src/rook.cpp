#include "rook.hpp"

Rook::Rook(PieceType piece_type, Team team, Coord position)
    : Slider(piece_type, team, position)
{
    directions = {Coord{1, 0}, Coord{-1, 0}, Coord{0, 1}, Coord{0, -1}};
}
