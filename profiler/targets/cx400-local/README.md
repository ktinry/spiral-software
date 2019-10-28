# CX400-LOCAL

## Example
```
opts                := SpiralDefaults;
opts.target         := rec();
opts.target.name    := "cx400-local";
transform           := DFT(32, -1);
ruletree            := RuleTreeMid(transform, opts);
icode               := CodeRuleTree(ruletree, opts);
CMeasure(icode, opts);
```
