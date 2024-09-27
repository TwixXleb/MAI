#ifndef DATABASE_H
#define DATABASE_H

#define MAX_NAME_LENGTH 50
#define NUM_SUBJECTS 5

typedef struct {
    int math;
    int physics;
    int chemistry;
    int biology;
    int literature;
} Grades;

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char gender; 
    Grades grades;
} Applicant;


#define KEY_PRINT_FILE "-f"
#define KEY_PARAMETER "-p"

#endif 
