#include <stdio.h>
#include <fcntl.h>      // O_CREAT
#include <sys/stat.h>   // mode constants
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

sem_t* from;
sem_t* priority;

volatile sig_atomic_t stop = 0;

void handle_sigint(int sig){
    stop = 1;
}


int main(int argc, char * argv[]){
    srand(getpid());

    printf("Anzahl Argumente:%d \n",argc);
    pid_t id = getpid();

    char comingFrom[32];
    comingFrom[0] = '/';
    comingFrom[31] = '\0';
    strncpy(comingFrom+1,argv[1],31);

    char waitsFor[32];
    waitsFor[0] = '/';
    waitsFor[31] = '\0';
    strncpy(waitsFor+1,argv[2],31);

    from = sem_open(comingFrom,0);
    if (from == SEM_FAILED){
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    priority = sem_open(waitsFor,0);
    if (priority == SEM_FAILED){
        perror("sem_open");
        exit(EXIT_FAILURE);
    } 
    
    // Sigaction setzen
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT,&sa,NULL) == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while (!stop){
        printf("Käfer %d: Komme von %s\n",id,argv[1]);
        

        int status = sem_wait(from);
        if (status == -1){
            if(stop) {break;}
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        usleep(1000 + 92* (rand() % 100)); // es passiert entweder nie oder immer ein deadlock // zeit ist doof 
        printf("Käfer %d: Teste ob %s frei ist\n",id,argv[2]);
        int status2 = sem_wait(priority);
        if (status2 == -1){
            if(stop){
                sem_post(from);
                break;
            }
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        printf("Käfer %d: Ich bin drüber! (Kam von %s)\n",id,argv[1]);
        sleep(1);

        sem_post(from);
        sem_post(priority);
        usleep(1000000 - 100 * (rand() % 10));
    }
    return 0;
}
