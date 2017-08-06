// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK-NOT: memory error
#include <stdlib.h>

extern int __VERIFIER_nondet_int(void);

void test_fun(int a[], int N)
{
    int i;
    int res;
    for (i = 0; i < N; i++) {
        res = 1;
        if (a[i] == 0) {
            res = 1;
        } else if (a[i] < 0) {
            res = 0;
        }
        while (a[i] > 0) {
            res = res * a[i];
            a[i]--;
        }
        a[i] = res;
    }
}

int main() {
  int array_size = __VERIFIER_nondet_int();
  if (array_size < 1 || array_size >= 2147483647 / sizeof(int)) {
     array_size = 1;
  }
  int* numbers = (int*) alloca(array_size * sizeof(int));
  test_fun(numbers, array_size);
}
