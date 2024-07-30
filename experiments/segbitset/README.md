A hierarchical bitset with following structure:

```
[                  1                   ]     => root  -+
[        1         ][       0          ]               |--> OR summary of descendants
[   1    ][   0    ][   0    ][   0    ]              -+
[ 1 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ]     => bit data itself
```

The original design purpose was:

1. for methods `any()`, `none()`, it only accesses the root node, it's fast to O(1).
2. for `and, or, xor` operations, and finding positions of true bits, subtrees with a zero root will be skipped quickly,
   it should be faster for sparse bit data than a raw for loop.

But the benchmark result shows that, for 10w bits data, the segbitset implementation is faster only when sparsity is below 2%.

It's welcome to open an issue for your optimization thoughts.
