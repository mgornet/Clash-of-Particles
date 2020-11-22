/**
 * @file particle.h
 *
 * @brief Simple definition of a particle
 *
 * @author Gornet Mélanie
 *
 * This is a simple definition of a particle
 *
 */
 
#ifndef PARTICLE_H
#define PARTICLE_H
 
/**
 * @brief An alias to the structure representing the particle.
 */
typedef struct particle particle;

/**
 * @brief The structure representing the particle.
 */

struct particle {
	/** The position of the particle (x,y) */
	double position[2];
	/** The velocity of the particle (vx,vy) */
	double velocity[2];
	/** The mass of the particle */
	double mass;
	/** The radius of the particle */
	double radius;
	/** The number of collisions in whitch the particle has been implicated */
	int nb_collisions;
	/** The color of the particle (BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE)*/
	int color;
};

/**
 * @brief Update the position of the particle to t + delta_t
 * 
 * @param p_my_particle a pointer to the particle
 * @param delta_t a float time
 */
void update_position(particle *p_my_particle, double delta_t);

/**
 * @brief Compute the time at whitch the particle will hit a vertical wall
 * 
 * @param p_my_particle a pointer to the particle
 * 
 * @return the time computed
 */
double expected_time_vertical_wall (particle *p_my_particle);

/**
 * @brief Compute the time at whitch the particle will hit an horizontal wall
 * 
 * @param p_my_particle a pointer to the particle
 * 
 * @return the time computed
 */
double expected_time_horizontal_wall (particle *p_my_particle);

/**
 * @brief Update the velocity of a particle after
 * 		  a collision with a vertical wall
 * 
 * @param p_my_particle a pointer to the particle
 */
void update_velocity_vertical_wall (particle *p_my_particle);

/**
 * @brief Update the velocity of a particle after
 * 		  a collision with an horizontal wall
 * 
 * @param p_my_particle a pointer to the particle
 */
void update_velocity_horizontal_wall (particle *p_my_particle);

/**
 * @brief Compute the time at whitch the two particles considerated
 * 		  will collide
 * 
 * @param p_particle_1 a pointer to the first particle
 * @param p_particle_2 a pointer to the second particle
 * 
 * @return the time computed
 */
 double expected_time_collision (particle *p_particle_1, particle *p_particle_2);

/**
 * @brief Update the velocity of two particles after
 * 		  they collided
 * 
 * @param p_particle_1 a pointer to the first particle
 * @param p_particle_2 a pointer to the second particle
 */
void update_velocities (particle *p_particle_1, particle *p_particle_2);

#endif
