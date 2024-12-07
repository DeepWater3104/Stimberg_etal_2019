#!/bin/bash

max_G_EXC=0.2
max_G_INH=4.0

num_G_EXC=11
num_G_INH=11

cat << EOF > condition.h
#define max_G_EXC ( ${max_G_EXC} )
#define max_G_INH ( ${max_G_INH} )
#define num_G_EXC ( ${num_G_EXC} )
#define num_G_INH ( ${num_G_INH} )
EOF

TMP="../../record/results_"
DATE=`date '+%Y-%m-%d-'`
TIME=`date '+%H-%M'`
DIR=$TMP$DATE$TIME
mkdir $DIR
mkdir $DIR/figure
mkdir $DIR/data
mkdir $DIR/job_output


make clean
make

cat << EOF > job.sh
#! /bin/bash

#PJM --rsc-list "node=1"
#PJM -g hp200139
#PJM --rsc-list "elapse=01:00:00"
#PJM -m b,e
#PJM --mail-list "fukami.satoshi760@mail.kyutech.jp"
#PJM -j
#PJM -o ../job_output/output.%j.out
#PJM -s
#PJM --spath ../job_output/stats.%j.stats

./run  10 10
EOF


cp -r ./ $DIR/src

cd $DIR/src

pjsub job.sh

cd -
