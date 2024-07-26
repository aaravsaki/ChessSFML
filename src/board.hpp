#pragma once
#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include <vector>

class Board : public sf::Drawable
{
    int m_rows;
    int m_cols;
    float m_tile_size;
    float m_horizontal_offset;
    sf::Texture pawn_img;
    std::vector<std::vector<Piece>> pieces;

public:
    Board(float horizontal_offset, float tile_size, int rows, int cols);
    ~Board() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states =sf::RenderStates()) const override;
};

