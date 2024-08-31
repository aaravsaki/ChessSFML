#pragma once
#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include <map>
#include <memory>
#include <vector>

class Board : public sf::Drawable
{
    int m_rows;
    int m_cols;
    float m_tile_size;
    float m_horizontal_offset;
    std::map<PieceType, sf::Texture> textures;
    std::vector<std::vector<std::unique_ptr<Piece>>> field;

    void initialize_textures();

    template <typename T>
    void initialize_piece(PieceType piece_type, Coord position, Team team)
    {
        auto [x, y] = position;
        field[x][y] = std::make_unique<T>(piece_type, team, position);
        field[x][y]->sprite.setTexture(textures[piece_type]);
        if (team == Team::black) field[x][y]->sprite.setColor(sf::Color::Black);
        field[x][y]->sprite.setPosition(x * m_tile_size + m_horizontal_offset, y * m_tile_size);
        field[x][y]->sprite.setScale(m_tile_size * 0.8f / field[x][y]->sprite.getLocalBounds().width, m_tile_size * 0.8f / field[x][y]->sprite.getLocalBounds().height);
        field[x][y]->sprite.move(m_tile_size * 0.1f, m_tile_size * 0.1f);
    }

    void initialize_pieces();

public:
    Board(float horizontal_offset, float tile_size, int rows, int cols);
    ~Board() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states =sf::RenderStates()) const override;
};

