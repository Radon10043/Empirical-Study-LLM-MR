#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/**
 * @brief KLP算法的C++实现
 *
 * @param matrix m行n列的矩阵, matrix[i][j]的值若为1, 表示第i个钥匙可以打开第j个锁, 否则就不能打开
 * @return vector<int> 若数组中第i个元素的值为true, 表示选择这把钥匙, 否则不选
 */
vector<int> KLP(vector<vector<int>> matrix) {

    int m = matrix.size(),      // 矩阵的行数, 即钥匙的个数
        n = matrix[0].size(),   // 矩阵的列数, 即锁的个数
        cnt = 0;                // 选择的钥匙数量
    vector<int> res;

    for (int k = 0; k < m; k++) {

        /* 寻找能开最多锁的钥匙 */
        int max_o_locks = 0, best_row_index = 0;
        for (int i = 0; i < m; i++) {
            int n_o_locks = count(matrix[i].begin(), matrix[i].end(), 1);
            if (n_o_locks > max_o_locks) {
                max_o_locks = n_o_locks;
                best_row_index = i;
            }
        }

        /* 如果最多能开0个锁, 表示已经是最小集了, 没必要继续迭代了 */
        if (!max_o_locks) break;

        /* matrix中第best_row_index行, 删掉行中打开的锁对应的每一列, 这里的删除方法就是把数组中的值置为-1 */
        for (int j = 0; j < n; j++) {
            if (matrix[best_row_index][j] == 1) {
                for (int i = 0; i < m; i++)
                    matrix[i][j] = -1;
            }
        }

        /* 删掉第best_row_index行, 同样将行中的数都置为-1 */
        for (int i = 0; i < n; i++)
            matrix[best_row_index][i] = -1;

        res.emplace_back(best_row_index), cnt++;

    }

    return res;

}