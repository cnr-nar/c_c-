#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
  
sem_t mutex;


void *runner(void *param);
void *runnerw(void *param);

int length_of_list;
int sum=0;
int *numbers;

int main(int argc, char *argv[])
{
    int number;
    int *ptr,*ptr2;
    int tid_array[2] = {1,2};
    sem_init(&mutex, 0, 1);

    pthread_t tid[2];
    pthread_attr_t attr;

    printf("Enter lenght of list: ");
    scanf("%d",&length_of_list);
    numbers = malloc(length_of_list * sizeof(numbers));



    printf("Random Dizi => ");
    
    for(int i=0;i<length_of_list;i++){    
        number = rand() % 10;
        numbers[i] = number;
        printf("%d ",numbers[i]);
    }
    printf("\n");

    pthread_attr_init(&attr);

    ptr = malloc(sizeof(int));
    ptr2 = malloc(sizeof(int));
    *ptr=1;
    *ptr2=2;
    pthread_create(&tid[0], &attr, runner, ptr);
    pthread_create(&tid[1], &attr, runnerw, ptr2);
    
    for (int i = 0; i < 2 ;i++){pthread_join(tid[i], NULL);}

    sem_destroy(&mutex);

    return 0;
}

void *runner(void *param){
    int tid = *((int *)param);
    if(length_of_list%2==0){
        for(int i = 0 ; i<length_of_list/2;i++){
        //sem_wait(&mutex);
        if(tid==1){
        sum = sum+numbers[i];
        printf("Thread%d %d değerini okudu toplam = %d\n",tid,numbers[i],sum);
        }
        // else if(tid==2){
        // sum = sum+numbers[(length_of_list-1)-i];
        // printf("Thread%d %d değerini okudu toplam = %d\n",tid,numbers[(length_of_list-1)-i],sum);
        // }
        //printf("Thread%d %d değerini okudu toplam = %d\n",tid,numbers[(length_of_list-1)-i],sum);
        //sem_post(&mutex);
        }
    }
    
}
void *runnerw(void *param){
    int tid = *((int *)param);
    for(int i = length_of_list-1 ; length_of_list/2<i;i--){
        //sem_wait(&mutex);
        sum = sum+numbers[i];
        printf("Thread%d %d değerini okudu toplam = %d\n",tid,numbers[i],sum);
    }
    //printf("Thread%d %d değerini okudu toplam = %d\n",tid,numbers[(length_of_list-1)-i],sum);
    //sem_post(&mutex);

}