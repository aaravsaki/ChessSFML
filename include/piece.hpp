#pragma once
#include <SFML/Graphics.hpp>
#include <set>

enum class PieceType {empty, pawn, knight, bishop, rook, queen, king};
enum class Team {none, white, black};

struct Coord
{
    int row;
    int col;

    auto operator<=>(const Coord&) const = default;

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
    PieceType getPieceType() const;
    void setCoord(Coord destination);
    virtual std::set<Coord> getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>&) const = 0;
    virtual ~Piece() = default;

    sf::Sprite sprite;
};
