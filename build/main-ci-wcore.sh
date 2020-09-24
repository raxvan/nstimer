#!/bin/bash

python3 /wcore/workspace/nstimer/prj.nstimer-test.py make linux

#build and stuff
cd /wcore/workspace/nstimer/build/nstimer-test_linux_make
make -n config=debug_x32 all

./bin/x32/Debug/_nstimer-test