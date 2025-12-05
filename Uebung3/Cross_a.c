#include <stdio.h>
#include <fcntl.h>      // O_CREAT
#include <sys/stat.h>   // mode constants
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

sem_t* from;
sem_t* priority;

int main(int argc, char * argv[]){
    srand(getpid());

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

    while (true){
        printf("Käfer %d: Ich komme von: %s\n",id,argv[1]);
        

        int status = sem_wait(from);
        if (status == -1){
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        usleep(10 + 30 * (rand() % 100));
        printf("Käfer %d: Ich überprüfe ob %s frei ist\n",id,argv[2]);
        int status2 = sem_wait(priority);
        if (status2 == -1){
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }
        printf("Käfer %d: Ich habe die Kreuzung überquert! (Gekommen von: %s)\n",id,argv[1]);
        sleep(1);

        sem_post(from);
        sem_post(priority);
        usleep(1000000 - 100 * (rand() % 10));
    }
    return 0;
}