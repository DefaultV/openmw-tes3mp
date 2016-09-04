#!/bin/sh

free -m
mkdir build
cd build
export CODE_COVERAGE=1
export RAKNET_ROOT=~/RakNet
export Terra_ROOT=~/terra-Linux-x86_64-332a506
if [ "${CC}" = "clang" ]; then export CODE_COVERAGE=0; fi
${ANALYZE}cmake .. -DBUILD_WITH_CODE_COVERAGE=${CODE_COVERAGE} -DBUILD_UNITTESTS=1 -DCMAKE_INSTALL_PREFIX=/usr -DBINDIR=/usr/games  -DCMAKE_BUILD_TYPE="None" -DUSE_SYSTEM_TINYXML=TRUE -DRakNet_LIBRARY_RELEASE=~/RakNet/lib/libRakNetLibStatic.a -DRakNet_LIBRARY_DEBUG=~/RakNet/lib/libRakNetLibStatic.a
