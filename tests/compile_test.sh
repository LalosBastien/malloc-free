#!/bin/sh
## compile_test.sh for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/tests
## 
## Made by LALOS Bastien
## Login   <lalos_b@etna-alternance.net>
## 
## Started on  Tue Feb  6 15:29:41 2018 LALOS Bastien
## Last update Thu Mar  1 22:42:45 2018 LALOS Bastien
##

## My malloc test
#gcc -Wall -g main.c -L$PWD  -lmy_malloc_Linux

## Test malloc
gcc -Wall -g tests.c -L$PWD  -lmy_malloc_Linux


LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root
export LD_LIBRARY_PATH

./a.out
