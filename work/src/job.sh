#! /bin/bash

#PJM --rsc-list "node=1"
#PJM -g hp200139
#PJM --rsc-list "elapse=01:30:00"
#PJM -m b,e
#PJM --mail-list "fukami.satoshi760@mail.kyutech.jp"
#PJM -j
#PJM -o ../job_output/output.%j.out
#PJM -s
#PJM --spath ../job_output/stats.%j.stats

. /vol0004/apps/oss/spack/share/spack/setup-env.sh

module load lang
export PLE_MPI_STD_EMPTYFILE=off

fapp -C -d ../detailed_profile/rep1  -Hevent=pa1 ./run 10 10
fapp -C -d ../detailed_profile/rep2  -Hevent=pa2 ./run 10 10
fapp -C -d ../detailed_profile/rep3  -Hevent=pa3 ./run 10 10
fapp -C -d ../detailed_profile/rep4  -Hevent=pa4 ./run 10 10
fapp -C -d ../detailed_profile/rep5  -Hevent=pa5 ./run 10 10
fapp -C -d ../detailed_profile/rep6  -Hevent=pa6 ./run 10 10
fapp -C -d ../detailed_profile/rep7  -Hevent=pa7 ./run 10 10
fapp -C -d ../detailed_profile/rep8  -Hevent=pa8 ./run 10 10
fapp -C -d ../detailed_profile/rep9  -Hevent=pa9 ./run 10 10
fapp -C -d ../detailed_profile/rep10  -Hevent=pa10 ./run 10 10
fapp -C -d ../detailed_profile/rep11  -Hevent=pa11 ./run 10 10
