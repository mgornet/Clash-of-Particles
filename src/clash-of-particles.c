#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "simulation.h"
#include "disc.h"

/* Window size */ 
#define SIZE 900


/* Function to enable the clash */
void clash_of_particles() {
	
	//initialisation of variables
	int newton = 1;
	int nb;
	
	//ask if the user wants to use the newton pendulum
	printf("Enable Newton (1/0)? "); 
    scanf("%d", &newton);
	
	//if he doesn't want to use the pendulum, ask him the number of random particles
	if (newton == 0){ 
		printf("How many particles? ");
		scanf("%d", &nb);
	}

	//create the window
    CreateWindow("Let It Clash", SIZE, SIZE);
 
	//launch newton
    if (newton == 1){
		simulation(1, 5);
	}
	//launch the random generation of particles
	else{
		simulation(0, nb);
	}

	//close window
    CloseWindow();
}


/* Main function */
int main(){
	clash_of_particles();
	return 0;
} 

