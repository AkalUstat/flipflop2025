#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_white_space(char *str) {
  int i = 0, j = 0;
  while (str[i]) {
    if (!isspace((unsigned char)str[i])) {
      str[j++] = str[i];
    }
    i++;
  }
  str[j] = '\0';
}

int pt_one() {
  FILE *infile;
  char line_buffer[256];

  infile = fopen("../inputs/p1.txt", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int sum = 0;
  const char *temp;
  char sub_ba[] = "ba";
  char sub_na[] = "na";
  char sub_ne[] = "ne";

  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    temp = line_buffer;

    while ((temp = strstr(temp, sub_ba)) != NULL) {
      sum++;
      // Move pointer forward to search for the next match
      temp += 2;
    }

    temp = line_buffer;

    while ((temp = strstr(temp, sub_na)) != NULL) {
      sum++;
      // Move pointer forward to search for the next match
      temp += 2;
    }
    temp = line_buffer;

    while ((temp = strstr(temp, sub_ne)) != NULL) {
      sum++;
      // Move pointer forward to search for the next match
      temp += 2;
    }
  }

  fclose(infile);

  return sum;
}

int pt_two() {
  FILE *infile;
  char line_buffer[256];

  infile = fopen("../inputs/p1.txt", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int sum = 0;
  const char *temp;
  size_t str_length;
  char sub_ba[] = "ba";
  char sub_na[] = "na";
  char sub_ne[] = "ne";

  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    trim_white_space(line_buffer);
    temp = line_buffer;
    int temp_sum = 0;

    while ((temp = strstr(temp, sub_ba)) != NULL) {
      temp_sum++;
      // Move pointer forward to search for the next match
      temp += 2;
    }

    temp = line_buffer;

    while ((temp = strstr(temp, sub_na)) != NULL) {
      temp_sum++;
      // Move pointer forward to search for the next match
      temp += 2;
    }
    temp = line_buffer;

    while ((temp = strstr(temp, sub_ne)) != NULL) {
      temp_sum++;
      // Move pointer forward to search for the next match
      temp += 2;
    }

    if (temp_sum % 2 != 0) {
      continue;
    }
    sum += temp_sum;
  }

  fclose(infile);

  return sum;
}

int pt_three() {
  FILE *infile;
  char line_buffer[256];

  infile = fopen("../inputs/p1.txt", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int sum = 0;
  const char *temp;
  size_t str_length;
  char sub_ba[] = "ba";
  char sub_na[] = "na";
  char sub_ne[] = "ne";

  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    trim_white_space(line_buffer);
    temp = line_buffer;
    int temp_sum = 0;
    // if this is not zero, this means it contains banena
    int banena_count = 0;

    while ((temp = strstr(temp, sub_ba)) != NULL) {
      temp_sum++;
      // Move pointer forward to search for the next match
      temp += 2;
    }

    temp = line_buffer;

    while ((temp = strstr(temp, sub_na)) != NULL) {
      temp_sum++;
      // Move pointer forward to search for the next match
      temp += 2;
    }
    temp = line_buffer;

    while ((temp = strstr(temp, sub_ne)) != NULL) {
      banena_count++;
      // Move pointer forward to search for the next match
      temp += 2;
    }

    if (banena_count > 0) {
      continue;
    }
    sum += temp_sum;
  }

  fclose(infile);

  return sum;
}

int main() {
  printf("Pt 1: Counts is: %d\n", pt_one());
  printf("Pt 2: Even Counts is: %d\n", pt_two());
  printf("Pt 3: Non Benana Counts is: %d\n", pt_three());
  return EXIT_SUCCESS;
}