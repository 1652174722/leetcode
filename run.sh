#!/bin/bash
make clean && make -j $(cat /proc/cpuinfo  |grep processor | wc -l) && make run