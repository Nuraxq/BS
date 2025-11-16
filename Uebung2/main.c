#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFERSIZE 512

void getNames(char* hostname,char* path, char* username){
    // Hostnamen Holen
    while(gethostname(hostname,sizeof(hostname)) != 0){
        if(errno == EINTR) continue;
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    // User ID holen 
    // Usernamen Holen mit User ID
    uid_t uID = getuid();
    struct passwd* pass = getpwuid(uID);
    if(!pass){
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    // usernamen in Buffer kopieren, (muss eigl nicht)
    strncpy(username,pass->pw_name,BUFFERSIZE);


    // Pfadnamen holen
    while(getcwd(path,BUFFERSIZE) == NULL){
        if(errno == EINTR) continue;

        perror("getcwd");
        exit(EXIT_FAILURE);
    }
}



int main(void){
    // Variablen für Hostnamen etc
    char hostname[HOST_NAME_MAX];
    char username[BUFFERSIZE];
    char path[PATH_MAX];
    getNames(hostname,path,username);

    
    while(true){
        printf("%s@%s %s$ ",username,hostname,path);
        
        char line[BUFFERSIZE];
        if(fgets(line,BUFFERSIZE,stdin) == NULL){
            if(ferror(stdin)){
                perror("fgets");
                return 1;
            }
        }

        // Befehl in einzelne Tokens zerteilen
        char* token = strtok(line,"&&");
        while(token != NULL){
            char befehl[BUFFERSIZE];
            char argument[BUFFERSIZE];

            // Wir lesen genau 1 Befehl mit genau 1 Argument ein
            if(sscanf(token,"%511s %511s",befehl,argument) < 2){
                puts("Usage: <Befehl> <Argument> (&& <Befehl <Argument> && ...)");
                return 1;
            }

            // neuen Prozess erzeugen
            pid_t pid = fork();
            if(pid < 0){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            // Der Kindprozess führt den Befehl aus
            if(pid == 0){
                execlp(befehl,befehl,argument, (char*)NULL);
                perror("execlp");
                return 1;
            }
            // Der Elternprozess wartet bis der Kindprozess fertig ist und überprüft 
            // Ob es ein Problem gab und gibt den Status aus
            else{
                int status;
                if(waitpid(pid,&status,0) == -1){
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
                // wir geben den Exit Status aus
                if(WIFEXITED(status)){
                    printf("Exit Status: %d\n", WEXITSTATUS(status));
                    // Falls das Programm einen Fehler meldet (Rückgabewert < 0) setzen wir Token auf NULL
                    // Daraufhin werden die weiteren Befehle nichtmehr eingelesen 
                    // und wir sind bereit neue Befehle einzulesen.
                    if(WEXITSTATUS(status) != 0){
                        printf("An error occured, command couldnt be executed properly!\n");
                        token = NULL;
                    }
                    else{
                        token = strtok(NULL,"&&");
                    }
                }
            }
            
        }
    }
    return 0;
}
