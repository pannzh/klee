// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK: memory error
extern int __VERIFIER_nondet_int(void);

void diff(int *A, int Alen, int *B, int Blen, int *D)
{
    int k = 0;
    int i = 0;
    int l1 = Alen;
    int l2 = Blen;
    int found;

    while (i < l1) {
        int j = 0;
        found = 0;
        while (j < l2 && !found) {
            if(A[i] == B[j]) {
                found = 1;
            } else {
                j++;
            }
        }
        if (!found) {
            D[k] = A[i];
            k++;
        }
        i++;
    }
}

int main() {
  int *A;
  int Alen = __VERIFIER_nondet_int();
  int *B;
  int Blen = __VERIFIER_nondet_int();
  int *D;
  diff(A, Alen, B, Blen, D);
  return 0;
}
