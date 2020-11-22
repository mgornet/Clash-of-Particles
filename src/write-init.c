#include <stdio.h>
#include <stdlib.h>

#include "write-init.h"


/* Write the initiation file of random particles */
int write_init(int nb_particles) {
	
	//create and open a file called "init"
    FILE *p_file = NULL;
    p_file = fopen("data/init.txt", "w");

	//error case
    if (p_file == NULL) {
        fprintf(stderr, "Cannot write to file init.txt!\n");
        exit(EXIT_FAILURE);
    }

	//write lines 1 and 2
    fprintf(p_file,"initial situation\n");
    fprintf(p_file,"%d\n", nb_particles);
    
    //write lines 3 to n+2 corresponding to the particules' attributes
    for (int i=0 ; i < nb_particles ; i++) {
		double r = (rand()/(double)RAND_MAX)*0.006+0.004;
		double x = (rand()/(double)RAND_MAX)*(1-r);
		double y = (rand()/(double)RAND_MAX)*(1-r);
		double vx = (rand()/(double)RAND_MAX)*0.001-0.0005;
		double vy = (rand()/(double)RAND_MAX)*0.001-0.0005;
		double m = (rand()/(double)RAND_MAX)*0.4+0.4;
		int c = 1 + rand()%7;
		fprintf(p_file,"%lf,%lf,%lf,%lf,%lf,%lf,%d\n",x,y,vx,vy,r,m,c);
	}
	
	//close the file
    fclose(p_file);
    p_file = NULL;
    
    return 0;
}

/*int main(){
	return 0;
}*/
