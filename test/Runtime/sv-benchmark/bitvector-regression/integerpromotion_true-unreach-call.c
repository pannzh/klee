// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// RUN: not test -f %t.klee-out/test000001.svcomp.err
extern void __VERIFIER_error() __attribute__ ((__noreturn__));

int main() {

  unsigned char port = 0x5a;
  unsigned char result_8 = ( ~port ) >> 4;
  if (result_8 != 0xfa) {
    goto ERROR;
  }

  return (0);
  // CHECK-NOT: svcomp error
  ERROR: __VERIFIER_error();
  return (-1);
}

