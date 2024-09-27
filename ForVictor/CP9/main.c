#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 8     // Максимальное количество элементов в таблице
#define TEXT_LENGTH 200     // Максимальная длина текстовой записи

// Структура элемента таблицы
typedef struct {
    long double key;         // Вещественный ключ (16 байт)
    char text[TEXT_LENGTH];  // Текстовая запись
} TableElement;

// Функция для вывода таблицы на экран
void printTable(TableElement arr[], int n) {
    for(int i = 0; i < n; i++) {
        printf("Элемент %d:\n", i + 1);
        printf("Ключ: %.4Lf\n", arr[i].key);
        printf("Текст: %s\n", arr[i].text);
        printf("-------------------------\n");
    }
}

// Процедура сортировки методом пузырька
void bubbleSort(TableElement arr[], int n) {
    int i, j;
    TableElement temp;
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(arr[j].key > arr[j + 1].key) {
                // Обмен элементов
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Функция двоичного поиска по ключу
int binarySearch(TableElement arr[], int n, long double key) {
    int left = 0;
    int right = n - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid].key == key) {
            return mid; // Ключ найден
        }
        else if(arr[mid].key < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Ключ не найден
}

// Функция инициализации таблицы в отсортированном порядке
void initSorted(TableElement arr[], int n, char *poemLines[]) {
    for(int i = 0; i < n; i++) {
        arr[i].key = (long double)(i + 1); // Ключи возрастают
        strcpy(arr[i].text, poemLines[i]);
    }
}

// Функция инициализации таблицы в обратном порядке
void initReverse(TableElement arr[], int n, char *poemLines[]) {
    for(int i = 0; i < n; i++) {
        arr[i].key = (long double)(n - i); // Ключи убывают
        strcpy(arr[i].text, poemLines[i]);
    }
}

// Функция инициализации таблицы случайным образом
void initRandom(TableElement arr[], int n, char *poemLines[]) {
    srand(time(NULL)); // Инициализация генератора случайных чисел
    for(int i = 0; i < n; i++) {
        arr[i].key = ((long double)rand() / (RAND_MAX)) * 100.0L; // Случайные ключи от 0 до 100
        strcpy(arr[i].text, poemLines[i]);
    }
}

// Функция обработки каждого случая
void performCase(int caseNumber, void (*initFunc)(TableElement[], int, char *[]), TableElement table[], int n, char *poemLines[]) {
    switch(caseNumber) {
        case 1:
            printf("=== Случай 1: Элементы уже отсортированы ===\n");
            break;
        case 2:
            printf("=== Случай 2: Элементы в обратном порядке ===\n");
            break;
        case 3:
            printf("=== Случай 3: Элементы неупорядочены (рандом) ===\n");
            break;
        default:
            printf("Неизвестный случай.\n");
    }

    // Инициализация таблицы
    initFunc(table, n, poemLines);
    
    // Вывод исходного состояния таблицы
    printf("Исходная таблица:\n");
    printTable(table, n);
    
    // Сортировка таблицы
    bubbleSort(table, n);
    
    // Вывод отсортированной таблицы
    printf("Отсортированная таблица:\n");
    printTable(table, n);
    printf("===========================================\n");
    
    // Выполнение двоичного поиска
    int searchCount;
    printf("Введите количество ключей для поиска в случае %d: ", caseNumber);
    scanf("%d", &searchCount);
    for(int i = 0; i < searchCount; i++) {
        long double key;
        printf("Введите ключ для поиска: ");
        scanf("%Lf", &key);
        int index = binarySearch(table, n, key);
        if(index != -1) {
            printf("Ключ найден на индексе %d:\n", index + 1);
            printf("Ключ: %.4Lf\n", table[index].key);
            printf("Текст: %s\n", table[index].text);
        }
        else {
            printf("Ключ %.4Lf не найден в таблице.\n", key);
        }
        printf("-------------------------\n");
    }
    printf("===========================================\n");
}

int main() {
    TableElement table[MAX_ELEMENTS];
    int n = MAX_ELEMENTS;

    // Фрагмент стихотворения "Руслан и Людмила" Александра Сергеевича Пушкина
    char *poemLines[MAX_ELEMENTS] = {
        "Ночь, улица, фонарь, аптека,",
        "Бессмысленный и тусклый свет.",
        "Живи еще хоть четверть века —",
        "Всё будет так. Исхода нет.",
        "Умрёшь — начнёшь опять сначала",
        "И повторится всё, как встарь:",
        "Ночь, ледяная рябь канала,",
        "Аптека, улица, фонарь."
    };

    // Обработка всех трех случаев
    performCase(1, initSorted, table, n, poemLines);
    performCase(2, initReverse, table, n, poemLines);
    performCase(3, initRandom, table, n, poemLines);

    return 0;
}
