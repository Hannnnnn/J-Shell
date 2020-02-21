#include "parser.h"
Command* Parser::parse(std::string& s) {
    auto result = this->get_tokens(s);

    if (result.second == false) {
        return nullptr;
    }

    Command* command = new Command();
    command->name = result.first[0];
    command->args = result.first;
    return command;
}



std::string& Parser::strip(std::string& s) {
    size_t start = s.find_first_not_of(' ');
    s.erase(0, start);
    

    size_t endline = s.find_last_not_of('\n');
    s.erase(endline + 1, s.size());

    size_t end = s.find_last_not_of(' ');
    s.erase(end + 1, s.size());

    return s;
}

std::pair<std::vector<std::string>, bool> Parser::get_tokens(std::string& s) {
    this->strip(s);
    std::vector<std::string> tokens;

    size_t p = 0;

    while (p < s.size()) {
        if (s[p] == ' ') {
            p++;
        }
        else if (s[p] == '"') {

        }
        else {
            size_t q = p;
           
            while (q < s.size() && s[q] != ' ') {
                q++;
            }
            tokens.push_back(s.substr(p, q - p));
            p = q;
        }
    }


    return std::make_pair(tokens, tokens.size() > 0 ? true : false);

}