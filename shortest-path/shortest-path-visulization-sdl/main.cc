#include <bitset>
#include <cmath>
#include <cstring>
#include <fstream>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <tuple>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <argparse/argparse.hpp>
#include <spdlog/spdlog.h>

// 一些设置
const int GRID_SIZE = 40;                // 绘制每个网格 Pixel 的个数
const int M = 12;                        // 方格行数, 迭代变量 i
const int N = 15;                        // 方格列数, 迭代变量 j
const int WINDOW_HEIGHT = M * GRID_SIZE; // 窗口高度 600
const int WINDOW_WIDTH = N * GRID_SIZE;  // 窗口宽度 800
const int COST_UNIT = 10;                // 默认边长 10, 即代价单位, 水平和垂直方向代价
const int DIAGONAL_COST = 14;            // 对角成本是 14 (根号2 x 10)
const int inf = 0x3f3f3f3f;

// 网格地图: 0 表示空白方格 (白色), 1 表示有障碍物 (灰色)
int GRID_MAP[M][N]; // 12 x 15

// 坐标 (i, j)
using Point = std::pair<int, int>;

// 方向 和 成本
const std::pair<int, std::pair<int, int>> DIRECTIONS[8] = {
    // 前 4 个是水平和竖直
    {COST_UNIT, {-1, 0}},
    {COST_UNIT, {0, -1}},
    {COST_UNIT, {1, 0}},
    {COST_UNIT, {0, 1}},
    // 后 4 个是斜向
    {DIAGONAL_COST, {-1, -1}},
    {DIAGONAL_COST, {-1, 1}},
    {DIAGONAL_COST, {1, -1}},
    {DIAGONAL_COST, {1, 1}},
};

// 命令行选项
struct Options {
  // 地图文件地址
  std::string map_file_path = "map.txt";
  // 是否启用每一步的窗口截图, 保存在当前目录下的 screenshot 目录中
  bool enable_screenshot = false;
  // 保存窗口截图的目录, 文件的保存格式是 "{step-number}.PNG"
  // 不带 / 结尾
  std::string screenshot_directory = "screenshots";
  // 两帧之间的时间间隔
  int delay_ms = 50;
  // 要演示的算法
  std::string algorithm = "dijkstra";
  // 起始点, 终点
  Point start = {0, 0}, target = {M - 1, N - 1};
  // 是否只采用 4 方向, 默认是 8 方向
  bool use_4directions = false;
  // astar/lpastar 的启发式权重, 默认是 1 倍权重, 0 时退化到 dijkstra
  int astar_heuristic_weight = 1;
  // astar 的启发式方法, 可选两种: 曼哈顿距离 'manhattan' 和 欧式距离 'euclidean'
  // 对于 4 方向, 默认是曼哈顿; 对于 8 方向默认是欧式
  std::string astar_heuristic_method = "";
};

// 黑板, 算法要把寻路中的数据写到这里, Visualizer 可视化器会从这个黑板上去读.
struct Blackboard {
  // 是否计算结束?
  bool isStopped = false;
  // 历史考察过的点, 即 访问数组
  // 有的也叫做 closed_set
  bool visited[M][N];
  // 当前候选的待扩展的点的代价值
  // 不在待扩展列表中的, 标记 -1
  // 有的也叫做 open_set
  int exploring[M][N];
  // 从出发到目标的一条最短路径 (包含 start 和 target)
  std::vector<Point> path;
};

// 算法实现的虚类
class Algorithm {
public:
  virtual ~Algorithm() {} // makes unique_ptr happy
  // 初始化算法的准备项.
  // 参数 start 和 target 分别表示起点和终点
  // 最好支持重复执行(幂等)
  virtual void Setup(Blackboard &b, const Options &options) = 0;
  // 每一帧会被调用一次, 算作走一步.
  // 在这里, Update 要把结果写到黑板上.
  // 如果已经结束, 则返回 0, 没结束返回 -1, 失败返回 -2
  // 在结束返回 0 的时候必须要做 blackboard 上的最短路结果 path 被设置.
  virtual int Update(Blackboard &b) = 0;
  // 处理地图变化 (目前就是新增和删除障碍物点)
  // 如果算法支持增量计算, 就直接增量重新规划路径
  // 否则就需要完全重新计算, 相当于 Setup 要重新执行一次
  virtual void HandleMapChanges(Blackboard &b, const Options &options,
                                const std::vector<Point> &to_become_obstacles,
                                const std::vector<Point> &to_remove_obstacles) = 0;
};

