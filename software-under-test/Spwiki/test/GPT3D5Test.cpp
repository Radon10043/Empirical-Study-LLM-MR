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
 * 修改步骤:
 * 1. DijkstraAlgorithmParamTest -> SpwikiParamTest
 * 2. DijkstraInput -> SpwikiInput
 * 3. dijkstra_shortest_path -> shortest_path
 * 4. 所有没有source_n的地方都加上了source_n
 */

/**
 * @brief Metamorphic Relation 3: Adding a constant value to the weight of every edge, the length of the shortest path should remain unchanged.
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
    for (auto &elem : follow_edges)
        elem[2] += 10; // Adding a constant value of 10 to the weight of each edge

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: Removing an intermediate vertex from the graph, the length of the shortest path should be less than or equal to the original shortest path length.
 *
 */
TEST_P(SpwikiParamTest, MR4) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Fix by Radon */
    /* Delete a vertex randomly? */
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, source_n - 1);
    int intermediate_vertex = dist(rng);

    /* Construct follow-up input by removing an intermediate vertex (if present) */
    vector<vector<int>> follow_edges = source_edges;
    for (auto it = follow_edges.begin(); it != follow_edges.end();) {
        if (it->at(0) == intermediate_vertex || it->at(1) == intermediate_vertex) {
            it = follow_edges.erase(it); // Remove edges connected to the intermediate vertex
        } else {
            ++it;
        }
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n - 1);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 5: Adding the same constant value to all edge weights should not change the shortest path length.
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
    int constant = 5; // arbitrary constant value
    for (auto &elem : follow_edges) {
        elem[2] += constant;
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Adding the same constant to all edge weights should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Reversing the direction of all edges in the graph should not change the shortest path length.
 */
TEST_P(SpwikiParamTest, MR6) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

     /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Reverse the direction of all edges in the graph */
    vector<vector<int>> follow_edges;
    for (auto& elem : source_edges){
        follow_edges.push_back({elem[1], elem[0], elem[2]});
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Reversing the direction of all edges in the graph should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 7: Adding a new vertex connected to all other vertices with the same weight, the length of the shortest path from the new vertex to any other vertex should be the same.
 */
TEST_P(SpwikiParamTest, MR7) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Adding a new vertex connected to all other vertices with the same weight */
    vector<vector<int>> follow_edges = source_edges;
    int newVertex = source_n; // Assume new vertex is the next sequential number after the existing vertices
    for (int i = 0; i < source_n; i++) {
        if (i != newVertex) {
            follow_edges.emplace_back(vector<int>{i, newVertex, 10}); // Adding a new edge of weight 10 from existing vertices to the new vertex
            follow_edges.emplace_back(vector<int>{newVertex, i, 10}); // Adding a new edge of weight 10 from the new vertex to existing vertices
        }
    }
    source_n++; // Increment the number of vertices

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, newVertex, source_dst, source_n);

    /* Verification - The length of the shortest path from the new vertex to any other vertex should be the same */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 8: Reversing the weights of the edges, the length of the shortest path should still be the same.
 */
TEST_P(SpwikiParamTest, MR8) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Reversing the weights of the edges */
    vector<vector<int>> follow_edges = source_edges;
    for (auto &elem : follow_edges) {
        elem[2] = -elem[2]; // Reversing the weights of the edges
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Reversing the weights of the edges should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 9: Adding a new edge to the existing graph should not increase the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR9) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Adding a new edge to the existing graph */
    vector<vector<int>> follow_edges = source_edges;
    follow_edges.emplace_back(vector<int>{source_src, source_dst, 5}); // Adding a new edge from source to destination with weight 5

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Adding a new edge to the existing graph should not increase the shortest path length */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 10: Removing an edge from the existing graph should not increase the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR10) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Removing an edge from the existing graph */
    vector<vector<int>> follow_edges;
    for (auto &edge : source_edges) {
        if (!(edge[0] == source_src && edge[1] == source_dst)) {
            follow_edges.push_back(edge); // Exclude the edge from source to destination
        }
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Removing an edge from the existing graph should not increase the shortest path length */
    EXPECT_LE(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 11: Adding a new vertex and connecting it to the source and destination vertices, the shortest path should not increase from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR11) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Adding a new vertex and connecting it to the source and destination vertices */
    vector<vector<int>> follow_edges = source_edges;
    int newVertex = source_n;
    follow_edges.push_back({source_src, newVertex, 8}); // Connecting the new vertex to the source with weight 8
    follow_edges.push_back({newVertex, source_dst, 8}); // Connecting the new vertex to the destination with weight 8
    source_n++; // Increment the number of vertices

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Adding a new vertex and connecting it to the source and destination vertices should not increase the shortest path length */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Reversing the direction of the graph and the source and destination, the shortest path length should remain the same.
 */
TEST_P(SpwikiParamTest, MR12) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Reversing the direction of the graph and the source and destination */
    vector<vector<int>> follow_edges;
    for (auto& edge : source_edges) {
        follow_edges.emplace_back(vector<int>{edge[1], edge[0], edge[2]}); // Reverse the direction of the edges
    }
    int follow_src = source_dst; // Reverse source and destination
    int follow_dst = source_src;

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, follow_src, follow_dst, source_n);

    /* Verification - Reversing the direction of the graph and the source and destination should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 13: Scaling all edge weights by a constant factor should scale the shortest path length by the same factor.
 */
