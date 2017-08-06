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

int (cstrcmp)(const char *s1, const char *s2)
 {
     unsigned char uc1, uc2;
     /* Move s1 and s2 to the first differing characters 
        in each string, or the ends of the strings if they
        are identical.  */
     while (*s1 != '\0' && *s1 == *s2) {
         s1++;
         s2++;
     }
     /* Compare the characters as unsigned char and
        return the difference.  */
     uc1 = (*(unsigned char *) s1);
     uc2 = (*(unsigned char *) s2);
     return ((uc1 < uc2) ? -1 : (uc1 > uc2));
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
    return cstrcmp(nondetString1,nondetString2);
}


