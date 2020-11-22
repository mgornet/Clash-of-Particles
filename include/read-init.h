#ifndef READINIT_H
#define READINIT_H

/**
 * @brief Read the initiation file
 * 		  whether its the random particles file or the newton pendulum file
 * 
 * @param h equal to `0` when executing a random generation of particles, `1` when executing newton
 * @param line the rank of the particle in the file from 1 to nb_particles
 * @param nb_particles the number of particles to create
 * @param i the int associated to a parameter :
 * 		  0 for x
 * 		  1 for y
 * 		  2 for vx
 * 		  3 for vy
 * 		  4 for r
 * 		  5 for m
 * 		  6 for c
 */
double read_init(int h, int line, int nb_particles, int i);

#endif
