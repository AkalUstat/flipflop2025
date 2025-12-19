#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
int pt_one() {

  FILE *infile;
  int charac;

  infile = fopen("../input/p5.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  char characters[114];
  int index = 0;

  while ((charac = fgetc(infile)) != EOF) {
    char processed = (char)charac;
    if (processed != '\n' && processed != '\r') {
      characters[index] = processed;
      index++;
    }
  }

  int input_length = index;

  printf("Input: ");
  for (int i = 0; i < input_length; i++) {
    printf("[%d:%c] ", i, characters[i]);
  }
  printf("\n");
  int current_position = 0;
  int direction = 1;
  int sum = 0;

  char visited[114];
  int visited_index = 0;

  while (true) {
    if (current_position >= input_length || current_position < 0) {
      break;
    }

    char target = characters[current_position];
    visited[visited_index++] = target;

   // printf("At pos %d ('%c'), searching %s for '%c'\n", current_position,
     //j      characters[current_position],
        //   direction == 1 ? "forward" : "backward", target);

    int search_pos = current_position + direction;
    int steps_inside = 1;

    // Search for matching character
    while (search_pos >= 0 && search_pos < input_length &&
           characters[search_pos] != target) {
      steps_inside++;
      search_pos += direction;
    }

    // found match or out of bounds?
    if (search_pos < 0 || search_pos >= input_length) {
      // No match found in this direction
      // try flipping directions, that's a good trick!
      direction = -direction;
      search_pos = current_position + direction;
      steps_inside = 1;

      while (search_pos >= 0 && search_pos < input_length &&
             characters[search_pos] != target) {
        steps_inside++;
        search_pos += direction;
      }

      // If still no match, something is wrong
      if (search_pos < 0 || search_pos >= input_length) {
        printf("No match found for '%c' at position %d\n", target,
               current_position);
        break;
      }
    }

    // printf("Moving into tunnel %c distance %d.\n", target, steps_inside);
    sum += steps_inside;

    current_position = search_pos + 1;

    // Check if we're done
    if (current_position >= input_length) {
      break;
    }

    direction = -direction;
  }

  for(int i = 0; i < input_length; i++) {
    char tunnel = characters[i];
    bool found = false;
    for(int j = 0 ; j <= visited_index; j++  ){
      if(tunnel == visited[j]) {
        found = true;
            break;
      }
    }
     
    if(!found) {
      // push it to the visited so that it isn't printed out again
        visited[++visited_index] = tunnel;
        printf("%c", tunnel);
    }

  }
  printf("\n");
  
  fclose(infile);
  return sum;
}
int pt_two() {
  int sum = 0;
  return sum;
}
int pt_three() {


  FILE *infile;
  int charac;

  infile = fopen("../input/p5.in", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  char characters[114];
  int index = 0;

  while ((charac = fgetc(infile)) != EOF) {
    char processed = (char)charac;
    if (processed != '\n' && processed != '\r') {
      characters[index] = processed;
      index++;
    }
  }

  int input_length = index;

  printf("Input: ");
  for (int i = 0; i < input_length; i++) {
    printf("[%d:%c] ", i, characters[i]);
  }
  printf("\n");
  int current_position = 0;
  int direction = 1;
  int sum = 0;

  char visited[114];
  int visited_index = 0;

  while (true) {
    if (current_position >= input_length || current_position < 0) {
      break;
    }

    char target = characters[current_position];
    visited[visited_index++] = target;

   // printf("At pos %d ('%c'), searching %s for '%c'\n", current_position,
     //j      characters[current_position],
        //   direction == 1 ? "forward" : "backward", target);

    int search_pos = current_position + direction;
    int steps_inside = 1;

    // Search for matching character
    while (search_pos >= 0 && search_pos < input_length &&
           characters[search_pos] != target) {
      steps_inside++;
      search_pos += direction;
    }

    // found match or out of bounds?
    if (search_pos < 0 || search_pos >= input_length) {
      // No match found in this direction
      // try flipping directions, that's a good trick!
      direction = -direction;
      search_pos = current_position + direction;
      steps_inside = 1;

      while (search_pos >= 0 && search_pos < input_length &&
             characters[search_pos] != target) {
        steps_inside++;
        search_pos += direction;
      }

      // If still no match, something is wrong
      if (search_pos < 0 || search_pos >= input_length) {
        printf("No match found for '%c' at position %d\n", target,
               current_position);
        break;
      }
    }

    // printf("Moving into tunnel %c distance %d.\n", target, steps_inside);
    if (target>= 'A' && target<= 'Z') { // if is uppercase (powered tunnels, so negative steps)
      sum -= steps_inside;
}else {    sum += steps_inside;}

    current_position = search_pos + 1;

    // Check if we're done
    if (current_position >= input_length) {
      break;
    }

    direction = -direction;
  }

  
  fclose(infile);
  return sum;
}
int main() {
  printf("Pt 1: total price is: %d\n", pt_one());
  printf("Pt 2: total price is: %d\n", pt_two());
  printf("Pt 3: total price is: %d\n", pt_three());
  return EXIT_SUCCESS;
}