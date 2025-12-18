#include <stdlib.h>

typedef struct {
  uint32_t *array;
  size_t count;
  size_t capacity;
} GrowableArray;

void init_growable_array(GrowableArray *a);
int push(GrowableArray *a, uint32_t item);
int find_index(GrowableArray *haystack, uint32_t needle);
int find_index_of_greatest_value(GrowableArray *haystack);