#!/bin/bash

if [ $1 != "" ]
then

    more template/MyTool.h | sed s:MyTool:$1: | sed s:MYTOOL_H:$1_H: > ./$1.h
    more template/MyTool.cpp | sed s:MyTool:$1: | sed s:MyTool\(\):$1\(\): > ./$1.cpp
    echo "#include \"$1.cpp\"" >>Unity.cpp

else

echo "Error no name given"

fi
