#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int num;
  int count;
} Item_CT;

typedef struct {
  Item_CT *array;
  size_t count;
  size_t capacity;
} GrowableArray;

typedef struct {
  int num;
  int digit;
} PartThreeReturn;

void init_growable_array(GrowableArray *a) {
  a->count = 0;
  a->capacity = 10;
  a->array = malloc(a->capacity * sizeof(Item_CT));
  if (!a->array)
    exit(1);
}

int push(GrowableArray *a, Item_CT item) {
  if (a->count >= a->capacity) {
    // double size to avoid resizing for every new item
    size_t new_capacity = (a->capacity == 0) ? 1 : a->capacity * 2;

    // alloc
    Item_CT *new_arr = realloc(a->array, sizeof(Item_CT) * new_capacity);
    if (new_arr == NULL) {
      return -1;
    }

    a->array = new_arr;
    a->capacity = new_capacity;
  }

  a->array[a->count++] = item;
  return 0;
}

int pt_one() {
  FILE *infile;
  char line_buffer[256];

  infile = fopen("../inputs/demo.txt", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  int sum = 0;

  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    int num = atoi(line_buffer);
    sum += num;
  }

  fclose(infile);

  return sum;
}

int pt_two() {

  FILE *infile;
  char line_buffer[256];

  infile = fopen("../inputs/demo.txt", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  long sum = 0;
  char *endptr;

  int len_input = 0;

  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    long num = strtol(line_buffer, &endptr, 10);
    if (endptr != line_buffer) {
      len_input += 1;
      sum += num;
    }
  }

  fclose(infile);

  // use division ceiling formula
  long result_long = (sum + len_input - 1) / len_input;

  return (int)result_long;
}

PartThreeReturn pt_three() {

  FILE *infile;
  char line_buffer[256];

  infile = fopen("../inputs/demo.txt", "r");

  if (infile == NULL) {
    printf("FlipFlop Codes Demo Problem: Failed to read input file\n");
    exit(EXIT_FAILURE);
  }

  long sum = 0;
  char *endptr;

  int len_input = 0;

  // use dynamic, growable array to store number counts
  GrowableArray num_counts;
  init_growable_array(&num_counts);

  // static array for digits (there are only 10)
  Item_CT digit_counts[10];

  while (fgets(line_buffer, sizeof(line_buffer), infile) != NULL) {
    long num = strtol(line_buffer, &endptr, 10);

    Item_CT *this_num_entry = NULL;

    for (int i = 0; i < num_counts.count; i++) {
      if (num_counts.array[i].num == num) {
        this_num_entry = &num_counts.array[i];
      }
    }

    if (this_num_entry == NULL) {
      Item_CT new_entry = {.num = num, .count = 1};
      push(&num_counts, new_entry);
    } else {
      this_num_entry->count += 1;
    }

    // now manipulate the digits
    int digit;
    while (num != 0) {
      // last digit
      digit = num % 10;

      Item_CT *this_digit_entry = NULL;

      for (int i = 0; i < 10; i++) {
        if (digit_counts[i].num == digit) {
          this_digit_entry = &digit_counts[i];
        }
      }

      if (this_digit_entry == NULL) {
        Item_CT new_entry = {.num = digit, .count = 1};
        digit_counts[digit] = new_entry;
      } else {
        this_digit_entry->count += 1;
      }

      num /= 10;
    }
  }

  Item_CT *most_referenced_num = &num_counts.array[0];
  for (int i = 0; i < num_counts.count; i++) {
    if (num_counts.array[i].count > most_referenced_num->count) {
      most_referenced_num = &num_counts.array[i];
    }
  }

  Item_CT *least_referenced_digit = &digit_counts[0];
  for (int i = 0; i < 10; i++) {
    if (digit_counts[i].count < least_referenced_digit->count) {
      least_referenced_digit = &digit_counts[i];
    }
  }

  fclose(infile);

  PartThreeReturn value = {.digit = least_referenced_digit->num,
                           .num = most_referenced_num->num};
  return value;
}

int main() {
  printf("Pt 1: Sum is: %d\n", pt_one());
  printf("Pt 2: Avg is: %d\n", pt_two());

  PartThreeReturn pt3 = pt_three();
  printf("Pt 3: Most used number is: %d. Least used digit is: %d\n", pt3.num,
         pt3.digit);

  return EXIT_SUCCESS;
}