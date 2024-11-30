#! bin/bash

make clean
make

TMP="../../record/results_"
DATE=`date '+%Y-%m-%d-'`
TIME=`date '+%H-%M'`
DIR=$TMP$DATE$TIME
mkdir $DIR
mkdir $DIR/figure
mkdir $DIR/data

cp -r ./ $DIR/src
cp -r ../plot $DIR/plot

cd $DIR/src
./run &
