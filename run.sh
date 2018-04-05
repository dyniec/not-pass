#!/bin/bash
for i in {0..8};do
  echo  "./main < tests/test${i}.in"
  ./main < tests/test${i}.in
done;
