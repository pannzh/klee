// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
#define SIZE 100000

signed int a[SIZE];

int main()
{
	int i;
	for(i = 0; i < SIZE; i++)
	{
		if(i>=0 && i<=10000)
			a[i] = 10;
		else
		a[i] = 0;
	}


	for(i = 0; i < SIZE; i++)
	{
        // CHECK: assert fail
		__VERIFIER_assert(a[i] == 10);
		
	}

	return 0;
}


