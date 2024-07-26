#include "board.hpp"

Board::Board(float horizontal_offset, float tile_size, int rows, int cols)
            : m_tile_size{tile_size}, m_rows{rows}, m_cols{cols}, m_horizontal_offset{horizontal_offset}
{
    pawn_img.loadFromFile("ChessAssets/b_pawn_1x_ns.png");
    pawn_img.setSmooth(true);
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
             tile.setFillColor((i+j) % 2 == 0 ? sf::Color::White : sf::Color::Black);
             tile.setOutlineColor(sf::Color::Black);
             if (i == 0 && j == 0) tile.setFillColor(sf::Color::Green);
             target.draw(tile, states);
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

