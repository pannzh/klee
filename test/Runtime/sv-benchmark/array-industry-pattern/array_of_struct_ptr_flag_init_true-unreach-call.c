// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
typedef unsigned int size_t;
extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;
extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
#define NULL 0
#define SIZE 20

typedef struct
{
	int *n;
}S;

void init(S a[], int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		a[i].n = (int *) malloc(sizeof(int));
	}
}

int main()
{
	S a[SIZE];
	int i;
	int flag;
	flag = 0;

	init(a, SIZE);

	for(i = 0; i < SIZE; i++)
	{
		if(a[i].n != NULL)
		{
			flag = 1;
		}
	}

	
	for(i = 0; i < SIZE; i++)
	{
		if (flag == 0)
            // CHECK-NOT: assert fail
            __VERIFIER_assert(a[i].n == NULL);
	}
	
	
	return 0;
}	
