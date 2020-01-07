#!/bin/bash
ess_path=$(python3 lib_path_extractor.py $2) 
echo $ess_path 
cd $ess_path 
ls -lla . 
mkdir "$1/$3" 
cp libessentials.so "$1/$3"