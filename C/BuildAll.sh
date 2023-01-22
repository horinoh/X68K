#!/bin/bash

for i in $(find . -type d -maxdepth 1)
do
  pushd $i
    make clean
    make
  popd
done