TEST_P(SpwikiParamTest, MR13) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Scaling all edge weights by a constant factor */
    vector<vector<int>> follow_edges = source_edges;
    int scalingFactor = 2; // arbitrary constant scaling factor
    for (auto &edge : follow_edges) {
        edge[2] *= scalingFactor; // scale the weight of each edge
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Scaling all edge weights by a constant factor should scale the shortest path length by the same factor */
    EXPECT_EQ(follow_out, source_out * scalingFactor);
}

/**
 * @brief Metamorphic Relation 14: Adding a cyclic path to the graph should not change the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR14) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Adding a cyclic path to the graph */
    vector<vector<int>> follow_edges = source_edges;
    follow_edges.emplace_back(vector<int>{source_dst, source_src, 3}); // Adding a cyclic path from destination back to source with weight 3

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Adding a cyclic path to the graph should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 15: Adding a self-loop to a vertex in the graph should not change the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR15) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Adding a self-loop to a vertex in the graph */
    vector<vector<int>> follow_edges = source_edges;
    follow_edges.emplace_back(vector<int>{source_src, source_src, 2}); // Adding a self-loop to the source vertex with weight 2

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Adding a self-loop to a vertex in the graph should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 16: Removing a vertex from the graph should not increase the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR16) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Fix by Radon */
    /* Delete a vertex randomly? */
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, source_n - 1);
    int vertex_to_remove = dist(rng);

    /* Construct follow-up input - Removing a vertex from the graph */
    vector<vector<int>> follow_edges = source_edges;
    for (auto it = follow_edges.begin(); it != follow_edges.end();) {
        if (it->at(0) == vertex_to_remove || it->at(1) == vertex_to_remove) {
            it = follow_edges.erase(it); // Remove edges connected to the vertex to be removed
        } else {
            ++it;
        }
    }
    source_n--; // Decrement the number of vertices

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Removing a vertex from the graph should not increase the shortest path length */
    EXPECT_LE(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 17: Settling a new monkey vertex should not change the shortest path from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR17) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Settling a new monkey vertex */
    vector<vector<int>> follow_edges = source_edges;
    int monkey_vertex = source_n; // Assumption: the monkey vertex is the next sequential number after the existing vertices
    follow_edges.emplace_back(vector<int>{source_src, monkey_vertex, 4}); // Add an edge from source to monkey vertex with weight 4
    follow_edges.emplace_back(vector<int>{monkey_vertex, source_dst, 4}); // Add an edge from monkey vertex to destination with weight 4
    source_n++; // Increment the number of vertices

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Settling a new monkey vertex should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 18: Randomly shuffling the edges in the graph should not change the shortest path from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR18) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    std::random_shuffle(source_edges.begin(), source_edges.end()); // Shuffle the edges randomly

    /* Get source output */
    int source_out = shortest_path(source_edges, input.src, input.dst, input.n);

    /* Verification - Randomly shuffling the edges in the graph should not change the shortest path length */
    EXPECT_EQ(source_out, shortest_path(source_edges, input.src, input.dst, input.n));
}
/**
 * @brief Metamorphic Relation 19: Reversing the direction of the graph, the shortest path from the destination to the source should not change.
 */
