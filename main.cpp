//
// Created by morteza on 18.12.20.
//

#include "execute.h"
#include <cstdio>
#include <csignal>

void control_c_handler(int signal);

pthread_t pthread;

int main(int argc, char **argv) {
    //change signal
    signal(SIGINT, control_c_handler);
    //new thread
    char *request_command;

    pthread_create(&pthread, nullptr, &read_message, nullptr);
    if (argc == 2) {
        file_execute_batch(argv[1]);
    }

    while (!finishedProgram & !isExecutingCommand) {
        request_command = read_each_command();
        trim(request_command);
        if (strlen(request_command) == 0) {
            main(0, nullptr);
        }
        if (!pre_execute(request_command)) {
            if (!finishedProgram) {
                printf("Command is Not Runnable");
            } else {
                printf("Exiting ... \n");
                exit(0);
            }
        }
    }
}

void control_c_handler(int signal) {
    printf("The Ctr + C is Clicked");
}



