#include "slider.hpp"

Slider::Slider(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}

std::unordered_set<Coord> Slider::getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const
{
    std::unordered_set<Coord> moves;
    Coord position = getCoord();

    for (auto &[dr, dc] : directions)
    {
        for (int row = position.row + dr, col = position.col + dc; row >= 0 && row < field.size() && col >= 0 && col < field.size(); row += dr, col += dc)
        {
            if (!field[row][col])
            {
                moves.insert(Coord{row, col});
            }
            else if (field[row][col]->getTeam() != getTeam())
            {
                moves.insert(Coord{row, col});
                break;
            }
            else
            {
                break;
            }
        }
    }

    return moves;
}

