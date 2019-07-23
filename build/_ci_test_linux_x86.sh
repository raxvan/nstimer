#!/bin/bash -xe

python3 prj.nstimer_test.py make linux
cd build/nstimer_test_linux_make

make config=debug_x32
make config=debug_x64

./bin/x32/Debug/_nstimer_test
./bin/x64/Debug/_nstimer_test


