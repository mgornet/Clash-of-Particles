#include <stdio.h>
#include <stdlib.h>

#include "particle.h"
#include "event.h"
#include "heap.h"


/* Function to test the file particle.c */
void test_particles(int k) {
	
	//initialise the particles given in the subject
	
	particle *p_p1 = malloc(sizeof(particle));
	particle *p_p2 = malloc(sizeof(particle));
	particle *p_p3 = malloc(sizeof(particle));
	particle *p_p4 = malloc(sizeof(particle));
	particle *p_p5 = malloc(sizeof(particle));
	particle *p_p6 = malloc(sizeof(particle));
	particle *p_p7 = malloc(sizeof(particle));
	particle *p_p8 = malloc(sizeof(particle));
	
	float time_to_collision[5];
	float new_velocities[16];
	
	p_p1->position[0]=0.25;
	p_p1->position[1]=0.25;
	p_p1->velocity[0]=0.5;
	p_p1->velocity[1]=0.0;
	p_p1->mass=0.5;
	p_p1->radius=0.01;
	
	p_p2->position[0]=0.25;
	p_p2->position[1]=0.25;
	p_p2->velocity[0]=-0.5;
	p_p2->velocity[1]=0.0;
	p_p2->mass=0.5;
	p_p2->radius=0.01;
	
	p_p3->position[0]=0.25;
	p_p3->position[1]=0.25;
	p_p3->velocity[0]=0.0;
	p_p3->velocity[1]=0.5;
	p_p3->mass=0.5;
	p_p3->radius=0.01;
	
	p_p4->position[0]=0.25;
	p_p4->position[1]=0.25;
	p_p4->velocity[0]=0.0;
	p_p4->velocity[1]=-0.5;
	p_p4->mass=0.5;
	p_p4->radius=0.01;
	
	p_p5->position[0]=0.25;
	p_p5->position[1]=0.25;
	p_p5->velocity[0]=0.25;
	p_p5->velocity[1]=-0.4;
	p_p5->mass=0.5;
	p_p5->radius=0.01;
	
	p_p6->position[0]=0.5;
	p_p6->position[1]=0.25;
	p_p6->velocity[0]=0.0;
	p_p6->velocity[1]=0.0;
	p_p6->mass=0.8;
	p_p6->radius=0.005;
	
	p_p7->position[0]=0.75;
	p_p7->position[1]=0.25;
	p_p7->velocity[0]=-0.25;
	p_p7->velocity[1]=0.0;
	p_p7->mass=0.5;
	p_p7->radius=0.01;
	
	p_p8->position[0]=0.6;
	p_p8->position[1]=0.8;
	p_p8->velocity[0]=0.25;
	p_p8->velocity[1]=-0.4;
	p_p8->mass=0.8;
	p_p8->radius=0.005;
	
	//first test
	
	if (k==1) {
	
		time_to_collision[0]=expected_time_vertical_wall(p_p1);
		time_to_collision[1]=expected_time_vertical_wall(p_p2);
		time_to_collision[2]=expected_time_vertical_wall(p_p3);
		time_to_collision[3]=expected_time_vertical_wall(p_p4);
		time_to_collision[4]=expected_time_vertical_wall(p_p5);
	
		update_velocity_vertical_wall(p_p1);
		update_velocity_vertical_wall(p_p2);
		update_velocity_vertical_wall(p_p5);
	
		new_velocities[0]=p_p1->velocity[0];
		new_velocities[1]=p_p1->velocity[1];
		new_velocities[2]=p_p2->velocity[0];
		new_velocities[3]=p_p2->velocity[1];
		new_velocities[4]=p_p5->velocity[0];
		new_velocities[5]=p_p5->velocity[1];
	
		printf("Time to collision :\n%f\n%f\n%f\n%f\n%f\n", time_to_collision[0],time_to_collision[1],time_to_collision[2],time_to_collision[3],time_to_collision[4]);
		printf("New velocities :\n(%f,%f)\n(%f,%f)\n(%f,%f)\n",new_velocities[0],new_velocities[1],new_velocities[2],new_velocities[3],new_velocities[4],new_velocities[5]);
	}
	
	//second test
	
	if (k==2){
	
		time_to_collision[0]=expected_time_horizontal_wall(p_p1);
		time_to_collision[1]=expected_time_horizontal_wall(p_p2);
		time_to_collision[2]=expected_time_horizontal_wall(p_p3);
		time_to_collision[3]=expected_time_horizontal_wall(p_p4);
		time_to_collision[4]=expected_time_horizontal_wall(p_p5);
	
		update_velocity_horizontal_wall(p_p3);
		update_velocity_horizontal_wall(p_p4);
		update_velocity_horizontal_wall(p_p5);
	
		new_velocities[0]=p_p3->velocity[0];
		new_velocities[1]=p_p3->velocity[1];
		new_velocities[2]=p_p4->velocity[0];
		new_velocities[3]=p_p4->velocity[1];
		new_velocities[4]=p_p5->velocity[0];
		new_velocities[5]=p_p5->velocity[1];
	
		printf("Time to collision :\n%f\n%f\n%f\n%f\n%f\n", time_to_collision[0],time_to_collision[1],time_to_collision[2],time_to_collision[3],time_to_collision[4]);
		printf("New velocities :\n(%f,%f)\n(%f,%f)\n(%f,%f)\n",new_velocities[0],new_velocities[1],new_velocities[2],new_velocities[3],new_velocities[4],new_velocities[5]);
	}
	
	//third test
	
	if (k==3){
	
		time_to_collision[0]=expected_time_collision(p_p1,p_p6);
		time_to_collision[1]=expected_time_collision(p_p1,p_p7);
		time_to_collision[2]=expected_time_collision(p_p1,p_p8);
		time_to_collision[3]=expected_time_collision(p_p7,p_p8);
		
		p_p1->position[0]=0.25;
		p_p1->position[1]=0.25;
		p_p1->velocity[0]=0.5;
		p_p1->velocity[1]=0.0;
		p_p1->mass=0.5;
		p_p1->radius=0.01;
		
		update_position(p_p1,time_to_collision[0]);
		update_position(p_p6,time_to_collision[0]);
		update_velocities(p_p1,p_p6);
		new_velocities[0]=p_p1->velocity[0];
		new_velocities[1]=p_p1->velocity[1];
		new_velocities[2]=p_p6->velocity[0];
		new_velocities[3]=p_p6->velocity[1];
		
		p_p1->position[0]=0.25;
		p_p1->position[1]=0.25;
		p_p1->velocity[0]=0.5;
		p_p1->velocity[1]=0.0;
		p_p1->mass=0.5;
		p_p1->radius=0.01;
		
		update_position(p_p1,time_to_collision[1]);
		update_position(p_p7,time_to_collision[1]);
		update_velocities(p_p1,p_p7);
		new_velocities[4]=p_p1->velocity[0];
		new_velocities[5]=p_p1->velocity[1];
		new_velocities[6]=p_p7->velocity[0];
		new_velocities[7]=p_p7->velocity[1];
		
		p_p1->position[0]=0.25;
		p_p1->position[1]=0.25;
		p_p1->velocity[0]=0.5;
		p_p1->velocity[1]=0.0;
		p_p1->mass=0.5;
		p_p1->radius=0.01;
		
		update_position(p_p1,time_to_collision[2]);
		update_position(p_p8,time_to_collision[2]);
		update_velocities(p_p1,p_p8);
		new_velocities[8]=p_p1->velocity[0];
		new_velocities[9]=p_p1->velocity[1];
		new_velocities[10]=p_p8->velocity[0];
		new_velocities[11]=p_p8->velocity[1];
	
		printf("Time to collision :\n%f\n%f\n%f\n%f\n", time_to_collision[0],time_to_collision[1],time_to_collision[2],time_to_collision[3]);
		printf("New velocities :\n(%f,%f)\n(%f,%f)\n(%f,%f)\n(%f,%f)\n(%f,%f)\n(%f,%f)\n",new_velocities[0],new_velocities[1],new_velocities[2],new_velocities[3],new_velocities[4],new_velocities[5],new_velocities[6],new_velocities[7],new_velocities[8],new_velocities[9],new_velocities[10],new_velocities[11]);
	}
	
	//deallocate
	
	free(p_p1);
	free(p_p2);
	free(p_p3);
	free(p_p4);
	free(p_p5);
	free(p_p6);
	free(p_p7);
	free(p_p8);
}

int main() {
	test_particles(1);
	test_particles(2);
	test_particles(3);
	return 0;
}

