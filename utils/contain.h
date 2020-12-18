//
// Created by morteza on 18.12.20.
//

#ifndef SHELL_CONTAIN_H
#define SHELL_CONTAIN_H

#endif //SHELL_CONTAIN_H
bool contain(const char *string,const char *request_string) {
    return (strstr(string, request_string) != nullptr);
}