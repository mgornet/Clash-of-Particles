#include <stdio.h>
#include <stdlib.h>

#include "particle.h"
#include "event.h"
#include "heap.h"

/* Auxiliary functions */

void print_level(heap_node *p_node, int level) {
    for (int i = 0; i < level - 1; i++) {
        printf("   ");
    }

    if (p_node == NULL) {
        printf("%snil\n", level == 0 ? "" : " +-");
        return;
    }

    printf("%s(%lf)\n", level == 0 ? "" : " +-", p_node->p_event->time);
    print_level(p_node->left, level + 1);
    print_level(p_node->right, level + 1);
}

/* Gives a pointer to the heap node pointer representing the father
	of node number n in the heap */
heap_node *go_to_father_node(heap *p_heap, int n) {
	char *carray = malloc(sizeof(int)*8+1);
	int level = 0;
	while (n != 0) {
		carray[level] = (n&1) ==1 ? 'r' : 'l';
		level = level+1;
		n = n>>1;
	}
	heap_node *p_father_node = p_heap -> root;
	for (int i = level-2 ; i >0 ; i--) {
		if (carray[i] == 'l') {
			p_father_node = p_father_node -> left;
		}
		else {
			p_father_node = p_father_node -> right;
		}
	}
	free(carray);
    return p_father_node;
}


/* Function to deallocate a node */
void deallocate_heap_node(heap_node *p_node){
		
	if(p_node != NULL){
		deallocate_heap_node(p_node->right);
		deallocate_heap_node(p_node->left);
		free(p_node);
	}
}
 
 
/* Function to deallocate an heap */
void deallocate_heap(heap *p_heap){
	deallocate_heap_node(p_heap->root);
}


/* Function that switches two events */
void switch_event(heap_node *p_1, heap_node *p_2){
	event *p_e1_switch = p_1->p_event;
	event *p_e2_switch = p_2->p_event;
	p_1->p_event = p_e2_switch;
	p_2->p_event = p_e1_switch;
}


/* Extract the minimum of a binary heap */
event *extract_min (heap *p_heap){
	
	int n = p_heap->size;
	
	//save root value
	event *p_root = malloc(sizeof(event));
	p_root = p_heap->root->p_event;
	
	//case of a 1-sized heap
	if (n==1){
		p_heap->root = NULL;
		free(p_heap->root);
		p_heap->size=0;
		return(p_root);
	}
	
	//case size > 2
	else{
		
		heap_node *p_node;
		
		//search for the last node, exchange value with the min and free the last node
		if (go_to_father_node(p_heap,n)->right != NULL){
			p_node = go_to_father_node(p_heap,n)->right;
			go_to_father_node(p_heap,n)->right = NULL;			
		}
		else {
			p_node = go_to_father_node(p_heap,n)->left;
			go_to_father_node(p_heap,n)->left = NULL;			
		}
		p_heap->root->p_event = p_node->p_event;
		p_node = NULL;
		free(p_node);
		
		//create pointer to the value that needs to be moved down the heap
		heap_node *p_current = p_heap->root;
		
		//while you're not at the end of the heap, continue to go down
		while (((p_current->left != NULL) && (p_current->p_event->time > p_current->left->p_event->time))
		   || ((p_current->right != NULL) && (p_current->p_event->time > p_current->right->p_event->time))){
			
			//case where you can exchange with both : choose the min
			if ((p_current->right != NULL)
			 && (p_current->left != NULL)
			 && (p_current->p_event->time > p_current->right->p_event->time)
	     	 && (p_current->p_event->time > p_current->left->p_event->time)){
				 
				 //the min is on the right
				if (p_current->left->p_event->time >= p_current->right->p_event->time){
					switch_event(p_current,p_current->right);
					p_current = p_current->right;
				}
				//the min is on the left
				else if (p_current->left->p_event->time < p_current->right->p_event->time){
					switch_event(p_current,p_current->left);
					p_current = p_current->left;
				}
			}
			
			//case where you can only exchange with the right node
			else if ((p_current->right != NULL)
				  && (p_current->p_event->time > p_current->right->p_event->time)
				  && (p_current->p_event->time < p_current->left->p_event->time)){
				switch_event(p_current,p_current->right);
				p_current = p_current->right;
			}
			//case where you can only exchange with the left node
			else if ((p_current->left != NULL)
			   && (p_current->p_event->time > p_current->left->p_event->time)
			   && (p_current->right == NULL || p_current->p_event->time < p_current->right->p_event->time)){
				switch_event(p_current,p_current->left);
				p_current = p_current->left;
			}
		}
		
		//update the size of the heap and return the root
		p_heap->size--;
		return(p_root);
	}
}
		
		
/* Insert an event at its right place in the binary heap */
void insert(heap *p_heap, event *p_my_event) {
	
	int n = p_heap -> size;
	
	//case where the heap is empty
	if(n==0){
		heap_node *node = malloc(sizeof(heap_node));
		node->p_event   = p_my_event;
		node->left      = NULL;
		node->right     = NULL;
		node->father    = NULL;
		p_heap->root    = node;
	}
	
	//case where the heap is not empty
	else{
		
		//create a new node in the heap to insert your event
		heap_node *node = malloc(sizeof(heap_node));
		
		//initialise a pointer to the father of the last node
		heap_node *p_father = go_to_father_node(p_heap, n+1);
		
		//insert your event on the left of the father if the place isn't taken
		if(p_father->left==NULL){
			node->p_event = p_my_event;
			node->left=NULL;
			node->right=NULL;
			node->father=p_father;
			p_father->left=node;
		}
		
		//insert it on the right if the place on the left is taken
		else{
			node->p_event = p_my_event;
			node->left=NULL;
			node->right=NULL;
			node->father=p_father;
			p_father->right=node;
		}
		
		//make your new event go up the heap until it reaches its right place
		while(node->father!=NULL && ((node -> p_event -> time) < (node -> father -> p_event -> time))) {
			switch_event(node, node->father);
			node=node->father;
		}
	}
	
	//update the size of the heap
	p_heap->size=n+1;
}


/* Check if a binary heap is empty */
bool is_empty(heap *p_heap) {
	
	//an heap is empty when its root points to NULL or the size of the heap is zero
	if (p_heap -> root == NULL || p_heap->size == 0) {
		return true;
	}
	else {
		return false;
	}
}


/* Create an empty binary heap */
heap nil() {
	
	//initialise an empty heap with a NULL pointer and a size = 0 
	heap *my_heap = malloc(sizeof(heap_node));
	my_heap -> size = 0 ;
	my_heap -> root = NULL;
	return *my_heap;
}

/* Print the binary heap given in argument */
void print_heap (heap *p_heap) {
	print_level(p_heap->root,1);
}


/*int main(){
	return 0;
}*/
