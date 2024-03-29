#include <iostream>
#include <vector>
using namespace std;
class Solution {
   public:
    // dfs 函数计算 [i..m] 行的子矩阵中满足 <= s 的数组和的个数
    //
    //      +--------+
    //      |        |
    //    i +---[x]--+  选择 mat[i][j] = x
    //      |########|  递归下面的子矩阵
    //      +--------+
    //
    // 思路是: 逐列循环，逐行递归
    // 就是，逐列地稳住当前行的每个元素，拆解到下一行起点的更小的矩阵上去
    // s 是针对当前子矩阵要满足的阈值, 逐行减少
    // s0 是针对当前子矩阵的数组和的最小值, 也就是子矩阵各行的首元素之和, s
    // 必须要不小于 s0 才可以
    // k 仅用于提前终止递归, 发现大于等于 k 的时候就及时结束
    // c 是计数, 递归过程中全局维护, 作为一个引用
    void dfs(const vector<vector<int>>& mat, int i, int s, int s0, int k,
             int& c) {
        if (s < s0 || c >= k) return;  // 提前结束

        if (i >= mat.size()) {  // 越过最后一行，进行计数
            c++;
            return;
        }

        for (int j = 0; j < mat[i].size(); j++) {
            // 提前剪枝: 因为每行是上升的，当前行不满足后，后续也不必要在看
            if (s - mat[i][j] < s0 - mat[i][0]) return;

            // 选择 mat[i][j]，缩小阈值，向下递归
            dfs(mat, i + 1, s - mat[i][j], s0 - mat[i][0], k, c);

            // 提前剪枝: c 在 dfs 函数调用后可能会增加，满足 >=k 后提前退出
            if (c >= k) return;
        }
    }

    // 计算矩阵中不超过阈值 s 的数组和的个数
    int count(const vector<vector<int>>& mat, int s, int s0, int k) {
        int c = 0;
        dfs(mat, 0, s, s0, k, c);
        return c;
    }

    int kthSmallest(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();

        // 最大的数组和，是最后一列之和
        // 最小的是第一列之和
        int l = 0;
        int r = 0;

        for (int i = 0; i < m; i++) {
            r += mat[i][n - 1];
            l += mat[i][0];
        }
        int s0 = l;  // 行头和

        // 值域二分, 二分找满足 count(s) >= k 的下界
        while (l < r) {
            int s = (l + r) >> 1;
            if (count(mat, s, s0, k) >= k)
                r = s;
            else
                l = s + 1;
        }
        return l;
    }
};

