#include "king.hpp"

King::King(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}


std::vector<Coord> King::getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const
{
    std::vector<Coord> moves;
    int dy = 1;
    Coord position = getCoord();

    if (getTeam() == Team::white)
    {
        dy = -1;
    }
    
    // Sliding moves (1 or 2 spaces forward)
    if (!field[position.row][position.col + dy])
    {
        moves.push_back(Coord{position.row, position.col + dy});
        if (position.row == 6 && !field[position.row][position.col  + 2 * dy])
        {
            moves.push_back(Coord{position.row, position.col + 2 * dy});
        }
    }

    // Attacking moves (one space diagonally)
    if (position.row < 7 && field[position.row + 1][position.col + dy] && 
        field[position.row + 1][position.col - 1]->getTeam() != getTeam())
    {
        moves.push_back(Coord{position.row + 1, position.col + dy});
    }

    if (position.row > 0 && field[position.row - 1][position.col + dy] && 
        field[position.row - 1][position.col - 1]->getTeam() != getTeam())
    {
        moves.push_back(Coord{position.row + 1, position.col + dy});
    }

    return moves;
}
