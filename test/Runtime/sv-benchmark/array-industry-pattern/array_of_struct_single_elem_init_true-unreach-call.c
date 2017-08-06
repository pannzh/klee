// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern int __VERIFIER_nondet_int(void);
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
#define SIZE 20
#define NULL (void *)0

struct S
{
	int p;
	int n;
};

struct S a[SIZE];

int main()
{

	int i;

	//init and update
	for (i = 0; i < SIZE; i++)
	{
        // CHECK-NOT: assert fail
		int q = __VERIFIER_nondet_int();
		struct S s;
		if (s.n == 0)
		{
		    s.p =10 ;
		}
		else
		{
	 		s.p = 20;
		}
		
		a[i] = s;
	}

	a[3].p = 30;
	a[3].n = 40;

	//check 2
	for (i = 0; i < SIZE; i++)
	{
		struct S s1 = a[i];
		if (i != 3 && s1.n == 0)
		{
            // CHECK-NOT: assert fail
			__VERIFIER_assert(s1.p == 10); 
		}
	}
	return 0;
}

