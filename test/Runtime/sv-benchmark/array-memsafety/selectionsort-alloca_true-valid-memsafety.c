// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK-NOT: memory error
#include <stdlib.h>

extern int __VERIFIER_nondet_int(void);

void SelectionSort(int a[], int array_size)
{
    int i;
    for (i = 0; i < array_size - 1; ++i)
    {
        int j, min, temp;
        min = i;
        for (j = i+1; j < array_size; ++j)
        {
            if (a[j] < a[min])
                min = j;
        }
        
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

int main() {
  int array_size = __VERIFIER_nondet_int();
  if (array_size < 1 || array_size >= 2147483647 / sizeof(int)) {
     array_size = 1;
  }
  int* numbers = (int*) alloca(array_size * sizeof(int));
  SelectionSort(numbers, array_size);
  return 0;
}  
