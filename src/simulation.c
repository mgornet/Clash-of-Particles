#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "disc.h"
#include "write-init.h"
#include "read-init.h"
#include "simulation.h"

#define SIZE 900
#define EPS 1e-12


/* Compute all the events compatible with the particule */
void compute_collisions(heap *p_Q, particle *p_particle, int nb_particles,
						particle *cloud[nb_particles], double general_time, particle *p_exclu){
	
	//create events of collision with other particles and insert them
	for (int j = 0 ; j < nb_particles ; j++) {
		if (p_particle != cloud[j] && p_exclu != cloud[j]) {	
			event *p_event_p                    = malloc(sizeof(event));
			p_event_p->time                     = general_time + expected_time_collision(p_particle, cloud[j]);
			p_event_p->p_particle_a             = p_particle;
			p_event_p->p_particle_b             = cloud[j];
			p_event_p->nb_collisions_particle_a = p_particle->nb_collisions;
			p_event_p->nb_collisions_particle_b = cloud[j]->nb_collisions;
			if (p_event_p->time != INFINITY && p_event_p->time > EPS){
				insert(p_Q,p_event_p);
			}
			free(p_event_p);
		}
	}
		
	//create event of collision with a vertical wall and insert it
	event *p_event_v                    = malloc(sizeof(event));
	p_event_v->time                     = general_time + expected_time_vertical_wall(p_particle);
	p_event_v->p_particle_a             = NULL;
	p_event_v->p_particle_b             = p_particle;
	p_event_v->nb_collisions_particle_a = 0;
	p_event_v->nb_collisions_particle_b = p_particle->nb_collisions;
	if (p_event_v->time != INFINITY && p_event_v->time > EPS){
		insert(p_Q,p_event_v);
	}
	free(p_event_v);
	
	//create event of collision with an horizontal wall and insert it
	event *p_event_h                    = malloc(sizeof(event));
	p_event_h->time                     = general_time + expected_time_horizontal_wall(p_particle);
	p_event_h->p_particle_a             = p_particle;
	p_event_h->p_particle_b             = NULL;
	p_event_h->nb_collisions_particle_a = p_particle->nb_collisions;
	p_event_h->nb_collisions_particle_b = 0;
	if (p_event_h->time != INFINITY && p_event_h->time > EPS){
		insert(p_Q,p_event_h);
	}
	free(p_event_h);
}


/* Initialise a particle */
particle *create_particle(int h, int k, int nb_particles){
	
	//malloc the particle in the heap
	particle *p_particle      = malloc(sizeof(particle));
	
	//initialise the particle's characteristics from the init file
	p_particle->position[0]   = read_init(h, k+1, nb_particles, 0)*SIZE;
	p_particle->position[1]   = read_init(h, k+1, nb_particles, 1)*SIZE;
	p_particle->velocity[0]   = read_init(h, k+1, nb_particles, 2)*SIZE;
	p_particle->velocity[1]   = read_init(h, k+1, nb_particles, 3)*SIZE;
	p_particle->radius        = read_init(h, k+1, nb_particles, 4)*SIZE;
	p_particle->mass          = read_init(h, k+1, nb_particles, 5);
	p_particle->nb_collisions = 0;
	p_particle->color         = read_init(h, k,nb_particles,6);
	
	//return the particle with the right characteristics
	return (p_particle);
}


