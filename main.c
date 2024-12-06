#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define STDNAME_LEN 40
#define DATA_MAX 1000

typedef struct {
    int math;
    int reading;
    int writing;
    char stdname[STDNAME_LEN];
}	student_t;

int main(void)
{
    int			input;
    student_t	*student, *current, *end;
    char		name[STDNAME_LEN];

    student = (student_t *)malloc(sizeof(student_t) * DATA_MAX);
    if (student == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		return 1;
	}
    FILE *fp = fopen("studentscore.txt", "r");
    if (fp == NULL)
	{
		fprintf(stderr, "Error: Unable to open file.\n");
		free(student);
		return 1;
    }
    current = student;
    while (fscanf(fp, "%s %d %d %d",
				  current->stdname,
				  &current->math,
				  &current->reading,
				  &current->writing) == 4) {
		current++;
		if (current - student >= DATA_MAX) break;
    }
    end = current;
    fclose(fp);

    printf("===== Menu =====\n\t1. Score for Student\n\t2. Stats for Subject\n\nEnter your choice: ");
    scanf("%d", &input);
    if (input == 1)
	{
		printf("Enter Student Name: ");
		scanf("%s", name);

		int	found = 0;
		for (current = student; current < end; current++) {
		    if (strcmp(name, current->stdname) == 0) {
				printf("Math: %d\nReading: %d\nWriting: %d\n", current->math, current->reading, current->writing);
				found = 1;
				break;
		    }
		}
		if (!found)
		    printf("Student not found.\n");
	}
    else if (input == 2)
	{
		int min_math = INT32_MAX, max_math = INT32_MIN, sum_math = 0;
		int min_reading = INT32_MAX, max_reading = INT32_MIN, sum_reading = 0;
		int min_writing = INT32_MAX, max_writing = INT32_MIN, sum_writing = 0;
		size_t count = 0;

		for (current = student; current < end; current++)
		{
		    sum_math += current->math;
		    sum_reading += current->reading;
		    sum_writing += current->writing;

		    if (current->math < min_math) min_math = current->math;
		    if (current->math > max_math) max_math = current->math;
		    if (current->reading < min_reading) min_reading = current->reading;
		    if (current->reading > max_reading) max_reading = current->reading;
		    if (current->writing < min_writing) min_writing = current->writing;
		    if (current->writing > max_writing) max_writing = current->writing;
		    count++;
		}
		printf("--- Subject Math ---\n");
		printf("Max: %d\nMin: %d\nAverage: %.2f\n", max_math, min_math, (float)sum_math / count);
		printf("--- Subject Reading ---\n");
		printf("Max: %d\nMin: %d\nAverage: %.2f\n", max_reading, min_reading, (float)sum_reading / count);
		printf("--- Subject Writing ---\n");
		printf("Max: %d\nMin: %d\nAverage: %.2f\n", max_writing, min_writing, (float)sum_writing / count);
	}
	else
		printf("Invalid choice.\n");
	free(student);
	return 0;
}