#include "deque.h"
#include <stdio.h>

void deque_init(Deque *dq) {
    dq->front = 0;
    dq->rear = -1;
    dq->size = 0;
}

bool deque_is_empty(const Deque *dq) {
    return dq->size == 0;
}

bool deque_is_full(const Deque *dq) {
    return dq->size == DEQUE_MAX_SIZE;
}

int deque_size(const Deque *dq) {
    return dq->size;
}

bool deque_push_front(Deque *dq, ElementType elem) {
    if (deque_is_full(dq)) {
        return false;
    }
    dq->front = (dq->front - 1 + DEQUE_MAX_SIZE) % DEQUE_MAX_SIZE;
    dq->data[dq->front] = elem;
    dq->size++;
    if (dq->rear == -1) {
        dq->rear = dq->front;
    }
    return true;
}

bool deque_push_back(Deque *dq, ElementType elem) {
    if (deque_is_full(dq)) {
        return false;
    }
    dq->rear = (dq->rear + 1) % DEQUE_MAX_SIZE;
    dq->data[dq->rear] = elem;
    dq->size++;
    if (dq->front == -1) {
        dq->front = dq->rear;
    }
    return true;
}

bool deque_pop_front(Deque *dq, ElementType *elem) {
    if (deque_is_empty(dq)) {
        return false;
    }
    *elem = dq->data[dq->front];
    if (dq->size == 1) {
        dq->front = 0;
        dq->rear = -1;
    } else {
        dq->front = (dq->front + 1) % DEQUE_MAX_SIZE;
    }
    dq->size--;
    return true;
}

bool deque_pop_back(Deque *dq, ElementType *elem) {
    if (deque_is_empty(dq)) {
        return false;
    }
    *elem = dq->data[dq->rear];
    if (dq->size == 1) {
        dq->front = 0;
        dq->rear = -1;
    } else {
        dq->rear = (dq->rear - 1 + DEQUE_MAX_SIZE) % DEQUE_MAX_SIZE;
    }
    dq->size--;
    return true;
}

bool deque_get(const Deque *dq, int index, ElementType *elem) {
    if (index < 0 || index >= dq->size) {
        return false;
    }
    int actual_index = (dq->front + index) % DEQUE_MAX_SIZE;
    *elem = dq->data[actual_index];
    return true;
}

void deque_print(const Deque *dq) {
    if (deque_is_empty(dq)) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque: ");
    for (int i = 0; i < dq->size; i++) {
        int idx = (dq->front + i) % DEQUE_MAX_SIZE;
        printf("%d ", dq->data[idx]);
    }
    printf("\n");
}
