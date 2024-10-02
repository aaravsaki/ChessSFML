#pragma once
#include <boost/process.hpp>
#include <string>
#include <vector>

namespace bp = boost::process;

class Computer
{
public:
    Computer();
    std::string calculateBestMove(std::vector<std::string> move_list, int await_lines = 1000);
    bool initializeComputer();
private:
    
    bool send(std::string_view message);
    bool receive(std::string_view message, int await_lines = 1000);
    bool sendAndReceive(std::string_view message, std::string_view response);
    
    bp::ipstream m_engine_output;
    bp::opstream m_engine_receiver;
    bp::child m_engine{"stockfish", bp::std_out > m_engine_output, bp::std_in < m_engine_receiver};


};
