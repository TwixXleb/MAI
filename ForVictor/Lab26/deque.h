// deque.h

#ifndef DEQUE_H
#define DEQUE_H

typedef struct Deque {
    int *data;
    int front;
    int rear;
    int capacity;
} Deque;

// Функции для работы с деком
Deque* create_deque(int capacity);
int is_empty(Deque *deque);
void add_front(Deque *deque, int item);
void add_rear(Deque *deque, int item);
int remove_front(Deque *deque);
int remove_rear(Deque *deque);
int size(Deque *deque);
void free_deque(Deque *deque);

#endif // DEQUE_H
