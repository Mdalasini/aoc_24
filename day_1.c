// Get line by line
// Split line by whitespace
// Create R and L array
// Sort both arrays.
// Get sorted_R[0...n] - sorted_L[0...n]
// Add the difference

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 0
#define FALSE 1

void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void printArray(int arr[], int len);
int absDifference(int a, int b);
int getLines(char * filepath);
int itemCount(int arr[], int len, int item);

int main()
{
	const unsigned MAX_LENGTH = 256;

	char * filepath = "inputs/day_1.txt";
	FILE * fp = fopen(filepath, "r");
	if (fp == NULL)
	{
		printf("Error: Unable to open file: %s\n", filepath);
		return 1;
	}

	char buffer[MAX_LENGTH];
	int lines_counted = getLines(filepath);

	// Arrays for both L and R
	int L[lines_counted], R[lines_counted];

	// Add to R or L
	int add_to_R = FALSE;
	int current_index = 0;

	// Read line by line
	while(fgets(buffer, MAX_LENGTH, fp))
	{
		// Split by white space
		char * token = strtok(buffer, " ");
		while (token != NULL)
		{
			if (add_to_R == FALSE)
			{
				L[current_index] = atoi(token);
				add_to_R = TRUE;
			} else 
			{
				R[current_index] = atoi(token);
				add_to_R = FALSE;
			}
			
			token = strtok(NULL, " ");
		}
		current_index++;
	}

	// Sort arrays
	mergeSort(R, 0, lines_counted - 1);
	mergeSort(L, 0, lines_counted - 1);

	int sim_score = 0;

	for (int i = 0; i < lines_counted; i++)
	{
		int count = itemCount(R, lines_counted, L[i]);
		sim_score += L[i] * count;
	}
		
	printf("simmilarity score: %d\n", sim_score);

	fclose(fp);

	return 0;
}

int getLines(char * filepath)
{
	const unsigned MAX_LENGTH = 256;
	FILE * fp = fopen(filepath, "r");
	if (fp == NULL)
	{
		printf("Error: Unable to open file: %s\n", filepath);
		return 1;
	}

	char buffer[MAX_LENGTH];
	int lines_counted = 0;

	// Read # of lines
	while(fgets(buffer, MAX_LENGTH, fp)) lines_counted++;

	fclose(fp);
	return lines_counted;
}

int absDifference(int a, int b)
{
	if (a > b) return a - b;
	else return b - a;
}

void printArray(int arr[], int len)
{
	for (int i = 0; i < len; i++) printf("%d\n", arr[i]);
}

int itemCount(int arr[], int len, int item)
{
	int count = 0;
	for (int i = 0; i < len; i++)
		if (arr[i] == item) count++;
	return count;
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays L[] and R[]
	for (i = 0; i < n1; i++) L[i] = arr[l + i];
	for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]
	i = 0;
	j = 0;
	k = l;
	while(i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		} else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[]
	// If any
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[]
	// If any
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}

