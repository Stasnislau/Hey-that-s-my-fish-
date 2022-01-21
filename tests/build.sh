#! /bin/sh

cd .. ; make clean ; make;
cd tests; gcc random_tests.c -o random_test;
gcc run_tests.c -o run;
