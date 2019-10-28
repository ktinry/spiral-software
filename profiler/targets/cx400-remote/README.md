# CX400-LOCAL
## Unintended behavior
- cannot remove tmpdirs in spiral-rmeote
- 同時に実行すると全く進まなくなる(CX400の問題？)

## Example
```
opts                := SpiralDefaults;
opts.target         := rec();
opts.target.name    := "cx400-remote";
transform           := DFT(32, -1);
ruletree            := RuleTreeMid(transform, opts);
icode               := CodeRuleTree(ruletree, opts);
CMeasure(icode, opts);
```

```
opts                := SIMDGlobals.getOpts(AVX_4x64f);
opts.target         := rec();
opts.target.name    := "cx400-remote";
transform           := TRC(MDDFT([64,64,64], -1)).withTags(opts.tags);
best                := DP(transform, rec(), opts);
ruletree            := best[1].ruletree;
icode               := CodeRuleTree(ruletree, opts);
PrintCode("AVX_3DDFT64", icode, opts);
```