// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK: memory error
extern int __VERIFIER_nondet_int(void);

int sumOfThirdBytes(int numbers[], int array_size)
{
    int i, sum;
    char* p;
    sum = 0;
    for (i = 0; i < array_size; i++) {
        p = &(numbers[i]);
        p = p + 2;
        sum = sum + *p;
    }
    return sum;
}

int main() {
  int* numbers;
  int array_size = __VERIFIER_nondet_int();
  return sumOfThirdBytes(numbers, array_size);
}
