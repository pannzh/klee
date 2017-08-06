// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK-NOT: memory error
#include <stdlib.h>

extern int __VERIFIER_nondet_int(void);

void sort(int *x, int n) {
    int pass;
    int i;
    for (pass=1; pass < n; pass++)  // count how many times
        // This next loop becomes shorter and shorter
        for (i=0; i < n - pass; i++)
            if (x[i] > x[i+1]) {
                // exchange elements
                int temp = x[i]; x[i] = x[i+1];  x[i+1] = temp;
            }
}

int main() {
  int array_size = __VERIFIER_nondet_int();
  if (array_size < 1 || array_size >= 2147483647 / sizeof(int)) {
     array_size = 1;
  }
  int* numbers = (int*) alloca(array_size * sizeof(int));
  sort(numbers, array_size);
  return 0;
}
