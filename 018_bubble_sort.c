/*
 * Exercise 18: http://c.learncodethehardway.org/
 *
 * Use pointers to functions to implement Bubble sort with custom comparison
 * callbacks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(int *arr, int count, const char *caption)
{
  printf("%s:\n", caption);

  int j = 0;
  for (j = 0; j < count; j++) printf("%d ", arr[j]);
  printf("\n");
}

typedef int (*compare_cb)(int a, int b);

int *bubble_sort(int *numbers, int count, compare_cb compare)
{
  int tmp = 0;
  int i = 0;
  int j = 0;

  int *result = malloc(count * sizeof(int));

  if (!result) { printf("Memory error"); exit(1); }

  memcpy(result, numbers, count * sizeof(int));

  for (i = 0; i < count - 1; i++) {
    for (j = 0; j < count - i - 1; j++) {
      if (compare(result[j], result[j+1]) > 0) {
        tmp = result[j+1];
        result[j+1] = result[j];
        result[j]   = tmp;
      }
    }
  }

  return result;
}

int compare_asc(int a, int b) { return a > b; }

int compare_desc(int a, int b) { return a < b; }

int main(int argc, char *argv[])
{
  printf("We are a bubble sort. We sort.\n");
  int array_size = 7;

  int test[] = { 5, 1, 4, 7, 6, 2, 3 };
  int *arr = malloc(array_size * sizeof(int));
  memcpy(arr, test, array_size * sizeof(int));

  print_array(arr, array_size, "\nOriginal array");

  int *asc  = bubble_sort(arr, array_size, compare_asc);
  int *desc = bubble_sort(arr, array_size, compare_desc);

  print_array(asc, array_size, "\nAscending");
  print_array(desc, array_size, "\nDescending");

  free(arr);
  free(asc);
  free(desc);

  return 0;
}
