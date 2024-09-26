#include "board.hpp"
#include "piece.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "king.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include <cmath>

void Board::initializeTextures()
{
    sf::Texture wpawn;
    sf::Texture wrook;
    sf::Texture wbishop;
    sf::Texture wknight;
    sf::Texture wqueen;
    sf::Texture wking;

    wpawn.loadFromFile("ChessAssets/w_pawn_1x_ns.png");
    wrook.loadFromFile("ChessAssets/w_rook_1x_ns.png");
    wbishop.loadFromFile("ChessAssets/w_bishop_1x_ns.png");
    wknight.loadFromFile("ChessAssets/w_knight_1x_ns.png");
    wking.loadFromFile("ChessAssets/w_king_1x_ns.png");
    wqueen.loadFromFile("ChessAssets/w_queen_1x_ns.png");

    m_textures[PieceType::pawn] = wpawn;
    m_textures[PieceType::rook] = wrook;
    m_textures[PieceType::bishop] = wbishop;
    m_textures[PieceType::knight] = wknight;
    m_textures[PieceType::king] = wking;
    m_textures[PieceType::queen] = wqueen;
}

void Board::initializePieces()
{
    Team team1 = Team::white;
    Team team2 = Team::black;

    if (m_current_turn == Team::black)
    {
        std::swap(team1, team2);
        initializePiece<King>(PieceType::king, Coord{0, 3}, team2);
        initializePiece<King>(PieceType::king, Coord{7, 3}, team1);

        initializePiece<Queen>(PieceType::queen, Coord{0, 4}, team2);
        initializePiece<Queen>(PieceType::queen, Coord{7, 4}, team1);
    }
    else
    {
        initializePiece<King>(PieceType::king, Coord{0, 4}, team2);
        initializePiece<King>(PieceType::king, Coord{7, 4}, team1);

        initializePiece<Queen>(PieceType::queen, Coord{0, 3}, team2);
        initializePiece<Queen>(PieceType::queen, Coord{7, 3}, team1);
    }

    for (int i = 0; i < m_cols; ++i)
    {
        initializePiece<Pawn>(PieceType::pawn, Coord{1, i}, team2);
        static_cast<Pawn*>(m_field[1][i].get())->dr = 1;
        initializePiece<Pawn>(PieceType::pawn, Coord{6, i}, team1);
        static_cast<Pawn*>(m_field[6][i].get())->dr = -1;
    }

    initializePiece<Rook>(PieceType::rook, Coord{0, 0}, team2);
    initializePiece<Rook>(PieceType::rook, Coord{0, 7}, team2);

    initializePiece<Rook>(PieceType::rook, Coord{7, 0}, team1);
    initializePiece<Rook>(PieceType::rook, Coord{7, 7}, team1);

    initializePiece<Knight>(PieceType::knight, Coord{0, 1}, team2);
    initializePiece<Knight>(PieceType::knight, Coord{0, 6}, team2);

    initializePiece<Knight>(PieceType::knight, Coord{7, 1}, team1);
    initializePiece<Knight>(PieceType::knight, Coord{7, 6}, team1);

    initializePiece<Bishop>(PieceType::bishop, Coord{0, 2}, team2);
    initializePiece<Bishop>(PieceType::bishop, Coord{0, 5}, team2);

    initializePiece<Bishop>(PieceType::bishop, Coord{7, 2}, team1);
    initializePiece<Bishop>(PieceType::bishop, Coord{7, 5}, team1);


    m_player_king = m_field[7][4].get();
}


