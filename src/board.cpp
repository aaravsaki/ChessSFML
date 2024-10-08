#include "board.hpp"
#include "piece.hpp"
#include "pawn.hpp" 
#include "knight.hpp"
#include "king.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include <cmath>
#include <string>
#include <iostream>

void Board::initializeTextures()
{
    sf::Texture wpawn;
    sf::Texture wrook;
    sf::Texture wbishop;
    sf::Texture wknight;
    sf::Texture wqueen;
    sf::Texture wking;

    wpawn.loadFromFile("ChessAssets/w_pawn_1x_ns.png");
    wrook.loadFromFile("ChessAssets/w_rook_1x_ns.png");
    wbishop.loadFromFile("ChessAssets/w_bishop_1x_ns.png");
    wknight.loadFromFile("ChessAssets/w_knight_1x_ns.png"); wking.loadFromFile("ChessAssets/w_king_1x_ns.png");
    wqueen.loadFromFile("ChessAssets/w_queen_1x_ns.png");

    m_textures[PieceType::pawn] = wpawn;
    m_textures[PieceType::rook] = wrook;
    m_textures[PieceType::bishop] = wbishop;
    m_textures[PieceType::knight] = wknight;
    m_textures[PieceType::king] = wking;
    m_textures[PieceType::queen] = wqueen;
}

void Board::initializePieces()
{
    Team team1 = Team::white;
    Team team2 = Team::black;

    if (m_current_turn == Team::black)
    {
        std::swap(team1, team2);
        initializePiece<King>(PieceType::king, Coord{0, 3}, team2);
        initializePiece<King>(PieceType::king, Coord{7, 3}, team1);

        initializePiece<Queen>(PieceType::queen, Coord{0, 4}, team2);
        initializePiece<Queen>(PieceType::queen, Coord{7, 4}, team1);
        m_player_king = m_field[7][3].get();
    }
    else
    {
        initializePiece<King>(PieceType::king, Coord{0, 4}, team2);
        initializePiece<King>(PieceType::king, Coord{7, 4}, team1);

        initializePiece<Queen>(PieceType::queen, Coord{0, 3}, team2);
        initializePiece<Queen>(PieceType::queen, Coord{7, 3}, team1);
        m_player_king = m_field[7][4].get();
    }

    for (int i = 0; i < m_cols; ++i)
    {
        initializePiece<Pawn>(PieceType::pawn, Coord{1, i}, team2);
        static_cast<Pawn*>(m_field[1][i].get())->dr = 1;
        initializePiece<Pawn>(PieceType::pawn, Coord{6, i}, team1);
        static_cast<Pawn*>(m_field[6][i].get())->dr = -1;
    }

    initializePiece<Rook>(PieceType::rook, Coord{0, 0}, team2);
    initializePiece<Rook>(PieceType::rook, Coord{0, 7}, team2);

    initializePiece<Rook>(PieceType::rook, Coord{7, 0}, team1);
    initializePiece<Rook>(PieceType::rook, Coord{7, 7}, team1);

    initializePiece<Knight>(PieceType::knight, Coord{0, 1}, team2);
    initializePiece<Knight>(PieceType::knight, Coord{0, 6}, team2);

    initializePiece<Knight>(PieceType::knight, Coord{7, 1}, team1);
    initializePiece<Knight>(PieceType::knight, Coord{7, 6}, team1);

    initializePiece<Bishop>(PieceType::bishop, Coord{0, 2}, team2);
    initializePiece<Bishop>(PieceType::bishop, Coord{0, 5}, team2);

    initializePiece<Bishop>(PieceType::bishop, Coord{7, 2}, team1);
    initializePiece<Bishop>(PieceType::bishop, Coord{7, 5}, team1);

}


Board::Board(float horizontal_offset, float vertical_offset, float tile_size, int rows, int cols)
            : m_tile_size{tile_size}, m_rows{rows}, m_cols{cols}, m_horizontal_offset{horizontal_offset}, m_vertical_offset{vertical_offset}, m_field(m_rows)
{
    for (auto& row : m_field) row.resize(m_cols);
    initializeTextures();
    initializePieces();
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(m_tile_size, m_tile_size));
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            tile.setPosition(col * m_tile_size + m_horizontal_offset, row * m_tile_size + m_vertical_offset);
            tile.setFillColor((row + col) % 2 == 0 ? sf::Color(212, 182, 163) : sf::Color(48, 40, 35));
            tile.setOutlineColor(sf::Color::Black);
            target.draw(tile, states);
            if (m_field[row][col]) target.draw(m_field[row][col]->sprite, states);
        }
    }

    if (m_selected_piece)
    {
        for (auto &[row, col] : m_selected_piece->getMoves(m_field))
        {
            tile.setPosition(col * m_tile_size + m_horizontal_offset, row * m_tile_size + m_vertical_offset);
            tile.setFillColor(sf::Color(0, 0, 128, 128));
            tile.setOutlineColor(sf::Color::Black);
            target.draw(tile, states);
        }

        if (m_selected_piece->getPieceType() == PieceType::king)
        {
            for (auto& it : getCastleMoves(m_selected_piece->getCoord()))
            {
                int row = it.first.row;
                int col = it.first.col;
                tile.setPosition(col * m_tile_size + m_horizontal_offset, row * m_tile_size + m_vertical_offset);
                tile.setFillColor(sf::Color(0, 0, 128, 128));
                tile.setOutlineColor(sf::Color::Black);
                target.draw(tile, states);
            }
        }
    }
}

