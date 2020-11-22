#include <stdio.h>
#include <stdbool.h>

#include "particle.h"
#include "event.h"

/* Test if an event is valid */
bool is_valid(event *p_my_event, double time) {
	
	//case of a refreshing event
	if (p_my_event->p_particle_a == NULL && p_my_event->p_particle_b == NULL ){
		return true;
	}
	//case of a collision with a vertical wall
	else if(p_my_event->p_particle_a == NULL && p_my_event->p_particle_b != NULL ){
		int c2 = p_my_event->nb_collisions_particle_b;
		int c2_bis = p_my_event -> p_particle_b->nb_collisions;
		if (c2==c2_bis) {
			return true;
		}
	}
		
	//case of a collision with a horizontal wall
	else if(p_my_event->p_particle_b == NULL && p_my_event->p_particle_a != NULL ){
		int c1 = p_my_event->nb_collisions_particle_a;
		int c1_bis = p_my_event -> p_particle_a->nb_collisions;
		if (c1==c1_bis) {
			return true;
		}
	}
	
	//case of a collision with another particle
	else if (p_my_event->p_particle_a != NULL && p_my_event->p_particle_b != NULL ) {
		int c1 = p_my_event->nb_collisions_particle_a;
		int c2 = p_my_event->nb_collisions_particle_b;
		int c1_bis = p_my_event->p_particle_a->nb_collisions;
		int c2_bis = p_my_event -> p_particle_b->nb_collisions;
		if (c1==c1_bis && c2==c2_bis) {
			return true;
		}
	}
	return false;
}

/* Tests functions */

/* Print the elements of a particle */
void print_particle(particle *p_particle){
	
	if (p_particle != NULL){
		printf("++ %lf\n", p_particle->position[0]);
		printf("%lf\n", p_particle->position[1]);
		printf("%lf\n", p_particle->velocity[0]);
		printf("%lf\n", p_particle->velocity[1]);
		printf("%lf\n", p_particle->radius);     
		printf("%lf\n", p_particle->mass);         
		printf("%d\n\n", p_particle->nb_collisions);
	}
}

/* Print the elements of an event */
void print_event(event *p_event){
	
	printf("+ %lf\n",p_event -> time);
	print_particle(p_event -> p_particle_a);
	print_particle(p_event -> p_particle_b);
	printf("%d\n",p_event -> nb_collisions_particle_a);
	printf("%d\n",p_event -> nb_collisions_particle_b);
}

/*int main(){
	return 0;
}*/
