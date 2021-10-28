#! /bin/bash
dir=$(cd -P -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd -P)
rm -r build
mkdir build && cd build
cmake ..
make