Coord Board::calculatePosition(int x, int y)
{
    int row = std::floor((y - m_vertical_offset) / m_tile_size);
    int col = std::floor((x - m_horizontal_offset) / m_tile_size);
    return Coord{row, col};
}

void Board::updateSelected(int mouse_x, int mouse_y)
{
    Coord clicked_tile = calculatePosition(mouse_x, mouse_y);
    Piece* clicked_piece = m_field[clicked_tile.row][clicked_tile.col].get();
    
    // Clicked out of bounds
    if (clicked_tile.row < 0 || clicked_tile.col < 0 || clicked_tile.row > 7 || clicked_tile.col > 7) { m_selected_piece = nullptr; }

    // Clicked with piece already selected
    else if (m_selected_piece)
    {
        std::unordered_set<Coord> moves = m_selected_piece->getMoves(m_field);
        std::unordered_map<Coord, Coord> castle_moves;
        Coord current_piece_tile = m_selected_piece->getCoord();

        if (m_selected_piece->getPieceType() == PieceType::king) { castle_moves = getCastleMoves(current_piece_tile); }
        
        if (!moves.contains(clicked_tile) && !castle_moves.contains(clicked_tile))
        {
            // Clicking enemy team piece that is out of range
            if (!clicked_piece || clicked_piece->getTeam() != m_selected_piece->getTeam()) { m_selected_piece = nullptr; }

            // Clicking different friendly piece
            else { m_selected_piece = clicked_piece; }
        }
        else if (castle_moves.contains(clicked_tile))
        {
            castle(m_selected_piece->getCoord(), castle_moves[clicked_tile]);
            updateTurn();
            makeComputerMove();
            updateTurn();
        }
        // Clicked valid move tile
        else
        {
            Coord origin = m_selected_piece->getCoord();
            std::unique_ptr<Piece> temp = std::move(silentMove(origin, clicked_tile));
            bool still_checked = playerInCheck();
            undoSilentMove(origin, clicked_tile, std::move(temp));

            if (!still_checked) 
            {
                std::string player_move = coordToMove(origin) + coordToMove(clicked_tile); makeMove(origin, clicked_tile);
                move_list.push_back(player_move);
                cmmove += player_move + " ";
                updateTurn();
                makeComputerMove();
                updateTurn();
            }

            m_selected_piece = nullptr;
        }
    }
    // Clicked in bounds with no piece already selected
    else
    {
        if (clicked_piece && m_current_turn == clicked_piece->getTeam()) { m_selected_piece = clicked_piece; }

        else { m_selected_piece = nullptr; }
    }
}

void Board::makeComputerMove()
{
    std::string computer_move = computer.calculateBestMove(move_list); cmmove += computer_move + " ";
    Coord comp_origin = moveToCoord(computer_move.substr(0, 2));
    Coord comp_destination = moveToCoord(computer_move.substr(2));
    makeMove(comp_origin, comp_destination);
    move_list.push_back(computer_move);
}

// 'Silently' moves a piece, returning the taken piece if there was one
// or nullptr otherwise, so that the move can be undone
std::unique_ptr<Piece> Board::silentMove(Coord origin, Coord destination)
{
    std::unique_ptr<Piece> temp = std::move(m_field[destination.row][destination.col]);
    m_field[destination.row][destination.col] = std::move(m_field[origin.row][origin.col]);
    m_field[destination.row][destination.col]->setCoord(destination);
    return temp;
}

void Board::undoSilentMove(Coord origin, Coord destination, std::unique_ptr<Piece> original_piece)
{
    m_field[origin.row][origin.col] = std::move(m_field[destination.row][destination.col]);
    m_field[origin.row][origin.col]->setCoord(origin);
    m_field[destination.row][destination.col] = std::move(original_piece);
}


bool Board::castlePossible(const Coord& king_current_tile, const Coord& rook_current_tile) const
{
    Piece* king = m_field[king_current_tile.row][king_current_tile.col].get();
    Piece* rook = m_field[rook_current_tile.row][rook_current_tile.col].get();

    if (king->has_moved || rook->has_moved) return false;

    std::unordered_set<Coord> attacked_squares = generateAttackedSquares();
    if (attacked_squares.contains(king_current_tile)) { return false; }
    int castle_row = king_current_tile.row;

    int king_dc = 1;
    if (rook_current_tile.col < king_current_tile.col) { king_dc = -1; }
    int destination_col = king_current_tile.col + 2 * king_dc;

    for (int col = king_current_tile.col + king_dc; col != destination_col + king_dc; col += king_dc)
    {
        if (attacked_squares.contains(Coord{castle_row, col})) { 
            return false; 
        }
    }

    int rook_dc = 1;
    if (rook_current_tile.col > king_current_tile.col) { rook_dc = -1; }

    for (int col = rook_current_tile.col + rook_dc; col != king_current_tile.col; col += rook_dc)
    {
        if (m_field[castle_row][col]) { return false; }
    }

    return true;
}

