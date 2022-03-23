
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#define W_BUF 15

int main(){
        sem_t *s_wolnych_pozycji = sem_open("/s_wolnych_pozycji", 0);
        if (s_wolnych_pozycji==SEM_FAILED) perror("sem_open");

        sem_t *s_zajetych_pozycji = sem_open("/s_zajetych_pozycji", 0);
        if (s_zajetych_pozycji==SEM_FAILED) perror("sem_open");

        sem_t *s_producent = sem_open("/s_producent",0);
         if (s_producent==SEM_FAILED) perror("sem_open");

        sem_t *s_konsument = sem_open("/s_konsument", 0);
        if (s_konsument==SEM_FAILED) perror("sem_open");

        int fd_glowny = shm_open("/buff_glowny", O_RDWR,0777);
        ftruncate(fd_glowny, W_BUF);                   //rozmiar bloku pamieci
        char *ptr_glowny = mmap(NULL, W_BUF, PROT_READ|PROT_WRITE, MAP_SHARED, fd_glowny, 0);

        int fd_wolnych = shm_open("/buff_wolnych",O_RDWR,0777);
        ftruncate(fd_wolnych, W_BUF);                   //rozmiar bloku pamieci
        char *ptr_wolnych = mmap(NULL, W_BUF, PROT_READ|PROT_WRITE, MAP_SHARED, fd_wolnych, 0);

        int fd_zajetych = shm_open("/buff_zajetych", O_RDWR,0777);
        ftruncate(fd_zajetych, W_BUF);
        
        char *ptr_zajetych = mmap(NULL, W_BUF, PROT_READ|PROT_WRITE, MAP_SHARED, fd_wolnych, 0);


        int fd_1 = shm_open("/buff_1", O_RDWR,0777);// wspoldzielona
        ftruncate(fd_1, 1);                   //rozmiar bloku pamieci
        char *ptr_1 = mmap(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd_1, 0);

        int fd_2 = shm_open("/buff_2", O_RDWR,0777);     // wzielona
        ftruncate(fd_2, 1);                   //rozmiar bloku pamieci
        char *ptr_2 = mmap(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd_2, 0);

        int fd_3 = shm_open("/buff_3", O_RDWR,0777);     //pamieca
        ftruncate(fd_3, 1);                   //rozmiar bloku pamieci
        char *ptr_3 = mmap(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd_3, 0);

        int fd_4 = shm_open("/buff_4", O_RDWR,0777);//pamiec wsp
        ftruncate(fd_4, 1);                   //rozmiar bloku pamieci
        char *ptr_4 = mmap(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED, fd_4, 0);

    while (1==1){
            sem_wait(s_konsument);
            
            sem_wait(s_zajetych_pozycji);
            int tym=ptr_zajetych[ptr_4[0]];
            ptr_4[0]=(ptr_4[0]+1)%W_BUF;
            sem_post(s_zajetych_pozycji);
	    printf("ptr_4: %d\n",ptr_4[0]);
            printf("konsumetn przetwarza :%d\n", tym);
            sleep(rand()%4);
    
            sem_wait(s_wolnych_pozycji);
            ptr_wolnych[ptr_1[0]]=tym;
            ptr_1[0]=(ptr_1[0]%W_BUF);
	    printf("ptr_1:%d\n",ptr_1[0]);
            sem_post(s_wolnych_pozycji);
            
            sem_post(s_producent);
    }


}

        
