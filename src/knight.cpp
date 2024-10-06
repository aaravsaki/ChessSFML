#include "knight.hpp"

Knight::Knight(PieceType piece_type, Team team, Coord position)
    : Piece(piece_type, team, position)
{
}

std::unordered_set<Coord> Knight::getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const
{
    auto [row, col] = getCoord();
    std::unordered_set<Coord> moves;
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
            moves.insert(Coord{row + dr, col + dc});
        }
    }
    return moves;
}
