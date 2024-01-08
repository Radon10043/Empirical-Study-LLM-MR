#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.h"

using namespace std;

vector<SpwikiInput> gen_tcs_randomly() {
    vector<SpwikiInput> tcs;
    mt19937 rng(random_device{}());

    /* clang-format off */
    uniform_int_distribution<int> dist_v(2, 10),    /* 顶点数量范围 */
                                  dist_w(1, 1000);  /* 边权重范围 */
    /* clang-format on */

    /* 构建测试用例 */
    for (int i = 0; i < TESTCASE_NUM; i++) {
        int num_v = dist_v(rng);
        vector<vector<int>> edges;
        for (int s = 0; s < num_v; s++)
            for (int d = s + 1; d < num_v; d++)
                edges.push_back({s, d, dist_w(rng)});

        uniform_int_distribution<int> dist_src(0, num_v - 1), dist_dst(0, num_v - 1);
        int src = dist_src(rng), dst = dist_dst(rng);
        while (dst == src)
            dst = dist_dst(rng);

        tcs.push_back(SpwikiInput(edges, src, dst, num_v));
    }

    /* 保存到文件, 方便调试 */
    ofstream fout("testcases.txt");
    for (int i = 0; i < TESTCASE_NUM; i++) {
        fout << "Testcase " << i << ": " << endl;
        fout << "------------------------------" << endl;
        fout << "edges: ";
        for (auto &edge : tcs[i].edges)
            fout << "(" << edge[0] << ", " << edge[1] << ", " << edge[2] << "), ";
        fout << endl;
        fout << "src: " << tcs[i].src << endl;
        fout << "dst: " << tcs[i].dst << endl;
        fout << "n  : " << tcs[i].n << endl;
        fout << endl;
    }
    fout.close();

    return tcs;
}