TEST_P(SpwikiParamTest, MR19) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Reversing the direction of the graph */
    vector<vector<int>> follow_edges = source_edges;
    for (auto& edge : follow_edges) {
        swap(edge[0], edge[1]); // Reverse the directions of the edges
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_dst, source_src, source_n);

    /* Verification - Reversing the direction of the graph should not change the shortest path from the destination to the source */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 20: Scaling all edge weights by a negative constant factor should not change the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR20) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Scaling all edge weights by a negative constant factor */
    vector<vector<int>> follow_edges = source_edges;
    int scalingFactor = -2; // arbitrary negative constant scaling factor
    for (auto &edge : follow_edges) {
        edge[2] *= scalingFactor; // scale the weight of each edge by the negative factor
    }

   /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Scaling all edge weights by a negative constant factor should not change the shortest path length from the source to the destination */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 21: Adding a new vertex and connecting it to all existing vertices with a constant weight, the shortest path from the source to the destination should not increase.
 */
TEST_P(SpwikiParamTest, MR21) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Adding a new vertex connected to all existing vertices with a constant weight */
    vector<vector<int>> follow_edges = source_edges;
    int new_vertex = source_n; // Assuming the new vertex is the next sequential number after the existing vertices
    for (int i = 0; i < source_n; i++) {
        if (i != new_vertex) {
            follow_edges.emplace_back(vector<int>{i, new_vertex, 5}); // Add an edge with weight 5 from the existing vertex to the new vertex
            follow_edges.emplace_back(vector<int>{new_vertex, i, 5}); // Add an edge with weight 5 from the new vertex to the existing vertex
        }
    }
    source_n++; // Increment the number of vertices

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Adding a new vertex and connecting it to all existing vertices should not increase the shortest path length */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 22: Removing an edge from the graph should not change the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR22) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input - Removing an edge from the graph */
    vector<vector<int>> follow_edges = source_edges;
    // Remove an edge based on some criteria, for example, the first edge in the vector
    if (!follow_edges.empty()) {
        follow_edges.erase(follow_edges.begin());
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification - Removing an edge from the graph should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 23: Adding or removing a non-essential vertex from the graph should not change the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR23) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, input.n);

    /* Construct follow-up input - Adding or removing a non-essential vertex from the graph */
    // Here, a non-essential vertex is a vertex with no influence on the shortest path between the source and destination

    // Step 1: Add a new non-essential vertex to the graph
    int new_vertex = input.n;  // Assuming the new vertex is the next sequential number after the existing vertices
    vector<vector<int>> follow_edges_add = source_edges;
    for (int i = 0; i < input.n; i++) {
        if (i != new_vertex) {
            follow_edges_add.push_back({i, new_vertex, 2}); // Add an edge with weight 2 from existing vertices to the new non-essential vertex
            follow_edges_add.push_back({new_vertex, i, 2}); // Add an edge with weight 2 from the new non-essential vertex to existing vertices
        }
    }
    int follow_out_add = shortest_path(follow_edges_add, source_src, source_dst, input.n + 1);

    // Step 2: Remove a non-essential vertex from the graph
    vector<vector<int>> follow_edges_remove = source_edges;
    // Remove the last vertex, assuming it is a non-essential vertex
    follow_edges_remove.erase(follow_edges_remove.end() - 1);
    int follow_out_remove = shortest_path(follow_edges_remove, source_src, source_dst, input.n - 1);

    /* Verification - Adding or removing a non-essential vertex from the graph should not change the shortest path length */
    EXPECT_EQ(follow_out_add, source_out);
    EXPECT_EQ(follow_out_remove, source_out);
}

