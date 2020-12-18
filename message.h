//
// Created by morteza on 18.12.20.
//
#include <pthread.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#ifndef SHELL_MASSAGING_H
#define SHELL_MASSAGING_H

#endif

void *read_message(void *arg) {
    int fd1;
    char *myfifo = "./myfifo";
    mkfifo(myfifo, 0666);
    char str1[80];
    while (!finishedProgram) {
        if (newMassage) {
            fd1 = open(myfifo, O_RDONLY);
            read(fd1, str1, 80);
            while (isExecutingCommand);
            printf("\nMessage : %s \n", str1);
            close(fd1);
        }
    }
    exit(0);
}

void send_massage(char *msg) {
    int fd;
    char *path = "./makefifo";
    mkfifo(path, 0666);
    fd = open(path, O_WRONLY);
    write(fd, msg, strlen(msg) + 1);
    close(fd);
}
