#include "knight.hpp"

Knight::Knight(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}

std::vector<Coord> Knight::getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const
{
    auto [row, col] = getCoord();
    std::vector<Coord> moves;
    for (auto &[dr, dc] : directions)
    {
        if (
            row + dr >= 0 
            && col + dc >= 0 
            && row + dr < field.size() 
            && col + dc < field.size()
            && (!field[row+dr][col+dc] || field[row+dr][col+dc]->getTeam() != getTeam())
        )
        {
            moves.push_back(Coord{row + dr, col + dc});
        }
    }
    return moves;
}