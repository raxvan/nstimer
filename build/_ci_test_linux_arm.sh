#!/bin/bash -xe

python3 prj.nstimer_test.py make linux
cd build/nstimer_test_linux_make

make config=debug_arm

./bin/ARM/Debug/_nstimer_test
