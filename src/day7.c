#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

long long count_paths(int R, int C) {
  int n = R + C - 2;
  int k = R - 1;
  if (k > n / 2)
    k = n - k; // C(n, k) = C(n, n-k)

  long long paths = 1;
  for (int i = 1; i <= k; i++) {
    paths = paths * (n - k + i) / i;
  }
  return paths;
}

long long combinations(int n, int k) {
  if (k < 0 || k > n)
    return 0;
  if (k > n / 2)
    k = n - k;
  long long res = 1;
  for (int i = 1; i <= k; i++) {
    res = res * (n - k + i) / i;
  }
  return res;
}

long long count_paths_3d(int R, int C, int H) {
  int n1 = R - 1;
  int n2 = C - 1;
  int n3 = H - 1;

  // Paths = C(n1+n2+n3, n1) * C(n2+n3, n2)
  return combinations(n1 + n2 + n3, n1) * combinations(n2 + n3, n2);
}

unsigned long long count_paths_nd(int D, int L) {
  int k = L - 1;
  unsigned long long total_paths = 1;
  int remaining_steps = D * k;

  for (int i = 0; i < D; i++) {
    total_paths *= combinations(remaining_steps, k);
    remaining_steps -= k;
  }
  return total_paths;
}

int pt_one() {
  FILE *infile;

  char line_buffer[256];

  infile = fopen("../input/p7.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[2];
  const char delimiters[] = " ";
  char *token;

  // row/col array
  GrowableArray sizes;
  init_growable_array(&sizes);
  // read input file and populate arrays
  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    int index = 0;

    token = strtok(line_buffer, delimiters);

    while (token != NULL) {
      if (index < 2) {
        data[index] = atoi(token);
        index++;
      }

      token = strtok(NULL, delimiters);
    }
    // since 10 - 99 requires only 7 bits, we can store our position in a 32-bit
    // integer: rows bits 0-7, columns 8-15
    //
    printf("Reading size: %dx%d\n", data[0], data[1]);
    uint16_t position_packed = (data[1] << 8) | (data[0]);
    push(&sizes, position_packed);
  }

  int sum_paths = 0;

  for (int i = 0; i < sizes.count; i++) {
    // extract values from the packed array
    uint16_t size = sizes.array[i];
    int size_rows = (size >> 0) & 0xFF;
    int size_columns = (size >> 8) & 0xFF;

    printf("For grid: %dx%d\n", size_rows, size_columns);

    sum_paths += count_paths(size_rows, size_columns);
  }
  return sum_paths;
}
int pt_two() {

  FILE *infile;

  char line_buffer[256];

  infile = fopen("../input/p7.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[2];
  const char delimiters[] = " ";
  char *token;

  // row/col array
  GrowableArray sizes;
  init_growable_array(&sizes);
  // read input file and populate arrays
  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    int index = 0;

    token = strtok(line_buffer, delimiters);

    while (token != NULL) {
      if (index < 2) {
        data[index] = atoi(token);
        index++;
      }

      token = strtok(NULL, delimiters);
    }
    // since 10 - 99 requires only 7 bits, we can store our position in a 32-bit
    // integer: rows bits 0-7, columns 8-15
    //
    printf("Reading size: %dx%d\n", data[0], data[1]);
    uint16_t position_packed = (data[1] << 8) | (data[0]);
    push(&sizes, position_packed);
  }

  int sum_paths = 0;

  for (int i = 0; i < sizes.count; i++) {
    // extract values from the packed array
    uint16_t size = sizes.array[i];
    int size_rows = (size >> 0) & 0xFF;
    int size_columns = (size >> 8) & 0xFF;

    printf("For grid: %dx%dx%d\n", size_rows, size_columns, size_rows);

    sum_paths += count_paths_3d(size_rows, size_columns, size_rows);
  }
  return sum_paths;
}
long long pt_three() {

  FILE *infile;

  char line_buffer[256];

  infile = fopen("../input/p7.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[2];
  const char delimiters[] = " ";
  char *token;

  // row/col array
  GrowableArray sizes;
  init_growable_array(&sizes);
  // read input file and populate arrays
  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    int index = 0;

    token = strtok(line_buffer, delimiters);

    while (token != NULL) {
      if (index < 2) {
        data[index] = atoi(token);
        index++;
      }

      token = strtok(NULL, delimiters);
    }
    // since 10 - 99 requires only 7 bits, we can store our position in a 32-bit
    // integer: rows bits 0-7, columns 8-15
    //
 //   printf("Reading size: %dx%d\n", data[0], data[1]);
    uint16_t position_packed = (data[1] << 8) | (data[0]);
    push(&sizes, position_packed);
  }

  long long sum_paths = 0;

  for (int i = 0; i < sizes.count; i++) {
    // extract values from the packed array
    uint16_t size = sizes.array[i];
    int dim = (size >> 0) & 0xFF;
    int dm_lens = (size >> 8) & 0xFF;

    // printf("For grid: %dx%dx%d\n", size_rows, size_columns, size_rows);

    sum_paths += count_paths_nd(dim, dm_lens);
  }
  return sum_paths;
}
int main() {
  printf("Pt 1: total number of shortest paths: %d\n", pt_one());
  printf("Pt 2: shortest paths in 3D: %d\n", pt_two());
  printf("Pt 3: shortest paths in nD: %llu\n", pt_three());
  return EXIT_SUCCESS;
}
