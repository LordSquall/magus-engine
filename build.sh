#!/bin/sh
rm -rf cmakeBuild

mkdir cmakeBuild
cd cmakeBuild
cmake ../

make
