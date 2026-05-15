/**
 * Copyright (c) 2012 MIT License by 6.172 Staff
 **/

#include "./util.h"

#define COARSEN_THRESHOLD 32

void isort(data_t* begin, data_t* end);

static inline void merge_m(data_t* A, int p, int q, int r);
static inline void copy_m(data_t* source, data_t* dest, int n);

void sort_m(data_t* A, int p, int r) {
  assert(A);
  int n = r - p + 1;
  if (n <= 1) {
    return;
  }
  if (n <= COARSEN_THRESHOLD) {
    isort(A + p, A + r);
    return;
  }

  int q = (p + r) / 2;
  sort_m(A, p, q);
  sort_m(A, q + 1, r);
  merge_m(A, p, q, r);
}

static inline void merge_m(data_t* A, int p, int q, int r) {
  assert(A);
  assert(p <= q);
  assert((q + 1) <= r);
  int n1 = q - p + 1;

  data_t* left = 0;
  mem_alloc(&left, n1 + 1);
  if (left == NULL) {
    return;
  }

  copy_m(A + p, left, n1);
  *(left + n1) = UINT_MAX;

  data_t* left_cursor = left;
  data_t* right_cursor = A + q + 1;
  data_t* right_end = A + r;
  data_t* dest = A + p;

  while (left_cursor < left + n1 && right_cursor <= right_end) {
    if (*left_cursor <= *right_cursor) {
      *dest++ = *left_cursor++;
    } else {
      *dest++ = *right_cursor++;
    }
  }

  while (left_cursor < left + n1) {
    *dest++ = *left_cursor++;
  }

  mem_free(&left);
}

static inline void copy_m(data_t* source, data_t* dest, int n) {
  assert(dest);
  assert(source);

  data_t* end = source + n;
  while (source < end) {
    *dest++ = *source++;
  }
}
