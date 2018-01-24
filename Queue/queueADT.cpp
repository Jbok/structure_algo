#include "queueADT.h"

////////////////////////////////////////////
///                                      ///
///   queue implemented by linked list   ///
///                                      /// 
////////////////////////////////////////////
/*
struct queue_type {
Node front;
Node rear;
int size;
};
struct node {
Item data;
struct node *next;
};
Queue create_queue() {
Queue ptr_queue = (Queue)malloc(sizeof(queue_type));
if (ptr_queue == NULL)
terminate("Error in create: queue could not be created.");
ptr_queue->front = NULL;
ptr_queue->rear= NULL;
ptr_queue->size = 0;
return ptr_queue;
}
void destroy(Queue q) {
make_empty(q);
free(q);
}
void make_empty(Queue q) {
while (is_empty(q)) {
dequeue(q);
}
if (q->size != 0)
terminate("Error in make_empty: queue could not be empty.");
}
bool is_empty(Queue q) {
return q->front == NULL;
}
void enqueue(Queue q, Item i) {
Node temp = create_node(i);
if (temp == NULL)
terminate("Error in push: queue is full.");

if (is_empty(q)) {
q->front = temp;
q->rear = temp;
}
else {
q->rear->next = temp;
q->rear = temp;
}
q->size++;
}
Item dequeue(Queue q) {
Node temp = q->front;
Item item = temp->data;

if (is_empty(q))
terminate("Erro in deque: queue is empty.");
else if (temp == q->rear) {
q->front = NULL;
q->rear = NULL;
}
else {
q->front = q->front->next;
}
free(temp);
q->size--;
return item;
}
Item peek(Queue q) {
Node temp = q->front;
Item item = temp->data;

return item;
}
Node create_node(Item i) {
Node ptr_node = (Node)malloc(sizeof(node));
ptr_node->next = NULL;
ptr_node->data = i;

return ptr_node;
}
void terminate(const char *message) {
printf("%s\n", message);
exit(1);
}
int get_size(Queue q) {
return q->size;
}


*/
