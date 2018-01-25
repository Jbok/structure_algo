#pragma once
#ifndef __QUEEUE_ADT_H__
#define __QUEEUE_ADT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



struct maze_node {
	int x;
	int y;
};
typedef struct maze_node Position;

typedef Position Item;

struct queue_type {
	int front;
	int rear;
	int size;
	Item* contents;
	int capacity;
};
typedef struct queue_type *Queue;


void terminate(const char *message);
int get_size(Queue q);
Queue create();
void destroy(Queue q);
void make_empty(Queue q);
bool is_empty(Queue q);
bool is_full(Queue q);
void enqueue(Queue q, Item i);
Item dequeue(Queue q);
Item peek(Queue q);
void reallocate(Queue q);







///                                      ///
///   queue implemented by linked list   ///
///                                      /// 
/*
typedef struct queue_type *Queue;
typedef struct node *Node;
typedef int Item;
*/
#endif