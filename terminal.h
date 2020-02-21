#ifndef TERMINAL_H
#define TERMINAL_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include<sys/wait.h> 
#include "parser.h"
#include "command.h"
class Terminal {

public:
    void shell();    
    int excute(Command *command);

private:
    const static int SIZE = 1024;
    char* user_name;
    char current_path[SIZE];
    char host_name[SIZE]; 
    std::string str;
    std::string EXIT_COMMAND{"exit"};
    std::string CD_COMMAND{"cd"};
    Parser parser;
};



#endif