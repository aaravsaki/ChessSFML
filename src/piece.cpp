#include "piece.hpp"

Piece::Piece(PieceType piece_type, Team team, Coord position)
            : m_type{piece_type}, m_team{team}, m_pos{position}
{
}

Team Piece::getTeam() const
{
    return m_team;
}

Coord Piece::getCoord() const
{
    return m_pos;
}

void Piece::setCoord(Coord destination)
{
    m_pos = destination;
}
