//
// Created by morteza on 18.12.20.
//

#ifndef SHELL_SPILIT_H
#define SHELL_SPILIT_H

#endif
void split(const char* cmd ,char **args,const char *splitBy) {
    int i=0;
    char *command;
    while((command=strsep(const_cast<char **>(&cmd), splitBy)) != nullptr ){
        args[i++]=command;
    }
    args[i]=nullptr;
}