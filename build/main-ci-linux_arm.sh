#!/bin/bash
set -e

MAIN_WORKSPACE=$1
THIS_WORKSPACE=$2

/bin/bash $MAIN_WORKSPACE/exec.sh $THIS_WORKSPACE python3 /wcore/workspace/nstimer/prj.nstimer-test.py -a make linux

#build
cd ${THIS_WORKSPACE}/nstimer/build/nstimer-test_linux_make
make config=debug_arm all

#run exe
./bin/ARM/Debug/_nstimer-test

