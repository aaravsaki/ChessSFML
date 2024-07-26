#include "game.hpp"

Game::Game() 
    : m_window{sf::VideoMode::getDesktopMode(), m_name},
    m_window_size{m_window.getSize()},
    m_board((m_window_size.x - m_window_size.y * 0.8f) / 2.0f, m_window_size.y / 8.0f * 0.8f, 8, 8)
{
}

void Game::draw_all()
{
    m_window.draw(m_board);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        m_window.clear(sf::Color(104, 40, 42));
        draw_all();
        m_window.display();
    }
}