/**
 * @brief Metamorphic Relation 24: Multiplying all edge weights by a constant factor should not change the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR24) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, input.n);

    /* Construct follow-up input - Multiplying all edge weights by a constant factor */
    vector<vector<int>> follow_edges = source_edges;
    int scaling_factor = 2;  // Multiplying all edge weights by 2
    for (auto &edge : follow_edges) {
        edge[2] *= scaling_factor;
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, input.n);

    /* Verification - Multiplying all edge weights by a constant factor should not change the shortest path length */
    EXPECT_EQ(source_out, follow_out);
}
/**
 * @brief Metamorphic Relation 25: Adding a new edge with a weight of 0 should not change the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR25) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, input.n);

    /* Construct follow-up input - Adding a new edge with a weight of 0 */
    vector<vector<int>> follow_edges = source_edges;
    int new_edge_weight = 0;
    follow_edges.emplace_back(vector<int>{source_src, source_dst, new_edge_weight});

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, input.n);

    /* Verification - Adding a new edge with a weight of 0 should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 26: Excluding all edges from the graph should result in a non-existent path between the source and destination.
 */
TEST_P(SpwikiParamTest, MR26) {
    /* Get source input */
    SpwikiInput input = GetParam();
    int source_src = input.src, source_dst = input.dst;

    /* Construct follow-up input - Excluding all edges from the graph */
    vector<vector<int>> follow_edges = {}; // Empty edge list

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, input.n);

    /* Verification - Excluding all edges should result in a non-existent path */
    EXPECT_EQ(follow_out, -1); // Assuming -1 represents a non-existent path
}
/**
 * @brief Metamorphic Relation 27: Adding a duplicate edge to the graph should not change the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR27) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, input.n);

    /* Construct follow-up input - Adding a duplicate edge to the graph */
    vector<vector<int>> follow_edges = source_edges;
    if (!source_edges.empty()) {
        follow_edges.push_back(source_edges.front()); // Add the first edge as a duplicate edge
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, input.n);

    /* Verification - Adding a duplicate edge to the graph should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 28: Removing all edges incident to the destination vertex should result in an unreachable destination from the source.
 */
TEST_P(SpwikiParamTest, MR28) {
    /* Get source input */
    SpwikiInput input = GetParam();
    int source_src = input.src, source_dst = input.dst;
    vector<vector<int>> source_edges = input.edges;

    /* Construct follow-up input - Removing all edges incident to the destination vertex */
    vector<vector<int>> follow_edges = source_edges;
    auto remove_if_dst = [source_dst](const vector<int>& edge) { return (edge[1] == source_dst); };
    follow_edges.erase(remove_if(follow_edges.begin(), follow_edges.end(), remove_if_dst), follow_edges.end());

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, input.n);

    /* Verification - Removing all edges incident to the destination vertex should result in unreachable destination */
    EXPECT_EQ(follow_out, -1); // Assuming -1 represents an unreachable destination
}
/**
 * @brief Metamorphic Relation 29: Adding a shortcut edge in the graph should not change the shortest path length from the source to the destination.
 */
TEST_P(SpwikiParamTest, MR29) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, input.n);

    /* Construct follow-up input - Adding a shortcut edge in the graph */
    vector<vector<int>> follow_edges = source_edges;
    // Assuming the shortcut edge connects the source directly to the destination with a lower weight
    follow_edges.push_back({source_src, source_dst, 5}); // Adding a shortcut edge with weight 5

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, input.n);

    /* Verification - Adding a shortcut edge in the graph should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 30: Adding a bi-directional shortcut edge between any two vertices in the graph should not change the shortest path length between these vertices.
 */
TEST_P(SpwikiParamTest, MR30) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;

    /* Select two distinct vertices in the graph */
    int vertex1 = 0;  // Assuming the vertices are 0-based
    int vertex2 = 1;

    /* Get the shortest path length between the selected vertices */
    int source_out = shortest_path(source_edges, vertex1, vertex2, input.n);

    /* Construct follow-up input - Adding a bi-directional shortcut edge between the selected vertices */
    vector<vector<int>> follow_edges = source_edges;
    int new_edge_weight = 3;  // Assuming the weight of the shortcut edge is 3
    follow_edges.push_back({vertex1, vertex2, new_edge_weight}); // Adding a shortcut edge from vertex1 to vertex2
    follow_edges.push_back({vertex2, vertex1, new_edge_weight}); // Adding a shortcut edge from vertex2 to vertex1

    /* Get the shortest path length between the selected vertices in the follow-up graph */
    int follow_out = shortest_path(follow_edges, vertex1, vertex2, input.n);

    /* Verification - Adding a bi-directional shortcut edge between any two vertices should not change the shortest path length between these vertices */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 31: Adding a disjoint subgraph with no connection to the existing graph should not change the shortest path length between vertices in the existing graph.
 */
