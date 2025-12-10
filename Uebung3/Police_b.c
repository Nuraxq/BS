#include <stdio.h>
#include <fcntl.h>      // O_CREAT
#include <sys/stat.h>   // mode constants
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>


int pipeFD;

int main(int argc, char * argv[]){

    pid_t pid[argc-1];
    // Pids auslesen
    for(int i = 0; i < argc-1;i++){
        pid[i] = (pid_t)strtol(argv[i+1],NULL,10);
    }
    pipeFD = open("police",O_RDONLY);
    if (pipeFD == -1){
            perror("open");
            exit(EXIT_FAILURE);
        } 
    while(true){
        sleep(5);
        // char array für Blockierten Käfer -> B heißt blocked F heißt free
        char blocked[argc-1];
    
        for (int i = 0; i < argc-1; i++){
            kill(pid[i],SIGUSR1);
            char b;
            while(read(pipeFD,&b,1) == 0){
                usleep(1000);
            }
            
            blocked[i] = b;
        }
        bool deadlock = true;
        for (int i = 0; i < argc-1; i++){
            if (blocked[i] == 'f'){
                deadlock = false;
            }
        }
        if (deadlock){
            printf("Deadlock!\n");
        }

    }

    if(close(pipeFD)){
        perror("close");
        exit(EXIT_FAILURE);
    }
    return 0;
}
