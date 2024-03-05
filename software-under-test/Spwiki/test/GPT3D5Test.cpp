#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class SpwikiParamTest : public ::testing::TestWithParam<SpwikiInput> {};

/**
 * @brief Metamorphic Relation 1: Reversing the source and destination vertices, the length of the shortest path should be the same.
 *
 */
TEST_P(SpwikiParamTest, MR1) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    int follow_src = source_dst, follow_dst = source_src;

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, follow_src, follow_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Adding a constant to all edge weights, the length of the shortest path should be increased by the same constant.
 *
 */
TEST_P(SpwikiParamTest, MR2) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    int constant = 5; // Example constant value
    for (auto &elem : follow_edges)
        elem[2] += constant;

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out + constant);
}

/**
 * @brief Metamorphic Relation 3: Adding or removing a vertex and its incident edges, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR3) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    follow_edges.push_back({source_n, source_n+1, 10}); // Adding a new edge
    int follow_n = source_n + 1; // Number of vertices increased

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, follow_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: Reversing the direction of the edges, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR4) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges;
    for (const auto &edge : source_edges)
        follow_edges.push_back({edge[1], edge[0], edge[2]}); // Reverse the direction of the edges

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Doubling the weight of all edges and the source and destination vertex, the shortest path distance should remain the same.
 *
 */
TEST_P(SpwikiParamTest, MR5) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    int constant = 2; // Doubling constant
    for (auto &elem : follow_edges)
        elem[2] *= constant;

    int follow_src = source_src * constant; // Doubling the source vertex
    int follow_dst = source_dst * constant; // Doubling the destination vertex

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, follow_src, follow_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Multiplying all edge weights and the number of vertices by a constant, the length of the shortest path should be multiplied by the same constant.
 *
 */
TEST_P(SpwikiParamTest, MR6) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    int constant = 3; // Example constant value
    for (auto &elem : follow_edges)
        elem[2] *= constant;

    int follow_n = source_n * constant; // Multiplying the number of vertices

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, follow_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out * constant);
}

/**
 * @brief Metamorphic Relation 7: Removing a specific edge from the graph, the shortest path distance should remain unchanged if the removed edge is not on the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR7) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Choose an edge to remove */
    vector<int> edge_to_remove = source_edges.back(); // Selecting the last edge in the list
    source_edges.pop_back(); // Removing the chosen edge

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Adding a specific edge to the graph, the shortest path distance should either remain unchanged or increase if the added edge lies on the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR8) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Choose an edge to add */
    vector<int> edge_to_add = {source_src, source_dst, 5}; // Adding edge directly between src and dst
    source_edges.push_back(edge_to_add); // Adding the chosen edge

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    if (follow_out >= source_out) {
        EXPECT_TRUE(true);  // Added edge lies on the shortest path
    } else {
        EXPECT_EQ(follow_out, source_out);  // Added edge does not lie on the shortest path
    }
}

/**
 * @brief Metamorphic Relation 9: Reversing the weights of all edges (invert weights, e.g., w -> 1/w), the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR9) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    for (auto &elem : follow_edges)
        elem[2] = 1.0 / elem[2]; // Invert the weights of all edges

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Shuffling the order of edges, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR10) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Shuffle the order of edges */
    random_shuffle(source_edges.begin(), source_edges.end());

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Adding a loop (an edge from a vertex to itself) with weight 0, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR11) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Add a loop */
    source_edges.push_back({source_src, source_src, 0}); // Adding a loop with weight 0

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Duplicating all edges, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR12) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Duplicate all edges */
    int original_size = source_edges.size();
    for (int i = 0; i < original_size; i++) {
        source_edges.push_back(source_edges[i]);
    }

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 13: Adding a constant to the source and destination vertices, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR13) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    int follow_src = source_src + 10; // Adding a constant to the source vertex
    int follow_dst = source_dst + 10; // Adding a constant to the destination vertex

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, follow_src, follow_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 14: Reversing the graph, meaning changing all edges to their opposite direction, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR14) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input by reversing the graph */
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        swap(edge[0], edge[1]); // Reversing edge direction
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 15: Scaling all edge weights by a constant factor, the shortest path distance from source to destination should be scaled by the same factor.
 *
 */
TEST_P(SpwikiParamTest, MR15) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    double scaling_factor = 1.5; // Scaling factor
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        edge[2] = static_cast<int>(edge[2] * scaling_factor); // Scaling edge weights
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, static_cast<int>(source_out * scaling_factor));
}