// 主要的程序 Visualizer
class Visualizer {
public:
  Visualizer(const Options &options, Blackboard &b, Algorithm *algo);
  // 初始化工作, 包括 SDL 的各种初始化, 需要显式调用
  // 返回 0 表示成功
  int Init();
  // 启动主循环, 直到退出
  void Start();
  // 释放 SDL 的资源, 需要显式调用
  void Destroy();

protected:
  // 保存一次屏幕截图
  void saveScreenShot();
  // 绘制一帧的情况
  void draw();
  // 处理输入, 返回 -1 表示要退出
  int handleInputs();
  // 处理最短路径结果的播放状态
  void handleShortestPathPalyStates();
  // 处理地图变化
  void handleMapChanges();

private:
  const Options &options;
  Blackboard &blackboard;
  Algorithm *algo;
  // 拷贝一份 enable_screenshot (因为要修改)
  bool enable_screenshot = false;
  // SDL
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  // 帧号
  int seq = 0;
  // 绘制最短路时的临时状态
  // shortest_grids[i][j] 是 true 表示 (i,j) 是最短路结果的一员
  bool shortest_grids[M][N];
  // 当前播放到第几个最短路点?
  int shortest_grid_no = 0;
  // 第一次绘制完毕最短路后变为 true
  bool is_shortest_path_ever_rendered = false;
  // 需要新增成为障碍物的坐标点
  std::vector<Point> to_become_obstacles, to_remove_obstacles;
};

// 一个编码规则 i*N+j => 标号, 注意, 因为 N 比 M 大, 所以采用 N
inline int pack(int i, int j) { return i * N + j; }
inline int pack(const Point &p) { return p.first * N + p.second; }
inline int unpack_i(int x) { return x / N; }
inline int unpack_j(int x) { return x % N; }
static const int n = M * N; // 总的节点数量

class AlgorithmImplBase : public Algorithm {
protected:
  // (距离 OR 边权, 节点号)
  using P = std::pair<int, int>;
  // 起始点标号 s, 结束点标号 t
  int s, t;

  // 一些 Utils (可重载)

  // 设置黑板 (清理) (允许重复执行)
  virtual void setupBlackboard(Blackboard &b);
};

class AlgorithmImplUtilMixin : public AlgorithmImplBase {
protected:
  // edges[x] => {{w, y}}  边权,邻接点
  std::vector<std::vector<P>> edges;
  // from[x] 保存 x 最短路的上一步由哪个节点而来
  // 默认是 inf, 如果最终算法结束仍然是 inf, 则表示算法失败
  int from[n];

  // 一些 Utils (可重载)

  // 初始化建图 (允许重复执行)
  virtual void setupEdges(bool use_4directions = false);
  // 收集最短路结果
  virtual void buildShortestPathResult(Blackboard &b);
};

// 算法实现 - dijkstra
class AlgorithmImplDijkstra : public AlgorithmImplUtilMixin {
public:
  virtual void Setup(Blackboard &b, const Options &options) override;
  virtual int Update(Blackboard &b) override;
  virtual void HandleMapChanges(Blackboard &b, const Options &options,
                                const std::vector<Point> &to_become_obstacles,
                                const std::vector<Point> &to_remove_obstacles) override;

protected:
  // 小根堆, 实际是按第一项 f[y] 作为比较
  std::priority_queue<P, std::vector<P>, std::greater<P>> q;
  // f[x] 保存出发点 s 到 x 的最短路
  int f[n];
};

// 算法实现 -- A star
// 事实上, A star 是一种优化的 dijkstra
class AlgorithmImplAStar : public AlgorithmImplDijkstra {
public:
  // Setup 其实可以直接复用 dijkstra 的
  void Setup(Blackboard &b, const Options &options) override;
  int Update(Blackboard &b) override;
  void HandleMapChanges(Blackboard &b, const Options &options, const std::vector<Point> &to_become_obstacles,
                        const std::vector<Point> &to_remove_obstacles) override;

private:
  int heuristic_weight = 1;
  int heuristic_method = 1; // 1 曼哈顿, 2 欧式
  // 计算节点 y 到目标 t 的未来预估代价, 曼哈顿距离
  int future_cost(int y, int t);
};

// 算法实现 - LPAstar
class AlgorithmImplLPAStar : public AlgorithmImplBase {
public:
  void Setup(Blackboard &b, const Options &options) override;
  int Update(Blackboard &b) override;
  void HandleMapChanges(Blackboard &b, const Options &options, const std::vector<Point> &to_become_obstacles,
                        const std::vector<Point> &to_remove_obstacles) override;

private:
  int heuristic_weight = 1;
  int heuristic_method = 1; // 1 曼哈顿, 2 欧式
  // 默认情况下, 传播是按照估价终止的
  // 如果这个 force_stop_until_target 设置到 true
  // 那么会强制传播到目标才终止(或者q空的时候).
  // 这个用来预防不良的, 高估的估价函数 (比如8方向的情况下的曼哈顿函数)
  bool force_stop_until_target = false;
  // { 标号, 边权 }
  using P = std::pair<int, int>;
  // { 键值k1, 键值k2, 标号 }
  using K = std::tuple<int, int, int>;
  // 前继 {标号, 边权}
  std::vector<std::vector<P>> pred;
  // 后继
  std::vector<std::vector<int>> succ;

  // g 值: 起点到当前点的实际代价 (旧值)
  // rhs 值: 起点到当前点的实际代价的临时值, 由前继节点更新而来
  int g[n], rhs[n];
  // 优先级队列 (因为要支持 update 操作, 所以用 map)
  std::map<K, int> q;

