#include "game.hpp"

namespace Menu
{
    void ShowMenuWindow(bool* p_open, Board& board)
    {
        if (!ImGui::Begin("Menu", p_open))
        {
            ImGui::End();
            return;
        }

        ImGui::SeparatorText("Game Settings");
        if (ImGui::Button("Reset Board")) board.resetBoard();
        //ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
        //ImGui::PopItemWidth();
        ImGui::End();
    }
}

Game::Game() 
    : m_window{sf::VideoMode::getDesktopMode(), m_name},
    m_window_size{m_window.getSize()},
    m_board((m_window_size.x - m_window_size.y * 0.8f) / 2.0f, 50, m_window_size.y / 8.0f * 0.8f, 8, 8)
{
}

void Game::draw_all()
{
    m_window.draw(m_board);
}

void Game::run()
{    
    m_window.setFramerateLimit(60);
    ImGui::SFML::Init(m_window);
    sf::Clock deltaClock;

    while (m_window.isOpen())
    {
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            ImGui::SFML::ProcessEvent(m_window, event);
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m_board.updateSelected(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
        ImGui::SFML::Update(m_window, deltaClock.restart());
        Menu::ShowMenuWindow(nullptr, m_board);
        //ImGui::ShowDemoWindow();

        m_window.clear(sf::Color(104, 40, 42));
        draw_all();
        ImGui::SFML::Render(m_window);
        m_window.display();
    }
    ImGui::SFML::Shutdown();
}


