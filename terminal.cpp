#include "terminal.h"
#include <errno.h>

int val;
void Terminal::shell() {
    
    while(true) {
        user_name = getenv("USER");
        getcwd(current_path, SIZE);
        gethostname(host_name,SIZE);
      
        printf("\033[1;31m%s@%s\033[0m:\033[1;36m%s\033[0m$ ", user_name, host_name, current_path);
          
        std::getline(std::cin, str);
        Command *command = parser.parse(str);
   
        if (command != nullptr) {
            if (command->name == EXIT_COMMAND) {
                printf("Bye\n"); 
                exit(0);
            } else if (command->name == CD_COMMAND) {

                if (command->args.size() == 1) {
                    char home_path[SIZE] = "/home/";
                    strcat(home_path, getenv("USER"));
                    chdir(home_path);    
                }
                else if (command->args.size() > 1) {
                    chdir(command->args[1].c_str());
                }

            } else {
               this->excute(command);
                
            }

        }
        
        delete command;

    }
    
}

int Terminal::excute(Command *command) {
    
    char **args;
    args = new char* [command->args.size() + 1];

    for (int i = 0 ; i < command->args.size() ; i++ ) {
        args[i] = new char[command->args[i].size() + 10];
       
        strcpy(args[i], command->args[i].c_str());
    
    }

    args[command->args.size()] = 0;
    
    pid_t pid = fork();
    if (pid == 0) {
        RedirCommand *redir = dynamic_cast<RedirCommand*>(command);
        if (redir != nullptr) {
            for (auto& in_file:redir->in) {
                freopen(in_file.c_str(),"r", stdin);
            }

            for (auto& out_file:redir->out) {
                freopen(out_file.c_str(), "w", stdout);
            }
        }

       if (execvp(command->name.c_str(), args) == -1)
            std::cout << "Jsh: No such command\n";
        exit(0);
    }
    else {
        int status;
        wait(&status);
        
        for (int i = 0 ; i <= command->args.size() ; i++ ) {
            delete[] args[i]; 
        }
        
        delete[] args;
        
        return WEXITSTATUS(status);
    }
   
}