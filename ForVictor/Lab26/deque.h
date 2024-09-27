#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>


#define DEQUE_MAX_SIZE 100


typedef int ElementType;


typedef struct {
    ElementType data[DEQUE_MAX_SIZE];
    int front;
    int rear;
    int size;
} Deque;


void deque_init(Deque *dq);
bool deque_is_empty(const Deque *dq);
bool deque_is_full(const Deque *dq);
int deque_size(const Deque *dq);
bool deque_push_front(Deque *dq, ElementType elem);
bool deque_push_back(Deque *dq, ElementType elem);
bool deque_pop_front(Deque *dq, ElementType *elem);
bool deque_pop_back(Deque *dq, ElementType *elem);
bool deque_get(const Deque *dq, int index, ElementType *elem);
void deque_print(const Deque *dq);

#endif 
