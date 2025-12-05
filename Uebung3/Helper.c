#include <stdio.h>
#include <fcntl.h>      // O_CREAT
#include <sys/stat.h>   // mode constants
#include <semaphore.h>
#include <unistd.h>

int main() {

    // Liste aller benötigten Semaphoren
    const char *sems[] = { "/north", "/east", "/south", "/west" };
    const int SEM_COUNT = 4;

    // Zuerst alle Semaphoren löschen (ignorieren, falls sie nicht existieren)
    for (int i = 0; i < SEM_COUNT; i++) {
        sem_unlink(sems[i]);
    }

    // Neue Semaphoren anlegen
    for (int i = 0; i < SEM_COUNT; i++) {
        sem_t *s = sem_open(sems[i], O_CREAT, 0600, 1);
        if (s == SEM_FAILED) {
            perror("sem_open");
            return 1;
        }
        sem_close(s);
    }

    printf("Alle Semaphoren erfolgreich erstellt.\n");
    return 0;
}