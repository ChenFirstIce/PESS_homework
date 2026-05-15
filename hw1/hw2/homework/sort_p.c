/**
 * Copyright (c) 2012 MIT License by 6.172 Staff
 **/

#include "./util.h"

static inline void merge_p(data_t* A, int p, int q, int r);
static inline void copy_p(data_t* source, data_t* dest, int n);

void sort_p(data_t* A, int p, int r) {
  assert(A);
  if (p < r) {
    int q = (p + r) / 2;
    sort_p(A, p, q);
    sort_p(A, q + 1, r);
    merge_p(A, p, q, r);
  }
}

static inline void merge_p(data_t* A, int p, int q, int r) {
  assert(A);
  assert(p <= q);
  assert((q + 1) <= r);
  int n1 = q - p + 1;
  int n2 = r - q;

  data_t* left = 0, * right = 0;
  mem_alloc(&left, n1 + 1);
  mem_alloc(&right, n2 + 1);
  if (left == NULL || right == NULL) {
    mem_free(&left);
    mem_free(&right);
    return;
  }

  copy_p(A + p, left, n1);
  copy_p(A + q + 1, right, n2);
  *(left + n1) = UINT_MAX;
  *(right + n2) = UINT_MAX;

  data_t* left_cursor = left;
  data_t* right_cursor = right;
  data_t* dest = A + p;
  data_t* end = A + r;

  while (dest <= end) {
    if (*left_cursor <= *right_cursor) {
      *dest++ = *left_cursor++;
    } else {
      *dest++ = *right_cursor++;
    }
  }
  mem_free(&left);
  mem_free(&right);
}

static inline void copy_p(data_t* source, data_t* dest, int n) {
  assert(dest);
  assert(source);

  data_t* end = source + n;
  while (source < end) {
    *dest++ = *source++;
  }
}
