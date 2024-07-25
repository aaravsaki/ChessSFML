#pragma once
#include <SFML/Graphics.hpp>

class Board : public sf::Drawable
{
    int m_rows;
    int m_cols;
    float m_tile_size;
    int pieces[8][8] = {0};

public:
    Board(float horizontal_offset, float tile_size, int rows, int cols);
    ~Board() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states =sf::RenderStates()) const override;
};

