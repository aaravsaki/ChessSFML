#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class PieceType {empty, pawn, knight, bishop, rook, queen, king};
enum class Team {none, white, black};

struct Coord
{
    int row;
    int col;

    bool operator==(const Coord&) const = default;
    bool operator<(const Coord& other)
    {
        return (row < other.col || row == other.row && col < other.col);
    }
};

class Piece
{
private:
    PieceType m_type{PieceType::empty};
    Team m_team{Team::none};
    Coord m_pos{-1, -1};

public:
    Piece() = delete;
    Piece(PieceType piece_type, Team team, Coord position);
    Team getTeam() const;
    Coord getCoord() const;
    void setCoord(Coord destination);
    virtual std::vector<Coord> getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>&) const = 0;
    virtual ~Piece() = default;

    sf::Sprite sprite;
};
