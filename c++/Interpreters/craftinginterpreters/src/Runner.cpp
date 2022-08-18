#include "Runner.hpp"
#include "fflang_def.hpp"
#include "Scanner.hpp"


bool Runner::is_error = false;
Scanner Runner::scanner = Scanner();

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
    std::ifstream file(filename);
    assert(file.is_open() && file.good());

    std::string line; 

    while (file.good())
    {
        std::getline(file , line);
        std::cout << line << "\n";
    }

    scanner.set_source(line);
    std::vector<Token::Type> tokens = scanner.start_scan();

}


void Runner::run_line(const char* line)
{
    if (is_error) halt(-1);
    std::cout << line << std::endl;
    Runner::scanner.rescan(line);
}

void Runner::halt(const int exit_code)
{
    exit(exit_code);
}

void Runner::halt(const char* msg , const int exit_code)
{
    is_error = true;
    std::cerr << msg << std::endl;
    exit(exit_code);
}


 