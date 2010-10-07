#!/bin/bash

TESTS=`ls *Test`

for test in $TESTS; do
    echo "Running $test"
    ./$test
done
