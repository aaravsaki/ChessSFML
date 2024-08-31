#include "board.hpp"
#include "piece.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "king.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "rook.hpp"

void Board::initialize_textures()
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

    textures[PieceType::pawn] = wpawn;
    textures[PieceType::rook] = wrook;
    textures[PieceType::bishop] = wbishop;
    textures[PieceType::knight] = wknight;
    textures[PieceType::king] = wking;
    textures[PieceType::queen] = wqueen;
}

void Board::initialize_pieces()
{
    for (int i = 0; i < m_cols; ++i)
    {
        initialize_piece<Pawn>(PieceType::pawn, Coord{1, i}, Team::black);
        initialize_piece<Pawn>(PieceType::pawn, Coord{6, i}, Team::white);
    }

    initialize_piece<Rook>(PieceType::rook, Coord{0, 0}, Team::black);
    initialize_piece<Rook>(PieceType::rook, Coord{0, 7}, Team::black);

    initialize_piece<Rook>(PieceType::rook, Coord{7, 0}, Team::white);
    initialize_piece<Rook>(PieceType::rook, Coord{7, 7}, Team::white);

    initialize_piece<Knight>(PieceType::knight, Coord{0, 1}, Team::black);
    initialize_piece<Knight>(PieceType::knight, Coord{0, 6}, Team::black);

    initialize_piece<Knight>(PieceType::knight, Coord{7, 1}, Team::white);
    initialize_piece<Knight>(PieceType::knight, Coord{7, 6}, Team::white);

    initialize_piece<Bishop>(PieceType::bishop, Coord{0, 2}, Team::black);
    initialize_piece<Bishop>(PieceType::bishop, Coord{0, 5}, Team::black);

    initialize_piece<Bishop>(PieceType::bishop, Coord{7, 2}, Team::white);
    initialize_piece<Bishop>(PieceType::bishop, Coord{7, 5}, Team::white);

    initialize_piece<King>(PieceType::king, Coord{0, 4}, Team::black);
    initialize_piece<King>(PieceType::king, Coord{7, 4}, Team::white);

    initialize_piece<Queen>(PieceType::queen, Coord{0, 3}, Team::black);
    initialize_piece<Queen>(PieceType::queen, Coord{7, 3}, Team::white);
}

Board::Board(float horizontal_offset, float tile_size, int rows, int cols)
            : m_tile_size{tile_size}, m_rows{rows}, m_cols{cols}, m_horizontal_offset{horizontal_offset}, field(m_rows)
{
    for (auto& row : field) row.resize(m_cols);
    initialize_textures();
    initialize_pieces();
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(m_tile_size, m_tile_size));
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            tile.setPosition(col * m_tile_size + m_horizontal_offset, row * m_tile_size);
            tile.setFillColor((row + col) % 2 == 0 ? sf::Color(212, 182, 163) : sf::Color(48, 40, 35));
            tile.setOutlineColor(sf::Color::Black);
            target.draw(tile, states);
            if (field[row][col]) target.draw(field[row][col]->sprite, states);

        }
    }

    
    //Drawing piece process
    //sf::Sprite sprite;
    //sprite.setTexture(pawn_img);
    //sprite.setPosition(m_horizontal_offset, 0);
    //sprite.setScale(m_tile_size * 0.8f / sprite.getLocalBounds().width, m_tile_size * 0.8f / sprite.getLocalBounds().height);
    //sprite.move(m_tile_size * 0.1f, m_tile_size * 0.1f);
    //target.draw(sprite, states);
}

// def magic function()
//  if mouse pressed:
//      get piece at mouse press
//      await mouse release
//      get piece at mouse release
//      if can take, take
//      if own piece, reset,
//      if empty, move
//      add additional checks for check/checkmate later

