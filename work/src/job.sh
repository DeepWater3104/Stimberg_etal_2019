#! /bin/bash

#PJM --rsc-list "node=1"
#PJM -g hp200139
#PJM --rsc-list "elapse=00:10:00"
#PJM -m b,e
#PJM --mail-list "fukami.satoshi760@mail.kyutech.jp"
#PJM -j
#PJM -o ../job_output/output.%j.out
#PJM -s
#PJM --spath ../job_output/stats.%j.stats

. /vol0004/apps/oss/spack/share/spack/setup-env.sh

module load lang
export PLE_MPI_STD_EMPTYFILE=off
fapp -C -d ../detailed_profile/ -Icpupa,cputime,nompi -Hevent=statistics ./run 10 10
