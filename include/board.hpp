#pragma once
#include "piece.hpp"
#include "uci.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
#include <string_view>
#include <unordered_map>

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
    Piece* m_player_king;
    Team m_current_turn{Team::white};

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

    // Returns list of squares currently 'attacked' by computer's pieces
    std::unordered_set<Coord> generateAttackedSquares() const;

    bool castlePossible(const Coord& king_current_tile, const Coord& rook_current_tile) const;

    std::string coordToMove(Coord coord);

    Coord moveToCoord(std::string move);

    std::unordered_map<Coord, Coord> getCastleMoves(const Coord& king_current_tile) const;

    void castle(const Coord& king_current_tile, const Coord& rook_current_tile);

public:
    Board(float horizontal_offset, float vertical_offset, float tile_size, int rows, int cols);

    ~Board() = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const override;

    void updateSelected(int mouse_x, int mouse_y);

    std::unique_ptr<Piece> silentMove(Coord origin, Coord destination);

    void undoSilentMove(Coord origin, Coord destination, std::unique_ptr<Piece> original_piece);

    void makeMove(Coord origin, Coord destination);

    void makeMove(std::string_view);

    void makeComputerMove();

    void resetBoard();

    bool playerInCheck() const;

    bool playerInCheckmate() const;

    void setCurrentTurn(Team team);
    
    void updateTurn();

    bool player_in_check{false};

    std::vector<std::string> move_list;


    Computer computer;
    std::string cmmove;
};

