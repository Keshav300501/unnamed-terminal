#!/bin/sh

if [ -d out ]; then
    cd src
    make clean
    cd ..
fi