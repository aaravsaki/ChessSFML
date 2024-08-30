#include "slider.hpp"

Slider::Slider(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}

std::vector<Coord> Slider::getMoves(std::vector<std::vector<std::unique_ptr<Piece>>> field) const
{
    std::vector<Coord> moves;
    Coord position = getCoord();

    for (auto &[dx, dy] : directions)
    {
        for (int x = position.x, y = position.y; x>= 0 && x < field.size() && y >= 0 && y < field[0].size(); x += dx, y += dy)
        {
            if (!field[x][y])
            {
                moves.push_back(Coord{x, y});
            }
            else if (field[x][y]->getTeam() != getTeam())
            {
                moves.push_back(Coord{x, y});
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
