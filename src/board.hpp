#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Board : public sf::Drawable
{
    class Tile : public sf::Drawable
    {
        sf::Vector2f m_position;
        sf::RectangleShape box{};
        //Piece piece;
        
    public:
        Tile(float size, const sf::Vector2f& pos, const sf::Color& color,
            const sf::Color& outline_color, float outline_thickness);
        ~Tile() = default;
        void draw(sf::RenderTarget& target, sf::RenderStates states =sf::RenderStates()) const override;
    };

    std::vector<Tile> tiles;
    int m_rows;
    int m_cols;

public:
    Board(float horizontal_offset, float tile_size, int rows, int cols);
    ~Board() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states =sf::RenderStates()) const override;
};

