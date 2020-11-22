/**
 * @file heap.h
 *
 * @brief Simple definition of a binary heap containing `floats` values
 *
 * @author Gornet Mélanie
 *
 * This is a simple definition of a binary heap containing `floats`
 * values implemented using a binary tree. Warning: the cells
 * pointers should not be shared as deallocation of a BST
 * deallocates the memory space reserved for the cells!
 *
 * Inserting a value and extracting the minimum value are guaranteed
 * to have a worst-case complexity in $O(\log n)$ where $n$ is the
 * size of the heap.
 *
 * The API of the binary heap is defined as follows:
 *
 * - a function to create an empty heap
 * - a function to check if the heap is empty
 * - a function to insert a new value in the heap
 * - a function to get the minimum value in the heap
 * - a function to print the binary heap
 * - a function to deallocate the binary heap
 */

#include <stdbool.h>

#include "event.h"

#ifndef HEAP_H
#define HEAP_H

/**
 * @brief An alias to the structure representing the nodes of the
 *        binary heap.
 */
typedef struct heap_node heap_node;

/**
 * @brief The structure representing the nodes of the binary heap.
 */
struct heap_node {
    /** A pointer to the event stored in the node */
    event *p_event;
    /** A pointer to the left child node */
    heap_node *left;
    /** A pointer to the right child node */
    heap_node *right;
    /** A pointer to the father node */
    heap_node *father;
};

/**
 * @brief An alias to the structure representing a binary heap.
 */
typedef struct heap heap;

/**
 * @brief The structure representing the binary heap.
 */
struct heap {
    /** The root of the binary heap. May be `NULL` */
    heap_node *root;
    /** The size of the binary heap */
    int       size;
};

/**
 * @brief Create a nil binary heap.
 *
 * @return a new empty binary heap
 */
heap nil();

/**
 * @brief Is the binary heap empty?
 *
 * @param p_heap a pointer to the heap you want to
 *        check the emptiness
 *
 * @return `true` is `p_heap` is empty, `false` else
 *
 * @pre `p_heap` is not `NULL`
 */
bool is_empty(heap *p_heap);

/**
 * @brief Gives a pointer to the heap node pointer representing
 * 		  the father of node number n in the heap
 *
 * @param p_heap a pointer to the heap
 * @param n is the place of the node you want the father of
 *
 * @pre `p_heap` is not `NULL`
 * 
 * @return the father node of the n-node
 */
heap_node *go_to_father_node(heap *p_heap, int n);

/**
 * @brief Insert a new event in the binary heap. The
 *        worst-case execution time of this function
 *        is guaranteed to be in \f$\log n\f$ where
 *        \f$n\f$ is the size of the binary heap.
 *
 * @param p_heap a pointer to the heap in which the value is
 *        to be inserted
 * @param p_event a pointer to the event to be inserted
 *
 * @pre `p_heap` is not `NULL`
 *
 * @post After the call, `p_heap` will point to a binary heap
 *       in which the event *p_event has been inserted according
 *       to the algorithm presented in the lab session.
 */
void insert(heap *p_heap, event *p_event);

/**
 * @brief Switch two events placed in argument in the heap.
 *
 * @param p_1 a pointer to the first node to switch
 * @param p_2 a pointer to the second node to switch
 */
void switch_event(heap_node *p_1, heap_node *p_2);

/**
 * @brief Extract the event of the binary heap which time is minimum. The
 *        worst-case execution time of this function
 *        is guaranteed to be in \f$\log n\f$ where \f$n\f$ is
 *        the size of the binary heap.
 *
 * @param p_heap a pointer to the heap from which the event is
 *        to be extracted
 *
 * @return the event of the binary heap which time is minimum
 *
 * @pre `p_heap` is not `NULL` and the binary heap is not empty
 */
event *extract_min(heap *p_heap);

/**
 * @brief Prints the binary heap.
 *
 * @param p_heap a pointer to the binary heap to be printed
 *
 * @pre `p_heap` is not `NULL`
 *
 * @post After the call, the binary heap is printed.
 */
void print_heap(heap *p_heap);

/**
 * @brief Deallocate the node.
 *
 * @param p_node a pointer to the node to be deallocated
 *
 * @pre `p_node` is not `NULL`
 */
void deallocate_heap_node(heap_node *p_node);

/**
 * @brief Deallocate the binary heap.
 *
 * @param p_heap  a pointer to the binary heap to be deallocated
 *
 * @pre `p_heap` is not `NULL`
 *
 * @post After the call, all memory regions used for the nodes
 *       are deallocated.
 */
void deallocate_heap(heap *p_heap);

#endif
