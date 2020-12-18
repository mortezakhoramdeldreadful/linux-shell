//
// Created by morteza on 18.12.20.
//

#ifndef SHELL_EXECUTE_H
#define SHELL_EXECUTE_H
extern bool finishedProgram = false;
extern bool isExecutingCommand = false;
extern bool newMassage = true;

#include <cstdlib>
#include <wait.h>
#include <unistd.h>
#include "command.h"
#include <cstdio>
#include "message.h"
#include "utils/trim.h"
#include "utils/split.h"


#endif

bool single_line_command_execute(char *command);

bool pipe_line_command_execute(char *command);

bool pre_execute(char *command);

bool pre_execute(char *command) {
    bool b = false;
    int type;
    if (contain(command, "msg")) {
        type = MESSAGE;
    } else if (contain(command, "|")) {
        if (count_substring(command, "|") != 1) {
            type = INCORRECT_COMMAND;
        }
        type = MULTI_LINE_COMMAND;
    } else if (contain(command, "quit")) {
        type = QUIT;
    } else {
        type = ONE_LINE_COMMAND;
    }
    if (type == ONE_LINE_COMMAND) {
        b = single_line_command_execute(command);
    } else if (type == MULTI_LINE_COMMAND) {
        b = pipe_line_command_execute(command);
    } else if (type == MESSAGE) {
        send_massage(command);
    } else {
        finishedProgram = true;
    }

    return b;
}

bool single_line_command_execute(char *command) {
    isExecutingCommand = true;
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        trim(command);
        remove(command, "\n");
        int spaceCount = 0;
        char *copy = (char *) malloc(strlen(command) * sizeof(char));
        strcpy(copy, command);
        char *temp = strtok(copy, " ");
        while (temp != nullptr) {
            temp = strtok(nullptr, " ");
            spaceCount++;
        }
        char *args[spaceCount];
        split(command, reinterpret_cast<char **>(&args), " ");
        if ((execvp(args[0], args)) == -1) {
            printf("command %s not found", args[0]);
            isExecutingCommand = false;
            exit(0);
        }
    } else if (pid > 0) {
        isExecutingCommand = false;
        return true;
    } else {
        isExecutingCommand = false;
        return false;
    }
}

bool pipe_line_command_execute(char *command) {

    isExecutingCommand = true;
    remove(command, "\"");
    remove(command, "\n");
    char *commands[2];
    int pipefd[2];
    int pid1 = 1, pid2 = 1;

    trim(command);
    split(command, commands, "|");

    pipe(pipefd);

    pid1 = fork();
    if (0 == pid1) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        trim(commands[1]);
        int spaceCount = 0;
        char *copy = (char *) malloc(strlen(commands[1]) * sizeof(char));
        strcpy(copy, commands[1]);
        char *temp = strtok(copy, " ");
        while (temp != nullptr) {
            temp = strtok(nullptr, " ");
            spaceCount++;
        }
        char *args[spaceCount];
        split(commands[1], reinterpret_cast<char **>(&args), " ");
        if ((execvp(args[0], args)) == -1) {
            printf("command not found or not supported");
            exit(0);
        }
    } else {
        pid2 = fork();
        if (pid2 == 0) {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            trim(commands[0]);
            int spaceCount = 0;
            char *copy = (char *) malloc(strlen(commands[0]) * sizeof(char));
            strcpy(copy, commands[0]);
            char *temp = strtok(copy, " ");
            while (temp != nullptr) {
                temp = strtok(nullptr, " ");
                spaceCount++;
            }
            char *args[spaceCount];
            split((commands[0]), reinterpret_cast<char **>(&args), " ");
            if ((execvp(args[0], args)) == -1) {
                printf("command not found or not supported");
                exit(0);
            }
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            isExecutingCommand = false;
            return true;
        }
    }
}


void file_execute_batch(char *fileName) {
    FILE *pFile;
    char *command = nullptr;
    size_t len = 0;
    pFile = fopen(fileName, "r");
    if (pFile == nullptr) {
        fprintf(stderr, "  file not found \n ");
        return;
    }
    while ((getline(&command, &len, pFile)) != -1 && !finishedProgram) {
        if (strcmp(command, "\n") == 0) {
            continue;
        }
        printf("\n > %s", command);
        trim(command);
        if (strlen(command) == 0) {
            return ;
        }
        if (!pre_execute(command)){
            if (!finishedProgram){
                printf("Command is Not Runnable");
            }else{
                printf("Exiting !! \n");
                exit(0);
            }
        }
    }

    fclose(pFile);
    if (command) {
        free(command);
    }
}