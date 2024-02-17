### how to run:

```bash
conan install . --output-folder=build --build=missing
cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make -C build runtests
```

### benchmark 结果

```
-------------------------------------------------------------------------------
Josephus benchmark small k
-------------------------------------------------------------------------------
/Users/hit9/dev/github/code-snippets/misc/josephus/josephus_benchmark.cpp:30
...............................................................................

benchmark name                       samples       iterations    est run time
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
josephus1                                      100             1    817.357 ms
                                        8.18318 ms    8.17325 ms    8.19896 ms
                                        63.1506 us    44.0342 us    92.3469 us

josephus2                                      100             6     5.2518 ms
                                        8.71584 us    8.71165 us    8.72731 us
                                        32.0921 ns    7.06087 ns    66.2129 ns

josephus3                                      100             9     5.0949 ms
                                         5.6142 us    5.58567 us    5.75457 us
                                        279.401 ns    5.85694 ns    666.631 ns


-------------------------------------------------------------------------------
Josephus benchmark large k
-------------------------------------------------------------------------------
/Users/hit9/dev/github/code-snippets/misc/josephus/josephus_benchmark.cpp:38
...............................................................................

benchmark name                       samples       iterations    est run time
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
josephus1                                      100             1    816.148 ms
                                        8.15791 ms    8.14685 ms    8.17466 ms
                                        68.0962 us    51.0583 us    109.909 us

josephus2                                      100             1     1.12929 s
                                        11.3286 ms    11.2343 ms    11.4899 ms
                                         616.68 us    414.625 us    902.743 us

josephus3                                      100             1     59.8492 s
                                        608.693 ms    605.662 ms    612.792 ms
                                        17.8878 ms    14.2023 ms    22.8401 ms


===============================================================================
```

结论:

* 线性算法在 `k` 比较小的时候不如对数算法.
* josephus3 这个对数算法在 `k` 比较大的时候会急剧恶化
