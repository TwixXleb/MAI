// quicksort.c

#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

Deque* quicksort(Deque *deque);
Deque* concatenate(Deque *less, int pivot, Deque *greater);

Deque* quicksort(Deque *deque) {
    if (size(deque) <= 1) {
        return deque;
    }

    int pivot = remove_rear(deque);
    Deque *less = create_deque(deque->capacity);
    Deque *greater = create_deque(deque->capacity);

    while (!is_empty(deque)) {
        int item = remove_front(deque);
        if (item <= pivot) {
            add_rear(less, item);
        } else {
            add_rear(greater, item);
        }
    }

    less = quicksort(less);
    greater = quicksort(greater);

    Deque *result = concatenate(less, pivot, greater);
    free_deque(less);
    free_deque(greater);

    return result;
}

Deque* concatenate(Deque *less, int pivot, Deque *greater) {
    Deque *result = create_deque(less->capacity + greater->capacity + 1);

    while (!is_empty(less)) {
        add_rear(result, remove_front(less));
    }

    add_rear(result, pivot);

    while (!is_empty(greater)) {
        add_rear(result, remove_front(greater));
    }

    return result;
}

void sort_deque(Deque *deque) {
    Deque *sorted_deque = quicksort(deque);
    while (!is_empty(sorted_deque)) {
        add_rear(deque, remove_front(sorted_deque));
    }
    free_deque(sorted_deque);
}
