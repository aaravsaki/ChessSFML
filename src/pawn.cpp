#include "pawn.hpp"

Pawn::Pawn(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}

std::vector<Coord> Pawn::getMoves(std::vector<std::vector<std::unique_ptr<Piece>>> field) const
{
    std::vector<Coord> moves;
    int dy = 1;
    Coord position = getCoord();

    if (getTeam() == Team::white)
    {
        dy = -1;
    }
    
    // Sliding moves (1 or 2 spaces forward)
    if (!field[position.x][position.y + dy])
    {
        moves.push_back(Coord{position.x, position.y + dy});
        if (position.x == 6 && !field[position.x][position.y  + 2 * dy])
        {
            moves.push_back(Coord{position.x, position.y + 2 * dy});
        }
    }

    // Attacking moves (one space diagonally)
    if (position.x < 7 && field[position.x + 1][position.y + dy] && 
        field[position.x + 1][position.y - 1]->getTeam() != getTeam())
    {
        moves.push_back(Coord{position.x + 1, position.y + dy});
    }

    if (position.x > 0 && field[position.x - 1][position.y + dy] && 
        field[position.x - 1][position.y - 1]->getTeam() != getTeam())
    {
        moves.push_back(Coord{position.x + 1, position.y + dy});
    }

    return moves;
}
