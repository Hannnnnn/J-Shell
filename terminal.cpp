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
            this->excute(command);
        }
        else {
            std::cout << "nullcmd" << std::endl;
        }
        
        delete command;

    }
    
}

int Terminal::execute_simple(SimpleCommand *simple) {
     char **args;

     if (simple != nullptr) {
        args = new char* [simple->args.size() + 1];

        for (int i = 0 ; i < simple->args.size() ; i++ ) {
            args[i] = new char[simple->args[i].size() + 10];
            strcpy(args[i], simple->args[i].c_str());
        }

        args[simple->args.size()] = 0;
        
        pid_t pid = fork();
        if (pid == 0) {
           
            RedirCommand *redir = dynamic_cast<RedirCommand*>(simple);

            if (redir != nullptr) {
             
                for (auto& in_file:redir->in) {
                    freopen(in_file.c_str(),"r", stdin);
                }

                for (auto& out_file:redir->out) {
                    freopen(out_file.c_str(), "w", stdout);
                }
            }
        if (execvp(simple->name.c_str(), args) == -1)
                std::cout << "Jsh: No such command\n";
            exit(0);
        }
        else {
            int status;
            wait(&status);
            
            for (int i = 0 ; i <= simple->args.size() ; i++ ) {
                delete[] args[i]; 
            }
            
            delete[] args;
            
            return WEXITSTATUS(status);
        }
    }
}
int Terminal::execute_list(ListCommand *list) {
    for (auto& item:list->commands) {
        execute_simple(dynamic_cast<SimpleCommand*>(item));
    }
}

int Terminal::excute(Command *command) {
    
    char **args;
    SimpleCommand *simple;
    ListCommand *list;
    if ((simple = dynamic_cast<SimpleCommand*>(command)) != nullptr) {

         if (simple != nullptr) {
            if (simple->name == EXIT_COMMAND) {
                printf("Bye\n"); 
                exit(0);
            } else if (simple->name == CD_COMMAND) {
                if (simple->args.size() == 1) {
                    char home_path[SIZE] = "/home/";
                    strcat(home_path, getenv("USER"));
                    chdir(home_path);
                    return 0;
                }
                else if (simple->args.size() > 1) {
                    chdir(simple->args[1].c_str());
                    return 0;
                }
            } else {
                return execute_simple(simple);
            }
        }
   
    }
    else if ( (list = dynamic_cast<ListCommand*>(command)) != nullptr) {
        return execute_list(list);
    }
    
   
}