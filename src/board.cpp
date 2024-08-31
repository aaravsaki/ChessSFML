#include "board.hpp"
#include "piece.hpp"
#include "pawn.hpp"

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
        initialize_piece<Pawn>(PieceType::pawn, Coord{i, 1}, Team::black);
        initialize_piece<Pawn>(PieceType::pawn, Coord{i, 6}, Team::white);
    }
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
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < m_cols; ++j)
        {
            tile.setPosition(i * m_tile_size + m_horizontal_offset, j * m_tile_size);
            tile.setFillColor((i+j) % 2 == 0 ? sf::Color(212, 182, 163) : sf::Color(48, 40, 35));
            tile.setOutlineColor(sf::Color::Black);
            target.draw(tile, states);
            if (field[i][j]) target.draw(field[i][j]->sprite, states);

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

