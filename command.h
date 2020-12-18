//
// Created by morteza on 18.12.20.
//

#ifndef SHELL_READLINE_H
#define SHELL_READLINE_H
#define ONE_LINE_COMMAND 1
#define MULTI_LINE_COMMAND 2
#define QUIT 3
#define INCORRECT_COMMAND 4
#define MESSAGE 5
#endif

#include <cstring>
#include <cstdio>
#include "utils/remove_string.h"
#include "utils/count_substring.h"
#include "utils/contain.h"

#define MAX 1000

char *read_each_command() {
    printf("\nmorteza@morteza-Lenovo-ideapad-510-15IKB:~$");
    char line[MAX];
    if (fgets(reinterpret_cast<char *>(&line), MAX, stdin) == nullptr) {
        exit(0);
    }
    char *line_ptr = remove(line, reinterpret_cast<const char *>("\n"));
    return line_ptr;
}





