// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK-NOT: memory
#include <stdlib.h>
extern int __VERIFIER_nondet_int(void);

int main() {
  int i, j;
  int length = __VERIFIER_nondet_int();
  if (length < 1 || length >= 2147483647 / sizeof(int)) length = 1;
  int *arr = alloca(length*sizeof(int));
  if (!arr) return 0;
  int *a = arr;
  while (*a != *(arr + length - 1)) {
    *a += *(arr + length - 1);
    a++;
  }
  return 0;
}
