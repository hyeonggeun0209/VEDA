#!/bin/sh

BASEPATH=$('pwd')

if [ -z $1 ]; then
    echo "ERROR: Use wn7 or cv2x as a parameter. e.g.: ./APP_COMPILATION <\"wn7\" or \"cv2x\">"
    exit 1
else
    if [ $1 != "wn7" ] && [ $1 != "cv2x" ]; then
        echo "ERROR:" $1 "is not wn7 or cv2x. e.g.: ./APP_COMPILATION <\"wn7\" or \"cv2x\">"
        exit 1
    fi

    HOSTNAME=$1 
fi

cp $BASEPATH/AppVaxALPR.crt /opt/opensdk/signature && cp $BASEPATH/AppVaxALPR.key /opt/opensdk/signature

if [ $HOSTNAME = "wn7" ]; then
    HOSTARCH=armv7-wn7-linux-gnueabihf
    cd $BASEPATH && make clean && make $HOSTARCH -j4
fi

if [ $HOSTNAME = "cv2x" ]; then
    HOSTARCH=aarch64-linux-gnu
    cd $BASEPATH && make clean && make $HOSTARCH -j20
fi
