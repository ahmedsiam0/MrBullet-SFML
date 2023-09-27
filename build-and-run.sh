#! /bin/sh

autoreconf --install
./configure --prefex ./build
make -j4 install
./build/bin/mr-bullet