  // 启发函数
  int h(int x);
  // 计算 queue 的 key 的函数
  K k(int x);
  // 初始化
  void init();
  // 更新节点
  void update(int x);
  // 收集最短路, 结果存储在入参 path (必须是空的)
  // 收集失败, 返回 -1, 否则返回 0
  int collect(std::vector<int> &path);
  // 新增障碍物
  void add_obstacle(int i, int j);
  // 清理障碍物
  void remove_obstacle(int i, int j);
};

// 算法 Handler 构造器表格, 每新增一个算法, 需要到这里注册一下
std::unordered_map<std::string, std::function<std::unique_ptr<Algorithm>()>> AlgorithmMakers = {
    {"dijkstra", []() { return std::make_unique<AlgorithmImplDijkstra>(); }},
    {"astar", []() { return std::make_unique<AlgorithmImplAStar>(); }},
    {"lpastar", []() { return std::make_unique<AlgorithmImplLPAStar>(); }},
};

// 一个切割类似 "x,y" 的字符串到 Point 的 util 函数
Point ParsePointString(const std::string &s);

// 检查点是否在地图中
inline bool ValidatePoint(const Point &p) {
  return p.first >= 0 && p.first < M && p.second >= 0 && p.second < N;
}
inline bool ValidatePoint(int x, int y) { return x >= 0 && x < M && y >= 0 && y < N; }

// 检查选项 start 和 target, 成功返回 0
int ValidateStartAndTarget(const Options &options) {
  if (!ValidatePoint(options.start)) {
    spdlog::error("非法的 start {},{}", options.start.first, options.start.second);
    return -1;
  }
  if (!ValidatePoint(options.target)) {
    spdlog::error("非法的 target {},{}", options.target.first, options.target.second);
    return -1;
  }
  if (GRID_MAP[options.start.first][options.start.second]) {
    spdlog::error("start 选在了障碍物上");
    return -1;
  }
  if (GRID_MAP[options.target.first][options.target.second]) {
    spdlog::error("target 选在了障碍物上");
    return -1;
  }
  return 0;
}

// 加载地图, 成功则返回 0
int LoadMap(const std::string &filepath);

int main(int argc, char *argv[]) {
  // 解析命令行参数到给定的 options 结构.
  Options options;
  argparse::ArgumentParser program("shortest-path-visulization-sdl");
  program.add_argument("-m", "--map")
      .help("地图文件")
      .default_value(std::string("map.txt"))
      .store_into(options.map_file_path);
  program.add_argument("--enable-screenshot")
      .help("是否启用每一步的窗口截图")
      .default_value(false)
      .store_into(options.enable_screenshot);
  program.add_argument("--screenshot-directory")
      .help("截图文件的保存目录")
      .default_value(std::string("screenshots"))
      .store_into(options.screenshot_directory);
  program.add_argument("-d", "--delay-ms")
      .help("帧之间的毫秒间隔")
      .default_value(50)
      .store_into(options.delay_ms);
  program.add_argument("algorithm")
      .help("算法名称")
      .metavar("ALGORITHM")
      .choices("dijkstra", "astar", "lpastar")
      .default_value(std::string("dijkstra"))
      .store_into(options.algorithm);
  program.add_argument("-d4", "--use-4-directions")
      .help("是否只采用4方向,默认是8方向")
      .default_value(false)
      .store_into(options.use_4directions);
  program.add_argument("-astar-w", "--astar-heuristic-weight")
      .help("AStar/LPAStar 算法的启发式未来估价的权重倍数, 自然数")
      .default_value(1)
      .store_into(options.astar_heuristic_weight);
  program.add_argument("-astar-m", "--astar-heuristic-method")
      .help(
          "AStar/LPAStar 算法的启发式方法, 曼哈顿 manhattan 或者 欧式距离 euclidean; 对于4方向默认是曼哈顿, "
          "8方向时默认是欧式")
      .default_value(std::string(""))
      .store_into(options.astar_heuristic_method);
  program.add_argument("-s", "--start").help("起始点").default_value("0,0");
  program.add_argument("-t", "--target").help("起始点").default_value("11,14");

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception &e) {
    spdlog::error(e.what());
    std::exit(1);
  }

  // 加载地图
  if (LoadMap(options.map_file_path) != 0)
    return -1;
  spdlog::info("地图加载成功 ({})", options.map_file_path);

  // 处理起始点 和 重点
  options.start = ParsePointString(program.get<std::string>("--start"));
  options.target = ParsePointString(program.get<std::string>("--target"));
  if (ValidateStartAndTarget(options) != 0)
    return -1;

  spdlog::info("支持的方向数量 => {}", options.use_4directions ? 4 : 8);

  // 处理启发式函数的选用
  if (options.astar_heuristic_method.empty()) {
    if (options.use_4directions) {
      spdlog::info("默认对于4方向移动时,选用曼哈顿距离作为启发函数");
      options.astar_heuristic_method = "manhattan";
    } else {
      spdlog::info("默认对于8方向移动时,选用欧式距离作为启发函数");
      options.astar_heuristic_method = "euclidean";
    }
  }

  // 选用算法
  if (AlgorithmMakers.find(options.algorithm) == AlgorithmMakers.end()) {
    spdlog::error("找不到算法的 handler:  {}", options.algorithm);
    std::exit(1);
  }
  // 构造 algorithm handler
  auto algo = AlgorithmMakers[options.algorithm]();
  spdlog::info("选用了算法 {}", options.algorithm);
  // 构造 Visualizer
  Blackboard b;
  Visualizer visualizer(options, b, algo.get());
  // 启动 Visualizer
  if (visualizer.Init() != 0)
    return -1;
  visualizer.Start();
  visualizer.Destroy();
  return 0;
}

