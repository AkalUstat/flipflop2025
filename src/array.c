#include "array.h"
#include <stdio.h>

void init_growable_array(GrowableArray *a) {
  a->count = 0;
  a->capacity = 10;
  a->array = malloc(a->capacity * sizeof(uint32_t));
  if (!a->array)
    exit(1);
}

int push(GrowableArray *a, uint32_t item) {
  if (a->count >= a->capacity) {
    // double size to avoid resizing for every new item
    size_t new_capacity = (a->capacity == 0) ? 1 : a->capacity * 2;

    // alloc
    uint32_t *new_arr = realloc(a->array, sizeof(uint32_t) * new_capacity);
    if (new_arr == NULL) {
      return -1;
    }

    a->array = new_arr;
    a->capacity = new_capacity;
  }

  a->array[a->count++] = item;
  return 0;
}
int find_index(GrowableArray *haystack, uint32_t needle) {
  int index = -1;
  for (int i = 0; i < haystack->count; i++) {
    if (haystack->array[i] == needle) {
      index = i;
      break;
    }
  }

  return index;
}
int find_index_of_greatest_value(GrowableArray *haystack) {
  int index = 0;
  uint32_t greatest_value = haystack->array[0];
  for (int i = 1; i < haystack->count; i++) {
    if (haystack->array[i] > greatest_value) {
      greatest_value = haystack->array[i];
      index = i;
    }
  }

  return index;
}