#include "knight.hpp"

Knight::Knight(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}

std::vector<Coord> Knight::getMoves(std::vector<std::vector<std::unique_ptr<Piece>>> field) const
{
    auto [x, y] = getCoord();
    std::vector<Coord> moves;
    for (auto &[dx, dy] : directions)
    {
        if (
            x + dx >= 0 
            && y + dy >= 0 
            && x + dx < field.size() 
            && y + dy < field.size()
            && (!field[x+dx][y+dy] || field[x+dx][y+dy]->getTeam() != getTeam())
        )
        {
            moves.push_back(Coord{x + dx, y + dy});
        }
    }
    return moves;
}
