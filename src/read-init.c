#include <stdio.h>
#include <stdlib.h>

#include "read-init.h"


/* Read the initiation file */
double read_init(int h, int line, int nb_particles, int i) {
	
	//get directly to the first particle
	line = line + 2;
	
	int fscanf_result = 0;
	
	//open the file to read
    FILE *p_file = NULL;
    if (h == 0){
		p_file = fopen("data/init.txt", "r");
		fscanf_result = fscanf(p_file, "initial situation");
		fscanf_result = fscanf(p_file, "%d",&nb_particles);
	}
	else if (h == 1){		
		p_file = fopen("data/newton-simple.txt", "r");
		fscanf_result = fscanf(p_file, "Simple test with Newton pendulum");
		fscanf_result = fscanf(p_file, "%d",&nb_particles);
	}

	//error case
    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", "init.txt");
        exit(EXIT_FAILURE);
    }
    
	//initialisation of the particle
    double x           = 0.0;
    double y           = 0.0;
    double vx          = 0.0;
    double vy          = 0.0;
    double r           = 0.0;
    double m           = 0.0;
    int c                  ;

    for (int k = 3 ; k < line + 1 ; k++) {
     
        fscanf_result = fscanf(p_file, "%lf,%lf,%lf,%lf,%lf,%lf,%d",&x,&y,&vx,&vy,&r,&m,&c);
    }
    
    fscanf_result = nb_particles;
    
    //close the file
    fclose(p_file);
    p_file = NULL;
    
    if (i==0){
		return(x);
	}
	else if (i==1){
		return(y);
	}
	else if (i==2){
		return(vx);
	}
	else if (i==3){
		return(vy);
	}
	else if (i==4){
		return(r);
	}
	else if (i==5){
		return(m);
	}
	else if (i==6){
		return(c);
	}
}


/*int main(){
	return 0;
}*/
