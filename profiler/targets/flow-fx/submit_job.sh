#!/bin/sh

pjsub > tmp_jobid.txt << EOL
#!/bin/sh
#PJM -L rscunit=fx
#PJM -L rscgrp=fx-debug
#PJM -L node=1:mesh
#PJM -L elapse=0:15:00
#PJM -o job_out
#PJM -e job_err
#PJM -S --spath job_inf
$@
EOL

read VAR_JOBID <<< $(cat tmp_jobid.txt | awk '{print $6}')
pjwait $VAR_JOBID > /dev/null
rm -f tmp_jobid.txt

cat job_out
