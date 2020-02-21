#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "command.h"
class Parser {

public:
    Command* parse(std::string& s);
    std::string& strip(std::string& s);
    std::pair<std::vector<std::string>, bool> get_tokens(std::string& s);
    


};



#endif