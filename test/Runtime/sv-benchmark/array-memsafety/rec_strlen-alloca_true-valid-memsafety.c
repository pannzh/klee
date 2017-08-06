// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK-NOT: memory error
#include <stdlib.h>

extern int __VERIFIER_nondet_int(void);

int strlen_rec(const char *p) {
	if(*p == '\0')
		return 0;
	else
		return 1 + strlen_rec(p+1);
}

int main() {
	 int length1 = __VERIFIER_nondet_int();
     if (length1 < 1) {
         length1 = 1;
     }
     char* nondetString1 = (char*) alloca(length1 * sizeof(char));
     nondetString1[length1-1] = '\0';
	 strlen_rec(nondetString1);
}

