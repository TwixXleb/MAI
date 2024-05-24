// quicksort.h

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "deque.h"

Deque* quicksort(Deque *deque);
Deque* concatenate(Deque *less, int pivot, Deque *greater);
void sort_deque(Deque *deque);

#endif // QUICKSORT_H
