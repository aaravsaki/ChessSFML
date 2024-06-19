#include "board.hpp"

Board::Tile::Tile(float size, const sf::Vector2f& pos, const sf::Color& color,
                  const sf::Color& outline_color, float outline_thickness)
                  : m_position{pos}
{
    box.setSize(sf::Vector2f(size, size));
    box.setPosition(m_position);
    box.setFillColor(color);
    box.setOutlineColor(outline_color);
    box.setOutlineThickness(outline_thickness);
}

void Board::Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(box, states);
}

Board::Board(float horizontal_offset, float tile_size, int rows, int cols)
            : m_rows{rows}, m_cols{cols}
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            tiles.push_back(Board::Tile{
                            tile_size, 
                            sf::Vector2f(i * tile_size + horizontal_offset, j * tile_size),
                            (i+j) % 2 == 0 ? sf::Color::White : sf::Color::Black,
                            sf::Color::Black,
                            1}
            );
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto tile : tiles) target.draw(tile, states);
}

