#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#define BUFFERSIZE 512

int main(void){
    // Hostnamen Holen
    char hostname[HOST_NAME_MAX];
    while(gethostname(hostname,sizeof(hostname)) != 0){
        if(errno == EINTR) continue;
        perror("gethostname");
        exit(EXIT_FAILURE);
    }
    // User ID holen
    // Irwie gibts hier keine INfos zu Fehlerbehandlung.
    uid_t uID = getuid();

    // Usernamen Holen
    char username[BUFFERSIZE];
    struct passwd* pass = getpwuid(uID);
    if(!pass){
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    strncpy(username,pass->pw_name,BUFFERSIZE);

    char path[PATH_MAX];
    while(getcwd(path,BUFFERSIZE) == NULL){
        if(errno == EINTR) continue;

        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    
    

    while(true){
        printf("%s@%s %s$ ",username,hostname,path);
        char befehl[BUFFERSIZE];
        char argument[BUFFERSIZE];

        if(scanf("%511s %511s",befehl,argument) < 2){
            puts("Fehler bei Scanf");
            return 1;
        }
        printf("Befehl: %s\n",befehl);
        printf("Argument: %s\n",argument);
    }
    return 0;
}