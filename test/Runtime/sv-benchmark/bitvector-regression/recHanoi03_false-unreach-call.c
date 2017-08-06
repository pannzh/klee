// RUN: %llvmgcc %s -emit-llvm -std=c99 -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=ReportError -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// RUN: test -f %t.klee-out/test000033.svcomp.err
extern void __VERIFIER_error() __attribute__ ((__noreturn__));

/*
 * recHanoi.c
 *
 *  Created on: 17.07.2013
 *      Author: Stefan Wissert
 */

extern int __VERIFIER_nondet_int(void);

/*
 * This function returns the optimal amount of steps,
 * needed to solve the problem for n-disks
 */
unsigned hanoi(int n) {
    if (n == 1) {
		return 1;
	}
	return 2 * (hanoi(n-1)) + 1;
}


int main() {
    int n = __VERIFIER_nondet_int();
    if (n < 1) {
    	return 0;
    }
    unsigned result = hanoi(n);
    // result and the counter should be the same!
    if (result+1>0 && result+1 == 1<<n) {
        return 0;
    } else {
        // CHECK: recHanoi03_false-unreach-call.c:39: svcomp error
        ERROR: __VERIFIER_error();
    }
}


