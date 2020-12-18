//
// Created by morteza on 18.12.20.
//

#ifndef SHELL_TRIM_H
#define SHELL_TRIM_H

#endif
char* trim(char *string){
    for (int i = 0; string[i] ; ++i) {
        if (i!=0 && i!=(strlen(string) - 1)){
            if (string[i] == ' ' && (string[i - 1] == ' ' || string[i + 1] == ' ')){
                remove(string, i);
                i--;
            }
        }else if(i==0){
            if (string[0] == ' '){
                remove(string, 0);
                i--;
            }
        }else{
            if (string[i] == ' ' && i == strlen(string) - 1){
                remove(string, i);
            }
        }
    }
    return string;
}