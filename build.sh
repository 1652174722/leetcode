#!/bin/bash

# download or install dependencies
yum install gtest-devel

# build
make clean && make