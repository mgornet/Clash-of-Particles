#include <stdio.h>
#include "write-init.h"
#include "read-init.h"


/* Function to test write-init and read-init */
void test_loader(){
	write_init(100);
	read_init(0, 1, 100, 0);
}
	

int main(){
	test_loader();
	return 0;
}

