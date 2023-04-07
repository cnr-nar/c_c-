#include <pthread.h> // for threads
#include <stdio.h>
#include <stdlib.h> // for malloc funtion
#include <time.h>
#include <unistd.h> // for sleep function
#include <semaphore.h> // for semaphores

#define MAX_THREADS 2
  
sem_t mutex;


void *runner(void *param);

int length_of_list;
int sum=0;
int *numbers;

int main(int argc, char *argv[])
{
    int number;
    int *ptr;

    srand(time(NULL)); // the reason of full rand.
    sem_init(&mutex, 0, 1);//initialization of semaphores or locks

    pthread_t tid[MAX_THREADS]; //Threads array
    pthread_attr_t attr; // deffault attribute threads

    printf("Enter lenght of list: ");
    scanf("%d",&length_of_list);
    numbers = malloc(length_of_list * sizeof(numbers)); // dynamic memory allocation for number ptr

    printf("Randomized Set => ");
    
    for(int i=0;i<length_of_list;i++){   // Generates random numbers 0-9 
        number = rand() % 10;
        numbers[i] = number; // appointing numbers
        printf("%d ",numbers[i]);
    }
    printf("\n");

    pthread_attr_init(&attr);

    for (int i = 0; i < MAX_THREADS; i++){ // Creates threads as MAX_THREADS
        ptr = malloc(sizeof(int)); // mem alloc of pointer
        *ptr=i+1; // assaign a number to pointer as tid
        pthread_create(&tid[i], &attr, runner, ptr);
    }
    for (int i = 0; i < MAX_THREADS ;i++){//Joins threads
        pthread_join(tid[i], NULL);
    }
        
    sem_destroy(&mutex); // destroy the lock or semaphores

    return 0;
}

void *runner(void *param){
    int tid = *((int *)param);// Get id of the Threads (Casts void ptr to int ptr and gets value of ptr)
    int i=0;
    while(numbers[i]!=-1){ // check condition
        if(tid==1 && numbers[i] !=-1){ //Forward counting Thread
            sem_wait(&mutex); // Aquaire lock 
            sum = sum+numbers[i];// '\0' is int 0, cheking condition became -1
            printf("Value of the Thread%d is %d, total sum = %d\n",tid,numbers[i],sum);
            numbers[i]=-1;       
        }
        sleep(1);// wait for 1 sec 
        if(tid==2 && numbers[(length_of_list-1)-i]!=-1){ // Backward counting Thread
            sem_post(&mutex); // Relese the lock
            sum = sum+numbers[(length_of_list-1)-i];
            printf("Value of the Thread%d is %d, total sum = %d\n",tid,numbers[(length_of_list-1)-i],sum);
            numbers[(length_of_list-1)-i]=-1;// '\0' is int 0, cheking condition became -1
        }
        sleep(1);
        i++;
    }
}