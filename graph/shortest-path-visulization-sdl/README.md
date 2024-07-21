一个用来可视化最短路算法的小工具.

![](misc/astar.gif)

### 安装依赖和构建

需要先安装 [conan](https://conan.io/), 然后执行以下来安装依赖:

```bash
make install
```

然后构建:

```bash
make configure
make build
```

#### 执行

查看帮助:

```
/build/shortest-path-visulization-sdl  --help
```

可视化 `dijkstra` 算法:

```bash
 ./build/shortest-path-visulization-sdl --start 6,1 --target 6,14 dijkstra
```

可视化 `A*` 算法:

```bash
 ./build/shortest-path-visulization-sdl --start 6,1 --target 6,14 astar
```

可以按下 `ESC` 来退出.

可以按下 `Ctrl-S` 来截图, 会保存在 `screenshots` 目录.

也可以用 `--enable-screenshot` 来对每一帧截图 (会自动在找到最短路后及时退出自动截图, 免得截图太多).

#### 地图

1. 地图规格 `12x15`, 0 表示空白, 1 表示障碍物
2. 地图文件 `map.txt`
3. 支持 8 个方向移动 (选项 `-d4` 来只使用四个方向).

#### 颜色说明

1. 黑色: 障碍物
1. 浅蓝色: 待扩展的方格, 也常叫做 `open_list`, `open_set`, 或者优先级队列中的元素
1. 深蓝色: 已经探索过的方格 (也常叫做 `closed_list`, `closed_set`, visited 数组)
1. 绿色: 起点, 终点都是绿色. 探索到的最短路径是绿色