std::unordered_map<Coord, Coord> Board::getCastleMoves(const Coord& king_current_tile) const
{
    std::unordered_map<Coord, Coord> castle_moves;
    constexpr int ROOK1_COL = 7;
    constexpr int ROOK2_COL = 0;
    constexpr int KING_CASTLE_JUMP = 2;
    Coord rook1_tile{king_current_tile.row, ROOK1_COL};
    Coord rook2_tile{king_current_tile.row, ROOK2_COL};


    if (m_field[king_current_tile.row][ROOK1_COL] && m_field[king_current_tile.row][ROOK1_COL]->getPieceType() == PieceType::rook && castlePossible(king_current_tile, rook1_tile))
    {
        castle_moves[Coord{king_current_tile.row, king_current_tile.col + KING_CASTLE_JUMP}] = rook1_tile;
    }

    if (m_field[king_current_tile.row][ROOK2_COL] && m_field[king_current_tile.row][ROOK2_COL]->getPieceType() == PieceType::rook && castlePossible(king_current_tile, rook2_tile))
    {
        castle_moves[Coord{king_current_tile.row, king_current_tile.col - KING_CASTLE_JUMP}] = rook2_tile;
    }

    return castle_moves;
}

void Board::castle(const Coord& king_current_tile, const Coord& rook_current_tile)
{
    int dc = 1;
    if (king_current_tile.col > rook_current_tile.col) { dc = -1; }

    Coord king_destination{king_current_tile.row, king_current_tile.col + 2 * dc};
    makeMove(king_current_tile, king_destination);

    Coord rook_destination{rook_current_tile.row, king_current_tile.col + dc};
    makeMove(rook_current_tile, rook_destination);

    std::string castle_move = coordToMove(king_current_tile) + coordToMove(king_destination);
    move_list.push_back(castle_move);
}

// Precondition: move is valid
void Board::makeMove(Coord origin, Coord destination)
{
    m_field[destination.row][destination.col] = std::move(m_field[origin.row][origin.col]);
    m_field[destination.row][destination.col]->setCoord(destination);
    m_field[destination.row][destination.col]->has_moved = true;
    m_field[origin.row][origin.col] = nullptr;
    if (m_field[destination.row][destination.col]->getPieceType() == PieceType::pawn)
    {
        static_cast<Pawn*>(m_field[destination.row][destination.col].get())->has_moved = true;
    }
    setTexturePos(destination.row, destination.col);
}

void Board::updateTurn()
{
    if (m_current_turn == Team::white) m_current_turn = Team::black;
    else m_current_turn = Team::white;
    player_in_check = playerInCheck();
}

void Board::setTexturePos(int row, int col)
{
    m_field[row][col]->sprite.setPosition(col * m_tile_size + m_horizontal_offset, row * m_tile_size + m_vertical_offset);
    m_field[row][col]->sprite.setScale(
        m_tile_size * 0.8f / m_field[row][col]->sprite.getLocalBounds().width, 
        m_tile_size * 0.8f / m_field[row][col]->sprite.getLocalBounds().height
    );
    m_field[row][col]->sprite.move(m_tile_size * 0.1f, m_tile_size * 0.1f);
}

void Board::setCurrentTurn(Team team)
{
    m_current_turn = team;
}

void Board::resetBoard()
{
    m_field.clear();
    move_list.clear();
    m_field.resize(m_rows);
    for (auto& row : m_field) row.resize(m_cols);
    initializePieces();
    m_current_turn = Team::white;
}

std::unordered_set<Coord> Board::generateAttackedSquares() const
{
    std::unordered_set<Coord> attacked_squares;
    std::unordered_set<Coord> piece_threats;
    Team player_team = m_player_king->getTeam();

    for (const auto& row : m_field)
    {
        for (const auto& tile : row)
       {
            if (tile && tile->getTeam() != player_team) piece_threats = tile->getMoves(m_field);
            attacked_squares.merge(piece_threats);
        }
    }
    return attacked_squares;
}

bool Board::playerInCheck() const
{
    Coord king_location = m_player_king->getCoord();
    Team player_team = m_player_king->getTeam();
    std::unordered_set<Coord> attacked_squares = generateAttackedSquares();
    return attacked_squares.contains(king_location);
}

std::string Board::coordToMove(Coord coord)
{
    std::string move;
    if (m_player_king->getTeam() == Team::white)
    {
        move += char('a' + coord.col);
        move += std::to_string(8 - coord.row);
    }
    else
    {
        move += char('h' - coord.col);
        move += std::to_string(coord.row + 1);
    }
    return move;
}

Coord Board::moveToCoord(std::string move)
{
    int row, col;
    if (m_player_king->getTeam() == Team::white)
    {
        row = 8 - std::stoi(move.substr(1));
        col = move[0] - 'a';
    }
    else
    {
        row = std::stoi(move.substr(1)) - 1;
        col = 'h' - move[0];
    }
    return Coord{row, col};
}