Point ParsePointString(const std::string &s) {
  std::string sx, sy;
  int flag = 0; // 0 时输出给 sx, 1 时输出给 sy
  for (const auto ch : s) {
    if (ch == ',')
      flag = 1; // 切换到输入给 sy
    else
      flag == 0 ? sx.push_back(ch) : sy.push_back(ch);
  }
  if (!flag)
    return {-1, -1}; // Invalid
  return {std::stoi(sx), std::stoi(sy)};
}

int LoadMap(const std::string &filepath) {
  std::fstream f;
  f.open(filepath);
  std::string line;
  int x = 0;
  while (std::getline(f, line)) {
    // 检查行数
    if (x >= M) {
      spdlog::error("地图: 必须恰好 {} 行", M);
      f.close();
      return -1;
    }
    // 检查每行字符个数
    if (line.size() != N + N - 1) { // 算进去空格
      spdlog::error("地图: 每行必须是 {} 个 0 或者 1, 目前第 {} 行是 {} 个字符 (包含空格计算在内)", N, x,
                    line.size());
      f.close();
      return -1;
    }
    // 读取每个字符
    int y = 0;
    for (auto ch : line) {
      if (ch == ' ')
        continue;
      int value = static_cast<int>(ch - '0');
      if (value != 0 && value != 1) {
        spdlog::error("地图: 每个字符要么是0要么是1, 发现了一个 '{}'", ch);
        f.close();
        return -2;
      }
      GRID_MAP[x][y++] = value;
    }
    x++;
  }
  f.close();
  return 0;
}

/////////////////////////////////////
/// 实现 Visualizer
/////////////////////////////////////

Visualizer::Visualizer(const Options &options, Blackboard &b, Algorithm *algo)
    : options(options), blackboard(b), algo(algo), enable_screenshot(options.enable_screenshot) {
  memset(shortest_grids, 0, sizeof(shortest_grids));
}

int Visualizer::Init() {
  // 初始化 SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    spdlog::error("SDL 初始化错误 {}", SDL_GetError());
    return -1;
  }
  // 初始化 SDL_image
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    spdlog::error("SDL_image 初始化错误: {}", IMG_GetError());
    SDL_Quit();
    return -2;
  }
  // 创建窗口
  window = SDL_CreateWindow("shortest-path-visulization-sdl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    spdlog::error("无法创建窗口: {}", SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    return -3;
  }

  // 创建渲染器
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == nullptr) {
    spdlog::error("创建渲染器失败: {}", SDL_GetError());
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return -1;
  }
  spdlog::info("初始化 SDL 成功");

  // 初始化算法设置
  algo->Setup(blackboard, options);

  spdlog::info("初始化算法成功");
  return 0;
}

void Visualizer::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}

void Visualizer::Start() {
  while (true) {
    // 处理输入
    if (handleInputs() == -1)
      break;

    // 更新算法步骤
    seq++;

    // 地图是否有变化?
    handleMapChanges();

    // 继续进行一步 Update
    int code = -1;
    if (!blackboard.isStopped) { // 只有没有结束时才执行一次 Update
      code = algo->Update(blackboard);
      if (code == 0) {
        spdlog::info("算法已结束, Ctrl-C 即可退出");
      } else if (code == -2) {
        spdlog::info("算法已失败, Ctrl-C 即可退出");
      }
    } else {
      // 否则, 需要设定当前需要绘制的最短路径点
      handleShortestPathPalyStates();
    }
    // 清理屏幕,并绘制一次
    // 背景颜色: 白色
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    draw();
    SDL_RenderPresent(renderer);
    if ((code == -2 || is_shortest_path_ever_rendered) && enable_screenshot) {
      enable_screenshot = false;
      spdlog::info("算法已结束, 已关闭自动截图");
    } else if ((!enable_screenshot && options.enable_screenshot) && !is_shortest_path_ever_rendered) {
      // 自动恢复录制
      enable_screenshot = true;
      spdlog::info("自动恢复截图");
    }
    // 自动截图一次
    if (enable_screenshot) {
      saveScreenShot();
    }
    // 睡眠 (不严格的 delay)
    SDL_Delay(options.delay_ms);
  }
}

void Visualizer::handleMapChanges() {
  for (const auto &p : to_become_obstacles)
    GRID_MAP[p.first][p.second] = 1;
  for (const auto &p : to_remove_obstacles)
    GRID_MAP[p.first][p.second] = 0;
  if (to_become_obstacles.size() > 0 || to_remove_obstacles.size() > 0) {
    algo->HandleMapChanges(blackboard, options, to_become_obstacles, to_remove_obstacles);
    // 注意清理当前最短路的播放
    memset(shortest_grids, 0, sizeof shortest_grids);
    shortest_grid_no = 0;
    is_shortest_path_ever_rendered = false;
  }
  to_become_obstacles.clear();
  to_remove_obstacles.clear();
}

