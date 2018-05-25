#!/bin/sh

srcdir=${srcdir-.}

echo "Generating dictionary"
../gen-lookup-dict ${srcdir}/test.lst test.dic

echo "Testing the dictionary"
./test-dict