TEST_P(SpwikiParamTest, MR31) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;
    
    /* Assume a new subgraph with vertices not connected to the existing graph */
    vector<vector<int>> new_subgraph = {{10, 11, 5}, {11, 12, 7}, {10, 12, 4}};

    /* Get the shortest path length between two existing vertices */
    int source_out = shortest_path(existing_edges, 0, 1, input.n);

    /* Construct follow-up input - Combining the existing graph with the new subgraph */
    vector<vector<int>> combined_edges = existing_edges;
    combined_edges.insert(combined_edges.end(), new_subgraph.begin(), new_subgraph.end());

    /* Get the shortest path length between the same two existing vertices in the combined graph */
    int follow_out = shortest_path(combined_edges, 0, 1, input.n + new_subgraph.size());

    /* Verification - Adding a disjoint subgraph should not change the shortest path length between existing vertices */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 32: Removing an isolated vertex from the graph should not change the shortest path length between any two existing vertices.
 */
TEST_P(SpwikiParamTest, MR32) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Remove the isolated vertex from the graph */
    vector<vector<int>> updated_edges;
    int isolated_vertex = 5; // Assuming the isolated vertex is vertex 5
    for (const auto& edge : existing_edges) {
        if (edge[0] != isolated_vertex && edge[1] != isolated_vertex) {
            updated_edges.push_back(edge);
        }
    }

    /* Get the shortest path length between two existing vertices */
    int source_out = shortest_path(existing_edges, 0, 1, input.n);

    /* Get the shortest path length between the same two existing vertices in the updated graph */
    int follow_out = shortest_path(updated_edges, 0, 1, input.n);

    /* Verification - Removing an isolated vertex should not change the shortest path length between any two existing vertices */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 33: Adding a cycle in the graph should not change the shortest path length between any pair of vertices.
 */
TEST_P(SpwikiParamTest, MR33) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Construct a graph with a cycle */
    vector<vector<int>> graph_with_cycle = existing_edges;
    graph_with_cycle.emplace_back(vector<int>{1, 4, 3});  // Adding an edge to create a cycle

    /* Get the shortest path length between two existing vertices */
    int source_out = shortest_path(existing_edges, 0, 2, input.n);

    /* Get the shortest path length between the same two existing vertices in the graph with a cycle */
    int follow_out = shortest_path(graph_with_cycle, 0, 2, input.n);

    /* Verification - Adding a cycle should not change the shortest path length between existing vertices */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 34: Adding a bridge in the graph should not change the shortest path length between any pair of non-adjacent vertices.
 */
TEST_P(SpwikiParamTest, MR34) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Construct a graph with a bridge */
    vector<vector<int>> graph_with_bridge = existing_edges;
    graph_with_bridge.emplace_back(vector<int>{4, 5, 7});  // Adding an edge to create a bridge

    /* Get the shortest path length between two non-adjacent vertices */
    int source_out = shortest_path(existing_edges, 0, 3, input.n);

    /* Get the shortest path length between the same two non-adjacent vertices in the graph with a bridge */
    int follow_out = shortest_path(graph_with_bridge, 0, 3, input.n);

    /* Verification - Adding a bridge should not change the shortest path length between non-adjacent vertices */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 35: Adding a shortcut path in the graph should not change the shortest path length between any pair of vertices.
 */
