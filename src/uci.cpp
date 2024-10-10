#include "uci.hpp"
#include <iostream>

Computer::Computer()
{
    initializeComputer();
    m_engine.detach();
}

bool Computer::send(std::string_view message) 
{
    m_engine_receiver << message << std::endl;
    return m_engine_receiver.good();
}

bool Computer::receive(std::string_view message, int await_lines)
{
    for (std::string line; std::getline(m_engine_output, line); await_lines--)
    {
        if (line == message) return true;
    }
    return false;
}

bool Computer::sendAndReceive(std::string_view message, std::string_view response)
{
    return send(message) && receive(response);
}

bool Computer::initializeComputer()
{
    return sendAndReceive("uci", "uciok") 
        && send("ucinewgame")
        && sendAndReceive("isready", "readyok");
}

std::string Computer::calculateBestMove(std::vector<std::string> move_list, int await_lines)
{
    std::string position{"position startpos"};
    if (!move_list.empty()) position += " moves";
    for (auto move : move_list)
    {
        position += (" " + move);
        std::cout << position << std::endl;
    }

    send(position);
    sendAndReceive("isready", "readyok");
    send("go depth 20");

    for (std::string line; std::getline(m_engine_output, line); await_lines--)
    {
        std::cout << line << std::endl;
        auto it = line.find("bestmove");
        if (it != line.npos) {

            std::cout << line.substr(9, 4);
            return line.substr(9, 4);
        }
    }
    return "0000";
}
