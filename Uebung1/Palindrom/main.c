#include <stdio.h>
#define MAX_WORDS 5
#define MAX_WORD_LENGTH 20


int convertStringToInt(char *str);
char* split(char* pointer);
void list(char* buffer, char liste[][MAX_WORD_LENGTH]);


int main(int argc, char* argv[]) {

    if(argc != 3) {
        printf("Wrong number of arguments\n");
    }

    char* ptr1 = argv[2];
    char* ptr2 = split(ptr1);

    int begin = convertStringToInt(ptr1);
    int end = convertStringToInt(ptr2);

    char* buffer = argv[1];

    char liste[MAX_WORDS][MAX_WORD_LENGTH];

    list(buffer, liste);

    int wordCount = begin;

    for (wordCount = begin; wordCount != end; wordCount++) {
        char* front = &liste[wordCount];
        int frontIndex = 0;
        char* back = &liste[wordCount];
        int backIndex = 0;

        int fehler = 0;

        while (back[backIndex] != '\0') {
            backIndex++;
        }
        if (back[--backIndex] != front[frontIndex]) {

            fehler = 1;

        }
        while (backIndex > frontIndex) {
            if (back[backIndex--] != front[frontIndex++]) {

                fehler = 1;

            }
        }
        if (fehler == 0) {
            printf("in wort %d ist kein fehler aufgetreten \n",wordCount);
        }else {
            printf("wort %d ist kein Palindrom \n",wordCount);
        }
    }

    return 0;
}

void list(char* buffer, char liste[][MAX_WORD_LENGTH]) {




    int indexBuffer = 0;
    int indexListe = 0;
    int wordCount = 0;
    while (buffer[indexBuffer] != '\0') {
        if (buffer[indexBuffer] != ',') {
            liste[wordCount][indexListe++] = buffer[indexBuffer++];
        }else {
            indexBuffer++;
            liste[wordCount][indexListe] = '\0';
            indexListe = 0;
            wordCount++;
        }
    }
}

char* split(char* pointer) {
    int i = 0;
    while(pointer[i] != ':') {
        i++;
    }
    return &pointer[i+1];
}

int convertStringToInt(char *str) {
    int num = 0;
    int i =0;

    while (str[i] != '\0') {

        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == ':') {
                break;
            }
            if (str[i] >= 48 && str[i] <= 57) {
                num = num * 10 + (str[i] - 48);
            }
            else {
                break;
            }
        }
        return num;
    }
}