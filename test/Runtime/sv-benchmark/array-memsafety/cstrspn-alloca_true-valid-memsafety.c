// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK-NOT: memory error
/*
 * Date: 17.12.2013
 * Author: Thomas Ströder
 */
#include <stdlib.h>

extern int __VERIFIER_nondet_int(void);

int (cstrspn)(const char *s1, const char *s2)
 {
     const char *sc1;
     const char *s;
     int c;
     for (sc1 = s1; *sc1 != '\0'; sc1++) {
         s = s2;
         c = *sc1;
         while (*s != '\0' && *s != (char)c)
             s++;
         if (*s != c)
             return (sc1 - s1);
     }
     return sc1 - s1;            /* terminating nulls don't match */
 }

int main() {
    int length1 = __VERIFIER_nondet_int();
    int length2 = __VERIFIER_nondet_int();
    if (length1 < 1) {
        length1 = 1;
    }
    if (length2 < 1) {
        length2 = 1;
    }
    char* nondetString1 = (char*) alloca(length1 * sizeof(char));
    char* nondetString2 = (char*) alloca(length2 * sizeof(char));
    nondetString1[length1-1] = '\0';
    nondetString2[length2-1] = '\0';
    return cstrspn(nondetString1,nondetString2);
}


