// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
#define SIZE 20

int __VERIFIER_nondet_int();
int main()
{
	int i;
	int a[SIZE];
	int b[SIZE];
	for(i = 0; i < SIZE;  i = i + 2)
	{
		a[i] = __VERIFIER_nondet_int();
		if(a[i] == 10)
			b[i] = 20;
	}

	for(i = 0; i < SIZE; i = i + 2)
	{
		if(a[i] == 10) {
            // CHECK-NOT: assert fail
			__VERIFIER_assert(b[i] == 20);
        }
	}
}

