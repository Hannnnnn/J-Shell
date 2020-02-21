#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string>

struct Command {
    std::string name;
    std::vector<std::string> args;
};

struct RedirCommand: public Command {

};

#endif