#include <stdio.h>
#include <math.h>

#include "particle.h"

#define SIZE 900
#define EPS 1e-12


/* Update the position of the particle to t + delta_t */
void update_position(particle *p_my_particle, double delta_t) {
	
	p_my_particle->position[0] = p_my_particle->position[0]
								   + delta_t * p_my_particle->velocity[0];
	p_my_particle->position[1] = p_my_particle->position[1]
								   + delta_t * p_my_particle->velocity[1];
}


/* Compute the time at whitch the particle will hit a vertical wall */
double expected_time_vertical_wall (particle *p_my_particle) {

	//definitions of short-cuts
	double x = p_my_particle->position[0];
	double vx = p_my_particle->velocity[0];
	double r = p_my_particle->radius;
	
	//case where vx could be considered equal to zero
	if (fabs(vx) < EPS) {
		return INFINITY;
	}
	
	//case where vx > 0
	else if (vx > 0.0) {
		return ((SIZE-x-r)/vx);
	}
	
	//case where vx < 0
	else {
		return ((r-x)/vx);
	}
}


/* Compute the time at whitch the particle will hit an horizontal wall */
double expected_time_horizontal_wall (particle *p_my_particle) {
	
	//definitions of short-cuts
	double y = p_my_particle->position[1];
	double vy = p_my_particle->velocity[1];
	double r = p_my_particle->radius;
	
	//case where vy could be considered equal to zero
	if (fabs(vy) < EPS) {
		return INFINITY;
	}
	
	//case where vy > 0
	else if (vy > 0.0) {
		return ((SIZE-y-r)/vy);
	}
	
	//case where vy < 0
	else {
		return ((r-y)/vy);
	}
}


/* Update the velocity of a particle after a collision with a vertical wall */
void update_velocity_vertical_wall (particle *p_my_particle) {
	
	//update velocity
	p_my_particle->velocity[0] = - (p_my_particle->velocity[0]);
	
	//update collision
	p_my_particle->nb_collisions++;
}


/* Update the velocity of a particle after a collision with an horizontal wall */
void update_velocity_horizontal_wall (particle *p_my_particle) {
	
	//update velocity
	p_my_particle->velocity[1] = - (p_my_particle->velocity[1]);
	
	//update collision
	p_my_particle->nb_collisions++;
}


/* Compute the time at whitch the two particles considerated will collide */
double expected_time_collision (particle *p_particle_1, particle *p_particle_2) {

	//definitions of short-cuts
	double x1 = p_particle_1->position[0];
	double y1 = p_particle_1->position[1];
	double vx1 = p_particle_1->velocity[0];
	double vy1 = p_particle_1->velocity[1];
	double r1 = p_particle_1->radius;
	double x2 = p_particle_2->position[0];
	double y2 = p_particle_2->position[1];
	double vx2 = p_particle_2->velocity[0];
	double vy2 = p_particle_2->velocity[1];
	double r2 = p_particle_2->radius;
	double delta_p[2];
	delta_p[0] = x2-x1;
	delta_p[1] = y2-y1;
	double delta_v[2];
	delta_v[0] = vx2-vx1;
	delta_v[1] = vy2-vy1;
	double pv = delta_p[0]*delta_v[0]+delta_p[1]*delta_v[1];
	double vv = delta_v[0]*delta_v[0]+delta_v[1]*delta_v[1];
	double pp = delta_p[0]*delta_p[0]+delta_p[1]*delta_p[1];
	
	//compute delta
	double delta = 4.0*pv*pv-4.0*vv*(pp-(r1+r2)*(r1+r2));
	
	//cases to exclude
	if (delta < EPS|| (-(pv+sqrt(pv*pv-vv*(pp-(r1+r2)*(r1+r2))))/vv) < EPS) {
		return INFINITY;
	}
	
	//compute delta_t
	else {
		return (-(pv+sqrt(pv*pv-vv*(pp-(r1+r2)*(r1+r2))))/vv);
	}
}


/* Update the velocity of two particles after they collided */
void update_velocities (particle *p_particle_1, particle *p_particle_2) {
	
	//definitions of short-cuts
	double x1 = p_particle_1->position[0];
	double y1 = p_particle_1->position[1];
	double vx1 = p_particle_1->velocity[0];
	double vy1 = p_particle_1->velocity[1];
	double r1 = p_particle_1->radius;
	double m1 = p_particle_1->mass;
	double x2 = p_particle_2->position[0];
	double y2 = p_particle_2->position[1];
	double vx2 = p_particle_2->velocity[0];
	double vy2 = p_particle_2->velocity[1];
	double r2 = p_particle_2->radius;
	double m2 = p_particle_2->mass;
	double delta_p[2];
	delta_p[0] = x2-x1;
	delta_p[1] = y2-y1;
	double delta_v[2];
	delta_v[0] = vx2-vx1;
	delta_v[1] = vy2-vy1;
	double pv = delta_p[0]*delta_v[0]+delta_p[1]*delta_v[1];
	
	//update velocities
	p_particle_1->velocity[0] = vx1+(((2*m2*pv)/((m1+m2)*(r1+r2)*(r1+r2)))*delta_p[0]);
	p_particle_1->velocity[1] = vy1+(((2*m2*pv)/((m1+m2)*(r1+r2)*(r1+r2)))*delta_p[1]);
	p_particle_2->velocity[0] = vx2-(((2*m1*pv)/((m1+m2)*(r1+r2)*(r1+r2)))*delta_p[0]);
	p_particle_2->velocity[1] = vy2-(((2*m1*pv)/((m1+m2)*(r1+r2)*(r1+r2)))*delta_p[1]);
	
	//update numbers of collisions
	p_particle_1->nb_collisions++;
	p_particle_2->nb_collisions++;
}

/*int main(){
	return 0;
}*/

