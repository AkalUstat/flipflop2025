#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int pt_one() {
  FILE *infile;
  int charac;

  infile = fopen("../inputs/p2.txt", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int current_height = 0;
  int greatest_height = 0;

  char up = '^';
  char down = 'v';

  while ((charac = fgetc(infile)) != EOF) {
    char processed = (char)charac;

    if (processed == up) {
      current_height++;
    } else if (processed == down) {
      current_height--;
    } else {
      printf("Unrecognized character: %c", processed);
    }

    if (current_height > greatest_height) {
      greatest_height = current_height;
    }
  }

  fclose(infile);

  return greatest_height;
}
int pt_two() {
  FILE *infile;
  int charac;

  infile = fopen("../inputs/p2.txt", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int current_height = 0;
  int greatest_height = 0;

  int continuity = 0;
  char last_char = '\0';

  char up = '^';
  char down = 'v';

  while ((charac = fgetc(infile)) != EOF) {
    char processed = (char)charac;

    if (processed == last_char) {
      continuity += 1;
    } else {
      continuity = 1;
    }

    if (processed == up) {
      current_height += continuity;
    } else if (processed == down) {
      current_height -= continuity;
    } else {
      printf("Unrecognized character: %c", processed);
    }

    if (current_height > greatest_height) {
      greatest_height = current_height;
    }

    last_char = processed;
  }

  fclose(infile);

  return greatest_height;
}

int fib(int n) {
  int last = 1;
  int prev = 0;
  int i;

  if (n == 0) {
    return 0;
  }

  for (i = 1; i < n; ++i) {
    int next = prev + last;
    prev = last;
    last = next;
  }

  return last;
}
int pt_three() {
  FILE *infile;
  int charac;

  infile = fopen("../inputs/p2.txt", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int current_height = 0;
  int greatest_height = 0;

  int continuity = 0;
  char last_char = '\0';

  char up = '^';
  char down = 'v';

  while ((charac = fgetc(infile)) != EOF) {
    char processed = (char)charac;

    if (processed == last_char) {
      continuity += 1;
    } else {
      if (last_char == up) {
        current_height += fib(continuity);
      } else if (last_char == down) {
        current_height -= fib(continuity);
      } else {
        printf("Unrecognized character: %c\n", processed);
      }

      if (current_height > greatest_height) {
        greatest_height = current_height;
      }

      continuity = 1;
    }

    last_char = processed;
  }

  // last check:
  if (continuity > 0) {
    if (last_char == up) {
      current_height += fib(continuity);
    } else if (last_char == down) {
      current_height -= fib(continuity);
    } else {
      printf("Unrecognized character: %c", last_char);
    }

    if (current_height > greatest_height) {
      greatest_height = current_height;
    }
  }

  fclose(infile);

  return greatest_height;
}

int main() {
  printf("Pt 1: Greatest Height is: %d\n", pt_one());
  printf("Pt 2: Greatest Cascading Height is: %d\n", pt_two());
  printf("Pt 3: Greatest Fibonnaci Height is: %d\n", pt_three());
  return EXIT_SUCCESS;
}