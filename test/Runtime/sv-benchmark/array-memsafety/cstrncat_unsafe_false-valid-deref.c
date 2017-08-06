// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// CHECK: memory error
extern int __VERIFIER_nondet_int(void);

char *(cstrncat)(char *s1, const char *s2, int n)
 {
     char *s = s1;
     /* Loop over the data in s1.  */
     while (*s != '\0')
         s++;
     /* s now points to s1's trailing null character, now copy
        up to n bytes from s1 into s stopping if a null character
        is encountered in s2.
        It is not safe to use strncpy here since it copies EXACTLY n
        characters, NULL padding if necessary.  */
     while (n != 0 && (*s = *s2++) != '\0') {
         n--;
         s++;
     }
     if (*s != '\0')
         *s = '\0';
     return s1;
 }

int main() {
  char *s1;
  char *s2;
  int n = __VERIFIER_nondet_int();
  cstrncat(s1, s2, n);
  return 0;
}
