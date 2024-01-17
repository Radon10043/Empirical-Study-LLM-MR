#ifndef _HAVE_FUNCTION_H
#define _HAVE_FUNCTION_H

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;

int* Dijkstra(int matrix[][100],int source,int vertex_num)
{
	bool visited[100];
	static int  dist[100];
    int  path[100];
    for(int i=0;i<100;i++)
	{
		visited[i]=false;
		path[i]=source;
    }
    visited[source] = true;
    for (int i = 0; i < vertex_num; i++)
    {
        dist[i] = matrix[source][i];
        path[i] = source;
    }

    
    int min_cost;        // 权值最小
    int min_cost_index;  // 权值最小的下标

    for (int i = 1; i < vertex_num; i++)  // 找到源点到另外 vertex_num-1 个点的最短路径
    {
        min_cost = 2147483647;
		
        for (int j = 0; j < vertex_num; j++)
        {
            if (visited[j] == false && dist[j] < min_cost)  // 找到权值最小
            {
                min_cost = dist[j];
                min_cost_index = j;
            }
        }
        
			visited[min_cost_index] = true;  // 该点已找到，进行标记

        for (int j = 0; j < vertex_num; j++)  // 更新 dist 数组
        {
            if (visited[j] == false && min_cost != 2147483647 &&
                matrix[min_cost_index][j] != 2147483647 &&  // 确保两点之间有边
                matrix[min_cost_index][j] + min_cost < dist[j])
            {
                dist[j] = matrix[min_cost_index][j] + min_cost;
                path[j] = min_cost_index;
            }
        }

    }
    return dist;
}

/**
 * @brief 求无向图中src到dst的最短路径长度
 *
 * @param edges 用于表示无向图的边的集合, 每个边包含三个元素: 起点, 终点, 权重
 * @param src 起点
 * @param dst 终点
 * @param n 图中节点数量
 * @return int src到dst的最短距离
 */
int shortest_path(vector<vector<int>> edges, int src, int dst, int n) {
    int matrix[100][100];
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            matrix[i][j] = INT_MAX;

    for (auto& edge : edges) {
        matrix[edge[0]][edge[1]] = edge[2];
        matrix[edge[1]][edge[0]] = edge[2];
    }

    int *dist = Dijkstra(matrix, src, n);
    return *(dist + dst);
}

#endif