int Visualizer::handleInputs() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      return -1;
    case SDL_KEYDOWN:
      // ESC 退出
      if (e.key.keysym.sym == SDLK_ESCAPE) {
        spdlog::info("监听到 ESC : 即将退出...");
        return -1;
      }
      // Ctrl-C 退出
      if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
        spdlog::info("监听到 Ctrl-C : 即将退出...");
        return -1;
      }
      // Ctrl-S 手动截图一次
      if (e.key.keysym.sym == SDLK_s && SDL_GetModState() & KMOD_CTRL) {
        spdlog::info("监听到 Ctrl-S : 即将截图一次...");
        saveScreenShot();
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      // 单击翻转地图元素, 新增或者删除一个障碍物, 更新地图
      if (e.button.button == SDL_BUTTON_LEFT) {
        Point p{e.button.y / GRID_SIZE, e.button.x / GRID_SIZE};
        int flag = 0;
        if (GRID_MAP[p.first][p.second]) { // 消除障碍物
          to_remove_obstacles.push_back(p);
        } else { // 新增障碍物
          to_become_obstacles.push_back(p);
          flag = 1;
        }
        spdlog::info("监听到鼠标左键点击 {},{}, {}一个障碍物", p.first, p.second, flag ? "新增" : "消除");
      }
      break;
    }
  }
  return 0;
}

void Visualizer::draw() {
  // 绘制方格 (x,y) 表示绘制坐标, (i, j) 表示方格坐标
  for (int i = 0, y = 0; i < M; i++, y += GRID_SIZE) {
    for (int j = 0, x = 0; j < N; j++, x += GRID_SIZE) {
      // 正方形 rect, 内侧是 inner (边框宽度 1)
      SDL_Rect rect = {x, y, GRID_SIZE, GRID_SIZE};
      SDL_Rect inner = {x + 1, y + 1, GRID_SIZE - 2, GRID_SIZE - 2};
      // 绘制外层正方形, 边框是黑色
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderDrawRect(renderer, &rect);
      // 选用内层正方形的填充颜色
      if (GRID_MAP[i][j] == 1)
        // 障碍物: 灰色
        SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
      else if ((i == options.start.first && j == options.start.second) ||
               (i == options.target.first && j == options.target.second))
        // 起始点: 绿色
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      else if (shortest_grids[i][j])
        // 最短路径点: 绿色
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      else if (blackboard.visited[i][j])
        // 访问过的路径点: 蓝色
        SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
      else if (blackboard.exploring[i][j] >= 0)
        // 将要扩展的点: 浅蓝色
        SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
      else
        // 默认是白色
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      // 绘制内侧正方形
      SDL_RenderFillRect(renderer, &inner);
    }
  }
}

void Visualizer::handleShortestPathPalyStates() {
  if (blackboard.path.empty())
    return;
  // 播放到下一个路径点, 到尾部则循环
  if (shortest_grid_no == blackboard.path.size() - 1) {
    shortest_grid_no = 0;
    memset(shortest_grids, 0, sizeof shortest_grids);
    is_shortest_path_ever_rendered = true;
  } else {
    shortest_grid_no++;
  }
  auto &p = blackboard.path[shortest_grid_no];
  shortest_grids[p.first][p.second] = true;
}

void Visualizer::saveScreenShot() {
  SDL_Surface *saveSurface = nullptr;
  SDL_Surface *infoSurface = SDL_GetWindowSurface(window);
  if (infoSurface == nullptr) {
    spdlog::warn("saveScreenShot: 创建 surface 失败 {}", SDL_GetError());
    return;
  }

  auto *pixels = new unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
  if (pixels == nullptr) {
    spdlog::warn("saveScreenShot: Unable to allocate memory for screenshot pixel data buffer!");
    return;
  }

  if (SDL_RenderReadPixels(renderer, nullptr, infoSurface->format->format, pixels,
                           infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
    spdlog::warn("saveScreenShot: 无法从 renderer 读取像素数据 {}", SDL_GetError());
    delete[] pixels;
    return;
  }

  saveSurface = SDL_CreateRGBSurfaceFrom(
      pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel,
      infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask,
      infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
  if (saveSurface == nullptr) {
    spdlog::warn("saveScreenShot: 无法创建 saveSurface: {}", SDL_GetError());
    delete[] pixels;
    return;
  }

  auto filename = options.screenshot_directory + "/" + std::to_string(seq) + ".PNG";

  if (IMG_SavePNG(saveSurface, filename.c_str()) != 0) {
    spdlog::warn("saveScreenShot: 保存截图失败 {} => {}", filename, IMG_GetError());
    SDL_FreeSurface(saveSurface);
    delete[] pixels;
    return;
  }

  spdlog::info("saveScreenShot: 保存截图成功 => {}", filename);

  SDL_FreeSurface(saveSurface);
  delete[] pixels;
  return;
}

/////////////////////////////////////
/// 实现 AlgorithmImplBase
/////////////////////////////////////

void AlgorithmImplBase::setupBlackboard(Blackboard &b) {
  // 清理黑板
  b.isStopped = false;
  memset(b.visited, 0, sizeof(b.visited));
  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++)
      b.exploring[i][j] = -1;
  b.path.clear();
}

/////////////////////////////////////
/// 实现 AlgorithmImplUtilMixin
/////////////////////////////////////

void AlgorithmImplUtilMixin::setupEdges(bool use_4directions) {
  memset(from, 0x3f, sizeof(from));
  // 构造 edges
  edges.clear();
  edges.resize(n);
  // 4 方向是取前 4 个.
  int K = use_4directions ? 4 : 8;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (GRID_MAP[i][j]) // 不可从障碍物出发
        continue;
      int x = pack(i, j);
      // 都可以走, 除非是有障碍物
      for (int k = 0; k < K; k++) {
        const auto &[w, d] = DIRECTIONS[k];
        auto i1 = i + d.first, j1 = j + d.second;
        // 不可到达障碍物, 不可越过边界
        if (ValidatePoint(i1, j1) && !GRID_MAP[i1][j1])
          edges[x].push_back({w, pack(i1, j1)});
      }
    }
  }
}

