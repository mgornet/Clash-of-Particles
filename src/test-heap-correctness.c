#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#include "particle.h"
#include "event.h"
#include "heap.h"
#include "disc.h"
#include "write-init.h"
#include "read-init.h"

#define SIZE 900


/* Function to test the correctness of the heap file */
void test_heap_correctness(){
	
	//create an empty heap
	heap my_heap = nil();
	
	//initialise the number of particles and events
	int nb_particles = 1000;
	int nb_events = 50;
	
	//write the init file
	write_init(nb_particles);

	for (int k = 0 ; k < nb_events ; k++){

		double a = (rand()/(double)RAND_MAX)*nb_particles;
		double b = (rand()/(double)RAND_MAX)*nb_particles;
		
		//initialisation of two particles for the event to insert
		particle *p_particle_1 = malloc(sizeof(particle));
		p_particle_1->position[0]   = read_init(0, a, nb_particles, 0)*SIZE;
		p_particle_1->position[1]   = read_init(0, a, nb_particles, 1)*SIZE;
		p_particle_1->velocity[0]   = read_init(0, a, nb_particles, 2)*SIZE;
		p_particle_1->velocity[1]   = read_init(0, a, nb_particles, 3)*SIZE;
		p_particle_1->radius        = read_init(0, a, nb_particles, 4)*SIZE;
		p_particle_1->mass          = read_init(0, a, nb_particles, 5)*SIZE;
		p_particle_1->nb_collisions = rand();
		
		particle *p_particle_2 = malloc(sizeof(particle));
		p_particle_2->position[0]   = read_init(0, b, nb_particles, 0)*SIZE;
		p_particle_2->position[1]   = read_init(0, b, nb_particles, 1)*SIZE;
		p_particle_2->velocity[0]   = read_init(0, b, nb_particles, 2)*SIZE;
		p_particle_2->velocity[1]   = read_init(0, b, nb_particles, 3)*SIZE;
		p_particle_2->radius        = read_init(0, b, nb_particles, 4)*SIZE;
		p_particle_2->mass          = read_init(0, b, nb_particles, 5)*SIZE;
		p_particle_2->nb_collisions = rand();
		
		//initialisation of the event to insert
		event *p_my_event = malloc(sizeof(event));
		p_my_event -> time = round((rand()/(double)RAND_MAX)*1000);
		p_my_event -> p_particle_a = p_particle_1;
		p_my_event -> p_particle_b = p_particle_2;
		p_my_event -> nb_collisions_particle_a = round((rand()/(double)RAND_MAX)*1000);
		p_my_event -> nb_collisions_particle_b = round((rand()/(double)RAND_MAX)*1000);
		
		//insertion of the event created
		insert(&my_heap, p_my_event);
	}
	
	//print the heap to verify function insert
	print_heap(&my_heap);
	
	//empty progressively the heap until its empty
	while(!is_empty(&my_heap)){
		print_event(extract_min(&my_heap));
	}
	
	//test dellocate function
	deallocate_heap(&my_heap);
}

int main(){
	test_heap_correctness();
	return 0;
}
