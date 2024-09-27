#include "pawn.hpp"

Pawn::Pawn(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}

std::set<Coord> Pawn::getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const
{
    std::set<Coord> moves;
    Coord position = getCoord();
    
    // Sliding moves (1 or 2 spaces forward)
    if (!field[position.row + dr][position.col]) // Not checking for bounds because final rank promotion is required
    {
        moves.insert(Coord{position.row + dr, position.col});
        if (!has_moved && !field[position.row + 2 * dr][position.col])
        {
            moves.insert(Coord{position.row + 2 * dr, position.col});
        }
    }

    // Attacking moves (one space diagonally)
    if (position.col < 7 && field[position.row + dr][position.col + 1] && 
        field[position.row + dr][position.col + 1]->getTeam() != getTeam())
    {
        moves.insert(Coord{position.row + dr, position.col + 1});
    }

    if (position.col > 0 && field[position.row + dr][position.col - 1] && 
        field[position.row + dr][position.col - 1]->getTeam() != getTeam())
    {
        moves.insert(Coord{position.row + dr, position.col - 1});
    }

    return moves;
}
