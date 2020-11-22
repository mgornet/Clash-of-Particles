/**
 * @mainpage Simulation of a clash of particles
 *
 * @section To execute the whole clash : make clash-particles
 * 
 * You have the possibility to generate a number of random particles or 
 * to simulate a Newton pendulum.
 */

/**
 * @file simulation.h
 *
 * @brief Simulation of the clash of particles
 *
 * @author Gornet Mélanie
 *
 * This is a description of the simulation and the functions it contains
 *
 */

#include "heap.h"

#ifndef SIMULATION_H
#define SIMULATION_H

/**
 * @brief Compute all the events compatible with the particule
 *
 * @param p_Q a pointer to the heap you insert the node in
 * @param p_particle a pointer to the particle involved in the collisions
 * @param nb_particles an int representing the number of particles
 * @param cloud a list of pointers to the other particles
 * @param general_time a float representing the time
 * @param p_exclu a pointer to the particle to exclude in case of a collision 
 * 		  between two particles, `NULL` otherwise
 */
void compute_collisions(heap *p_Q, particle *p_particle, int nb_particles,
						particle *cloud[nb_particles], double general_time, particle *p_exclu);

/**
 * @brief Run the simulation
 *
 * @param h equal to `0` when executing a random generation of particles, `1` when executing newton
 * @param nb_particles an int representing the number of particles
 */			
void simulation(int h, int nb_particles);

/**
 * @brief Initialise a particle
 * 
 * @param h equal to `0` when executing a random generation of particles, `1` when executing newton
 * @param k the rank of the particle in the cloud
 * @param nb_particle the number of particles to generate
 * 
 * @return a pointer to the particle created
 */
particle *create_particle(int h, int k, int nb_particles);

#endif
