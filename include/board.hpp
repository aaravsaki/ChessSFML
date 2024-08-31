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
        auto [row, col] = position;
        field[row][col] = std::make_unique<T>(piece_type, team, position);
        field[row][col]->sprite.setTexture(textures[piece_type]);
        if (team == Team::black) field[row][col]->sprite.setColor(sf::Color::Black);
        field[row][col]->sprite.setPosition(col * m_tile_size + m_horizontal_offset, row * m_tile_size);
        field[row][col]->sprite.setScale(m_tile_size * 0.8f / field[row][col]->sprite.getLocalBounds().width, m_tile_size * 0.8f / field[row][col]->sprite.getLocalBounds().height);
        field[row][col]->sprite.move(m_tile_size * 0.1f, m_tile_size * 0.1f);
    }

    void initialize_pieces();

public:
    Board(float horizontal_offset, float tile_size, int rows, int cols);
    ~Board() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states =sf::RenderStates()) const override;
};

