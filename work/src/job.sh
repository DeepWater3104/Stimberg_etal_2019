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
