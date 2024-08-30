#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class PieceType {empty, pawn, knight, bishop, rook, queen, king};
enum class Team {none, white, black};

struct Coord
{
    int x;
    int y;
};

class Piece
{
private:
    PieceType m_type{PieceType::empty};
    Team m_team{Team::none};
    Coord m_pos{-1, -1};

public:
    Piece() = default;
    Piece(PieceType piece_type, Team team, Coord position);
    Team getTeam() const;
    Coord getCoord() const;
    virtual std::vector<Coord> getMoves(std::vector<std::vector<std::unique_ptr<Piece>>>) const = 0;
    virtual ~Piece() = default;

    sf::Sprite sprite;
};
