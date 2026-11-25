
#include <stdio.h>

#define MAX 100

struct student
{
    int id;
    char name[50];
    float fees;
    int paid;
    int course;
    int result;
};

struct student s[MAX];
int count = 0;

// Load data from file
void loadData()
{
    FILE *fp;

    fp = fopen("student.txt", "r");

    if (fp == NULL)
        return;

    while (count < MAX)
    {
        if (fscanf(fp, "%d|", &s[count].id) != 1)
            break;

        if (fscanf(fp, "%s|", s[count].name) != 1)
            break;

        if (fscanf(fp, "%f|", &s[count].fees) != 1)
            break;

        if (fscanf(fp, "%d|", &s[count].paid) != 1)
            break;

        if (fscanf(fp, "%d|", &s[count].course) != 1)
            break;

        if (fscanf(fp, "%d", &s[count].result) != 1)
            break;

        count++;
    }

    fclose(fp);
}

// Save data into file
void saveData()
{
    FILE *fp;
    int i;

    fp = fopen("student.txt", "w");

    if (fp == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        fprintf(fp, "%d|", s[i].id);

        fprintf(fp, "%s|", s[i].name);

        fprintf(fp, "%f|", s[i].fees);

        fprintf(fp, "%d|", s[i].paid);

        fprintf(fp, "%d|", s[i].course);

        fprintf(fp, "%d\n", s[i].result);
    }

    fclose(fp);
}

// Find student
int findStudent(int id)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (s[i].id == id)
            return i;
    }

    return -1;
}

int main()
{
    char userid[50], password[50];
    int choice, id, pos, i;

    loadData();

    // Login system
    printf("Enter User ID: ");
    scanf("%s", userid);

    printf("Enter Your Password: ");
    scanf("%s", password);

    // Check User ID
    for (i = 0; userid[i] != '\0'; i++)
    {
        if (!((userid[i] >= 'A' && userid[i] <= 'Z') ||
              (userid[i] >= 'a' && userid[i] <= 'z') ||
              (userid[i] >= '0' && userid[i] <= '9')))
        {
            printf("Invalid User ID!\n");
            return 0;
        }
    }

    // Check Password
    for (i = 0; password[i] != '\0'; i++)
    {
        if (password[i] < '0' || password[i] > '9')
        {
            printf("Invalid Password!\n");
            return 0;
        }
    }

    printf("\nLogin Successful!\n");

    do
    {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Update Fee Payment\n");
        printf("3. Allocate Course\n");
        printf("4. Update Result\n");
        printf("5. Display Students\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            // Add student
            case 1:

                if (count >= MAX)
                {
                    printf("Student limit reached!\n");
                    break;
                }

                printf("Enter Student ID: ");
                scanf("%d", &id);

                if (findStudent(id) != -1)
                {
                    printf("Student ID already exists!\n");
                    break;
                }

                s[count].id = id;

                printf("Enter Student Name: ");
                scanf("%s", s[count].name);

                printf("Enter Fees: ");
                scanf("%f", &s[count].fees);

                printf("Is the fee paid? (1=Yes, 0=No): ");
                scanf("%d", &s[count].paid);

                if (s[count].paid != 1)
                    s[count].paid = 0;

                s[count].course = 0;
                s[count].result = -1;

                count++;

                if (s[count - 1].paid == 1)
                    printf("Fee paid successfully!\n");
                else
                    printf("Fee should be paid!\n");

                saveData();

                printf("Student record saved!\n");

                break;

            // Update fee payment
            case 2:

                printf("Enter Student ID: ");
                scanf("%d", &id);

                pos = findStudent(id);

                if (pos == -1)
                {
                    printf("Student not found!\n");
                    break;
                }

                s[pos].paid = 1;

                printf("Fee payment updated successfully!\n");

                saveData();

                break;

            // Allocate course
            case 3:

                printf("Enter Student ID: ");
                scanf("%d", &id);

                pos = findStudent(id);

                if (pos == -1)
                {
                    printf("Student not found!\n");
                    break;
                }

                if (s[pos].paid != 1)
                {
                    printf("Please pay the fees first!\n");
                    break;
                }

                printf("\nSelect Course:\n");
                printf("1. DS\n");
                printf("2. AI\n");
                printf("3. ML\n");
                printf("4. Web\n");

                printf("Enter your choice: ");
                scanf("%d", &s[pos].course);

                if (s[pos].course >= 1 &&
                    s[pos].course <= 4)
                {
                    printf("Course allocated successfully!\n");
                    s[pos].result = -1;
                    saveData();
                }
                else
                {
                    printf("Course not available!\n");
                    s[pos].course = 0;
                }

                break;

            // Update result
            case 4:

                printf("Enter Student ID: ");
                scanf("%d", &id);

                pos = findStudent(id);

                if (pos == -1)
                {
                    printf("Student not found!\n");
                    break;
                }

                if (s[pos].course == 0)
                {
                    printf("Course not allocated!\n");
                    break;
                }

                printf("\nEnter Student Marks: ");
                scanf("%d", &s[pos].result);

                if (s[pos].result >= 90 &&
                    s[pos].result <= 100)
                {
                    printf("Result: Excellent\n");
                }
                else if (s[pos].result >= 60 &&
                         s[pos].result < 90)
                {
                    printf("Result: Good\n");
                }
                else if (s[pos].result >= 0 &&
                         s[pos].result < 60)
                {
                    printf("Result: Fail\n");
                }
                else
                {
                    printf("Invalid Marks!\n");
                    s[pos].result = -1;
                    break;
                }

                printf("Result updated successfully!\n");

                saveData();

                break;

            // Display students
            case 5:

                if (count == 0)
                {
                    printf("No student records found!\n");
                    break;
                }

                printf("\n===== STUDENT RECORDS =====\n");

                for (i = 0; i < count; i++)
                {
                    printf("\nStudent ID: %d\n", s[i].id);
                    printf("Name: %s\n", s[i].name);
                    printf("Fees: %f\n", s[i].fees);

                    if (s[i].paid == 1)
                        printf("Fee Status: Paid\n");
                    else
                        printf("Fee Status: Unpaid\n");

                    printf("Course: ");

                    if (s[i].course == 1)
                        printf("DS\n");
                    else if (s[i].course == 2)
                        printf("AI\n");
                    else if (s[i].course == 3)
                        printf("ML\n");
                    else if (s[i].course == 4)
                        printf("Web\n");
                    else
                        printf("Not Allocated\n");

                    printf("Result: ");

                    if (s[i].result == -1)
                        printf("Pending\n");
                    else if (s[i].result >= 90)
                        printf("Excellent\n");
                    else if (s[i].result >= 60)
                        printf("Good\n");
                    else
                        printf("Fail\n");

                    printf("-------------------------\n");
                }

                break;

            // Exit
            case 6:

                saveData();

                printf("Data saved successfully!\n");
                printf("Thank you!\n");

                break;

            default:

                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}

