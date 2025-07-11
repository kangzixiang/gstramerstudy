#!/bin/bash

CURRENT_DIR=$(cd $(dirname $0); pwd)
FILE=${CURRENT_DIR}/output

if [ ! -d "$FILE" ]; then
    echo "$FILE not exist"
    mkdir ${FILE}
fi

cd ${FILE}

cmake ..

make -j16