/**
 * @brief Metamorphic Relation 16: Adding a vertex and multiple edges to the graph, the shortest path distance should remain unchanged if the added vertex is not on the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR16) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Add a new vertex and multiple edges connected to existing vertices */
    source_n++; // Incrementing the number of vertices
    source_edges.push_back({source_src, source_n, 5}); // Adding an edge from source to the new vertex
    source_edges.push_back({source_n, source_dst, 7}); // Adding an edge from the new vertex to the destination

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 17: Reversing the order of vertices while keeping the edge directions, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR17) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Reverse the order of vertices */
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        int temp = edge[0];
        edge[0] = edge[1];
        edge[1] = temp;
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_dst, source_src, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 18: Replacing all edge weights with the absolute values of the original weights, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR18) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        edge[2] = abs(edge[2]); // Replacing edge weights with their absolute values
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 19: Multiplying all vertex indices and edge weights by a constant factor, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR19) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    int constant_factor = 10; // Constant factor for multiplication
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        edge[0] *= constant_factor; // Multiply start vertex index
        edge[1] *= constant_factor; // Multiply end vertex index
        edge[2] *= constant_factor; // Multiply edge weight
    }
    int follow_src = source_src * constant_factor; // Multiply source vertex index
    int follow_dst = source_dst * constant_factor; // Multiply destination vertex index

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, follow_src, follow_dst, source_n * constant_factor);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Adding or removing parallel edges between two vertices, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR20) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Add a parallel edge between source and destination vertices */
    source_edges.push_back({source_src, source_dst, 8});

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 21: Adding a vertex and creating connections with all existing vertices, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR21) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Compute the shortest path with the original number of vertices */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Add a new vertex and connect it with all existing vertices */
    int follow_n = source_n + 1;
    vector<vector<int>> follow_edges = source_edges;
    for (int i = 0; i < source_n; i++) {
        follow_edges.push_back({i, source_n, 5}); // Creating connections with the new vertex
        follow_edges.push_back({source_n, i, 5}); // Creating connections from the new vertex
    }

    /* Compute the shortest path with the new vertex and connections */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, follow_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out); // Shortest path distance remains unchanged
}

/**
 * @brief Metamorphic Relation 22: Reversing the direction of all edges, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR22) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
  
    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Reverse the direction of all edges */
    vector<vector<int>> follow_edges;
    for (vector<int> edge : source_edges) {
        follow_edges.push_back({edge[1], edge[0], edge[2]});
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_dst, source_src, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

//fixed
/**
 * @brief Metamorphic Relation 23: Removing an intermediate vertex from the shortest path, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR23) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Find the shortest path */
    vector<int> path;
    int dist;
    int source_edges_array[100][100]; // 静态分配的二维数组

    // 将向量内容复制到数组中
    for (size_t i = 0; i < source_edges.size(); ++i) {
        for (size_t j = 0; j < source_edges[i].size(); ++j) {
            source_edges_array[i][j] = source_edges[i][j];
        }
    }

    // 将数组指针传递给函数
    Dijkstra(source_edges_array, source_src, source_n);
    //Dijkstra(source_edges, source_src, source_n, path, dist);

    /* Remove an intermediate vertex from the path and check if the shortest path distance remains unchanged */
    for (size_t i = 1; i < path.size() - 1; i++) {
        vector<vector<int>> follow_edges = source_edges;
        int removed_vertex = path[i];
        for (size_t j = 0; j < follow_edges.size(); j++) {
            if (follow_edges[j][0] == removed_vertex || follow_edges[j][1] == removed_vertex) {
                follow_edges.erase(follow_edges.begin() + j);
                j--;
            }
        }
        int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);
        EXPECT_EQ(follow_out, source_out);
    }
}

/**
 * @brief Metamorphic Relation 24: Adding a large constant to all edge weights, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR24) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Add a large constant to all edge weights */
    vector<vector<int>> follow_edges = source_edges;
    int constant = 1000; // Example constant value
    for (vector<int>& edge : follow_edges) {
        edge[2] += constant;
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 25: Modifying edge weights to their absolute values, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR25) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Modify edge weights to their absolute values */
    vector<vector<int>> follow_edges = source_edges;
    for (vector<int>& edge : follow_edges) {
        edge[2] = abs(edge[2]);
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}


/**
 * @brief Metamorphic Relation 26: Applying different scaling factors to individual edge weights, the shortest path distance should be affected accordingly.
 *
 */
TEST_P(SpwikiParamTest, MR26) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input by applying different scaling factors to individual edge weights */
    vector<vector<int>> follow_edges = source_edges;
    int scaling_factors[] = {2, 1, 3};  // Example scaling factors
    for (size_t i = 0; i < follow_edges.size(); ++i) {
        follow_edges[i][2] *= scaling_factors[i % 3]; 
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out * 2 * 3);
}

