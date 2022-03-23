#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>
#define W_BUF 15
//poczatkowy
int main(){
        
        sem_unlink("/s_wolnych_pozycji");
        sem_unlink("/s_zajetych_pozycji");
        sem_unlink("/s_producent");
        sem_unlink("/s_konsument");

        sem_t *s_wolnych_pozycji = sem_open("/s_wolnych_pozycji", O_CREAT|O_TRUNC, 0777, 1);
        if (s_wolnych_pozycji==SEM_FAILED) perror("sem_open");
        sem_t *s_zajetych_pozycji = sem_open("/s_zajetych_pozycji", O_CREAT|O_TRUNC, 0777,1);
        if (s_zajetych_pozycji==SEM_FAILED) perror("sem_open");
        sem_t *s_producent = sem_open("/s_producent", O_CREAT|O_TRUNC, 0777, W_BUF);
        if (s_producent==SEM_FAILED) perror("sem_open");
        sem_t *s_konsument = sem_open("/s_konsument", O_CREAT|O_TRUNC, 0777, 0);
        if (s_konsument==SEM_FAILED) perror("sem_open");


        int fd_1 = shm_open("/buff_1", O_CREAT | O_RDWR|O_TRUNC, 0777);     //pamiec wspoldzielona
        ftruncate(fd_1, 1);                   //rozmiar bloku pamieci
        char *ptr_1 = mmap(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd_1, 0);
        ptr_1[0]=0;

        int fd_2 = shm_open("/buff_2", O_CREAT | O_RDWR|O_TRUNC, 0777);     //pamiec wspoldzielona
        ftruncate(fd_2, 1);                   //rozmiar bloku pamieci
        char *ptr_2 = mmap(NULL, 1, PROT_READ|PROT_WRITE|O_TRUNC, MAP_SHARED, fd_2, 0);
        ptr_2[0]=0;

        int fd_3 = shm_open("/buff_3", O_CREAT | O_RDWR|O_TRUNC, 0777);     //pamiec wspoldzielona
        ftruncate(fd_3, 1);                   //rozmiar bloku pamieci
        char *ptr_3 = mmap(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd_3, 0);
        ptr_3[0]=0;

        int fd_4 = shm_open("/buff_4", O_CREAT | O_RDWR|O_TRUNC, 0777);     //pamiec wspoldzielona
        ftruncate(fd_4, 1);                   //rozmiar bloku pamieci
        char *ptr_4 = mmap(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd_4, 0);
        ptr_4[0]=0;

        int fd_wolnych = shm_open("/buff_wolnych", O_CREAT | O_RDWR|O_TRUNC, 0777);     //pamiec wspoldzielona
        ftruncate(fd_wolnych, W_BUF);                   //rozmiar bloku pamieci
        char *ptr_wolnych = mmap(NULL, W_BUF, PROT_READ|PROT_WRITE, MAP_SHARED, fd_wolnych, 0);

        

        for (int i=0;i<W_BUF;i++){ 
            ptr_wolnych[i]=i;
        }
        return 0;
}



