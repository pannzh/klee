// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK-NOT: memory error
#include <stdlib.h>

extern int __VERIFIER_nondet_int(void);

void insertionSort(int a[], int array_size)
{
    int i, j, index;
    for (i = 1; i < array_size; ++i)
    {
        index = a[i];
        for (j = i; j > 0 && a[j-1] > index; j--)
            a[j] = a[j-1];

        a[j] = index;
    }
}

int main() {
  int array_size = __VERIFIER_nondet_int();
  if (array_size < 1 || array_size >= 2147483647 / sizeof(int)) {
     array_size = 1;
  }
  int* a = (int*) alloca(array_size * sizeof(int));
  insertionSort(a, array_size);
  return 0;
}
