#include "Runner.hpp"
#include "fflang_def.hpp"
#include "Scanner.hpp"
#include "terminal_utils/color.hpp"
#include "expr/BinaryExpr.hpp"

using Terinal_Utils::Color;

Scanner Runner::scanner = Scanner();
bool Runner::is_error = false;

// method
void Runner::run_prompt()
{
    std::cout << "fflang( " << FF_LANG_VERSION << " )" << std::endl;
    std::cout << "> ";
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "exit" || line == "quit" || line == "q")
        {
            scanner.print_debug_info();
            break;
        }
        else
        {
            run_line(line.c_str());
        }
        std::cout << "> ";
    }
}


void Runner::run_file(const char* filename)
{
    Runner::clear();
    std::ifstream file(filename);
    assert(file.is_open() && file.good());

    std::string line; 

    while (file.good() && !is_error)
    {
        std::getline(file , line);
        run_line(line.c_str());
    }
    #ifndef TEST
    #ifdef DEBUG
        scanner.print_debug_info();
    #endif
    #endif
}


void Runner::run_line(const char* line)
{
    Runner::scanner.append_scan(line);
}

void Runner::error(const char* message )
{
    std::cerr << "Error: " << Color::RED << message << Color::RESET << std::endl;
}

void Runner::error(const std::string& message )
{
    error(message.c_str());
}

void Runner::error(const int line, const int row, const char* message)
{
    std::cerr << "Error: " << Color::RED << message << Color::RESET << " at line " << line << " row " << row << std::endl;
}

void Runner::fatal_error(const char* message , const int exit_code)
{
    error(message);
    halt(exit_code);
}

void Runner::fatal_error(const std::string& message , const int exit_code)
{
    fatal_error(message.c_str(), exit_code);
}

void Runner::halt(const int exit_code)
{
    exit(exit_code);
}

void Runner::halt(const char* msg , const int exit_code)
{
    std::cerr << msg << std::endl;
    exit(exit_code);
}

bool Runner::has_error()
{
    return is_error;
}

#ifdef TEST
int Runner::get_token_num()
{
    return scanner.get_token_num();
}
#endif


void Runner::clear()
{
    scanner.clear_state();
}