#pragma once
#include <SFML/Graphics.hpp>

class Game
{
    sf::Vector2u window_size(1920u, 1080u);
    sf::RenderWindow window;

public:
    Game();
    ~Game() = default;
};