TEST_P(SpwikiParamTest, MR35) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Construct a graph with a shortcut path */
    vector<vector<int>> graph_with_shortcut = existing_edges;
    graph_with_shortcut.emplace_back(vector<int>{1, 3, 5}); // Adding an edge to create a shortcut path

    /* Get the shortest path length between two vertices without the shortcut */
    int source_out = shortest_path(existing_edges, 0, 4, input.n);

    /* Get the shortest path length between the same two vertices in the graph with the shortcut */
    int follow_out = shortest_path(graph_with_shortcut, 0, 4, input.n);

    /* Verification - Adding a shortcut path should not change the shortest path length between any pair of vertices */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 36: Changing the direction of a single edge in the graph should not change the shortest path length.
 */
TEST_P(SpwikiParamTest, MR36) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Select a single edge to change the direction */
    // Assuming the graph is non-directed, the direction change should not impact shortest paths
    vector<int> edge_to_change = existing_edges[0];
    vector<vector<int>> graph_with_directional_change = existing_edges;
    graph_with_directional_change.erase(graph_with_directional_change.begin());
    graph_with_directional_change.emplace_back(vector<int>{edge_to_change[1], edge_to_change[0], edge_to_change[2]});

    /* Get the shortest path length after changing the direction of the edge */
    int source_out = shortest_path(existing_edges, 0, 4, input.n);
    int follow_out = shortest_path(graph_with_directional_change, 0, 4, input.n);

    /* Verification - Changing the direction of a single edge should not change the shortest path length */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 37: Adding a long detour in the graph should not change the shortest path length between any pair of vertices.
 */
TEST_P(SpwikiParamTest, MR37) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Construct a graph with a detour */
    vector<vector<int>> graph_with_detour = existing_edges;
    graph_with_detour.emplace_back(vector<int>{1, 5, 10}); // Adding an edge to create a detour, increasing the distance between vertices 1 and 5

    /* Get the shortest path length between two vertices without the detour */
    int source_out = shortest_path(existing_edges, 0, 4, input.n);

    /* Get the shortest path length between the same two vertices in the graph with the detour */
    int follow_out = shortest_path(graph_with_detour, 0, 4, input.n);

    /* Verification - Adding a detour in the graph should not change the shortest path length between any pair of vertices */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 38: Adding or removing any isolated vertices in the graph should not change the shortest path length between any pair of vertices.
 */
TEST_P(SpwikiParamTest, MR38) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Add isolated vertices to the graph */
    vector<vector<int>> graph_with_isolated_vertices = existing_edges;
    graph_with_isolated_vertices.emplace_back(vector<int>{6, 7, 2}); // Adding an edge to create an isolated vertex 6
    graph_with_isolated_vertices.emplace_back(vector<int>{8, 9, 3}); // Adding an edge to create an isolated vertex 8

    /* Remove existing isolated vertices from the graph */
    vector<vector<int>> graph_without_isolated_vertices = existing_edges;
    // Remove edges incident to isolated vertices
    graph_without_isolated_vertices.erase(std::remove_if(graph_without_isolated_vertices.begin(), graph_without_isolated_vertices.end(), 
        [](const vector<int>& edge) { return edge[0] == 6 || edge[0] == 7 || edge[1] == 6 || edge[1] == 7; }), graph_without_isolated_vertices.end());

    /* Get the shortest path length between two vertices in the original graph and the modified graphs */
    int source_out = shortest_path(existing_edges, 0, 4, input.n);
    int follow_out_add = shortest_path(graph_with_isolated_vertices, 0, 4, input.n);
    int follow_out_remove = shortest_path(graph_without_isolated_vertices, 0, 4, input.n);

    /* Verification - Adding or removing isolated vertices in the graph should not change the shortest path length between any pair of vertices */
    EXPECT_EQ(source_out, follow_out_add);
    EXPECT_EQ(source_out, follow_out_remove);
}
/**
 * @brief Metamorphic Relation 39: Adding or removing parallel edges in the graph should not change the shortest path length between any pair of vertices.
 */
