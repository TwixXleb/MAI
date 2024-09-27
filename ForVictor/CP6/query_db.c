#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"


int all_grades_unique(Grades g) {
    int grades[NUM_SUBJECTS] = {g.math, g.physics, g.chemistry, g.biology, g.literature};
    for (int i = 0; i < NUM_SUBJECTS - 1; i++) {
        for (int j = i + 1; j < NUM_SUBJECTS; j++) {
            if (grades[i] == grades[j]) {
                return 0; 
            }
        }
    }
    return 1; 
}


void print_table(Applicant *applicants, int count) {
    printf("ID | Имя                 | Пол | М | Ф | Х | Б | Л\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-3d| %-20s| %-3c| %-1d| %-1d| %-1d| %-1d| %-1d\n",
               applicants[i].id,
               applicants[i].name,
               applicants[i].gender,
               applicants[i].grades.math,
               applicants[i].grades.physics,
               applicants[i].grades.chemistry,
               applicants[i].grades.biology,
               applicants[i].grades.literature);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s -f | -p\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], KEY_PRINT_FILE) == 0) {
        
        FILE *fp = fopen("applicants.dat", "rb");
        if (!fp) {
            perror("Не удалось открыть файл для чтения");
            return EXIT_FAILURE;
        }

        Applicant applicants[20];
        size_t read = fread(applicants, sizeof(Applicant), 20, fp);
        if (read != 20) {
            perror("Ошибка при чтении данных из файла");
            fclose(fp);
            return EXIT_FAILURE;
        }

        fclose(fp);
        print_table(applicants, 20);
    }
    else if (strcmp(argv[1], KEY_PARAMETER) == 0) {
        
        
        FILE *fp = fopen("applicants.dat", "rb");
        if (!fp) {
            perror("Не удалось открыть файл для чтения");
            return EXIT_FAILURE;
        }

        Applicant applicants[20];
        size_t read = fread(applicants, sizeof(Applicant), 20, fp);
        if (read != 20) {
            perror("Ошибка при чтении данных из файла");
            fclose(fp);
            return EXIT_FAILURE;
        }

        fclose(fp);

        
        Applicant filtered[20];
        int count = 0;
        for (int i = 0; i < 20; i++) {
            if (applicants[i].gender == 'F' && all_grades_unique(applicants[i].grades)) {
                filtered[count++] = applicants[i];
            }
        }

        
        if (count == 0) {
            printf("Нет абитуриенток, удовлетворяющих критерию.\n");
        }
        else {
            printf("Абитуриентки с разными оценками по всем предметам:\n");
            print_table(filtered, count);
        }
    }
    else {
        fprintf(stderr, "Неизвестный ключ: %s\n", argv[1]);
        fprintf(stderr, "Использование: %s -f | -p\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
