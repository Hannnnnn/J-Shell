#include "parser.h"

Command* Parser::parse_list(std::vector<std::string>& tokens) {
    
    ListCommand* list_command = new ListCommand();

    auto list = std::find(tokens.begin(), tokens.end(), ";");

    while (list != tokens.end()) {
        std::vector<std::string> sub_tokens(tokens.begin(), list);
        list_command->commands.push_back(parse_command(sub_tokens));
        tokens.erase(tokens.begin(), list + 1);
        list = std::find(tokens.begin(), tokens.end(), ";");
    }
    
    if (tokens.size() > 0) {
        list_command->commands.push_back(parse_command(tokens));
    }

    return list_command;
}

Command* Parser::parse_command(std::vector<std::string>& tokens) {

    auto in_redir = std::find(tokens.begin(), tokens.end(), "<");
    auto out_redir = std::find(tokens.begin(), tokens.end(), ">");
    auto list = std::find(tokens.begin(), tokens.end(), ";");
   
    Command* command = nullptr;

    if (list != tokens.end()) {
        command = parse_list(tokens);
    }   
    else if (in_redir != tokens.end() || out_redir != tokens.end()) {
        command = parse_redir(tokens);
       
    }
    else {
        command = new SimpleCommand(tokens[0], tokens);
    }
    return command;
}   


Command* Parser::parse(std::string& s) {
    auto result = this->get_tokens(s);
     
    std::vector<std::string>& tokens = result.first; 
    if (result.second == false || tokens.size() < 1) {
        return nullptr;
    }
  
    return parse_command(tokens);
}

Command* Parser::parse_redir(std::vector<std::string>& tokens) {
    // <
    RedirCommand* redir = new RedirCommand();

    for (auto iter = tokens.begin(); iter != tokens.end(); ) {
        if (*iter == "<") {
            
            iter = tokens.erase(iter);
            if (iter  != tokens.end()) {
                redir->in.push_back(*(iter));
                iter = tokens.erase(iter);
                continue;
            }
            else {
                std::cout << "Jsh: syntax error" << std::endl;
                return nullptr;
            }
        
        }

        iter++;
    }

    for (auto iter = tokens.begin(); iter != tokens.end(); ) {
        if (*iter == ">") {
            iter = tokens.erase(iter);
            if (iter  != tokens.end()) {
                redir->out.push_back(*(iter));
                iter = tokens.erase(iter);
                continue;
            }
            else {
                std::cout << "Jsh: syntax error" << std::endl;
                return nullptr;
            }

        }
        iter++;
    }
    if (tokens.size() < 1) {
        return nullptr;
    }
    redir->name = tokens[0];
    redir->args = tokens;

    return redir;
    // >
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
            size_t q = p+1;
            while (q < s.size() && s[q] != '"') {
                q++;
            }
            if (q < s.size() && s[q] == '"') {
                if (q - p > 1)
                    tokens.push_back(s.substr(p+1, q - p - 1));
                p = q + 1;
            }
            else {
                std::cout << "Jsh: syntax error" << std::endl;
                return std::make_pair(tokens, false);
            }
        } else if (s[p] == ';') {
            tokens.push_back(s.substr(p++, 1));
        }
        else {
            size_t q = p;
           
            while (q < s.size() && s[q] != ' ' && s[q] != ';') {
                q++;
            }
            tokens.push_back(s.substr(p, q - p));
            p = q;
        }
    }


    return std::make_pair(tokens, tokens.size() > 0 ? true : false);

}