TEST_P(SpwikiParamTest, MR39) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;
    
    /* Add parallel edges to the graph */
    vector<vector<int>> graph_with_parallel_edges = existing_edges;
    graph_with_parallel_edges.push_back({0, 1, 3}); // Adding a parallel edge to the graph
    // Remove existing parallel edges from the graph
    vector<vector<int>> graph_without_parallel_edges = existing_edges;
    graph_without_parallel_edges.erase(
        std::remove(graph_without_parallel_edges.begin(), graph_without_parallel_edges.end(), vector<int>{0, 1, 2}), 
        graph_without_parallel_edges.end());

    /* Get the shortest path length between two vertices in the original graph and the modified graphs */
    int source_out = shortest_path(existing_edges, 0, 2, input.n);
    int follow_out_add = shortest_path(graph_with_parallel_edges, 0, 2, input.n);
    int follow_out_remove = shortest_path(graph_without_parallel_edges, 0, 2, input.n);

    /* Verification - Adding or removing parallel edges in the graph should not change the shortest path length between any pair of vertices */
    EXPECT_EQ(follow_out_add, source_out);
    EXPECT_EQ(follow_out_remove, source_out);
}

/**
 * @brief Metamorphic Relation 40: Adding a hub node in the graph should not change the shortest path length between non-adjacent vertices.
 */
TEST_P(SpwikiParamTest, MR40) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Construct a graph with a hub node */
    vector<vector<int>> graph_with_hub = existing_edges;
    // Add edges from the hub to the existing nodes
    for (int i = 0; i < existing_edges.size(); i++) {
        graph_with_hub.emplace_back(vector<int>{existing_edges[i][0], existing_edges[i][1], 3});
    }

    /* Get the shortest path length between two non-adjacent vertices */
    int source_out = shortest_path(existing_edges, 0, 3, input.n);

    /* Get the shortest path length between the same two non-adjacent vertices in the graph with a hub */
    int follow_out = shortest_path(graph_with_hub, 0, 3, input.n);

    /* Verification - Adding a hub node in the graph should not change the shortest path length between non-adjacent vertices */
    EXPECT_EQ(follow_out, source_out);
}
/**
 * @brief Metamorphic Relation 41: Replacing an edge in the graph with a shorter path of multiple edges should not change the shortest path length between any pair of vertices.
 */
TEST_P(SpwikiParamTest, MR41) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Construct a graph with a replaced shorter path of multiple edges */
    vector<vector<int>> graph_with_shorter_path = existing_edges;
    // Replace an edge with a shorter path of multiple edges
    graph_with_shorter_path.emplace_back(vector<int>{0, 3, 2});
    graph_with_shorter_path.emplace_back(vector<int>{3, 4, 3});
    graph_with_shorter_path.emplace_back(vector<int>{4, 2, 4});
    // Remove the original edge from the graph
    graph_with_shorter_path.erase(std::remove(graph_with_shorter_path.begin(), graph_with_shorter_path.end(), vector<int>{0, 2, 6}), 
                                graph_with_shorter_path.end());

    /* Get the shortest path length between two vertices with the original and replaced edges */
    int source_out = shortest_path(existing_edges, 0, 2, input.n);
    int follow_out = shortest_path(graph_with_shorter_path, 0, 2, input.n);

    /* Verification - Replacing an edge with a shorter path of multiple edges should not change the shortest path length between any pair of vertices */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 42: Adding a long bypass path in the graph should not change the shortest path length between any pair of vertices.
 */
TEST_P(SpwikiParamTest, MR42) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> existing_edges = input.edges;

    /* Construct a graph with a bypass path */
    vector<vector<int>> graph_with_bypass_path = existing_edges;
    // Add a long bypass path in the graph
    graph_with_bypass_path.emplace_back(vector<int>{0, 3, 5});
    graph_with_bypass_path.emplace_back(vector<int>{3, 4, 6});
    graph_with_bypass_path.emplace_back(vector<int>{4, 2, 3});

    /* Get the shortest path length between two vertices with and without the bypass path */
    int source_out = shortest_path(existing_edges, 0, 2, input.n);
    int follow_out = shortest_path(graph_with_bypass_path, 0, 2, input.n);

    /* Verification - Adding a long bypass path in the graph should not change the shortest path length between any pair of vertices */
    EXPECT_EQ(follow_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, SpwikiParamTest, testing::ValuesIn(gen_tcs_randomly()));