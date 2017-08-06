// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// RUN: test -f %t.klee-out/test000001.svcomp.err
extern void __VERIFIER_error() __attribute__ ((__noreturn__));

int main() {
  float f = 1;
  int i = f;
  if (i == 1){
    goto ERROR;
  }
  return (0);
  // CHECK: implicitfloatconversion_false-unreach-call.c:15: svcomp error
  ERROR: __VERIFIER_error();
  return (-1);
}

