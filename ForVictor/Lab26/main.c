#include <stdio.h>
#include "deque.h"
#include "sort.h"

int main() {
    Deque deque1, deque2;

    deque_init(&deque1);
    deque_init(&deque2);
    
    deque_push_back(&deque1, 5);
    deque_push_back(&deque1, 3);
    deque_push_back(&deque1, 8);
    deque_push_back(&deque1, 1);
    
    deque_push_back(&deque2, 7);
    deque_push_back(&deque2, 2);
    deque_push_back(&deque2, 6);
    deque_push_back(&deque2, 4);

    printf("Первый дек:\n");
    deque_print(&deque1);

    printf("Второй дек:\n");
    deque_print(&deque2);

    
    if (concatenate_deques(&deque1, &deque2)) {
        printf("После конкатенации:\n");
        deque_print(&deque1);
    } else {
        printf("Не удалось конкатенировать деки: недостаточно места.\n");
    }

    
    quicksort_deque(&deque1);
    printf("После сортировки:\n");
    deque_print(&deque1);

    return 0;
}
