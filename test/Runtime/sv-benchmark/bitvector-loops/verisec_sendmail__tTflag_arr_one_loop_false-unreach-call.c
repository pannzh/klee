// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// RUN: test -f %t.klee-out/test000021.svcomp.assertfail
extern void __VERIFIER_error() __attribute__ ((__noreturn__));

extern char __VERIFIER_nondet_char();

void __VERIFIER_assert(int cond) {
  if (!(cond)) {
    ERROR: __VERIFIER_error();
  }
  return;
}

int main (void)
{
  char in[11]; // = "3277192070";
  char *s;
  unsigned char c;
  int i, j;
  int idx_in;
  for (i = 0; i < 11; i++)
    in[i] = __VERIFIER_nondet_char();
  in[10] = 0;
  idx_in = 0;
  s = in;
  i = 0;
  c = in[idx_in];
  while (('0' <= c) && (c <= '9'))
  {
    j = c - '0';
    i = i * 10U + j;
    idx_in++;
    c = in[idx_in];
  }
  // CHECK: verisec_sendmail__tTflag_arr_one_loop_false-unreach-call.c:39: svcomp assert failed
  /* BAD */
  __VERIFIER_assert (i >= 0);
  return 0;
}

