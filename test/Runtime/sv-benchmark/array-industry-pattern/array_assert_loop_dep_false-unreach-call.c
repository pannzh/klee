// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// RUN: test -f %t.klee-out/test000001.svcomp.assertfail
extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
#define SIZE 20
int main()
{
	int i;
	int a[SIZE];
	for(i = 0; i < SIZE; i++)
	{
		a[i] = 10;
	}


	for(i = 0; i < SIZE; i++)
	{
        // CHECK: assert fail
		__VERIFIER_assert(a[i] == 10 );

		if(i+1 != 15000)
			a[i+1] = 20;
	}

	return 0;
}