void AlgorithmImplUtilMixin::buildShortestPathResult(Blackboard &b) {
  std::vector<int> path;
  path.push_back(t);
  int x = t;
  while (x != s) {
    x = from[x];
    path.push_back(x);
  }
  // 反向求最短路
  for (int i = path.size() - 1; i >= 0; --i) {
    auto x = path[i];
    b.path.push_back({unpack_i(x), unpack_j(x)});
  }
  b.isStopped = true;
}

/////////////////////////////////////
/// 实现 Dijkstra
/////////////////////////////////////

void AlgorithmImplDijkstra::Setup(Blackboard &b, const Options &options) {
  // 清理黑板
  setupBlackboard(b);
  // 建图
  setupEdges(options.use_4directions);
  // 清理 f, 到无穷大
  memset(f, 0x3f, sizeof(f));
  // 清理 queue
  while (q.size())
    q.pop();
  // 设置初始坐标
  s = pack(options.start);
  f[s] = 0;
  from[s] = s;
  q.push({f[s], s});
  // 设置结束
  t = pack(options.target);
}

int AlgorithmImplDijkstra ::Update(Blackboard &b) {
  while (!q.empty()) {
    auto [_, x] = q.top();
    q.pop();
    // 访问过的要忽略
    int i = unpack_i(x), j = unpack_j(x);
    // x 已经不算待扩展了, 恢复到 -1
    b.exploring[i][j] = -1;
    if (b.visited[i][j])
      continue;
    b.visited[i][j] = true;
    // 到达目标, 及时退出 (将 return 0)
    if (t == x)
      break;
    // 添加邻居节点进入待扩展
    for (const auto &[w, y] : edges[x]) {
      if (f[y] > f[x] + w) {
        f[y] = f[x] + w;
        from[y] = x;
        q.push({f[y], y});
        b.exploring[unpack_i(y)][unpack_j(y)] = f[y];
      }
    }
    // 每次 Update 只考察一个点, 不算结束
    return -1;
  }
  // 已经结束,需要计算最短路
  if (from[t] == inf)
    return -2; // 失败
  buildShortestPathResult(b);
  return 0;
}

void AlgorithmImplDijkstra::HandleMapChanges(Blackboard &b, const Options &options,
                                             const std::vector<Point> &to_become_obstacles,
                                             const std::vector<Point> &to_remove_obstacles) {
  if (to_become_obstacles.empty() && to_remove_obstacles.empty())
    return;
  // dijkstra 不支持增量计算, 只可以重新计算
  spdlog::info("dijkstra 算法不支持增量计算, 将重新计算");
  Setup(b, options);
}

/////////////////////////////////////
/// 实现 AStar
/////////////////////////////////////

void AlgorithmImplAStar::Setup(Blackboard &b, const Options &options) {
  heuristic_weight = options.astar_heuristic_weight;
  if (options.astar_heuristic_method == "euclidean") {
    heuristic_method = 2;
    spdlog::info("astar 选用欧式距离");
  } else {
    heuristic_method = 1;
    spdlog::info("astar 选用曼哈顿距离");
  }
  // 复用 dijkstra 的 Setup 即可
  AlgorithmImplDijkstra::Setup(b, options);
}

