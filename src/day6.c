#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

const int GRID_X_MAX = 1000;
const int GRID_Y_MAX = 1000;

const int PICTURE_FRAME_DIM = 500;

const int TOTAL_SECONDS = 100;

int pt_one() {

  FILE *infile;

  char line_buffer[256];

  infile = fopen("../inputs/p6.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[2];
  const char delimiters[] = ",";
  char *token;

  // positions array
  GrowableArray positions;
  init_growable_array(&positions);
  // speed array
  GrowableArray speeds;
  init_growable_array(&speeds);
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
    // integer: x bits 0-7, y 8-15
    //
    // cast data to uint, because negatives will contaminate the whole 32-bit
    // space
    int32_t packed = ((uint16_t)data[1] << 16) | (uint16_t)data[0];
    push(&speeds, packed);
    // printf("(%d, %d)\n", data[0], data[1]);
    uint32_t position_packed = (0 << 16) | (0);
    push(&positions, position_packed);
  }
  // run for 100 seconds
  for (int i = 1; i <= TOTAL_SECONDS; i++) {

    // printf("Second %d: \n", i);
    // for each bird
    for (int bird_indx = 0; bird_indx < positions.count; bird_indx++) {
      // get its current position
      uint32_t position = positions.array[bird_indx];
      int pos_x = (position >> 0) & 0xFFFF;
      int pos_y = (position >> 16) & 0xFFFF;

      // get its speeds

      int32_t speed = speeds.array[bird_indx];
      int speed_x = (int16_t)((speed >> 0) & 0xFFFF);
      int speed_y = (int16_t)((speed >> 16) & 0xFFFF);

      int new_x = pos_x + speed_x;
      int new_y = pos_y + speed_y;
      // deal with buffer overflows
      //

      new_x = ((pos_x + speed_x) % GRID_X_MAX + GRID_X_MAX) % GRID_X_MAX;
      new_y = ((pos_y + speed_y) % GRID_Y_MAX + GRID_Y_MAX) % GRID_Y_MAX;

      // update position
      uint32_t new_packed_pos = (new_y << 16) | new_x;
      positions.array[bird_indx] = new_packed_pos;

      // printf("Bird %d at (%d, %d)\n", bird_indx, new_x, new_y);
    }
  }
  // take picture (get all of the birds in the frame) -> center of frame is
  // 500x500
  int left_x_bound = GRID_X_MAX - 500 - (PICTURE_FRAME_DIM / 2);
  int right_x_bound = GRID_X_MAX - 500 + (PICTURE_FRAME_DIM / 2) - 1;
  int lower_y_bound = GRID_Y_MAX - 500 - (PICTURE_FRAME_DIM / 2);
  int upper_y_bound = GRID_Y_MAX - 500 + (PICTURE_FRAME_DIM / 2) - 1;

  int sum = 0;
  for (int bird_indx = 0; bird_indx < positions.count; bird_indx++) {
    uint32_t position = positions.array[bird_indx];
    int pos_x = (position >> 0) & 0xFFFF;
    int pos_y = (position >> 16) & 0xFFFF;

    // printf("bird %d at (%d, %d)", bird_indx + 1, pos_x, pos_y);
    if (pos_x <= right_x_bound && pos_x >= left_x_bound &&
        pos_y >= lower_y_bound && pos_y <= upper_y_bound) {
      sum++;
    }
  }

  return sum;
}

