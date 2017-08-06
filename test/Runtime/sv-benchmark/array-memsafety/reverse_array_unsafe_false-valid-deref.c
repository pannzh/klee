// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK: memory error
#include <stdlib.h>
extern int __VERIFIER_nondet_int(void);

int main() {
  int i, j, tmp;
  int length = __VERIFIER_nondet_int();
  if (length < 1) length = 1;
  // make sure that length is odd
  if (length % 2 == 0) length++;
  int *arr = alloca(length);
  // make sure the marker occurs only once
  for (i=0; i<length; i++) {
    if (arr[i] == '\0') arr[i]++;
  }
  // mark the middle
  arr[length / 2 + 1] = '\0';
  // runs from left to right
  int *a = arr;
  // runs from right to left
  int *b = arr + length - 1;
  // swap elements until we reach the marker
  while (*a != 0 && *b != 0) {
    tmp = *a;
    *a = *b;
    *b = tmp;
    a++;
    b--;
  }
  return 0;
}
