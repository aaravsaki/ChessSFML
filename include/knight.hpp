#pragma once
#include "piece.hpp"

class Knight : public Piece
{
public:
    Knight() = delete;
    Knight(PieceType piece_type, Team team, Coord position);
    std::set<Coord> getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>& field) const override;
    ~Knight() override = default;
private:
    std::vector<Coord> directions{
        Coord{-1, -2}, 
        Coord{-1, 2}, 
        Coord{1, -2}, 
        Coord{1, 2}, 
        Coord{-2, -1}, 
        Coord{-2, 1}, 
        Coord{2, -1}, 
        Coord{2, 1}
    };
};
