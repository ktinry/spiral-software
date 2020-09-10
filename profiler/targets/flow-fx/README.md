# FX1000 in Flow system (Nagoya University)

## TODO
### Makefile
`TIMER           ?= ../common/rdtsc_time.c # This is NOT working in A64FX`
- This is NOT working in A64FX (dependent on Intel CPU)
- use papi_time.c or clock_gettime()


## Warning
```sh
#!/bin/sh
#PJM -L rscunit=fx
#PJM -L rscgrp=fx-debug
#PJM -L node=1:mesh
#PJM -L elapse=0:10:00
#PJM -o out__ITR
#PJM -e err__ITR
#PJM -S --spath inf__ITR
```

- Should change elapse time if you create large functions

## Example
```sh
opts := SpiralDefaults;
opts.target := rec();
opts.target.name := "flow-fx";
transform := DFT(32, -1);
ruletree := RuleTreeMid(transform, opts);
icode := CodeRuleTree(ruletree, opts);
CMeasure(icode, opts);
```
