如何运行?
---------

```
cmake -B build -S .
make -C build
./build/bench
```

我电脑上的结果:


```

-------------------------------------------------------------------------------
Benchmark Scale: 100 x 100
-------------------------------------------------------------------------------
/Users/hit9/dev/github/code-snippets/problems/matrix-sorted-search/benchmark/test.cc:82
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Benchmark Solution1 O(log(m*n))                100            55      7.524 ms
                                        1.31632 us    1.28767 us     1.3464 us
                                        150.616 ns    132.058 ns    174.285 ns

Benchmark Solution2 O(m+n)                     100            73     7.4825 ms
                                        994.336 ns    983.676 ns    1.00548 us
                                         55.688 ns     47.766 ns    67.8874 ns


-------------------------------------------------------------------------------
Benchmark Scale: 100 x 10000
-------------------------------------------------------------------------------
/Users/hit9/dev/github/code-snippets/problems/matrix-sorted-search/benchmark/test.cc:110
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Benchmark Solution1 O(log(m*n))                100             3    10.4103 ms
                                        33.7817 us    30.1712 us    37.6765 us
                                         19.106 us    17.0428 us    21.8079 us

Benchmark Solution2 O(m+n)                     100             2    12.9558 ms
                                        58.5935 us    53.2971 us    63.9076 us
                                        27.1461 us    24.5621 us    30.1752 us


-------------------------------------------------------------------------------
Benchmark Scale: 10000 x 10000
-------------------------------------------------------------------------------
/Users/hit9/dev/github/code-snippets/problems/matrix-sorted-search/benchmark/test.cc:138
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Benchmark Solution1 O(log(m*n))                100            11     8.0751 ms
                                          5.876 us    5.50704 us    6.31113 us
                                        2.03888 us    1.74714 us    2.52083 us

Benchmark Solution2 O(m+n)                     100             1    15.1152 ms
                                        125.508 us    106.701 us     148.17 us
                                        104.764 us    89.7794 us    124.035 us


===============================================================================
```