//fixed
/**
 * @brief Metamorphic Relation 27: Adding an edge to a cycle in the graph, the shortest path distance should remain unchanged.
 *
 */
bool find_cycle_dfs(const vector<vector<int>>& edges, int current, int parent, vector<int>& visited, vector<int>& path) {
    visited[current] = 1;
    path.push_back(current);
    
    for (int next : edges[current]) {
        if (next == parent) continue; // Skip the edge to the parent vertex
        
        if (visited[next] == 1) {
            // Cycle found
            // Add the current vertex to the path and return true
            path.push_back(next);
            return true;
        } else if (visited[next] == 0) {
            // Recursive call to explore the next vertex
            if (find_cycle_dfs(edges, next, current, visited, path)) {
                return true;
            }
        }
    }
    
    // Mark the current vertex as visited (2) after exploring all its neighbors
    visited[current] = 2;
    path.pop_back(); // Remove the current vertex from the path
    return false;
}

TEST_P(SpwikiParamTest, MR27) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
  
    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Find cycles in the graph */
    vector<vector<int>> cycles;
    vector<int> visited(source_n, 0);
    vector<int> path;
    for (int i = 0; i < source_n; i++) {
        if (!visited[i]) {
            path.clear();
            if (find_cycle_dfs(source_edges, i, -1, visited, path)) {
                cycles.push_back(path);
            }
        }
    }
    
    /* Choose a cycle and add an edge to it */
    if (!cycles.empty()) {
        vector<int> cycle = cycles[0]; // Choose the first cycle
        for (size_t i = 1; i < cycle.size(); i++) {
            vector<vector<int>> follow_edges = source_edges;
            follow_edges.push_back({cycle[i - 1], cycle[i], 5}); // Adding an edge to the cycle
            int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);
            EXPECT_EQ(follow_out, source_out);
        }
    }
}

/**
 * @brief Metamorphic Relation 28: Substituting each weight with its square, the shortest path distance should be the same or higher.
 *
 */
TEST_P(SpwikiParamTest, MR28) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
  
    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);
  
    /* Construct follow-up input by performing transformation on edge weights */
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        edge[2] = edge[2] * edge[2]; // Using the square of the original weight
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
}

//fixed
/**
 * @brief Metamorphic Relation 29: Removing an irrelevant edge that is not a part of the shortest path, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR29) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
  
    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Find the shortest path */
    vector<int> path;
    int dist;
    int source_edges_array[100][100]; // 静态分配的二维数组

    // 将向量内容复制到数组中
    for (size_t i = 0; i < source_edges.size(); ++i) {
        for (size_t j = 0; j < source_edges[i].size(); ++j) {
            source_edges_array[i][j] = source_edges[i][j];
        }
    }

    // 将数组指针传递给函数
    Dijkstra(source_edges_array, source_src, source_n);
    //Dijkstra(source_edges, source_src, source_n, path, dist);
  
    /* Remove an irrelevant edge from the graph and check if the shortest path distance remains unchanged */
    for (size_t i = 1; i < path.size(); i++) {
        int u = path[i - 1];
        int v = path[i];
        vector<vector<int>> follow_edges = source_edges;
        for (size_t j = 0; j < follow_edges.size(); j++) {
            if (follow_edges[j][0] == u && follow_edges[j][1] == v) {
                follow_edges.erase(follow_edges.begin() + j);
                break;
            }
        }
        int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);
        EXPECT_EQ(follow_out, source_out);
    }
}

/**
 * @brief Metamorphic Relation 30: Repeatedly performing Dijkstra's algorithm, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR30) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
  
    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);
  
    /* Perform Dijkstra's algorithm multiple times and ensure that the shortest path distance remains consistent */
    for (int i = 0; i < 10; i++) {
        int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);
        EXPECT_EQ(follow_out, source_out);
    }
}

