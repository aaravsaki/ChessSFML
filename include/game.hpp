#pragma once
#include "board.hpp"

class Game
{
    sf::String m_name{"ChessSFML"};
    sf::RenderWindow m_window{};
    sf::Vector2u m_window_size{};
    Board m_board;

public:

    Game();
    ~Game() = default;
    void draw_board();
    void draw_all();
    void run();
};