int AlgorithmImplAStar ::Update(Blackboard &b) {
  while (!q.empty()) {
    auto [_, x] = q.top();
    q.pop();
    // 访问过的要忽略
    int i = unpack_i(x), j = unpack_j(x);
    // x 已经不算待扩展了, 恢复到 -1
    b.exploring[i][j] = -1;
    if (b.visited[i][j])
      continue;
    b.visited[i][j] = true;
    // 到达目标, 及时退出 (将 return 0)
    if (t == x)
      break;
    // 添加邻居节点进入待扩展
    for (const auto &[w, y] : edges[x]) {
      auto g = f[x] + w;                    // s 到 y 的实际代价
      auto h = future_cost(y, t);           // y 到目标的未来代价的估计
      auto cost = g + heuristic_weight * h; // 总代价 = 实际 + 权重*未来
      if (f[y] > g) {                       // 如果当前实际代价比之前计算的更优
        f[y] = g;                           // 维护 y 的实际代价
        b.exploring[unpack_i(y)][unpack_j(y)] = f[y];
        q.push({cost, y});
        from[y] = x; // 最短路来源
      }
    }
    return -1;
  }
  // 每次 Update 只考察一个点, 不算结束
  if (from[t] == inf)
    return -2; // 失败
  // 已经结束,需要计算最短路
  buildShortestPathResult(b);
  return 0;
}

int AlgorithmImplAStar::future_cost(int y, int t) {
  auto ti = unpack_i(t), tj = unpack_j(t);
  // y 的坐标
  auto yi = unpack_i(y), yj = unpack_j(y);
  // 注意乘以 10
  // 对于 y 的未来代价预估, 曼哈顿距离
  if (heuristic_method == 1)
    return (abs(ti - yi) + abs(tj - yj)) * COST_UNIT;
  // 欧式距离
  return std::floor(std::hypot(abs(ti - yi), abs(tj - yj))) * COST_UNIT;
}

void AlgorithmImplAStar::HandleMapChanges(Blackboard &b, const Options &options,
                                          const std::vector<Point> &to_become_obstacles,
                                          const std::vector<Point> &to_remove_obstacles) {
  if (to_become_obstacles.empty() && to_remove_obstacles.empty())
    return;
  // astar 不支持增量计算, 只可以重新计算
  spdlog::info("astar 算法不支持增量计算, 将重新计算");
  Setup(b, options);
}

/////////////////////////////////////
/// 实现 LPAstar
/////////////////////////////////////

int AlgorithmImplLPAStar::h(int x) {
  // 方格内的坐标
  auto ti = unpack_i(t), tj = unpack_j(t);
  auto xi = unpack_i(x), xj = unpack_j(x);
  // 曼哈顿
  if (heuristic_method == 1)
    return (abs(ti - xi) + abs(tj - xj)) * COST_UNIT;
  // 欧式距离
  return std::floor(std::hypot(abs(ti - xi), abs(tj - xj))) * COST_UNIT;
}

AlgorithmImplLPAStar::K AlgorithmImplLPAStar::k(int x) {
  return {std::min(g[x], rhs[x]) + heuristic_weight * h(x), std::min(g[x], rhs[x]), x};
}

void AlgorithmImplLPAStar::init() {
  memset(g, 0x3f, sizeof g);
  memset(rhs, 0x3f, sizeof rhs);
  rhs[s] = 0;
  q.insert({k(s), s});
}

void AlgorithmImplLPAStar::update(int x) {
  // 其实点不可更新, g[s] 和 rhs[s] 恒等于 0
  if (x == s)
    return;
  // 从队列中删除
  q.erase(k(x));
  // 根据 x 的前继节点的实际代价 g, 加上边权 w, 取最小.
  // 来获取 x 处的新代价 rhs
  rhs[x] = inf;
  for (auto [y, w] : pred[x])
    rhs[x] = std::min(rhs[x], g[y] + w);
  // 如果 x 的 g 和 rhs 没有对齐, 则重新加入队列等待更新
  if (g[x] != rhs[x])
    q.insert({k(x), x});
}

int AlgorithmImplLPAStar::collect(std::vector<int> &path) {
  path.push_back(t);
  // st 用来判环, 如果检测到, 则即时终止, 以防死循环
  std::bitset<n> st;
  int x = t;
  while (x != s) {
    if (st[x]) {
      spdlog::warn("得到的路径存在环, 可能启发函数设计不良存在高估, 将强制继续传播一轮以恢复");
      force_stop_until_target = true;
      return -1;
    }
    st[x] = 1;
    // 找到 g + w 最小的前继邻居
    int y1 = inf;
    int g1 = inf;
    for (const auto &[y, w] : pred[x]) {
      if (g1 >= g[y] + w) {
        g1 = g[y] + w;
        y1 = y;
      }
    }
    if (y1 >= inf)
      break;
    x = y1;
    path.push_back(x);
  }
  // 原地反转
  for (int l = 0, r = path.size() - 1; l < r; l++, r--)
    std::swap(path[l], path[r]);
  return 0;
}

void AlgorithmImplLPAStar::add_obstacle(int i, int j) {
  int x = pack(i, j);
  // 到达 x 的边权全部无穷大
  for (auto &[y, w] : pred[x])
    w = inf;

  // x 到达后继邻居的边权全部无穷大
  for (auto y : succ[x])
    for (auto &[x1, w] : pred[y])
      if (x1 == x)
        w = inf;

  // update x 和 后继邻居
  // 原则是:  update 边权有变化的边的末端节点
  update(x);
  for (auto y : succ[x])
    update(y);
}

