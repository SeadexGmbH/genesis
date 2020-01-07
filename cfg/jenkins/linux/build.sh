#!/bin/bash


export WORKING_DIR=$(pwd)
echo $WORKING_DIR

cd ../../..

export FMT_INCLUDE_DIR=~/Downloads/libfmt/include
echo $FMT_INCLUDE_DIR
export FMT_LIB_PATH=~/Downloads/libfmt/build/libfmt.so
echo $FMT_LIB_PATH

export SPDLOG_INCLUDE_DIR=~/Downloads/libspdlog/include
echo $SPDLOG_INCLUDE_DIR
export SPDLOG_LIB_PATH=~/Downloads/libspdlog/build/libspdlog.so
echo $SPDLOG_L

# install 7zip
apt-get install p7zip

cd ~/Downloads && \
    wget https://github.com/SeadexGmbH/essentials/releases/download/2.1.3/essentials_2_1_3.7z && \
    7z x essentials_2_1_3.7z
    
export ESSENTIALS_INCLUDE_DIR=~/Downloads/essentials/source/essentials/include
echo $ESSENTIALS_INCLUDE_DIR
export ESSENTIALS_LIB_PATH="~/Downloads/essentials/build/Linux/x64/gcc 10/Release/lib/libessentials.so"
echo "$ESSENTIALS_LIB_PATH"

cd $WORKING_DIR
cd ../../..

cd cmaked
cmake .. -G "Unix Makefiles" -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DSPDLOG_FMT_EXTERNAL=ON -DCMAKE_BUILD_TYPE=Debug -DFMT_LIB_INCLUDE=$FMT_INCLUDE_DIR -DFMT_LIB=$FMT_LIB_PATH -DSPDLOG_LIB_INCLUDE=$SPDLOG_INCLUDE_DIR -DSPDLOG_LIB=$SPDLOG_LIB_PATH -DESSENTIALS_LIB_INCLUDE=$ESSENTIALS_INCLUDE_DIR -DESSENTIALS_LIB="$ESSENTIALS_LIB_PATH" -DBUILD_SHARED_LIBS=ON -DGEN_BUILD_EXAMPLES=ON
make

cd ..
cd cmake
cmake .. -G "Unix Makefiles" -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DSPDLOG_FMT_EXTERNAL=ON -DCMAKE_BUILD_TYPE=Release -DFMT_LIB_INCLUDE=$FMT_INCLUDE_DIR -DFMT_LIB=$FMT_LIB_PATH -DSPDLOG_LIB_INCLUDE=$SPDLOG_INCLUDE_DIR -DSPDLOG_LIB=$SPDLOG_LIB_PATH -DESSENTIALS_LIB_INCLUDE=$ESSENTIALS_INCLUDE_DIR -DESSENTIALS_LIB="$ESSENTIALS_LIB_PATH" -DBUILD_SHARED_LIBS=ON -DGEN_BUILD_EXAMPLES=ON
make

cd ..
mkdir externals
cd externals
mkdir gcc
mkdir clang

cd ~/Downloads
cd essentials/build/Linux/x64
cd "gcc 10/Release/lib"
cp libessentials.so $WORKING_DIR/../../../externals/gcc

cd $WORKING_DIR
cd ../../../externals

cp -RT $ESSENTIALS_INCLUDE_DIR include