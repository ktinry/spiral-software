# Oakbridge-CX

## Warning
```sh
#PJM -L rscgrp=debug
#PJM -L node=1
#PJM -L elapse=0:30:00
#PJM -o job_out
#PJM -e job_err
#PJM -S --spath job_inf
#PJM -g jh190015
```

- You must specify your project id instead of 'jh190015'.
- You should use a different resource group when time consuming.

## Example
opts                := SpiralDefaults;
opts.target         := rec();
opts.target.name    := "oakbridge-cx";
transform           := DFT(32, -1);
ruletree            := RuleTreeMid(transform, opts);
icode               := CodeRuleTree(ruletree, opts);
CMeasure(icode, opts);
