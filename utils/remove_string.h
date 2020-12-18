//
// Created by morteza on 18.12.20.
//

#ifndef SHELL_REMOVE_STRING_H
#define SHELL_REMOVE_STRING_H

#endif //SHELL_REMOVE_STRING_H

char* remove(char *string, const char *remove_char) {
    size_t lenght = strlen(remove_char);
    char *tmp = string;
    while ((tmp = strstr(tmp, remove_char)) != nullptr) {
        memmove(tmp, tmp + lenght, strlen(tmp + lenght) + 1);
    }
    return string;
}
char* remove(char *str, const int index) {
    memmove(str + index, str + index + 1, strlen(str) - index);
    return str;
}
