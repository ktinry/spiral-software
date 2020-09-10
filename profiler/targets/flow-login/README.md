# FX1000 in Flow system (Nagoya University)

- You can use profiler target 'flow-login' in parallel
    - Also 'flow-fx'

## Example
```sh
opts := SpiralDefaults;
opts.target := rec();
opts.target.name := "flow-login";
transform := DFT(32, -1);
ruletree := RuleTreeMid(transform, opts);
icode := CodeRuleTree(ruletree, opts);
CMeasure(icode, opts);
```
