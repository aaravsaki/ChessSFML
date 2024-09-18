#include "king.hpp"

King::King(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}

std::vector<Coord> King::getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const
{
    std::vector<Coord> moves;

    std::vector<Coord> directions{
        Coord{1,1}, 
        Coord{1,0}, 
        Coord{1,-1}, 
        Coord{0,1}, 
        Coord{0,-1}, 
        Coord{-1,1}, 
        Coord{-1,0}, 
        Coord{-1,-1}
    };

    Coord position = getCoord();

    for (auto &[dr, dc] : directions)
    {
        Coord target{position.row + dr, position.col + dc};
        if (target.row >= 0 && target.col >= 0 && target.row < field.size() && target.col < field.size())
        {
            if (!field[target.row][target.col] || field[target.row][target.col]->getTeam() != getTeam())
            {
                moves.push_back(target);
            }
        }
    }


    return moves;
}
