#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <boost/functional/hash.hpp>

enum class PieceType {empty, pawn, knight, bishop, rook, queen, king};
enum class Team {none, white, black};

struct Coord
{
    int row;
    int col;

    auto operator<=>(const Coord&) const = default;

};

template <>
struct std::hash<Coord>
{
    std::size_t operator()(const Coord& coord) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, boost::hash_value(coord.row));
        boost::hash_combine(seed, boost::hash_value(coord.col));
        return seed;
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
    PieceType getPieceType() const;
    void setCoord(Coord destination);
    virtual std::unordered_set<Coord> getMoves(const std::vector<std::vector<std::unique_ptr<Piece>>>&) const = 0;
    virtual ~Piece() = default;

    sf::Sprite sprite;
    bool has_moved{false};
};
