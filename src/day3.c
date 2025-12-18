#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

int pt_one() {
  FILE *infile;

  char line_buffer[256];

  infile = fopen("../inputs/p3.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[3];
  const char delimiters[] = ",";
  char *token;

  GrowableArray colors;
  init_growable_array(&colors);

  GrowableArray counts;
  init_growable_array(&counts);

  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    int index = 0;

    token = strtok(line_buffer, delimiters);

    while (token != NULL) {
      if (index < 3) {
        data[index] = atoi(token);
        index++;
      }

      token = strtok(NULL, delimiters);
    }

    // since 10 - 99 requires only 7 bits, we can store our color in a 32-bit
    // integer: Num #1 bits 0-7, #2 8-15, #3 16-23
    uint32_t packed = (data[2] << 16) | (data[1] << 8) | data[0];
    int found_index = find_index(&colors, packed);
    if (found_index == -1) {
      push(&colors, packed);
      push(&counts, 1);
    } else {
      counts.array[found_index] += 1;
    }
  }

  int greatest_idx = find_index_of_greatest_value(&counts);

  fclose(infile);

  return colors.array[greatest_idx];
}
int pt_two() {
  FILE *infile;

  char line_buffer[256];

  infile = fopen("../inputs/p3.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[3];
  const char delimiters[] = ",";
  char *token;

  GrowableArray colors;
  init_growable_array(&colors);

  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    int index = 0;

    token = strtok(line_buffer, delimiters);

    while (token != NULL) {
      if (index < 3) {
        data[index] = atoi(token);
        index++;
      }

      token = strtok(NULL, delimiters);
    }

    // Red = 0
    // Green = 1
    // Blue = 2
    // Special = 3
    if ((data[0] == data[1] == data[2]) || (data[0] == data[1]) ||
        (data[1] == data[2]) || (data[0] == data[2])) {
      // printf("Special: %d,%d,%d\n", data[0], data[1], data[2]);
      push(&colors, 3);

    } else if (data[0] > data[1] && data[0] > data[2]) {
      // printf("Red: %d,%d,%d\n", data[0], data[1], data[2]);
      push(&colors, 0);
    } else if (data[1] > data[0] && data[1] > data[2]) {
      // printf("Green: %d,%d,%d\n", data[0], data[1], data[2]);
      push(&colors, 1);
    } else if (data[2] > data[0] && data[2] > data[1]) {
      // printf("Blue: %d,%d,%d\n", data[0], data[1], data[2]);
      push(&colors, 2);
    }
  }

  int sum = 0;
  for (int i = 0; i <= colors.count; i++) {
    if (colors.array[i] == 1) {
      sum++;
    }
  }

  fclose(infile);
  return sum;
}
int pt_three() {
  FILE *infile;

  char line_buffer[256];

  infile = fopen("../inputs/p3.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[3];
  const char delimiters[] = ",";
  char *token;

  GrowableArray prices;
  init_growable_array(&prices);

  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    int index = 0;

    token = strtok(line_buffer, delimiters);

    while (token != NULL) {
      if (index < 3) {
        data[index] = atoi(token);
        index++;
      }

      token = strtok(NULL, delimiters);
    }

    // Red = 5
    // Green = 2
    // Blue = 4
    // Special = 10
    if ((data[0] == data[1] == data[2]) || (data[0] == data[1]) ||
        (data[1] == data[2]) || (data[0] == data[2])) {
      // printf("Special: %d,%d,%d\n", data[0], data[1], data[2]);
      push(&prices, 10);

    } else if (data[0] > data[1] && data[0] > data[2]) {
      // printf("Red: %d,%d,%d\n", data[0], data[1], data[2]);
      push(&prices, 5);
    } else if (data[1] > data[0] && data[1] > data[2]) {
      // printf("Green: %d,%d,%d\n", data[0], data[1], data[2]);
      push(&prices, 2);
    } else if (data[2] > data[0] && data[2] > data[1]) {
      // printf("Blue: %d,%d,%d\n", data[0], data[1], data[2]);
      push(&prices, 4);
    }
  }

  int sum = 0;
  for (int i = 0; i <= prices.count; i++) {
    sum += prices.array[i];
  }

  fclose(infile);
  return sum;
}
int main() {

  uint32_t num_unpack = pt_one();
  int num1 = (num_unpack >> 0) & 0xFF;
  int num2 = (num_unpack >> 8) & 0xFF;
  int num3 = (num_unpack >> 16) & 0xFF;
  printf("Pt 1: Most occuring color is: %d,%d,%d\n", num1, num2, num3);
  printf("Pt 2: Number of Greens is: %d\n", pt_two());
  printf("Pt 3: total price is: %d\n", pt_three());
  return EXIT_SUCCESS;
}