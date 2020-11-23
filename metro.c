#include <time.h>

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

#define PORT 8080 
#define ONE_SECOND 1000000
#define NUM_RAILS 5
#define print printf
#define NUM_METROS 34


sem_t AB;
sem_t BC;
sem_t CD;
sem_t EB;
sem_t FA;
sem_t SOCK;

pthread_t metros[NUM_METROS];
int has_arrived_metros[NUM_METROS];


int sock = 0, valread; 
struct sockaddr_in serv_addr; 

char buffer[1024] = {0}; 

void enter(int ID){
    sem_wait(&SOCK);
    int rail = ( 3 * ID ) % NUM_RAILS ;
    char message[20] ;
    sprintf(message, "%d:1:%d", rail, ID);
    send(sock, message, strlen(message), 0);
    read(sock, buffer, 1024);
    printf("ID-%d has entered %d", ID, rail );
    sem_post(&SOCK);

}

void leave(int ID){
    sem_wait(&SOCK);
    int rail = ( 3 * ID ) % NUM_RAILS ;
    char message[20] ;
    sprintf(message, "%d:0:%d", rail, ID);
    send(sock, message, strlen(message), 0);
    read(sock, buffer, 1024);
    printf("ID-%d has left %d", ID, rail);
    sem_post(&SOCK);

}

void setup_socket(){

    sem_init(&SOCK, 0, 1);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
}

void* metro_func(void* rail){  
    
    usleep(ONE_SECOND * rand()%15);
    int metro_ID = (int) rail;
    int rail_num = ( 3 * metro_ID ) % NUM_RAILS ;
    switch (rail_num){
    case 0:
    // ENTERING A->B
        sem_wait(&AB);
       enter(metro_ID);
        usleep(ONE_SECOND*6);
        leave(metro_ID);        
        sem_post(&AB);
        break;
    
    case 1:
    // ENTERING B->C
       sem_wait(&BC);
        enter(metro_ID);
        usleep(ONE_SECOND*6);
        leave(metro_ID);
       sem_post(&BC);
        break;

    case 2:
    // ENTERING C->D
       sem_wait(&CD);
        enter(metro_ID);
        usleep(ONE_SECOND*6);
        leave(metro_ID);       
        sem_post(&CD);
        break;
    case 3:
    // ENTERING E->B
       sem_wait(&EB);
        enter(metro_ID);
        usleep(ONE_SECOND*6);
        leave(metro_ID);
       sem_post(&EB);
        break;

    case 4:
    // ENTERING F->A
       sem_wait(&FA);
        enter(metro_ID);
        usleep(ONE_SECOND*6);
        leave(metro_ID);
       sem_post(&FA);
        break;

    default:
        printf("%d appeared out of the blue. It has been destroyed.\n", metro_ID);
        break;
    }   
    has_arrived_metros[metro_ID] = 1;
}


int main(){
   
   sem_init(&AB, 0, 1);
   sem_init(&BC, 0, 1);
   sem_init(&CD, 0, 1);
   sem_init(&EB, 0, 1);
   sem_init(&FA, 0, 1);
   setup_socket();


   printf("Die Berlin Metro Station jetzt ist geöffnet.\n");

    int rail_number = 0;
    for (int i=0; i<=NUM_METROS; i++){
        pthread_create(&metros[i], NULL, metro_func,(void*)i);
        has_arrived_metros[i] = 0;
    }
    
    int not_done = 1;
    int i;
    while(not_done){
        usleep(ONE_SECOND);
        i = NUM_METROS;
        while( (has_arrived_metros[i]==1) && i ) i--;
        if (has_arrived_metros[i] == 0) not_done = -1;
    }
    printf("\n Everyone has arrived.\n");
    return 0;
    
}