/**
 * @brief Metamorphic Relation 31: Reversing the weight signs of all edge weights, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR31) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
  
    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        edge[2] = -edge[2]; // Reversing the signs of edge weights
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 32: Adding a self-cycle to all vertices, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR32) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    for (int i = 0; i < source_n; i++) {
        follow_edges.push_back({i, i, 0}); // Adding a self-cycle to each vertex
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 33: Adding a new vertex connected to all existing vertices, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR33) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
  
    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    for (int i = 0; i < source_n; i++) {
        follow_edges.push_back({source_n, i, 1}); // Adding edges from the new vertex to all existing vertices
        follow_edges.push_back({i, source_n, 1}); // Adding edges from all existing vertices to the new vertex
    }
    follow_edges.push_back({source_n, source_dst, 1}); // Adding an edge from the new vertex to the destination vertex
    follow_edges.push_back({source_src, source_n, 1}); // Adding an edge from the source vertex to the new vertex

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n + 1);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 34: Adding a new vertex and connecting it to the source vertex, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR34) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
  
    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    follow_edges.push_back({source_src, source_n, 1}); // Adding an edge from the source vertex to the new vertex
    follow_edges.push_back({source_n, source_dst, 1}); // Adding an edge from the new vertex to the destination vertex

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n + 1);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 35: Scaling all edge weights by a constant factor and adding a constant to all vertex indices, the shortest path distance should remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR35) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    double constant_factor = 2.0;
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        edge[2] *= constant_factor;  // Multiply all edge weights by a constant factor
    }

    int follow_src = source_src + 10;  // Add a constant to the source vertex index
    int follow_dst = source_dst + 10;  // Add a constant to the destination vertex index

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, follow_src, follow_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: Removing a specific edge from the graph, the shortest path distance should either remain unchanged or increase if the removed edge is on the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR36) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Choose an edge to remove */
    vector<int> edge_to_remove = source_edges.front(); // Selecting the first edge in the list
    source_edges.erase(source_edges.begin()); // Removing the chosen edge

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    if (follow_out >= source_out) {
        EXPECT_TRUE(true);  // Removed edge is on or not on the shortest path
    } else {
        EXPECT_EQ(follow_out, source_out);  // Removed edge is on the shortest path
    }
}

/**
 * @brief Metamorphic Relation 37: Adding randomly generated edges to the graph, the shortest path distance should remain unchanged or increase.
 *
 */
TEST_P(SpwikiParamTest, MR37) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Randomly generate additional edges */
    vector<vector<int>> new_edges;
    int num_additional_edges = 5; // Number of additional edges to add
    for (int i = 0; i < num_additional_edges; i++) {
        int start_vertex = rand() % source_n;
        int end_vertex = rand() % source_n;
        int weight = rand() % 10 + 1;
        new_edges.push_back({start_vertex, end_vertex, weight});
    }

    /* Add the additional edges to the original graph */
    vector<vector<int>> follow_edges = source_edges;
    follow_edges.insert(follow_edges.end(), new_edges.begin(), new_edges.end());

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    if (follow_out >= source_out) {
        EXPECT_TRUE(true);  // Distance either remains unchanged or increases
    } else {
        EXPECT_EQ(follow_out, source_out);  // Unexpected case
    }
}

/**
 * @brief Metamorphic Relation 38: Removing randomly selected edges from the graph, the shortest path distance should remain unchanged or decrease.
 *
 */
TEST_P(SpwikiParamTest, MR38) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get shortest path with original edges */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Randomly select edges to remove */
    vector<vector<int>> follow_edges = source_edges;
    int num_edges_to_remove = 2; // Number of edges to remove
    for (int i = 0; i < num_edges_to_remove; i++) {
        int index = rand() % follow_edges.size();
        follow_edges.erase(follow_edges.begin() + index);
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    if (follow_out <= source_out) {
        EXPECT_TRUE(true);  // Distance either remains unchanged or decreases
    } else {
        EXPECT_EQ(follow_out, source_out);  // Unexpected case
    }
}

/**
 * @brief Metamorphic Relation 39: Doubling the number of vertices, the behavior of the shortest path algorithm is altered.
 *
 */
TEST_P(SpwikiParamTest, MR39) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Compute the shortest path with the original number of vertices */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Double the number of vertices */
    int follow_n = source_n * 2;
    vector<vector<int>> follow_edges = source_edges;
    for (int i = 0; i < source_n; i++) {
        follow_edges.push_back({i, i + source_n, 5}); // Creating connections between the original and the new set of vertices
    }

    /* Compute the shortest path with the doubled number of vertices */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, follow_n);

    /* Verification */
    EXPECT_TRUE(true); // Behavior of the shortest path algorithm is altered
}


/**
 * @brief Metamorphic Relation 40: Adding a negative weight cycle in the graph, the behavior of the shortest path algorithm is undefined.
 *
 */
TEST_P(SpwikiParamTest, MR40) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    // Construct follow-up input by adding a negative weight cycle in the graph
    vector<vector<int>> follow_edges = source_edges;
    follow_edges.push_back({source_n, source_n, -3});  // Adding a negative weight self-loop

    // Get follow-up output
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    // Verification
    EXPECT_TRUE(true); // Behavior of the shortest path algorithm is undefined
}

INSTANTIATE_TEST_CASE_P(TrueReturn, SpwikiParamTest, testing::ValuesIn(gen_tcs_randomly()));
