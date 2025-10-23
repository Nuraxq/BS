#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


bool check_palindrome(const char word[]) {
    auto const length = (int)strlen(word);
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
    int start = 0;
    int end = 0;
    if (sscanf(argv[2]," %d:%d",&start,&end) < 2) {
        perror("Fehler bei sscanf!");
        return 1;
    }
    if(start > end || start < 0 || end < 0){
        perror("Bereichsgrenzen ungültig!");
        return 1;
    }

    int count = 0;
    int anzahl_palindrome = 0;

    const char* iter2 = strtok(argv[1],",");

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
