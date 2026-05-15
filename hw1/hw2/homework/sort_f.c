/**
 * Copyright (c) 2012 MIT License by 6.172 Staff
 **/

#include "./util.h"

#define COARSEN_THRESHOLD 32

void isort(data_t* begin, data_t* end);

static inline void sort_f_helper(data_t* A, int p, int r, data_t* scratch);
static inline void merge_f(data_t* A, int p, int q, int r, data_t* scratch);
static inline void copy_f(data_t* source, data_t* dest, int n);

void sort_f(data_t* A, int p, int r) {
  assert(A);
  int n = r - p + 1;
  if (n <= 1) {
    return;
  }

  data_t* scratch = 0;
  mem_alloc(&scratch, n / 2 + 2);
  if (scratch == NULL) {
    return;
  }
  sort_f_helper(A, p, r, scratch);
  mem_free(&scratch);
}

static inline void sort_f_helper(data_t* A, int p, int r, data_t* scratch) {
  int n = r - p + 1;
  if (n <= 1) {
    return;
  }
  if (n <= COARSEN_THRESHOLD) {
    isort(A + p, A + r);
    return;
  }

  int q = (p + r) / 2;
  sort_f_helper(A, p, q, scratch);
  sort_f_helper(A, q + 1, r, scratch);
  merge_f(A, p, q, r, scratch);
}

static inline void merge_f(data_t* A, int p, int q, int r, data_t* scratch) {
  assert(A);
  assert(scratch);
  assert(p <= q);
  assert((q + 1) <= r);
  int n1 = q - p + 1;

  copy_f(A + p, scratch, n1);

  data_t* left_cursor = scratch;
  data_t* left_end = scratch + n1;
  data_t* right_cursor = A + q + 1;
  data_t* right_end = A + r;
  data_t* dest = A + p;

  while (left_cursor < left_end && right_cursor <= right_end) {
    if (*left_cursor <= *right_cursor) {
      *dest++ = *left_cursor++;
    } else {
      *dest++ = *right_cursor++;
    }
  }

  while (left_cursor < left_end) {
    *dest++ = *left_cursor++;
  }
}

static inline void copy_f(data_t* source, data_t* dest, int n) {
  assert(dest);
  assert(source);

  data_t* end = source + n;
  while (source < end) {
    *dest++ = *source++;
  }
}
