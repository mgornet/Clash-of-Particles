#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "particle.h"
#include "event.h" 
#include "heap.h" 


/* Function that prints the complexity of the insert and extract_min functions */
void complexity(){
		
	//create an empty heap
	heap my_heap = nil();
	
	//n represents the parameter of the complexity
	for (int n = 20 ; n < 10000001 ; n = 2*n){
		
		clock_t start_insert = clock();
		
		//create i events to insert
		for (int i = 0 ; i < n ; i++){
			 
			//initialisation of the event to insert
			event *p_my_event = malloc(sizeof(event));
			p_my_event -> time = i;
			p_my_event -> p_particle_a = NULL;
			p_my_event -> p_particle_b = NULL;
			p_my_event -> nb_collisions_particle_a = 0;
			p_my_event -> nb_collisions_particle_b = 0;
		
			//insertion of the event created
			insert(&my_heap, p_my_event);
		}
		
		clock_t end_insert = clock();
		
		//compute the time requiered to insert i events
		double time_to_insert = (double)(end_insert - start_insert)/CLOCKS_PER_SEC;
		
		
		clock_t start_extract = clock();
		
		//extraction of i events
		for (int i = 0 ; i < n ; i++){
			
			//extraction of each event
			event *p_e = extract_min(&my_heap);
		}
		
		clock_t end_extract = clock();
	
		//compute the time requiered to extract i events
		double time_to_extract = (double)(end_extract - start_extract)/CLOCKS_PER_SEC;
		
		//write the data in the file and close it
		FILE *p_file = NULL;
		
		//open the file in the right directory
		p_file = fopen("scripts/data_complexity_heap.csv", "w+");
	
		//error case
		if (p_file == NULL) {
			fprintf(stderr, "Cannot write to file data_complexity_heap.csv!\n");
			exit(EXIT_FAILURE);
		}
    
		//write the data in the file
		fprintf(p_file, "%d,%lf,%lf\n", n, time_to_insert, time_to_extract);

		//close the file
		fclose(p_file);
		
		//write_complexity(p_file, n, time_to_insert, time_to_extract);
		p_file = NULL;
	}
}

int main() {
	complexity();
	return 0;
}

