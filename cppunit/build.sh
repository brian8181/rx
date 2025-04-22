#!/bin/bash
set -x #echo on

g++ -std=c++11 ./src/main.cpp ./src/Calculator.cpp -lcppunit -o ./build/test_calculator
