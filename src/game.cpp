#include "game.hpp"

Game::Game() 
    : m_window{sf::VideoMode(m_window_size.x, m_window_size.y), m_name}
{
}

void Game::run()
{
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(m_window_size.x / 2, m_window_size.y / 2);

    while (m_window.isOpen())
    {
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        m_window.clear();
        m_window.draw(shape);
        m_window.display();
    }
}
