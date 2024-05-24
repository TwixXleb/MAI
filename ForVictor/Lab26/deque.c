// deque.c

#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

Deque* create_deque(int capacity) {
    Deque *deque = (Deque*)malloc(sizeof(Deque));
    deque->data = (int*)malloc(capacity * sizeof(int));
    deque->front = -1;
    deque->rear = -1;
    deque->capacity = capacity;
    return deque;
}

int is_empty(Deque *deque) {
    return (deque->front == -1);
}

void add_front(Deque *deque, int item) {
    if (deque->front == 0 && deque->rear == deque->capacity - 1) {
        printf("Deque is full\n");
        return;
    }
    if (deque->front == -1) {
        deque->front = deque->rear = 0;
    } else if (deque->front == 0) {
        deque->front = deque->capacity - 1;
    } else {
        deque->front = deque->front - 1;
    }
    deque->data[deque->front] = item;
}

void add_rear(Deque *deque, int item) {
    if (deque->front == 0 && deque->rear == deque->capacity - 1) {
        printf("Deque is full\n");
        return;
    }
    if (deque->front == -1) {
        deque->front = deque->rear = 0;
    } else if (deque->rear == deque->capacity - 1) {
        deque->rear = 0;
    } else {
        deque->rear = deque->rear + 1;
    }
    deque->data[deque->rear] = item;
}

int remove_front(Deque *deque) {
    if (is_empty(deque)) {
        printf("Deque is empty\n");
        exit(EXIT_FAILURE);
    }
    int item = deque->data[deque->front];
    if (deque->front == deque->rear) {
        deque->front = deque->rear = -1;
    } else if (deque->front == deque->capacity - 1) {
        deque->front = 0;
    } else {
        deque->front = deque->front + 1;
    }
    return item;
}

int remove_rear(Deque *deque) {
    if (is_empty(deque)) {
        printf("Deque is empty\n");
        exit(EXIT_FAILURE);
    }
    int item = deque->data[deque->rear];
    if (deque->front == deque->rear) {
        deque->front = deque->rear = -1;
    } else if (deque->rear == 0) {
        deque->rear = deque->capacity - 1;
    } else {
        deque->rear = deque->rear - 1;
    }
    return item;
}

int size(Deque *deque) {
    if (is_empty(deque)) {
        return 0;
    }
    if (deque->rear >= deque->front) {
        return (deque->rear - deque->front + 1);
    }
    return (deque->capacity - deque->front + deque->rear + 1);
}

void free_deque(Deque *deque) {
    free(deque->data);
    free(deque);
}
