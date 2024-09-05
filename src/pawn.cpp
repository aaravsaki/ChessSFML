#include "pawn.hpp"

Pawn::Pawn(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}

std::vector<Coord> Pawn::getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const
{
    std::vector<Coord> moves;
    int dr = 1;
    Coord position = getCoord();

    if (getTeam() == Team::white)
    {
        dr = -1;
    }
    
    // Sliding moves (1 or 2 spaces forward)
    if (!field[position.row + dr][position.col]) // Not checking for bounds because final rank promotion is required
    {
        moves.push_back(Coord{position.row + dr, position.col});
        if ((position.row == 6 && getTeam() == Team::white || position.row == 1 && getTeam() == Team::black)
            && !field[position.row + 2 * dr][position.col])
        {
            moves.push_back(Coord{position.row + 2 * dr, position.col});
        }
    }

    // Attacking moves (one space diagonally)
    if (position.col < 7 && field[position.row + dr][position.col + 1] && 
        field[position.row + dr][position.col + 1]->getTeam() != getTeam())
    {
        moves.push_back(Coord{position.row + dr, position.col + 1});
    }

    if (position.col > 0 && field[position.row + dr][position.col - 1] && 
        field[position.row + dr][position.col - 1]->getTeam() != getTeam())
    {
        moves.push_back(Coord{position.row + dr, position.col - 1});
    }

    return moves;
}
