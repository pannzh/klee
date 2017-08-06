// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// RUN: test -f %t.klee-out/test000001.svcomp.err
extern void __VERIFIER_error() __attribute__ ((__noreturn__));

int main() {
  unsigned int allOne = -1;

  int castToInt = allOne;
  long castToLong = allOne;
  long castToLong2 = castToInt;
  unsigned long castToULong = allOne;

  if (castToInt == -1 && castToLong == 4294967295UL &&
      castToLong2 == -1 && castToULong == 4294967295UL) {
    goto ERROR;
  }

  return (0);
  // CHECK: signextension2_false-unreach-call.c:22: svcomp error
  ERROR: __VERIFIER_error();
  return (-1);
}