int pt_two() {

  FILE *infile;

  char line_buffer[256];

  infile = fopen("../inputs/p6.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[2];
  const char delimiters[] = ",";
  char *token;

  // positions array
  GrowableArray positions;
  init_growable_array(&positions);
  // speed array
  GrowableArray speeds;
  init_growable_array(&speeds);

  int sum = 0;
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
    // since 10 - 99 requires only 7 bits, we can store our position in a
    // 32-bit integer: x bits 0-7, y 8-15
    //
    // cast data to uint, because negatives will contaminate the whole 32-bit
    // space
    int32_t packed = ((uint16_t)data[1] << 16) | (uint16_t)data[0];
    push(&speeds, packed);
    //  printf("(%d, %d)\n", data[0], data[1]);
    uint32_t position_packed = (0 << 16) | (0);
    push(&positions, position_packed);
  }

  // take a thousand pictures

  const long long SECONDS_PER_HOUR = 3600;
  const int NUM_PICTURES = 1000;

  int total_sum = 0;

  // For each picture
  for (int pic = 1; pic <= NUM_PICTURES; pic++) {
    long long t = (long long)pic * SECONDS_PER_HOUR;
    int count = 0;

    // Calculate position for each bird
    for (int bird_indx = 0; bird_indx < speeds.count; bird_indx++) {
      int32_t speed = speeds.array[bird_indx];
      int speed_x = (int16_t)((speed >> 0) & 0xFFFF);
      int speed_y = (int16_t)((speed >> 16) & 0xFFFF);

      // Calculate position directly
      long long pos_x = ((long long)speed_x * t) % GRID_X_MAX;
      long long pos_y = ((long long)speed_y * t) % GRID_Y_MAX;

      // Handle negative modulo
      if (pos_x < 0)
        pos_x += GRID_X_MAX;
      if (pos_y < 0)
        pos_y += GRID_Y_MAX;

      // Check if in frame [250, 749]
      if (pos_x >= 250 && pos_x <= 749 && pos_y >= 250 && pos_y <= 749) {
        count++;
      }
    }

    total_sum += count;
  }

  return total_sum;
}
int pt_three() {

  FILE *infile;

  char line_buffer[256];

  infile = fopen("../inputs/p6.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int data[2];
  const char delimiters[] = ",";
  char *token;

  // positions array
  GrowableArray positions;
  init_growable_array(&positions);
  // speed array
  GrowableArray speeds;
  init_growable_array(&speeds);

  int sum = 0;
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
    // since 10 - 99 requires only 7 bits, we can store our position in a
    // 32-bit integer: x bits 0-7, y 8-15
    //
    // cast data to uint, because negatives will contaminate the whole 32-bit
    // space
    int32_t packed = ((uint16_t)data[1] << 16) | (uint16_t)data[0];
    push(&speeds, packed);
    //  printf("(%d, %d)\n", data[0], data[1]);
    uint32_t position_packed = (0 << 16) | (0);
    push(&positions, position_packed);
  }

  const long long SECONDS_PER_YEAR = 31556926;
  const int NUM_PICTURES = 1000;

  int total_sum = 0;

  // For each picture
  for (int pic = 1; pic <= NUM_PICTURES; pic++) {
    long long t = (long long)pic * SECONDS_PER_YEAR;
    int count = 0;

    // Calculate position for each bird
    for (int bird_indx = 0; bird_indx < speeds.count; bird_indx++) {
      int32_t speed = speeds.array[bird_indx];
      int speed_x = (int16_t)((speed >> 0) & 0xFFFF);
      int speed_y = (int16_t)((speed >> 16) & 0xFFFF);

      // Calculate position directly
      long long pos_x = ((long long)speed_x * t) % GRID_X_MAX;
      long long pos_y = ((long long)speed_y * t) % GRID_Y_MAX;

      // Handle negative modulo
      if (pos_x < 0)
        pos_x += GRID_X_MAX;
      if (pos_y < 0)
        pos_y += GRID_Y_MAX;

      // Check if in frame [250, 749]
      if (pos_x >= 250 && pos_x <= 749 && pos_y >= 250 && pos_y <= 749) {
        count++;
      }
    }

    total_sum += count;
  }

  return total_sum;
}

int main() {
  printf("Pt 1: total price is: %d\n", pt_one());
  printf("Pt 2: total price is: %d\n", pt_two());
  printf("Pt 3: total price is: %d\n", pt_three());
  return EXIT_SUCCESS;
}
