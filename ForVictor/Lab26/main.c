#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include "deque.h"
#include "quicksort.h"

void print_deque(Deque *deque) {
    printf("Дек: ");
    for (int i = 0; i < size(deque); i++) {
        printf("%d ", deque->data[(deque->front + i) % deque->capacity]);
    }
    printf("\n");
}

void concatenate_deques(Deque *deque1, Deque *deque2) {
    while (!is_empty(deque2)) {
        add_rear(deque1, remove_front(deque2));
    }
}

int main() {
    // Установить локаль на Russian_Russia.65001 для поддержки UTF-8
    setlocale(LC_ALL, "Russian_Russia.65001");

    Deque *deque1 = create_deque(100);
    Deque *deque2 = create_deque(100);
    int choice, value, time;
    char input[9999];

    while (1) {
        printf("\n1. Ввести дек №1\n");
        printf("2. Добавить элемент в конец дека №1\n");
        printf("3. Добавить элемент в начало дека №1\n");
        printf("4. Удалить элемент из конца дека №1\n");
        printf("5. Удалить элемент из начала дека №1\n");
        printf("6. Отсортировать дек №1\n");
        printf("7. Конкатенировать дек №1 с деком №2\n");
        printf("8. Показать дек №1\n");
        printf("9. Выйти\n");
        printf("Выберите опцию: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите элементы дека №1 (окончание ввода /):\n");
                while (1) {
                    scanf("%s", input);
                    if (input[0] == '/') break;
		    value = atoi(input);
                    add_rear(deque1, value);
                }
		sleep(3);
		break;
            case 2:
                printf("Введите значение: ");
                scanf("%d", &value);
                add_rear(deque1, value);
		sleep(3);
                break;
            case 3:
                printf("Введите значение: ");
                scanf("%d", &value);
                add_front(deque1, value);
		sleep(3);
                break;
            case 4:
                if (!is_empty(deque1)) {
                    value = remove_rear(deque1);
                    printf("Удалено значение: %d\n", value);
                } else {
                    printf("Дек пуст\n");
                }
		sleep(3);
                break;
            case 5:
                if (!is_empty(deque1)) {
                    value = remove_front(deque1);
                    printf("Удалено значение: %d\n", value);
                } else {
                    printf("Дек пуст\n");
                }
		sleep(3);
                break;
            case 6:
                sort_deque(deque1);
		printf("Подождите, идет сортировка");
		time = 2;
		while (time > 0) {
		    printf(".");
		    sleep(1);
		    time = time - 1;
                }
		printf(".\n");
		sleep(1);
                printf("Дек отсортирован\n");
		sleep(3);
                break;
            case 7:
                printf("Введите элементы дека 2 (окончание ввода /):\n");
                while (1) {
                    scanf("%s", input);
                    if (input[0] == '/') break;
		    value = atoi(input);
                    add_rear(deque1, value);
                }
                concatenate_deques(deque1, deque2);
		printf("Подождите, идет процесс конкатенации");
		time = 2;
		while (time > 0) {
		    printf(".");
		    sleep(1);
		    time = time - 1;
                }
		printf(".\n");
		sleep(1);
                printf("Деки конкатенированы\n");
		sleep(3);
                break;
            case 8:
		printf("Подождите, идет печать дека");
		time = 2;
		while (time > 0) {
		    printf(".");
		    sleep(1);
		    time = time - 1;
                }
		printf(".\n");
		sleep(1);
                print_deque(deque1);
		sleep(3);
                break;
            case 9:
                free_deque(deque1);
                free_deque(deque2);
                printf("Ожидание 3 секунд перед завершением");
                time = 2;
		while (time > 0) {
		    printf(".");
		    time = time - 1;
		    sleep(1);
                }
		printf(".\n");
		sleep(1);
                exit(0);
            default:
                printf("Неверный выбор, попробуйте снова\n");
        }
    }

    return 0;
}
