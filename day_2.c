// Read every line (report) 
// Levels = number in report
// Check that the reports are sorted
// Check that the max abs difference between two neighbouring reports
// is at most 3
// If so assign "safe"
// else "Unsafe"
// return # of safe

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const char * filepath = "inputs/day_2.txt";

enum 
{
	true,
	false
} typedef boolean;

boolean isSorted(int arr[], int len);
boolean diffWithin(int arr[], int len, int max);
int absDiff(int a, int b);
int getLineCount(const char * filepath);
void subsetLessOne(int og[], int subset[], int og_len, int i);

int main()
{
	int safe_count = 0;
	FILE * fp = fopen(filepath, "r");
	int buffer_size = 256;
	char buffer[buffer_size];
	if (fp == NULL) 
	{
		printf("Error: unable to open file: `%s`\n", filepath);
		return 1;
	}

	int file_len = getLineCount(filepath);

	// Read line by line
	while(fgets(buffer, buffer_size, fp))
	{
		int * report = NULL;
		int * temp = NULL;
		size_t current_size, new_size;
		
		// Initial allocation
		current_size = 0;
		report = (int *)malloc(current_size * sizeof(int));
		if (report == NULL)
		{
			printf("Error: malloc failed.\n");
			return 1;
		}

		// Split by white space
		char * token = strtok(buffer, " ");
		while (token != NULL)
		{
			new_size = current_size + 1;
			temp = (int *)realloc(report, new_size * sizeof(int));
			if (temp == NULL)
			{
				printf("Error: realloc failed.\n");
				return 1;
			} else
			{
				report = temp;
				temp = NULL;
				current_size = new_size;
			}
			report[current_size-1] = atoi(token);
			token = strtok(NULL, " ");
		}
		boolean is_sorted = isSorted(report, current_size);
		boolean diff_within = diffWithin(report, current_size, 3);

		if (is_sorted == true && diff_within == true) safe_count++;
		else 
		{
			// Get every variation of the array
			// Check that at least one of them is safe
			int subset[current_size-1]; // hold variations of the og
			for (int i = 0; i < current_size; i++)
			{
				subsetLessOne(report, subset, current_size, i);
				is_sorted = isSorted(subset, current_size-1);
				diff_within = diffWithin(subset, current_size-1, 3);
				if (is_sorted == true && diff_within == true)
				{
					safe_count++;
					break;
				}
			}
		}
		free(report);
	}

	printf("safe_count: %d\n", safe_count);

	fclose(fp);

	return 0;
}

void subsetLessOne(int og[], int subset[], int og_len, int i)
{
	if (i >= og_len)
		printf("Error: Invalid index.\n");
	else
  {
		int current_index = 0;
		for (int j = 0; j < og_len; j++)
		{
			if (j != i) 
			{
				subset[current_index] = og[j];
				current_index++;
			}
		}
	}
}

int getLineCount(const char * filepath)
{
	int buffer_size = 256;
	char buffer[buffer_size];
	int lines_counted = 0;
	FILE * fp = fopen(filepath, "r");

	while(fgets(buffer, buffer_size, fp)) lines_counted++;
	fclose(fp);
	return lines_counted;
}

int absDiff(int a, int b)
{
	if (a > b) return a - b;
	return b - a;
}

boolean isSorted(int arr[], int len)
{
	if (len <= 1) return true;
	boolean plusPlus = false; // increment
	boolean minusMinus = false; // decrement
	boolean dampened = false;

	for (int i = 1; i < len; i++)
	{
		if (arr[i] > arr[i-1]) plusPlus = true;
		if (arr[i] < arr[i-1]) minusMinus = true;
		if (arr[i] == arr[i-1]) return false;
		if (plusPlus == true && minusMinus == true) return false;
	}
	return true;
}

boolean diffWithin(int arr[], int len, int max)
{
	int prev_num = arr[0];
	int abs_diff, i;
	for (i = 0; i < len; i++)
	{
		abs_diff = absDiff(arr[i], prev_num);
		prev_num = arr[i];
		if (abs_diff > max) return false;
	}
	return true;
}
