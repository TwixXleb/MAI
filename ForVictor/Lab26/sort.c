#include "sort.h"
#include <stdio.h>


void swap(ElementType *a, ElementType *b) {
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}


void quicksort_recursive(Deque *dq, int low, int high) {
    if (low < high) {
        
        ElementType pivot;
        if (!deque_get(dq, high, &pivot)) {
            return;
        }

        int i = low - 1;
        for (int j = low; j < high; j++) {
            ElementType current;
            if (deque_get(dq, j, &current)) {
                if (current < pivot) {
                    i++;
                    ElementType elem_i, elem_j;
                    deque_get(dq, i, &elem_i);
                    deque_get(dq, j, &elem_j);
                    swap(&elem_i, &elem_j);
                    
                    
                    dq->data[(dq->front + i) % DEQUE_MAX_SIZE] = elem_i;
                    dq->data[(dq->front + j) % DEQUE_MAX_SIZE] = elem_j;
                }
            }
        }
        
        ElementType elem_i_plus_1, elem_high;
        deque_get(dq, i + 1, &elem_i_plus_1);
        deque_get(dq, high, &elem_high);
        swap(&elem_i_plus_1, &elem_high);
        dq->data[(dq->front + i + 1) % DEQUE_MAX_SIZE] = elem_i_plus_1;
        dq->data[(dq->front + high) % DEQUE_MAX_SIZE] = elem_high;

        int pi = i + 1;

        
        quicksort_recursive(dq, low, pi - 1);
        quicksort_recursive(dq, pi + 1, high);
    }
}

void quicksort_deque(Deque *dq) {
    if (dq->size <= 1) {
        return;
    }
    quicksort_recursive(dq, 0, dq->size - 1);
}

bool concatenate_deques(Deque *dq1, const Deque *dq2) {
    if (dq1->size + dq2->size > DEQUE_MAX_SIZE) {
        return false; 
    }
    for (int i = 0; i < dq2->size; i++) {
        ElementType elem;
        if (deque_get(dq2, i, &elem)) {
            deque_push_back(dq1, elem);
        }
    }
    return true;
}
