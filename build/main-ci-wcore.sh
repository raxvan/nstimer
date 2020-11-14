#!/bin/bash
set -e -o pipefail

MAIN_WORKSPACE=$1
THIS_WORKSPACE=$2

python3 ${THIS_WORKSPACE}/nstimer/prj.nstimer-test.py -a make linux

#build and stuff
cd ${THIS_WORKSPACE}/nstimer/build/nstimer-test_linux_make
make config=debug_x64 all

#run leak detection
valgrind --leak-check=full --log-fd=1 --error-exitcode=1911 ./bin/x64/Debug/_nstimer-test
