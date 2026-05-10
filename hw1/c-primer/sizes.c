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
