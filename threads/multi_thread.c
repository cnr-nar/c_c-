// addition by using multi-thread

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_THREADS 2
  
sem_t mutex;


void *runner(void *param);

int liste_uzunlugu;
int toplam=0;
int *sayilarin_listesi;

int main(int argc, char *argv[])
{
    int sayilar;
    int *ptr;

    srand(time(NULL));

    sem_init(&mutex, 0, 1);

    pthread_t thread_id[MAX_THREADS];
    pthread_attr_t attr;

    scanf("%d",&liste_uzunlugu);

    sayilarin_listesi = malloc(liste_uzunlugu * sizeof(sayilarin_listesi));

    printf("Random Dizi => ");
    
    for(int i=0;i<liste_uzunlugu;i++){    
        sayilar = rand() % 10;
        sayilarin_listesi[i] = sayilar;
        printf("%d ",sayilarin_listesi[i]);
    }
    printf("\n");

    pthread_attr_init(&attr);

    for (int i = 0; i < 2; i++){
        ptr = malloc(sizeof(int));
        *ptr=i+1;
        pthread_create(&thread_id[i], &attr, runner, ptr);
    }
    
    for (int i = 0; i < 2 ;i++) pthread_join(thread_id[i], NULL);
        
    sem_destroy(&mutex);

    return 0;
}

void *runner(void *param){
    int thread_id = *((int *)param);
    int i=0;
    while(sayilarin_listesi[i]!=-1){
        if(thread_id==1 && sayilarin_listesi[i] !=-1){
            sem_wait(&mutex);
            toplam = toplam+sayilarin_listesi[i];
            printf("Thread%d %d değerini okudu toplam = %d\n",thread_id,sayilarin_listesi[i],toplam);
            sayilarin_listesi[i]=-1;       
        }
        sleep(1); 
        if(thread_id==2 && sayilarin_listesi[(liste_uzunlugu-1)-i]!=-1){
            sem_post(&mutex);
            toplam = toplam+sayilarin_listesi[(liste_uzunlugu-1)-i];
            printf("Thread%d %d değerini okudu toplam = %d\n",thread_id,sayilarin_listesi[(liste_uzunlugu-1)-i],toplam);
            sayilarin_listesi[(liste_uzunlugu-1)-i]=-1;
        }
        sleep(1);
        i++;
    }
    if(thread_id==2) printf("Thread2 okunacak değer bulamadı.\n");
}