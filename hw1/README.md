# Homework 1 修改后的代码

本文档列出本次实验中需要提交或重点说明的修改文件。源码文件本身位于 `hw1/` 目录中，本文件作为报告附件使用。

## 1. `hw1/c-primer/sizes.c`

主要修改：使用 `PRINT_SIZE` 宏输出指定 C 类型的大小，并输出对应指针大小；额外输出 `student`、数组 `x` 和 `&x` 的大小。

```c
// Copyright (c) 2012 MIT License by 6.172 Staff

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PRINT_SIZE(type) \
  printf("size of %-20s : %zu bytes\n", #type, sizeof(type)); \
  printf("size of %-20s : %zu bytes\n", #type "*", sizeof(type*));

int main() {
  PRINT_SIZE(int)
  PRINT_SIZE(short)
  PRINT_SIZE(long)
  PRINT_SIZE(char)
  PRINT_SIZE(float)
  PRINT_SIZE(double)
  PRINT_SIZE(unsigned int)
  PRINT_SIZE(long long)
  PRINT_SIZE(uint8_t)
  PRINT_SIZE(uint16_t)
  PRINT_SIZE(uint32_t)
  PRINT_SIZE(uint64_t)
  PRINT_SIZE(uint_fast8_t)
  PRINT_SIZE(uint_fast16_t)
  PRINT_SIZE(uintmax_t)
  PRINT_SIZE(intmax_t)
  PRINT_SIZE(__int128)

  typedef struct {
    int id;
    int year;
  } student;

  student you;
  you.id = 12345;
  you.year = 4;

  int x[5];

  printf("size of %-20s : %zu bytes\n", "student", sizeof(you));
  printf("size of %-20s : %zu bytes\n", "student*", sizeof(student*));
  printf("size of %-20s : %zu bytes\n", "x", sizeof(x));
  printf("size of %-20s : %zu bytes\n", "&x", sizeof(&x));

  return 0;
}
```

## 2. `hw1/c-primer/pointer.c`

主要修改：注释掉非法赋值语句，并在注释中回答指针和 `const` 相关问题。

```c
// Copyright (c) 2012 MIT License by 6.172 Staff

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char * argv[]) {  // What is the type of argv? char** (pointer to pointer to char)
  int i = 5;
  int * pi = &i;
  int j = *pi;

  char c[] = "6.172";
  char * pc = c;
  char d = *pc;
  printf("char d = %c\n", d);  // Prints: char d = 6

  char ** pcp;
  pcp = argv;  // Valid because argv is char**, and pcp is char**.

  const char * pcc = c;
  char const * pcc2 = c;  // Same as pcc: pointer to const char.

  // *pcc = '7';  // invalid: pcc points to const char.
  pcc = *pcp;     // valid: pcc itself is not const.
  pcc = argv[0];  // valid: reassigning the pointer, not the pointed-to char.

  char * const cp = c;
  // cp = *pcp;   // invalid: cp is a const pointer.
  // cp = *argv;  // invalid: cp is a const pointer.
  *cp = '!';      // valid: cp points to non-const char.

  const char * const cpc = c;
  // cpc = *pcp;    // invalid: cpc is a const pointer.
  // cpc = argv[0]; // invalid: cpc is a const pointer.
  // *cpc = '@';    // invalid: cpc points to const char.

  return 0;
}
```

## 3. `hw1/c-primer/swap.c`

主要修改：将 `swap` 改为接收 `int*`，通过地址修改调用者变量。

```c
// Copyright (c) 2012 MIT License by 6.172 Staff

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}

int main() {
  int k = 1;
  int m = 2;
  swap(&k, &m);
  printf("k = %d, m = %d\n", k, m);

  return 0;
}
```

## 4. `hw1/matrix-multiply/Makefile`

主要修改：release 模式使用 `-O3 -DNDEBUG`。

```makefile
CFLAGS_RELEASE := -O3 -DNDEBUG
```

## 5. `hw1/matrix-multiply/matrix_multiply.c`

主要修改：

- 引入 `tbassert.h` 并启用维度断言。
- 在 `make_matrix` 中将矩阵元素初始化为 0。
- 在 `free_matrix` 中释放矩阵行、行指针数组和结构体。
- 将乘法循环顺序改为 `i-k-j`，提升连续内存访问比例。

关键代码如下：

```c
#include "./tbassert.h"

matrix* make_matrix(int rows, int cols) {
  matrix* new_matrix = malloc(sizeof(matrix));
  new_matrix->rows = rows;
  new_matrix->cols = cols;

  new_matrix->values = (int**)malloc(sizeof(int*) * rows);
  for (int i = 0; i < rows; i++) {
    new_matrix->values[i] = (int*)malloc(sizeof(int) * cols);
    for (int j = 0; j < cols; j++) {
      new_matrix->values[i][j] = 0;
    }
  }

  return new_matrix;
}

void free_matrix(matrix* m) {
  for (int i = 0; i < m->rows; i++) {
    free(m->values[i]);
  }
  free(m->values);
  free(m);
}

int matrix_multiply_run(const matrix* A, const matrix* B, matrix* C) {
  tbassert(A->cols == B->rows,
           "A->cols = %d, B->rows = %d\n", A->cols, B->rows);
  tbassert(A->rows == C->rows,
           "A->rows = %d, C->rows = %d\n", A->rows, C->rows);
  tbassert(B->cols == C->cols,
           "B->cols = %d, C->cols = %d\n", B->cols, C->cols);

  for (int i = 0; i < A->rows; i++) {
    for (int k = 0; k < A->cols; k++) {
      for (int j = 0; j < B->cols; j++) {
        C->values[i][j] += A->values[i][k] * B->values[k][j];
      }
    }
  }

  return 0;
}
```

## 6. `hw1/matrix-multiply/testbed.c`

主要修改：

- 将矩阵大小设置为 `1000 x 1000`。
- 创建三个同维度矩阵 `A`、`B`、`C`。
- 程序结束前调用 `free_matrix` 释放所有矩阵。

关键代码如下：

```c
const int kMatrixSize = 1000;

A = make_matrix(kMatrixSize, kMatrixSize);
B = make_matrix(kMatrixSize, kMatrixSize);
C = make_matrix(kMatrixSize, kMatrixSize);

matrix_multiply_run(A, B, C);

free_matrix(A);
free_matrix(B);
free_matrix(C);
```
