#pragma once
#include <SFML/Graphics.hpp>

class Game
{
    sf::Vector2u m_window_size{1920u, 1080u};
    sf::String m_name{"ChessSFML"};
    sf::RenderWindow m_window{};

public:
    Game();
    ~Game() = default;
    void run();
};
