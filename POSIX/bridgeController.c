#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>


#define NB_CAMIONS 5
#define NB_VOITURES 5
#define NB_VEHICULES (NB_CAMIONS + NB_VOITURES)
#define SLEEP_TIME 1000000


//semaphore pour vehicules
sem_t sem_compteur[NB_VEHICULES];

// Protege les variables d'etat.
pthread_mutex_t camion_sc ;

int camions_bloques = 0;
int curr_weight_on_bridge = 0;

int write_to_bridge(char* line){
    FILE* file = fopen("bridge.txt","a");
    fprintf(file,"%s\n" ,line);    
    fclose(file);
    return 1;
}

void* car(int id){
    char car_string[30] = "";
    sprintf(car_string, "Car %d has entered the bridge.", id);
    write_to_bridge(car_string);
    
    sprintf(car_string, "Car %d has left the bridge.", id);
    write_to_bridge(car_string);
    // join threads n shit
    usleep(SLEEP_TIME); //attendre 1 seconde
}

void* truck(int id){
    char truck_string[30] = "";
    sprintf(truck_string, "Truck %d entered.", id);
    write_to_bridge(truck_string);
    
    sprintf(truck_string, "Truck %d has left", id);
    write_to_bridge(truck_string);
    // join threads n shit
    usleep(SLEEP_TIME); //attendre 1 seconde
}

void entrer_pont(int tonnes, int id){
    
}

void quitter_pont(int tonnes, int id){
    
}

 

int main(){
    write_to_bridge("_______.new._______");    
    car(1);
    truck(3);
    car(4);
    truck(12);
    write_to_bridge("_______.END._______");
    return 0;
}

