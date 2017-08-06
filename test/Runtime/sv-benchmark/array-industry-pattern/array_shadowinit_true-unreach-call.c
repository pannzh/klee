// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
/*
  The program initializes the array 'a' in a loop having loop counter 'i' with a variable 'k' which is a shadow of 'i'. Checks universally quantified property \forall i, a[i] = i.
*/

#define fun main

extern int __VERIFIER_nondet_int(void);

int N;
int main() {
 N=__VERIFIER_nondet_int();
 if(N>0) {
  int i,k;
  int a[N];

  i=0;
  k=0;
  while(i < N) {
   a[k]=k;
   i=i+1;
   k=k+1;
  }

  i=0;
  while(i < N) {
   // CHECK-NOT: assert fail
   __VERIFIER_assert(a[i]==i);
   i=i+1;
  }
 }
 return 0;
}
