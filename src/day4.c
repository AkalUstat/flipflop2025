#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))

int pt_two() {
  FILE *infile;

  char line_buffer[256];

  infile = fopen("../inputs/p4.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[2];
  const char delimiters[] = ",";
  char *token;

  GrowableArray positions;
  init_growable_array(&positions);
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
    // since 10 - 99 requires only 7 bits, we can store our position in a 32-bit
    // integer: x bits 0-7, y 8-15
    uint16_t packed = (data[1] << 8) | data[0];
    push(&positions, packed);
  }

  int sum = 0;

  int curr_x = 0;
  int curr_y = 0;

  for (int i = 0; i < positions.count; i++) {
    uint16_t num_unpack = positions.array[i];
    int dest_x = (num_unpack >> 0) & 0xFF;
    int dest_y = (num_unpack >> 8) & 0xFF;

    int delta_x = dest_x - curr_x;
    int delta_y = dest_y - curr_y;

    int tentative_x = curr_x + delta_x;
    int tentative_y = curr_y + delta_y;

    if (tentative_x < 0) {
      tentative_x = 0;
    } else if (tentative_x > 100) {
      tentative_x = 100;
    }

    if (tentative_y < 0) {
      tentative_y = 0;
    } else if (tentative_y > 100) {
      tentative_y = 100;
    }

    printf("Current position (%d, %d) ", curr_x, curr_y);

    curr_x = tentative_x;
    curr_y = tentative_y;

    printf("to (%d, %d) ", curr_x, curr_y);

    // the diagonal is the chess board distance
    int chess_dist = MAX(abs(delta_x), abs(delta_y));
    sum += chess_dist;

    printf("With travel: %dx.\n", chess_dist);
  }

  return sum;
}
int pt_one() {

  FILE *infile;

  char line_buffer[256];

  infile = fopen("../inputs/p4.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[2];
  const char delimiters[] = ",";
  char *token;

  GrowableArray positions;
  init_growable_array(&positions);
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
    // since 10 - 99 requires only 7 bits, we can store our position in a 32-bit
    // integer: x bits 0-7, y 8-15
    uint16_t packed = (data[1] << 8) | data[0];
    push(&positions, packed);
  }

  int sum = 0;

  int curr_x = 0;
  int curr_y = 0;

  for (int i = 0; i < positions.count; i++) {
    uint16_t num_unpack = positions.array[i];
    int dest_x = (num_unpack >> 0) & 0xFF;
    int dest_y = (num_unpack >> 8) & 0xFF;

    int delta_x = dest_x - curr_x;
    int delta_y = dest_y - curr_y;

    int tentative_x = curr_x + delta_x;
    int tentative_y = curr_y + delta_y;

    if (tentative_x < 0) {
      tentative_x = 0;
    } else if (tentative_x > 100) {
      tentative_x = 100;
    }

    if (tentative_y < 0) {
      tentative_y = 0;
    } else if (tentative_y > 100) {
      tentative_y = 100;
    }

    printf("Current position (%d, %d) ", curr_x, curr_y);

    curr_x = tentative_x;
    curr_y = tentative_y;

    printf("to (%d, %d) ", curr_x, curr_y);

    sum += abs(delta_x) + abs(delta_y);
    printf("With travel: %dx, %dy.\n", abs(delta_x), abs(delta_y));
  }

  return sum;
}

// custom qsort comparator
int compare_ints_desc(const void *elem1, const void *elem2) {
  uint32_t packed_val_1 = *(const uint32_t *)elem1;
  uint32_t packed_val_2 = *(const uint32_t *)elem2;

  // manhattan dist
  int manhattan_one = (packed_val_1 >> 16) & 0xFF;
  int manhattan_two = (packed_val_2 >> 16) & 0xFF;

  // compare them
  if (manhattan_one > manhattan_two) {
    return 1;
  } else if (manhattan_two > manhattan_one) {
    return -1;
  }
  return 0;
}
int pt_three() {

  FILE *infile;

  char line_buffer[256];

  infile = fopen("../inputs/p4.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[3];
  const char delimiters[] = ",";
  char *token;

  GrowableArray positions;
  init_growable_array(&positions);
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
    // since 10 - 99 requires only 7 bits, we can store our position in a 32-bit
    // integer: x bits 0-7, y 8-15, manhattan dist from (0,0) 16-23
    int manhattan_dist = abs(data[1] - 0) + (abs(data[0] - 0));
    uint32_t packed = (manhattan_dist << 16) | (data[1] << 8) | data[0];
    push(&positions, packed);
  }

  // sort array
  qsort(positions.array, positions.count, sizeof(uint32_t), compare_ints_desc);

  int sum = 0;

  int curr_x = 0;
  int curr_y = 0;

  for (int i = 0; i < positions.count; i++) {
    uint16_t num_unpack = positions.array[i];
    int dest_x = (num_unpack >> 0) & 0xFF;
    int dest_y = (num_unpack >> 8) & 0xFF;

    int delta_x = dest_x - curr_x;
    int delta_y = dest_y - curr_y;

    int tentative_x = curr_x + delta_x;
    int tentative_y = curr_y + delta_y;

    if (tentative_x < 0) {
      tentative_x = 0;
    } else if (tentative_x > 100) {
      tentative_x = 100;
    }

    if (tentative_y < 0) {
      tentative_y = 0;
    } else if (tentative_y > 100) {
      tentative_y = 100;
    }

    printf("Current position (%d, %d) ", curr_x, curr_y);

    curr_x = tentative_x;
    curr_y = tentative_y;

    printf("to (%d, %d) ", curr_x, curr_y);

    // the diagonal is the chess board distance
    int chess_dist = MAX(abs(delta_x), abs(delta_y));
    sum += chess_dist;

    printf("With travel: %dx.\n", chess_dist);
  }

  return sum;
}

int main() {
  printf("Pt 1: total price is: %d\n", pt_one());
  printf("Pt 2: total price is: %d\n", pt_two());
  printf("Pt 3: total price is: %d\n", pt_three());
  return EXIT_SUCCESS;
}