void AlgorithmImplLPAStar::remove_obstacle(int i, int j) {
  int x = pack(i, j);

  // 到达 x 的边权全部恢复
  for (auto &[y, w] : pred[x]) {
    int i1 = unpack_i(y), j1 = unpack_j(y);
    int di = i - i1, dj = j - j1;
    if (di != 0 && dj != 0) { // 斜边邻居
      w = DIAGONAL_COST;
    } else { // 水平竖直邻居
      w = COST_UNIT;
    }
  }
  // x 到达后继邻居的边权全部恢复
  for (auto y : succ[x]) { // 对每个 x 的后继 y
    int i1 = unpack_i(y), j1 = unpack_j(y);
    int di = i - i1, dj = j - j1;
    for (auto &[x1, w] : pred[y])
      // 找到 y 的前继 x 的边权 w
      if (x1 == x) {
        if (di != 0 && dj != 0) { // 斜边邻居
          w = DIAGONAL_COST;
        } else { // 水平竖直邻居
          w = COST_UNIT;
        }
      }
  }
  // update x 和 后继邻居
  // 原则是:  update 边权有变化的边的末端节点
  update(x);
  for (auto y : succ[x])
    update(y);
}

// 支持增量计算
void AlgorithmImplLPAStar::HandleMapChanges(Blackboard &b, const Options &options,
                                            const std::vector<Point> &to_become_obstacles,
                                            const std::vector<Point> &to_remove_obstacles) {
  if (to_become_obstacles.empty() && to_remove_obstacles.empty())
    return;
  spdlog::info("LAPStar 支持增量计算, 将进行增量寻路修正");
  // 清理一下黑板  (以完全重新渲染)
  setupBlackboard(b);
  // 新增障碍物
  for (const auto &p : to_become_obstacles) {
    add_obstacle(p.first, p.second);
  }
  // 移除障碍物
  for (const auto &p : to_remove_obstacles) {
    remove_obstacle(p.first, p.second);
  }
  spdlog::info("LAPStar 增量修改完毕");
}

void AlgorithmImplLPAStar::Setup(Blackboard &b, const Options &options) {
  heuristic_weight = options.astar_heuristic_weight;
  if (heuristic_weight > 1) {
    spdlog::warn("选用 LAPStar 时的启发权重设置为 > 1, 这可能会引起代价高估, 导致增量计算不充分");
  }
  if (options.astar_heuristic_method == "euclidean") {
    heuristic_method = 2;
    spdlog::info("LPAStar 选用欧式距离");
  } else {
    heuristic_method = 1;
    spdlog::info("LPAStar 选用曼哈顿距离");
    if (!options.use_4directions)
      spdlog::warn("LPAStar 在8方向上采用曼哈顿可能会引起代价高估");
  }
  // 清理黑板
  setupBlackboard(b);
  // 建图
  pred.clear();
  succ.clear();
  pred.resize(n);
  succ.resize(n);
  // 初始化 pred 和 succ
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int x = pack(i, j);
      int di_max = options.use_4directions ? 4 : 8;
      for (int di = 0; di < di_max; di++) {
        const auto &[w, d] = DIRECTIONS[di];
        auto i1 = i + d.first, j1 = j + d.second;
        auto y = pack(i1, j1);
        if (ValidatePoint(i1, j1)) {
          // 现在考虑的边 (x => y)
          // 后继
          succ[x].push_back(y);
          // 前继, 从障碍物出发或者到达障碍物都算作无穷大的边权
          pred[y].push_back({x, (GRID_MAP[i][j] || GRID_MAP[i1][j1]) ? inf : w});
        }
      }
    }
  }

  // 清理 q
  q.clear();
  // 设置初始坐标
  s = pack(options.start);
  // 设置结束点
  t = pack(options.target);
  // 初始化
  init();
}

int AlgorithmImplLPAStar::Update(Blackboard &b) {
  while (q.size()) {
    auto it = q.begin();
    if ((!force_stop_until_target) && it->first >= k(t) && rhs[t] == g[t])
      break;

    // 弹出队头
    int x = it->second;
    q.erase(it);

    int i = unpack_i(x), j = unpack_j(x);
    b.visited[unpack_i(x)][unpack_j(x)] = true;

    if (g[x] > rhs[x]) {
      // 局部过一致
      g[x] = rhs[x];
    } else {
      // 局部欠一致, 通常说明新增了障碍物
      g[x] = inf;
      update(x);
    }
    // 向后继节点传播, 更新邻域
    for (auto y : succ[x]) {
      update(y);
      b.exploring[unpack_i(y)][unpack_j(y)] = g[y];
    }

    // 无论如何, 已经扩散到目标, 都可以终止
    if (x == t)
      break;

    // 每一次 Update 都只考察一个点, 不算结束
    return -1;
  }

  // 已经结束, 需要计算最短路
  if (g[t] >= inf)
    return -2; // 失败

  std::vector<int> path;
  if (collect(path) != 0)
    // 收集失败, 继续重试 Update
    return -1;
  // 收集成功, 重置 force_stop_until_target
  force_stop_until_target = false;
  // 输出到 blackboard
  b.path.clear();
  for (auto x : path)
    b.path.push_back({unpack_i(x), unpack_j(x)});
  b.isStopped = true;
  return 0;
}
