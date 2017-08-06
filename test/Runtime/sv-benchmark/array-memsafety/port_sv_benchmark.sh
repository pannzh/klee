#!/bin/bash

SRC_TESTS_DIR=
DST_TESTS_DIR=.

if [ $# -eq 1 ];then
    SRC_TESTS_DIR=$1
elif [ $# -eq 2 ];then
    SRC_TESTS_DIR=$1
    DST_TESTS_DIR=$2
else
    echo "Usage: $0 SRC_TESTS_DIR [DST_TESTS_DIR]"
    exit 1
fi

for c_source in `ls ${SRC_TESTS_DIR}/*.c`;do
    c_source_base=$(basename $c_source)
    echo "$c_source_base" | grep -E ".*_true-.*.c" &>/dev/null
    ret=$?
    ret_str=
    check_status=
    if [ $ret -eq 0 ];then
        ret_str="true"
        check_status="CHECK-NOT"
    else
        ret_str="false"
        check_status="CHECK"
    fi
    cat > $DST_TESTS_DIR/$c_source_base << EOF
// RUN: %llvmgcc %s -emit-llvm -g -c -o %t1.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out -exit-on-error-type=Ptr -svcomp-runtime %t1.bc 2>&1 | FileCheck %s
// $check_status: memory error
EOF
    cat $c_source >> $DST_TESTS_DIR/$c_source_base
    echo "Find: ($ret_str) $c_source_base"
    
done
