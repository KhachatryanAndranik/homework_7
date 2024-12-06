#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[50];
    char surname[50];
    int id;
    float grade;
} Student;


void addStudent(Student** students, int* count);
void removeStudent(Student** students, int* count, int id);
void searchStudent(Student* students, int count, int id);
void displayStudents(Student* students, int count);
float calculateAverageGrade(Student* students, int count);
void saveToFile(Student* students, int count);
void readFromFile(Student** students, int* count);

int main() {
    Student* students = NULL; 
    int count = 0; 
    int choice, id;

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Search Student\n");
        printf("4. Display All Students\n");
        printf("5. Display Average Grade\n");
        printf("6. Save to File\n");
        printf("7. Read from File\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addStudent(&students, &count);
            break;
        case 2:
            printf("Enter ID to remove: ");
            scanf("%d", &id);
            removeStudent(&students, &count, id);
            break;
        case 3:
            printf("Enter ID to search: ");
            scanf("%d", &id);
            searchStudent(students, count, id);
            break;
        case 4:
            displayStudents(students, count);
            break;
        case 5:
            printf("Average grade: %.2f\n", calculateAverageGrade(students, count));
            break;
        case 6:
            saveToFile(students, count);
            break;
        case 7:
            readFromFile(&students, &count);
            break;
        case 8:
            free(students);
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}


void addStudent(Student** students, int* count) {
    *students = realloc(*students, (*count + 1) * sizeof(Student));
    if (*students == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", (*students)[*count].name);
    printf("Enter surname: ");
    scanf("%s", (*students)[*count].surname);
    printf("Enter ID: ");
    scanf("%d", &(*students)[*count].id);
    printf("Enter grade: ");
    scanf("%f", &(*students)[*count].grade);
    (*count)++;
}


void removeStudent(Student** students, int* count, int id) {
    for (int i = 0; i < *count; i++) {
        if ((*students)[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                (*students)[j] = (*students)[j + 1];
            }
            *students = realloc(*students, (*count - 1) * sizeof(Student));
            (*count)--;
            printf("Student with ID %d removed.\n", id);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}


void searchStudent(Student* students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Name: %s, Surname: %s, ID: %d, Grade: %.2f\n",
                students[i].name, students[i].surname, students[i].id, students[i].grade);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}


void displayStudents(Student* students, int count) {
    if (count == 0) {
        printf("No students available.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Surname: %s, ID: %d, Grade: %.2f\n",
            students[i].name, students[i].surname, students[i].id, students[i].grade);
    }
}


float calculateAverageGrade(Student* students, int count) {
    if (count == 0) return 0.0;

    float sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += students[i].grade;
    }
    return sum / count;
}


void saveToFile(Student* students, int count) {
    FILE* file = fopen("group_details.csv", "w");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%d,%.2f\n", students[i].name, students[i].surname, students[i].id, students[i].grade);
    }
    fclose(file);
    printf("Student details saved to 'group_details.csv'.\n");
}


void readFromFile(Student** students, int* count) {
    FILE* file = fopen("group_details.csv", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    *students = NULL; 
    *count = 0;

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        *students = realloc(*students, (*count + 1) * sizeof(Student));
        if (*students == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }
        sscanf(line, "%[^,],%[^,],%d,%f",
            (*students)[*count].name,
            (*students)[*count].surname,
            &(*students)[*count].id,
            &(*students)[*count].grade);
        (*count)++;
    }
    fclose(file);
    printf("Student details loaded from 'group_details.csv'.\n");
}