int main(void) {
    vector<vector<int>> mat{
        {269,  355,  523,  524,  648,  789,  791,  953,  1017, 1206,
         1358, 1365, 1628, 1800, 1849, 1883, 2553, 2687, 2728, 3356,
         3418, 3566, 3626, 3629, 3741, 3773, 3840, 3848, 4068, 4404,
         4499, 4522, 4568, 4630, 4674, 4748, 4851},
        {13,   174,  250,  269,  302,  417,  440,  504,  800,  835,
         963,  1186, 1348, 1377, 1480, 1582, 2015, 2078, 2194, 2574,
         2585, 2656, 2785, 3281, 3526, 3774, 3868, 3890, 4114, 4184,
         4270, 4334, 4478, 4859, 4970, 4977, 4980},
        {29,   51,   199,  213,  214,  230,  264,  315,  391,  572,
         719,  1040, 1222, 1272, 1323, 1606, 1655, 1742, 2152, 2235,
         2557, 2590, 2706, 3149, 3296, 3497, 3585, 3642, 3784, 4105,
         4143, 4201, 4255, 4311, 4343, 4392, 4428},
        {159,  384,  829,  1249, 1437, 1572, 1779, 1828, 1872, 1906,
         1926, 2310, 2331, 2340, 2515, 2569, 2604, 2633, 2686, 2856,
         2935, 3009, 3146, 3183, 3381, 3588, 3714, 3770, 3927, 3970,
         4311, 4330, 4341, 4349, 4778, 4911, 4940},
        {424,  655,  674,  742,  756,  777,  833,  900,  1062, 1192,
         1365, 1521, 1524, 1587, 1634, 1915, 2089, 2161, 2286, 2342,
         2499, 2898, 2934, 2966, 3034, 3164, 3212, 3514, 3545, 3638,
         3691, 3777, 3845, 4166, 4468, 4585, 4901},
        {72,   306,  332,  474,  481,  733,  1386, 1502, 1746, 1760,
         1851, 1949, 1980, 2017, 2155, 2238, 2246, 2283, 2473, 2751,
         2908, 3078, 3101, 3582, 3588, 3642, 3944, 4003, 4005, 4239,
         4283, 4325, 4361, 4616, 4636, 4900, 4930},
        {276,  570,  573,  723,  849,  906,  919,  961,  1064, 1077,
         1547, 1611, 1704, 1884, 2066, 2074, 2133, 2158, 2232, 2377,
         2451, 2771, 3302, 3702, 3745, 3815, 3967, 4078, 4100, 4271,
         4426, 4553, 4616, 4622, 4836, 4861, 4975},
        {454,  548,  573,  759,  931,  955,  990,  1002, 1021, 1045,
         1217, 2077, 2176, 2269, 2446, 2776, 2782, 2784, 2839, 2843,
         2984, 3027, 3046, 3172, 3255, 3386, 3518, 3541, 3563, 3872,
         4085, 4258, 4322, 4420, 4634, 4677, 4741},
        {269,  305,  530,  649,  761,  896,  943,  954,  1124, 1311,
         1611, 1632, 1717, 1802, 1876, 1901, 2095, 2160, 2265, 2378,
         2711, 2729, 2757, 2891, 3135, 3276, 3358, 3367, 3484, 3713,
         3727, 3770, 3962, 3978, 4203, 4775, 4966},
        {14,   53,   433,  653,  1052, 1332, 1368, 1371, 1912, 1970,
         2009, 2069, 2120, 2141, 2238, 2242, 2252, 2507, 2508, 2591,
         2603, 2686, 2879, 2913, 3096, 3600, 3632, 3648, 3833, 3959,
         4041, 4058, 4382, 4527, 4571, 4686, 4962},
        {162,  187,  270,  712,  1121, 1243, 1398, 1481, 1507, 1810,
         1845, 1854, 1910, 2158, 2234, 2254, 2613, 2818, 2871, 3000,
         3014, 3075, 3092, 3295, 3673, 3706, 3845, 3905, 3910, 4320,
         4341, 4388, 4471, 4585, 4686, 4843, 4998},
        {29,   34,   169,  204,  250,  506,  619,  684,  714,  761,
         798,  801,  978,  1048, 1065, 1492, 1822, 1957, 1988, 2114,
         2241, 2589, 2922, 3004, 3031, 3228, 3231, 3262, 3411, 3680,
         3716, 3749, 3760, 3863, 4465, 4788, 4830},
        {38,   127,  391,  458,  548,  879,  988,  1202, 1215, 1410,
         1719, 1868, 2053, 2298, 2430, 2441, 2829, 2925, 3084, 3119,
         3274, 3388, 3504, 3666, 3883, 3903, 4044, 4117, 4203, 4208,
         4301, 4494, 4503, 4800, 4826, 4855, 4939},
        {45,   74,   261,  376,  454,  493,  500,  543,  567,  868,
         990,  1256, 1413, 1577, 1847, 1985, 1999, 2016, 2153, 2235,
         2370, 2498, 2948, 2993, 3036, 3316, 3446, 3613, 3838, 4147,
         4161, 4185, 4281, 4337, 4376, 4575, 4689},
        {10,   123,  302,  509,  594,  878,  1419, 1462, 1508, 1584,
         1691, 1694, 1746, 1918, 1931, 2086, 2138, 2480, 2665, 2678,
         2737, 2738, 2751, 2906, 2963, 3024, 3029, 3131, 3294, 3347,
         3747, 3887, 3918, 4265, 4310, 4828, 4900},
        {74,   259,  277,  309,  500,  500,  738,  824,  981,  982,
         1330, 1375, 1738, 1900, 1966, 2019, 2109, 2465, 2525, 2613,
         2687, 2789, 2816, 2955, 3568, 3621, 3837, 3874, 3989, 4039,
         4162, 4263, 4271, 4294, 4707, 4731, 4859},
        {2,    586,  875,  1022, 1112, 1117, 1280, 1325, 1455, 1614,
         1768, 1845, 2275, 2351, 2409, 2412, 2443, 2576, 2681, 2950,
         3019, 3176, 3239, 3282, 3400, 3571, 3686, 3757, 3868, 3885,
         3976, 4133, 4176, 4244, 4814, 4898, 4978},
        {118,  284,  351,  528,  598,  907,  975,  1185, 1366, 1401,
         1408, 1533, 1547, 1712, 1841, 1921, 2229, 2367, 2423, 2542,
         2657, 2906, 3032, 3262, 3288, 3371, 3420, 3515, 3732, 3904,
         3925, 4131, 4450, 4542, 4746, 4944, 4995},
        {38,   261,  382,  952,  990,  1239, 1299, 1304, 1307, 1510,
         1512, 1611, 1892, 1982, 2150, 2194, 2348, 2372, 2448, 2552,
         2747, 2777, 2827, 2903, 2975, 3163, 3266, 3720, 3884, 3916,
         4088, 4106, 4109, 4309, 4348, 4710, 4912},
        {40,   311,  557,  852,  931,  1017, 1075, 1131, 1227, 1313,
         1323, 1493, 1530, 1598, 1752, 1992, 2087, 2098, 2196, 2325,
         2334, 2379, 2466, 2503, 2869, 2910, 2939, 3457, 3571, 3719,
         3864, 4213, 4457, 4532, 4706, 4757, 4825},
        {256,  464,  602,  745,  936,  1022, 1118, 1421, 1725, 2000,
         2033, 2035, 2103, 2129, 2179, 2243, 2279, 2298, 2417, 2632,
         2921, 2991, 3035, 3201, 3267, 3436, 3456, 3588, 3671, 3866,
         3878, 4077, 4547, 4650, 4805, 4892, 4987},
        {64,   66,   138,  145,  399,  481,  624,  641,  796,  939,
         1050, 1666, 1923, 2000, 2307, 2479, 2592, 2780, 3011, 3063,
         3174, 3430, 3472, 3601, 3645, 3696, 3776, 3806, 4057, 4196,
         4208, 4365, 4459, 4520, 4596, 4721, 4906},
        {62,   102,  137,  324,  401,  557,  577,  804,  827,  854,
         908,  1273, 1409, 1656, 1756, 1794, 1818, 2175, 2508, 2558,
         2784, 3191, 3196, 3384, 3424, 3440, 3441, 3447, 3547, 3595,
         3740, 3899, 4097, 4306, 4515, 4660, 4817},
        {50,   314,  515,  535,  604,  608,  771,  871,  872,  924,
         937,  984,  1115, 1264, 1353, 1404, 1459, 1584, 1635, 1766,
         1954, 2009, 2448, 2509, 2782, 2895, 2934, 3043, 3179, 3392,
         3515, 3673, 3873, 4362, 4367, 4552, 4615},
        {116,  390,  449,  765,  770,  1054, 1216, 1249, 1351, 1530,
         1872, 2061, 2137, 2164, 2308, 2345, 2442, 2535, 2830, 2850,
         2975, 3310, 3378, 3433, 3461, 3694, 3698, 3787, 3854, 4048,
         4083, 4089, 4293, 4457, 4577, 4659, 4993},
        {182,  279,  500,  675,  700,  899,  966,  1045, 1058, 1112,
         1128, 1151, 1236, 1306, 1443, 1565, 1617, 1625, 1753, 1838,
         2360, 2629, 2913, 3054, 3262, 3408, 3641, 3644, 3830, 3863,
         4015, 4092, 4099, 4220, 4452, 4757, 4927},
        {184,  206,  289,  305,  462,  530,  914,  943,  1127, 1328,
         1424, 1571, 1572, 1953, 2163, 2293, 2472, 2559, 2822, 3115,
         3145, 3178, 3647, 3807, 3822, 3856, 3938, 3962, 4009, 4024,
         4252, 4407, 4425, 4640, 4684, 4709, 4778},
        {49,   78,   128,  215,  516,  749,  859,  906,  1187, 1325,
         1376, 1480, 1557, 1748, 1902, 1988, 2075, 2082, 2155, 2546,
         2664, 2668, 2784, 2809, 2855, 2936, 3377, 3512, 3597, 3848,
         4250, 4336, 4355, 4497, 4632, 4852, 4881},
        {60,   96,   295,  304,  363,  728,  764,  975,  1122, 1147,
         1195, 1210, 1347, 1497, 1580, 1605, 1653, 1841, 1949, 2094,
         2156, 2366, 2602, 2612, 2784, 3096, 3701, 3767, 3773, 4387,
         4395, 4458, 4592, 4737, 4820, 4917, 4953},
        {196,  273,  316,  390,  481,  519,  582,  782,  897,  975,
         1144, 1364, 1663, 1963, 2218, 2423, 2648, 2861, 2981, 3204,
         3373, 3385, 3550, 3774, 3937, 4160, 4181, 4222, 4257, 4307,
         4333, 4440, 4493, 4741, 4886, 4902, 4918},
        {34,   235,  467,  586,  650,  814,  824,  902,  1229, 1273,
         1436, 1726, 1869, 1941, 2159, 2175, 2294, 2311, 2789, 2863,
         2949, 3046, 3059, 3240, 3283, 3536, 3544, 3614, 3713, 4097,
         4136, 4159, 4446, 4464, 4595, 4663, 4947},
        {355,  614,  713,  796,  934,  982,  1043, 1222, 1396, 1463,
         1551, 1712, 1918, 2221, 2229, 2312, 2368, 2405, 2489, 2820,
         2966, 3058, 3081, 3155, 3556, 3686, 3695, 3767, 4217, 4283,
         4332, 4501, 4691, 4740, 4897, 4958, 4961},
        {191,  232,  395,  594,  860,  892,  992,  1022, 1317, 1717,
         1769, 1872, 2161, 2296, 2373, 2471, 2728, 2836, 2852, 2856,
         3035, 3054, 3077, 3164, 3450, 3509, 3532, 3643, 3707, 3737,
         4110, 4205, 4539, 4737, 4817, 4972, 4982}};

    Solution s;
    cout << s.kthSmallest(mat, 3) << endl;
    return 0;
}
