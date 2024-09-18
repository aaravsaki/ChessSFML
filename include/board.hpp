#pragma once
#include <cmath>
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
    float m_vertical_offset;
    std::map<PieceType, sf::Texture> m_textures;
    std::vector<std::vector<std::unique_ptr<Piece>>> m_field;
    Piece* m_selected_piece = nullptr;
    Team currentTurn{Team::white};

    void initializeTextures();

    template <typename T>
    void initializePiece(PieceType piece_type, Coord position, Team team)
    {
        auto [row, col] = position;
        m_field[row][col] = std::make_unique<T>(piece_type, team, position);
        m_field[row][col]->sprite.setTexture(m_textures[piece_type]);
        if (team == Team::black) m_field[row][col]->sprite.setColor(sf::Color::Black);
        setTexturePos(row, col);
    }

    void initializePieces();
    void setTexturePos(int row, int col);

    // Given the (x, y) coordinates of a mouse click,
    // calculates the respective board coordinate
    Coord calculatePosition(int x, int y);

public:
    Board(float horizontal_offset, float vertical_offset, float tile_size, int rows, int cols);
    ~Board() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states =sf::RenderStates()) const override;
    void updateSelected(int mouse_x, int mouse_y);
    void makeMove(Coord origin, Coord destination);
    void resetBoard();
};

