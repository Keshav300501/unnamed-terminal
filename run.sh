#!/bin/sh

if [ ! -d out ]; then
    cd src
    make all
    cd ../out
else
    cd out
fi
./main
