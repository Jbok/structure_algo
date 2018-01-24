#include "queueADT.h"
#define INIT_CAPACITY 100

void terminate(const char *message) {
	printf("%s\n", message);
	exit(1);
}

int get_size(Queue q) {
	return q->size;
}

Queue create() {
	Queue q = (Queue)malloc(sizeof(queue_type));
	if (q == NULL)
		terminate("Error in create: queue could not be created.");
	q->contents = (Item *)malloc(INIT_CAPACITY*sizeof(Item));
	if (q->contents == NULL)
		terminate("Error in create: queue contents could not be created.");
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->capacity = INIT_CAPACITY;
	return q;
}

void destroy(Queue q) {
	free(q->contents);
	free(q);
}

void make_empty(Queue q) {
	q->front = 0;
	q->rear = -1;
	q->size = 0;
}

bool is_empty(Queue q) {
	return q->size == 0;
}

bool is_full(Queue q) {
	return q->size == q->capacity;
}

void enqueue(Queue q, Item i) {
	if (is_full(q))
		reallocate(q);
	q->rear = (q->rear + 1) % q->capacity;
	(q->contents)[q->rear] = i;
	q->size++;
}

Item dequeue(Queue q) {
	if (is_empty(q))
		terminate("Error in dequeue: queue is empty.");
	Item result = (q->contents)[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	return result;
}

Item peek(Queue q){
	if (is_empty(q))
		terminate("Error in dequeue: queue is empty.");
	Item result = (q->contents)[q->front];
	return result;
}

void reallocate(Queue q) {
	Item *temp = (Item *)malloc(sizeof(Item) * 2 * q->capacity);
	if (temp == NULL)
		terminate("Erro in create: queue could not be expanded.");
	int j = q->front;
	for (int i = 0; i < q->size; i++) {
		temp[i] = (q->contents)[j];
		j = (j + 1)*(q->capacity);
	}
	free(q->contents);

	q->front = 0;
	q->rear = q->size - 1;
	q->contents = temp;
	q->capacity *= 2;
}

///                                      ///
///   queue implemented by linked list   ///
///                                      /// 
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
