#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <filesystem>
#include <regex>
#include <vector>

int main(int argc, const char** argv){
    std::map<std::string, std::string> flags = {};
    std::vector<int> qfs = {};

    /*
    check argv for command line arguments
    */
    for (int i = 0; i < argc; i++){
        if (argv[i][0] != '-'){
            std::regex r("[0-9]+"); // number regex
            if (std::regex_match(std::string(argv[i]), r)) qfs.push_back(std::stoi(std::string(argv[i])));
        }
        else {
        std::string arg = argv[i];
            size_t split_pos = arg.find("=");
            if (split_pos != std::string::npos){
                flags[arg.substr(0,split_pos)] = arg.substr(split_pos+1, arg.size()-split_pos-1);
            }
            else {
                flags[arg] = "";
            }
        }
    }
    bool colored_errors = flags.count("--colored") > 0;

    if (!std::filesystem::exists(std::filesystem::u8path(std::string("./.qf")))){
        if (colored_errors) std::cerr << "\e[1;31m";
        std::cerr << "ERROR: " << (colored_errors? "\e[0m" : "") << "No quickfix file found in current directory" << std::endl;
        return 1;
    }
    std::wifstream file("./.qf");

    file.close();
    return 0;
}


