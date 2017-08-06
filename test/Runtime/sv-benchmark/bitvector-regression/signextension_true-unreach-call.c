// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// RUN: not test -f %t.klee-out/test000001.svcomp.err
extern void __VERIFIER_error() __attribute__ ((__noreturn__));

int main() {

  unsigned short int allbits = -1;
  short int signedallbits = allbits;
  int unsignedtosigned = allbits;
  unsigned int unsignedtounsigned = allbits;
  int signedtosigned = signedallbits;
  unsigned int signedtounsigned = signedallbits;

  /*
  printf ("unsignedtosigned: %d\n", unsignedtosigned);
  printf ("unsignedtounsigned: %u\n", unsignedtounsigned);
  printf ("signedtosigned: %d\n", signedtosigned);
  printf ("signedtounsigned: %u\n", signedtounsigned);
  */

  if (unsignedtosigned != 65535 || unsignedtounsigned != 65535
      || signedtosigned != -1 || signedtounsigned != 4294967295) {
    goto ERROR;
  }

  return (0);
  // CHECK-NOT: svcomp error
  ERROR: __VERIFIER_error();
  return (-1);
}

