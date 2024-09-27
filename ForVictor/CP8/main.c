#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 


typedef struct {
    int data;   
    int next;   
} Node;


typedef struct {
    Node nodes[MAX_SIZE]; 
    int head;             
    int free;             
} List;


typedef struct {
    List* list;    
    int current;   
} Iterator;


void initializeList(List* list) {
    list->head = -1; 
    list->free = 0;  
    for(int i = 0; i < MAX_SIZE - 1; i++) {
        list->nodes[i].next = i + 1; 
    }
    list->nodes[MAX_SIZE - 1].next = -1; 
}


int allocateNode(List* list) {
    if(list->free == -1) {
        printf("Ошибка: Список заполнен!\n");
        return -1;
    }
    int newNode = list->free;
    list->free = list->nodes[newNode].next;
    return newNode;
}


void freeNode(List* list, int index) {
    list->nodes[index].next = list->free;
    list->free = index;
}


void initIterator(Iterator* it, List* list) {
    it->list = list;
    it->current = list->head;
}


int hasNext(Iterator* it) {
    return it->current != -1;
}


int nextIterator(Iterator* it, int* value) {
    if(it->current == -1)
        return 0;
    *value = it->list->nodes[it->current].data;
    it->current = it->list->nodes[it->current].next;
    return 1;
}


void printList(List* list) {
    Iterator it;
    initIterator(&it, list);
    printf("Список: ");
    int value;
    while(hasNext(&it)) {
        nextIterator(&it, &value);
        printf("%d ", value);
    }
    printf("\n");
}


void insertList(List* list, int value) {
    int newNode = allocateNode(list);
    if(newNode == -1) return; 
    list->nodes[newNode].data = value;
    list->nodes[newNode].next = -1;
    if(list->head == -1) {
        
        list->head = newNode;
    }
    else {
        
        int current = list->head;
        while(list->nodes[current].next != -1)
            current = list->nodes[current].next;
        list->nodes[current].next = newNode;
    }
    printf("Элемент %d вставлен в список.\n", value);
}


void deleteList(List* list, int value) {
    if(list->head == -1) {
        printf("Ошибка: Список пуст.\n");
        return;
    }
    int current = list->head;
    int prev = -1;
    while(current != -1 && list->nodes[current].data != value) {
        prev = current;
        current = list->nodes[current].next;
    }
    if(current == -1) {
        printf("Ошибка: Значение %d не найдено в списке.\n", value);
        return;
    }
    if(prev == -1) {
        
        list->head = list->nodes[current].next;
    }
    else {
        list->nodes[prev].next = list->nodes[current].next;
    }
    freeNode(list, current);
    printf("Элемент %d удален из списка.\n", value);
}


int lengthList(List* list) {
    int count = 0;
    Iterator it;
    initIterator(&it, list);
    while(hasNext(&it)) {
        nextIterator(&it, &(it.list->nodes[it.current].data));
        count++;
    }
    return count;
}


void reverseList(List* list) {
    int prev = -1;
    int current = list->head;
    int next;
    while(current != -1) {
        next = list->nodes[current].next;
        list->nodes[current].next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
    printf("Список был успешно перевернут.\n");
}


void displayMenu() {
    printf("\nМеню:\n");
    printf("1. Печать списка\n");
    printf("2. Вставка элемента\n");
    printf("3. Удаление элемента\n");
    printf("4. Подсчет длины списка\n");
    printf("5. Перевернуть список\n");
    printf("6. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    List list;
    initializeList(&list);
    int choice, value;
    while(1) {
        displayMenu();
        if(scanf("%d", &choice) != 1){
            printf("Ошибка ввода. Попробуйте снова.\n");
            
            while(getchar() != '\n');
            continue;
        }
        switch(choice) {
            case 1:
                printList(&list);
                break;
            case 2:
                printf("Введите значение для вставки: ");
                if(scanf("%d", &value) != 1){
                    printf("Ошибка ввода.\n");
                    while(getchar() != '\n');
                    break;
                }
                insertList(&list, value);
                break;
            case 3:
                printf("Введите значение для удаления: ");
                if(scanf("%d", &value) != 1){
                    printf("Ошибка ввода.\n");
                    while(getchar() != '\n');
                    break;
                }
                deleteList(&list, value);
                break;
            case 4:
                printf("Длина списка: %d\n", lengthList(&list));
                break;
            case 5:
                reverseList(&list);
                break;
            case 6:
                printf("Выход из программы.\n");
                exit(0);
            default:
                printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
        }
    }
    return 0;
}
