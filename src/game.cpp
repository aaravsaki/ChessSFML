#include "game.hpp"

namespace Menu
{
    void ShowMenuWindow(Board& board, bool* p_open = nullptr)
    {
        if (!ImGui::Begin("Menu", p_open))
        {
            ImGui::End();
            return;
        }

        ImGui::SeparatorText("Game Settings");
        if (ImGui::Button("Reset as White")) 
        {
            board.setCurrentTurn(Team::white);
            board.resetBoard();
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset as Black"))
        {
            board.setCurrentTurn(Team::black);
            board.resetBoard();
            board.makeComputerMove();
            board.updateTurn();
        }
        ImGui::SeparatorText("Computer Settings");
        ImGui::SeparatorText("Shortcuts");
        //ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
        //ImGui::PopItemWidth();
        ImGui::End();
    }

    void ShowCheckWindow(Board& board, bool* p_open = nullptr)
    {        
        // Overlay window adapted from imgui demo
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

        int location = 1;
        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos;
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos, window_pos_pivot;
        window_pos.x = work_pos.x + work_size.x - PAD;
        window_pos.y = work_pos.y + PAD;
        window_pos_pivot.x = 1.0f;
        window_pos_pivot.y = 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        ImGui::SetNextWindowBgAlpha(0.35f);

        if (!ImGui::Begin("Game Info Overlay", p_open, window_flags))
        {
            ImGui::End();
            return;
        }

        if (board.game_over)
        {
            if (board.player_in_check) { ImGui::Text("Game Over: Computer Wins"); }
            else if (board.computer_in_check) { ImGui::Text("Game Over: Player Wins"); }
            else { ImGui::Text("Game Over: Stalemate"); }
        }
        else if (board.player_in_check) { ImGui::Text("Player in Check"); }
        else if (board.computer_in_check) { ImGui::Text("Computer in Check"); }
        else { ImGui::Text("Not in Check"); }

        ImGui::SeparatorText("Move List");
        ImGui::Text("%s ", board.cmmove.c_str());
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
    int err = ImGui::SFML::Init(m_window); // return later
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
        Menu::ShowMenuWindow(m_board);
        Menu::ShowCheckWindow(m_board);
        //ImGui::ShowDemoWindow();

        m_window.clear(sf::Color(104, 40, 42));
        draw_all();
        ImGui::SFML::Render(m_window);
        m_window.display();
    }
    ImGui::SFML::Shutdown();
}


