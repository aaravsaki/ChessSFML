#include "board.hpp"

Board::Board(float horizontal_offset, float tile_size, int rows, int cols)
            : m_tile_size{tile_size}, m_rows{rows}, m_cols{cols}
{
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(m_tile_size, m_tile_size));
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < m_cols; ++j)
        {
             tile.setPosition(i * tile.getSize().x + 100, j * tile.getSize().x);
             tile.setFillColor((i+j) % 2 == 0 ? sf::Color::White : sf::Color::Black);
             tile.setOutlineColor(sf::Color::Black);
             target.draw(tile, states);
        }
    }
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

