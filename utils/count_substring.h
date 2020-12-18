//
// Created by morteza on 18.12.20.
//

#ifndef SHELL_COUNT_SUBSTRING_H
#define SHELL_COUNT_SUBSTRING_H

#endif //SHELL_COUNT_SUBSTRING_H
int count_substring(const char *string, const char *request_char) {
    char *copy = (char *) malloc(strlen(string) * sizeof(char));
    strcpy(copy, string);
    int counter_char = 0;
    for (int i = 0; string[i] ; ++i) {
        if (string[i]==*request_char){
            counter_char++;
        }
    }
    return counter_char;
}