/* Run the simulation */
void simulation(int h, int nb_particles) {
	
	//create an initialisation file of particles
	write_init(nb_particles);
	
	//initiate all parameters
	double general_time = 0.0; 
	double refresh_time = 3;
	double max_time     = 10000;
	heap Q              = nil();
	heap *p_Q           = &Q;
	particle *cloud[nb_particles];
	
	//initiate window 
	CreateWindow("Clash-of-particles", SIZE, SIZE); 
	EmptySpace();
	
	for (int k = 0 ; k < nb_particles ; k++) {
		
		//read the characteristics of each particle
		particle * p_particle = create_particle(h, k, nb_particles);
		
		//stock the particles in cloud
		cloud[k] = p_particle;
		
		//draw each particle
		DrawDISC(p_particle->position[0],p_particle->position[1],
				 p_particle->radius, p_particle->color);
				 
		
		free(p_particle); 
	}
	UpdateScreen();
	
	//create all events between particles and insert them in Q
	for (int i = 0 ; i < nb_particles ; i++) {	
		for (int j = i+1 ; j < nb_particles ; j++) {
				event *p_event_p                    = malloc(sizeof(event));
				p_event_p->time                     = general_time + expected_time_collision(cloud[i], cloud[j]);
				p_event_p->p_particle_a             = cloud[i];
				p_event_p->p_particle_b             = cloud[j];
				p_event_p->nb_collisions_particle_a = 0;
				p_event_p->nb_collisions_particle_b = 0;
				if (p_event_p->time != INFINITY && p_event_p->time > EPS){
					insert(p_Q,p_event_p);
				}
				free(p_event_p);
		}
		
		//create event of collision with a vertical wall and insert it
			event *p_event_v                    = malloc(sizeof(event));
			p_event_v->time                     = general_time + expected_time_vertical_wall(cloud[i]);
			p_event_v->p_particle_a             = NULL;
			p_event_v->p_particle_b             = cloud[i];
			p_event_v->nb_collisions_particle_a = 0;
			p_event_v->nb_collisions_particle_b = 0;
			if (p_event_v->time != INFINITY && p_event_v->time > EPS){
				insert(p_Q,p_event_v);
			}
			free(p_event_v);
		
		//create event of collision with an horizontal wall and insert it
			event *p_event_h                    = malloc(sizeof(event));
			p_event_h->time                     = general_time + expected_time_horizontal_wall(cloud[i]);
			p_event_h->p_particle_a             = cloud[i];
			p_event_h->p_particle_b             = NULL;
			p_event_h->nb_collisions_particle_a = 0;
			p_event_h->nb_collisions_particle_b = 0;
			if (p_event_h->time != INFINITY && p_event_h->time > EPS){
				insert(p_Q,p_event_h);
			}
			free(p_event_h); 
	}
	
	//create refreshing event and insert it
	event *p_event_r                    = malloc(sizeof(event));
	p_event_r->time                     = 0.0;
	p_event_r->p_particle_a             = NULL;
	p_event_r->p_particle_b             = NULL;  
	p_event_r->nb_collisions_particle_a = 0;
	p_event_r->nb_collisions_particle_b = 0;
	if (p_event_r->time != INFINITY){
		insert(p_Q,p_event_r);
	}
	free(p_event_r);
	
	//analyse all events until the heap is emptied
	while (!is_empty(p_Q) && general_time < max_time) {
		
		//extract the earliest event from Q 
		event *p_e = extract_min(p_Q); 
		
		//update the particles positions up to time t
		if (is_valid(p_e, p_e->time)) {
			for (int i = 0 ; i < nb_particles ; i++){
				update_position(cloud[i], (p_e->time-general_time));
			}
			
			//if the earliest event is a refreshing event
			if (p_e->p_particle_a==NULL && p_e->p_particle_b==NULL) {
				
				//redraw the particles in the GUI
				EmptySpace();
				for (int l = 0 ; l < nb_particles ; l++){
					DrawDISC(cloud[l]->position[0],cloud[l]->position[1],
							 cloud[l]->radius,cloud[l]->color);
				}
				UpdateScreen();
				
				//add a refreshing event at time t + refresh rate in Q
				event *p_event_r                    = malloc(sizeof(event));
				p_event_r->time                     = p_e -> time + refresh_time;
				p_event_r->p_particle_a             = NULL;
				p_event_r->p_particle_b             = NULL;
				p_event_r->nb_collisions_particle_a = 0;
				p_event_r->nb_collisions_particle_b = 0;
				if (p_event_r->time != INFINITY && p_event_r->time > 0){
					insert(p_Q,p_event_r);
				}
				free(p_event_r); 
			}
			
			//if the earliest event is a collision with a vertical wall
			else if (p_e->p_particle_a==NULL && p_e->p_particle_b!=NULL) {
				
				//update the particle velocity and its number of collisions
				update_velocity_vertical_wall(p_e->p_particle_b);
				
				//compute new collisions involving the particle and insert them in Q
				compute_collisions(p_Q, p_e->p_particle_b, nb_particles, cloud, p_e->time, NULL);
			}
			
			//if the earliest event is a collision with an horizontal wall
			else if (p_e->p_particle_a!=NULL && p_e->p_particle_b==NULL) {
			
				//update the particle velocity and its number of collisions
				update_velocity_horizontal_wall(p_e->p_particle_a);
				
				//compute new collisions involving the particle and insert them in Q
				compute_collisions(p_Q, p_e->p_particle_a, nb_particles, cloud, p_e->time, NULL);
			}
			
			//if the earliest event is a collision with an other particle
			else if (p_e->p_particle_a!=NULL && p_e->p_particle_b!=NULL) {
				
				//update the particles velocities and numbers of collisions
				update_velocities(p_e->p_particle_a, p_e->p_particle_b);
				
				//compute new collisions involving the particle a and insert them in Q
				compute_collisions(p_Q, p_e->p_particle_a, nb_particles, cloud, p_e->time, p_e->p_particle_b);
				
				//compute new collisions involving the particle b and insert them in Q
				compute_collisions(p_Q, p_e->p_particle_b, nb_particles, cloud, p_e->time, p_e->p_particle_a);
			}
			
			//update the time
			general_time = p_e->time;
			
			//deallocate
			free(p_e);
		}
	}
	deallocate_heap(p_Q);
}

/*int main(){
	//simulation(20);
	return 0;
}*/
