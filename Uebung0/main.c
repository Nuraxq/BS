#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hello.h"


bool check_palindrome(const char word[]) {
    const auto length = strlen(word);
    for(int i = 0; i < length/2 ; i++) {
        if(word[i] != word[length-i-1]) {
            return false;
        }
    }
    return true;
}


int main(int argc,char* argv[]) {
    if(argc != 3) {
        perror("Unpassend viele Argumente!");
        exit(EXIT_FAILURE);
    }

    // HIER NOCH FEHLER BEHANDELN DAS IST SO ASS BIS JZ
    char* iter = strtok(argv[2],":");
    int start = atoi(iter);
    iter = strtok(NULL,":");
    int end = atoi(iter);


    int count = 0;
    char* iter2 = strtok(argv[1],",");
    int anzahl_palindrome = 0;
    while(iter2 != NULL) {
        if(count >= start && count <= end) {
            if(check_palindrome(iter2)) {
                anzahl_palindrome++;
            }
        }
        count++;
        iter2 = strtok(NULL,",");
    }

    printf("Anzahl gefundener Palindrome:%d" , anzahl_palindrome);
    return 0;
}
