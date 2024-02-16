### how to run:

```bash
conan install . --output-folder=build --build=missing
cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make -C build runtests
```

### benchmark 结果

```
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
josephus1                                      100             1    822.556 ms
                                        8.24663 ms     8.2315 ms    8.26419 ms
                                        83.2977 us    72.0809 us    102.499 us

josephus2                                      100             6      5.298 ms
                                        8.81794 us    8.74617 us    9.07949 us
                                        607.072 ns    134.314 ns    1.36979 us

josephus3                                      100            10      5.649 ms
                                        5.72819 us    5.60981 us    6.01864 us
                                        848.938 ns    163.109 ns    1.57624 us


-------------------------------------------------------------------------------
Josephus benchmark
-------------------------------------------------------------------------------
/Users/hit9/dev/github/code-snippets/misc/josephus/josephus_benchmark.cpp:38
...............................................................................

benchmark name                       samples       iterations    est run time
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
josephus1                                      100             1    818.592 ms
                                        8.23013 ms    8.21039 ms    8.25592 ms
                                        114.254 us    92.0127 us    149.332 us

josephus2                                      100             1     1.17267 s
                                        11.6032 ms    11.5148 ms    11.7092 ms
                                        492.352 us    424.428 us    609.043 us

josephus3                                      100             1     1.00273 m
                                        603.662 ms    603.407 ms        604 ms
                                        1.48506 ms    1.12084 ms    2.11708 ms
```

结论:

* 线性算法在 `k` 比较小的时候不如对数算法.
* josephus3 这个对数算法在 `k` 比较大的时候会急剧恶化
