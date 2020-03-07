#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string>
enum Type {FATHER_COMM, SIMPLE_COMM, REDIR_COMM};
struct Command {
    Type type = Type::FATHER_COMM;
    

    Command() {

    }

    virtual ~Command() = default;

};

struct SimpleCommand: public Command {
    Type type = Type::SIMPLE_COMM;
    std::string name;
    std::vector<std::string> args;
    SimpleCommand() {
        
    }
    SimpleCommand(std::string& _name, std::vector<std::string>& _args) 
        :name{_name},
        args{_args}{

    }
};

struct RedirCommand: public SimpleCommand {
    Type type = Type::REDIR_COMM;
    std::vector<std::string>  in;
    std::vector<std::string>  out;
    RedirCommand() {

    }
    
    
};

#endif