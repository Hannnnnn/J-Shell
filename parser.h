#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "command.h"

class Parser {

public:
    Command* parse_command(std::vector<std::string>& tokens);
    Command* parse_list(std::vector<std::string>& tokens);
    Command* parse_redir(std::vector<std::string>& tokens);
    Command* parse(std::string& s);
    std::string& strip(std::string& s);
    std::pair<std::vector<std::string>, bool> get_tokens(std::string& s);

};



#endif