#!/bin/sh
## compile_test.sh for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/tests
## 
## Made by LALOS Bastien
## Login   <lalos_b@etna-alternance.net>
## 
## Started on  Tue Feb  6 15:29:41 2018 LALOS Bastien
## Last update Tue Feb  6 22:08:14 2018 LALOS Bastien
##

gcc -Wall -g main.c -L$PWD  -lmy_malloc_Linux

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root
export LD_LIBRARY_PATH

./a.out