Board::Board(float horizontal_offset, float vertical_offset, float tile_size, int rows, int cols)
            : m_tile_size{tile_size}, m_rows{rows}, m_cols{cols}, m_horizontal_offset{horizontal_offset}, m_vertical_offset{vertical_offset}, m_field(m_rows)
{
    for (auto& row : m_field) row.resize(m_cols);
    initializeTextures();
    initializePieces();
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(m_tile_size, m_tile_size));
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            tile.setPosition(col * m_tile_size + m_horizontal_offset, row * m_tile_size + m_vertical_offset);
            tile.setFillColor((row + col) % 2 == 0 ? sf::Color(212, 182, 163) : sf::Color(48, 40, 35));
            tile.setOutlineColor(sf::Color::Black);
            target.draw(tile, states);
            if (m_field[row][col]) target.draw(m_field[row][col]->sprite, states);
        }
    }

    if (m_selected_piece)
    {
        for (auto &[row, col] : m_selected_piece->getMoves(m_field))
        {
            tile.setPosition(col * m_tile_size + m_horizontal_offset, row * m_tile_size + m_vertical_offset);
            tile.setFillColor(sf::Color(0, 0, 128, 128));
            tile.setOutlineColor(sf::Color::Black);
            target.draw(tile, states);
        }
    }
}

Coord Board::calculatePosition(int x, int y)
{
    int row = std::floor((y - m_vertical_offset) / m_tile_size);
    int col = std::floor((x - m_horizontal_offset) / m_tile_size);
    return Coord{row, col};
}

void Board::updateSelected(int mouse_x, int mouse_y)
{
    Coord clicked_tile = calculatePosition(mouse_x, mouse_y);

    if (clicked_tile.row < 0 || clicked_tile.col < 0 || clicked_tile.row > 7 || clicked_tile.col > 7)
    {
        m_selected_piece = nullptr;
    }
    else if (m_selected_piece)
    {
        std::vector<Coord> moves = m_selected_piece->getMoves(m_field);
        if (std::find(moves.begin(), moves.end(), clicked_tile) == moves.end())
        {
            if (!m_field[clicked_tile.row][clicked_tile.col] || m_field[clicked_tile.row][clicked_tile.col]->getTeam() != m_selected_piece->getTeam())
            {
                m_selected_piece = nullptr;
            }
            else
            {
                m_selected_piece = m_field[clicked_tile.row][clicked_tile.col].get();
            }
        }
        else
        {
            makeMove(m_selected_piece->getCoord(), clicked_tile);
            m_selected_piece = nullptr;
        }
    }
    else
    {
        if (m_field[clicked_tile.row][clicked_tile.col] && m_current_turn == m_field[clicked_tile.row][clicked_tile.col]->getTeam())
        {
            m_selected_piece = m_field[clicked_tile.row][clicked_tile.col].get();
        }
        else
        {
            m_selected_piece = nullptr;
        }
    }
}

// Precondition: move is valid
void Board::makeMove(Coord origin, Coord destination)
{
    m_field[destination.row][destination.col] = std::move(m_field[origin.row][origin.col]);
    m_field[destination.row][destination.col]->setCoord(destination);
    if (m_field[destination.row][destination.col]->getPieceType() == PieceType::pawn)
    {
        static_cast<Pawn*>(m_field[destination.row][destination.col].get())->has_moved = true;
    }
    setTexturePos(destination.row, destination.col);
    if (m_current_turn == Team::white) m_current_turn = Team::black;
    else m_current_turn = Team::white;
}

void Board::setTexturePos(int row, int col)
{
    m_field[row][col]->sprite.setPosition(col * m_tile_size + m_horizontal_offset, row * m_tile_size + m_vertical_offset);
    m_field[row][col]->sprite.setScale(
        m_tile_size * 0.8f / m_field[row][col]->sprite.getLocalBounds().width, 
        m_tile_size * 0.8f / m_field[row][col]->sprite.getLocalBounds().height
    );
    m_field[row][col]->sprite.move(m_tile_size * 0.1f, m_tile_size * 0.1f);
}

void Board::setCurrentTurn(Team team)
{
    m_current_turn = team;
}

void Board::resetBoard()
{
    m_field.clear();
    m_field.resize(m_rows);
    for (auto& row : m_field) row.resize(m_cols);
    initializePieces();
    m_current_turn = Team::white;
}
