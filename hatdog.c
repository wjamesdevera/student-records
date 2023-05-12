#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 7

typedef struct {
    int roll_number;
    char name[50];
    char sex[5];
    float prelim_grade;
    float midterm_grade;
    float final_grade;
    float average_grade;
} student;

student students[MAX_STUDENTS];
int student_count = 0;

void add_student() {
    if (student_count == MAX_STUDENTS) {
        printf("Cannot add more students. Maximum number of students reached.\n");
        return;
    }

    student s;
    printf("Enter roll number: ");
    scanf("%d", &s.roll_number);
    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter sex (M/F): ");
    scanf(" %s", &s.sex);
    printf("Enter prelim grade: ");
    scanf("%f", &s.prelim_grade);
    printf("Enter midterm grade: ");
    scanf("%f", &s.midterm_grade);
    printf("Enter final grade: ");
    scanf("%f", &s.final_grade);
    s.average_grade = (s.prelim_grade + s.midterm_grade + s.final_grade) / 3.0f;

    students[student_count++] = s;
}

void display_all_students() {
    for (int i = 0; i < student_count; i++) {
        student s = students[i];
        printf("Roll number: %d\n", s.roll_number);
        printf("Name: %s\n", s.name);
        printf("Sex: %s\n", s.sex);
        printf("Prelim grade: %.2f\n", s.prelim_grade);
        printf("Midterm grade: %.2f\n", s.midterm_grade);
        printf("Final grade: %.2f\n", s.final_grade);
        printf("Average grade: %.2f\n", s.average_grade);
        printf("\n");
    }
}

void display_average_grade() {
    int roll_number;
    printf("Enter roll number of student to display average grade: ");
    scanf("%d", &roll_number);

    for (int i = 0; i < student_count; i++) {
        student s = students[i];
        if (s.roll_number == roll_number) {
            printf("Average grade of student with roll number %d is %.2f\n", roll_number, s.average_grade);
            return;
        }
    }

    printf("Student with roll number %d not found.\n", roll_number);
}

void display_highest_and_lowest() {
    if (student_count == 0) {
        printf("No students to display.\n");
        return;
    }

    student highest = students[0];
    student lowest = students[0];

    for (int i = 1; i < student_count; i++) {
        student s = students[i];
        if (s.average_grade > highest.average_grade) {
            highest = s;
        }
        if (s.average_grade < lowest.average_grade) {
            lowest = s;
        }
    }

    printf("Student with highest average grade:\n");
    printf("Roll number: %d\n", highest.roll_number);
    printf("Name: %s\n", highest.name);
    printf("Average grade: %.2f\n", highest.average_grade);

    printf("\n");

    printf("Student with lowest average grade:\n");
    printf("Roll number: %d\n", lowest.roll_number);
    printf("Name: %s\n", lowest.name);
    printf("Average grade: %.2f\n", lowest.average_grade);
}

void save_student_info_to_txt_file()
{
    char *filepath = "student_records.txt";
    FILE *file;

    file = fopen("student_records.txt", "w");
    
    if (file == NULL)
    {
        printf("ERROR: opening student_records.txt");
        return;
    }
    
    for (int i = 0; i < student_count; i++)
    {
        fprintf(file, "%d\n", students[i].roll_number);
        fprintf(file, "%s\n", students[i].name);
        fprintf(file, "%s\n", students[i].sex);
        fprintf(file, "%.2f\n", students[i].prelim_grade);
        fprintf(file, "%.2f\n", students[i].midterm_grade);
        fprintf(file, "%.2f\n", students[i].final_grade);
        fprintf(file, "%.2f\n", students[i].average_grade);
    }

    fclose(file);
}


#define BUFFER_SIZE 1024
void retrieve_student_records()
{
    FILE *file;

    file = fopen("student_records.txt", "r");
    
    if (file == NULL)
    {
        return;
    }

    char buffer[BUFFER_SIZE];

    int lineCount = 0;
    while(fgets(buffer, BUFFER_SIZE, file) != NULL)
    {
        int len = strlen(buffer);
        
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        
        int subGroup = lineCount % 7;
        switch (subGroup)
        {
            case 0:
                students[student_count].roll_number = atoi(buffer);
                break;
            case 1:
                strcpy(students[student_count].name, buffer);
                break;
            case 2:
                strcpy(students[student_count].sex, buffer);
                break;
            case 3:
                students[student_count].prelim_grade = atof(buffer);
                break;
            case 4:
                students[student_count].midterm_grade = atof(buffer);
                break;
            case 5:
                students[student_count].final_grade = atof(buffer);
                break;
            case 6:
                students[student_count].average_grade = atof(buffer);
                student_count++;
                break;
            default:
                break;
        }
        lineCount++;
    }
    fclose(file);
}

int main() {
    char choice;
    retrieve_student_records();
    do {
        printf("\nMenu:\n");
        printf("a) Add student records\n");
        printf("b) Display all student records\n");
        printf("c) Display average grade of a selected student\n");
        printf("d) Display the highest and lowest\n");
        printf("e) Exit Application\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                add_student();
                break;
            case 'b':
                display_all_students();
                break;
            case 'c':
                display_average_grade();
                break;
            case 'd':
                display_highest_and_lowest();
                break;
            case 'e':
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'e');
    save_student_info_to_txt_file();
    return 0;
}
