/**
 * @file event.h
 *
 * @brief Simple definition of an event
 *
 * @author Gornet Mélanie
 *
 * This is a simple definition of an event
 */

#include <stdbool.h>

#include "particle.h"

#ifndef EVENT_H
#define EVENT_H

/**
 * @brief An alias to the structure representing the event
 */
typedef struct event event;

/**
 * @brief The structure representing an event.
 */

struct event {
	/** The time at which the event occurs */
	double time;
	/** A pointer to the first particle involved in the collision */
	particle *p_particle_a;
	/** A pointer to the second particle involved in the collision */
	particle *p_particle_b;
	/** The number of collisions in which the particle a has been involved at the time of the event */
	int nb_collisions_particle_a;
	/** The number of collisions in which the particle b has been involved at the time of the event */
	int nb_collisions_particle_b;
};

/**
 * @brief Test if an event is valid according to the definition of a
 * 		  valid event in the subject
 * 
 * @param p_my_event a pointer to the event to consider
 * @param time the time when the event is checked
 * 
 * @return `true` if the evnt is valid, `false` else
 */
bool is_valid(event *p_my_event, double time);

/**
 * @brief Print the elements of a particle
 * 
 * @param p_particle a pointer to the particle to print
 */
void print_particle(particle *p_particle);

/**
 * @brief Print the elements of an event
 * 
 * @param p_event a pointer to the event to print
 */
void print_event(event *p_event);

#endif
