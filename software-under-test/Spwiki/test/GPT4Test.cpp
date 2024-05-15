#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "../src/function.h"
#include "utils.h"

using namespace std;

class SpwikiParamTest : public ::testing::TestWithParam<SpwikiInput> {};

/**
 * @brief Metamorphic Relation 3: Adding a new vertex and an edge that does not affect the shortest path between src and dst should not change the shortest path
 * distance.
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
    // Add a new vertex n, and an edge with a large weight that does not affect the original
    // shortest path.
    vector<vector<int>> follow_edges = source_edges;
    int new_vertex_id = source_n;                                        // Assume the new vertex ID is source_n
    follow_edges.push_back({new_vertex_id, new_vertex_id + 1, INT_MAX}); // Add a disconnected edge
    int follow_n = source_n + 2;                                         // Increment number of vertices

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, follow_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 4: If an alternative path is added with a smaller total weight than the original shortest path, the new shortest path distance
 * should be less than or equal to the original shortest path distance.
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
    // Create a new edge with lower weight than existing edges to potentially create a shorter path
    vector<vector<int>> follow_edges = source_edges;
    // Assuming there's a path from vertex src to vertex u and u to dst,
    // and that both src and dst are greater than or equal to 0 and less than n
    int u = (source_src + source_dst) / 2;      // A mid-way vertex
    follow_edges.push_back({source_src, u, 1}); // Very low weight edge from src to u
    follow_edges.push_back({u, source_dst, 1}); // Very low weight edge from u to dst

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 5: Removing an edge that is not part of the shortest path should not affect the shortest path distance.
 *
 */
TEST_P(SpwikiParamTest, MR5) { // Fixed
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Make sure the removed edge is not on the shortest_path */
    for (const auto &edge : source_edges) {
        if (((edge[0] == source_src && edge[1] == source_dst) || (edge[1] == source_src && edge[0] == source_dst)) && edge[2] == source_out) {
            GTEST_SKIP() << "The edge to remove is on the shortest path.";
        }
    }

    /* Construct follow-up input */
    // Remove an edge that's not on the current shortest path
    vector<vector<int>> follow_edges;
    for (const auto &edge : source_edges) {
        if ((edge[0] != source_src || edge[1] != source_dst) && (edge[1] != source_src || edge[0] != source_dst)) {
            // Assumes the removed edge is not on the shortest path
            follow_edges.push_back(edge);
        }
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 6: Permuting the vertices and consistently renaming the vertices in the edges should not change the shortest path distance.
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
    // Create a permutation map for vertex renaming
    std::unordered_map<int, int> vertex_permutation;
    for (int i = 0; i < source_n; ++i) {
        vertex_permutation[i] = (i + 1) % source_n; // Simple rotation permutation
    }
    // Apply the permutation to the edges
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        edge[0] = vertex_permutation[edge[0]];
        edge[1] = vertex_permutation[edge[1]];
    }
    int follow_src = vertex_permutation[source_src], follow_dst = vertex_permutation[source_dst];

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, follow_src, follow_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 7: Increasing the weight of each edge not on the shortest path should not change the shortest path distance.
 *
 */
TEST_P(SpwikiParamTest, MR7) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Get the shortest path edges (not provided, developer needs to implement this step to identify the edges in the current shortest path) */
    vector<vector<int>> shortest_path_edges = find_shortest_path_edges(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    // Increase the weight of edges not on the shortest path
    for (auto &edge : follow_edges) {
        // Assuming is_on_shortest_path is a predicate function that determines if an edge is on the shortest path
        if (!is_on_shortest_path(shortest_path_edges, edge)) {
            edge[2] += 100; // Increase the weight significantly
        }
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 8: Removing a vertex and its connecting edges that are not on the
 * shortest path should not change the shortest path distance.
 *
 */
TEST_P(SpwikiParamTest, MR8) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Get the vertices on the shortest path */
    std::set<int> shortest_path_vertices = get_shortest_path_vertices(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges;
    for (auto &edge : source_edges) {
        if (shortest_path_vertices.count(edge[0]) && shortest_path_vertices.count(edge[1])) {
            // If both vertices of the edge are in the shortest path, keep the edge
            follow_edges.push_back(edge);
        }
    }

    /* Decrement the count of vertices */
    int follow_n = source_n - 1;

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, follow_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 9: Reflexive relation, for any vertex v, the shortest path from v to v should be zero.
 *
 */
TEST_P(SpwikiParamTest, MR9) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src;
    int source_n = input.n;

    /* Construct follow-up input */
    // Source and destination vertices are the same for reflexive check
    int follow_src = source_src;
    int follow_dst = follow_src;

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, follow_src, follow_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, 0);
}

/**
 * @brief Metamorphic Relation 10: Adding a new edge that does not create a shorter path than the existing shortest path should not change the shortest path
 * distance.
 *
 */
TEST_P(SpwikiParamTest, MR10) { // Fixed
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    // Add an edge with a weight that is larger than the shortest path distance
    int new_weight = source_out + 10;                      // ensure the new edge doesn't create a shorter path
    follow_edges.push_back({0, source_n, new_weight}); // edge from vertex 0 to the last vertex

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n + 1);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 11: Adding an identical edge with the same weight should not change the shortest path distance.
 *
 */
TEST_P(SpwikiParamTest, MR11) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    // Add an edge that is identical to one of the existing edges
    vector<vector<int>> follow_edges = source_edges;
    follow_edges.push_back(source_edges[0]); // Assuming there is at least one edge

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 12: Swapping weights between edges while keeping the overall graph topology should not change the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR12) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    // Swap weights between two edges in the graph
    if (source_edges.size() > 1) { // Ensure there are at least two edges to swap between
        std::swap(source_edges[0][2], source_edges[1][2]);  // Swap the weights of the first two edges
    }
    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    // If the edges swapped are on the shortest path and their weights are unique,
    // the shortest path might be changed—if not, it remains the same.
    if (are_edges_on_shortest_path(source_edges[0], source_edges[1])) {
        EXPECT_NE(follow_out, source_out);
    } else {
        EXPECT_EQ(follow_out, source_out);
    }
#endif
}

/**
 * @brief Metamorphic Relation 13: Scaling weights of all edges by the same positive factor should not change the topology of the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR13) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
    const int scale_factor = 3; // Any positive integer scale factor

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    // Scale the weights of all edges by scale_factor
    for (vector<int> &edge : source_edges) {
        edge[2] *= scale_factor;
    }

    /* Get follow-up output with scaled input */
    int follow_out_scaled = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Get follow-up output with scaled source_out (assuming scaling affects shortest path distance) */
    int follow_out = source_out * scale_factor;

    /* Verification */
    EXPECT_EQ(follow_out_scaled, follow_out);
}

/**
 * @brief Metamorphic Relation 14: Changing the names of vertices consistently should not change the shortest path length.
 * Names transformation like: orig_name -> orig_name + 1
 *
 */
TEST_P(SpwikiParamTest, MR14) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    // Increase the name of every vertex by 1
    vector<vector<int>> increased_edges;
    for (auto &edge : source_edges) {
        increased_edges.push_back({edge[0] + 1, edge[1] + 1, edge[2]});
    }
    int increased_src = source_src + 1;
    int increased_dst = source_dst + 1;
    int increased_n = source_n + 1;

    /* Get follow-up output */
    int follow_out = shortest_path(increased_edges, increased_src, increased_dst, increased_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 15: If the start and end vertices of some edges are swapped, the shortest path distance must remain unchanged.
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
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        std::swap(edge[0], edge[1]); // Swap the start and end vertices of each edge
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 16: If all edge weights are translated by adding a constant value (besides INT_MAX), the minimum distance value should be
 * translated by the same constant multiplied by the number of edges in the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR16) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    int translation = 3;  // Constant translation, cannot be INT_MAX
    for (vector<int>& edge : follow_edges) {
        if (edge[2] < INT_MAX - translation) {
            edge[2] += translation;  // Translate the weight, avoiding overflow
        }
    }
    
    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification depends on the implementation of the program under test. If shortest path distances can be represented with overflow considerations, the translated weight should reflect the change */
    // Assuming shortest path edges can be determined, we adjust the expected outcome.
    int expected_follow_out = source_out; // Initialize with source_out value.
    if (expected_follow_out != INT_MAX) {
        int num_edges_in_shortest_path = get_number_of_edges_in_shortest_path(source_edges, source_src, source_dst, source_n);
        expected_follow_out += translation * num_edges_in_shortest_path; // Translate outcome by the number of edges in the shortest path.
    }
    EXPECT_EQ(follow_out, expected_follow_out);
#endif
}

/**
 * @brief Metamorphic Relation 17: After removing a vertex and all its connecting edges, if the vertex was not in the shortest path, the shortest path distance
 * must remain unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR17) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    int vertex_to_remove = ...; // Some vertex not part of the shortest path
    vector<vector<int>> follow_edges;
    for (const vector<int>& edge : source_edges) {
        if (edge[0] != vertex_to_remove && edge[1] != vertex_to_remove) {
            follow_edges.push_back(edge); // Keep all edges that do not include the vertex to remove
        }
    }
    int follow_n = source_n - 1;

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, follow_n);

    /* Verification */
    if (vertex_not_in_shortest_path(vertex_to_remove)) {
        EXPECT_EQ(follow_out, source_out);
    } else {
        EXPECT_NE(follow_out, source_out);
    }
#endif
}

/**
 * @brief Metamorphic Relation 18: The function must be idempotent, that is, performing the operation twice should provide the same result as doing it once.
 *
 */
TEST_P(SpwikiParamTest, MR18) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    // Perform the operation again without changing anything
    int follow_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 19: After inverting the graph (reversing the direction of each edge in a directed graph), the shortest path distance in an
 * undirected graph should stay unchanged.
 *
 */
TEST_P(SpwikiParamTest, MR19) {
    /* Provided the input graph is undirected, reversing edges has no meaning, and the testcase would be identical to MR15. */

    /* However, if the graph was directed, you would need to implement a function to reverse the graph's edge directions.
    This testcase is not applicable for an undirected graph, and would be removed or modified. */
}

/**
 * @brief Metamorphic Relation 20: Changing the weight of an edge on the shortest path to a higher value should result in the same or a longer shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR20) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Get the shortest path edges (not provided, developer needs to implement this step) */
    vector<vector<int>> shortest_path_edges = find_shortest_path_edges(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    // Increase the weight of one edge on the shortest path
    for (auto &edge : follow_edges) {
        if (is_edge_on_shortest_path(shortest_path_edges, edge)) {
            edge[2] += 10; // Increase the weight slightly
            break; // Increment weight of only one edge to avoid multiple effect
        }
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_GE(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 21: Adding a new edge with negligible weight (e.g., zero) should result in the same or a shorter shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR21) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    // Add a new edge with zero weight that might create a new shortest path
    follow_edges.push_back({0, source_n - 1, 0});

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 22: If the destination vertex becomes unreachable, the output should reflect that (e.g., return INT_MAX or a special value
 * indicating no path).
 *
 */
TEST_P(SpwikiParamTest, MR22) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Make the destination vertex unreachable */
    // Remove any edges connecting to the destination vertex
    vector<vector<int>> follow_edges;
    for (auto &edge : source_edges) {
        if (edge[0] != source_dst && edge[1] != source_dst) {
            follow_edges.push_back(edge);
        }
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    // Assuming INT_MAX is used to represent an unreachable vertex in the implementation
    EXPECT_EQ(follow_out, INT_MAX);
}

/**
 * @brief Metamorphic Relation 23: Adding a new edge that bypasses an intermediary vertex on the shortest path should result in the same or a shorter path.
 *
 */
TEST_P(SpwikiParamTest, MR23) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    // Let's say we bypass a vertex 'u' on the existing shortest path.
    // We need to identify such a vertex and the edges src->u and u->dst
    int intermediary_vertex_u = find_intermediary_vertex_on_path(source_edges, source_src, source_dst);
    int src_to_u_weight = find_edge_weight(source_edges, source_src, intermediary_vertex_u);
    int u_to_dst_weight = find_edge_weight(source_edges, intermediary_vertex_u, source_dst);

    follow_edges.push_back({source_src, source_dst, src_to_u_weight + u_to_dst_weight - 1});

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 24: Changing the start vertex in a connected graph should yield a shortest path distance within the range of existing distances.
 *
 */
TEST_P(SpwikiParamTest, MR24) {
#if 0
    /* Get source input for all pairs */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_n = input.n;
    vector<int> shortest_path_distances;

    /* Get source output for all pairs */
    for (int v = 0; v < source_n; ++v) {
        for (int u = 0; u < source_n; ++u) {
            int distance = shortest_path(source_edges, v, u, source_n);
            shortest_path_distances.push_back(distance);
        }
    }

    /* Get the range of shortest path distances */
    int min_distance = *std::min_element(shortest_path_distances.begin(), shortest_path_distances.end());
    int max_distance = *std::max_element(shortest_path_distances.begin(), shortest_path_distances.end());

    /* Changing the start vertex */
    int new_src = ...; // Select a different start vertex
    for (int u = 0; u < source_n; ++u) {
        int new_distance = shortest_path(source_edges, new_src, u, source_n);

        /* Verification */
        EXPECT_GE(new_distance, min_distance);
        EXPECT_LE(new_distance, max_distance);
    }
#endif
}

/**
 * @brief Metamorphic Relation 25: For an undirected graph, reversing the direction of all edges should not change the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR25) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input by reversing the direction of all edges */
    vector<vector<int>> reversed_edges = source_edges;
    for (auto &edge : reversed_edges) {
        std::swap(edge[0], edge[1]); // Swap start and end vertices
    }

    /* Get follow-up output */
    int reversed_out = shortest_path(reversed_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(source_out, reversed_out);
}

/**
 * @brief Metamorphic Relation 26: For a connected graph, converting it to a complete graph with same edge weights should not decrease the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR26) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input for a complete graph */
    vector<vector<int>> complete_edges;
    for (int i = 0; i < source_n; ++i) {
        for (int j = i + 1; j < source_n; ++j) {
            // Add edge with max possible weight assuming no edge exists
            int weight = INT_MAX;
            // Check if the edge is part of the original graph
            for (auto &edge : source_edges) {
                if ((edge[0] == i && edge[1] == j) || (edge[0] == j && edge[1] == i)) {
                    weight = edge[2];
                    break;
                }
            }
            complete_edges.push_back({i, j, weight});
            complete_edges.push_back({j, i, weight});
        }
    }

    /* Get follow-up output */
    int complete_out = shortest_path(complete_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_GE(complete_out, source_out);
}

/**
 * @brief Metamorphic Relation 27: Splitting an edge by introducing an intermediate vertex with two new edges should maintain or increase the shortest path
 * length.
 *
 */
TEST_P(SpwikiParamTest, MR27) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    // Pick an edge (e.g., the first one) to split by adding a new vertex
    vector<vector<int>> split_edges = source_edges;
    if (!source_edges.empty()) {
        vector<int> edge_to_split = source_edges.front();
        int new_vertex = source_n; // Assuming new vertex has an ID equal to source_n
        int weight_split_1 = edge_to_split[2] / 2;
        int weight_split_2 = edge_to_split[2] - weight_split_1;
        split_edges.push_back({edge_to_split[0], new_vertex, weight_split_1});
        split_edges.push_back({new_vertex, edge_to_split[1], weight_split_2});
        // Replace the original edge with one of the split edges to avoid duplicate
        split_edges[0] = split_edges[split_edges.size() - 2];
        // Remove last two elements which are now duplicates
        split_edges.pop_back();
        split_edges.pop_back();
    }

    /* Get follow-up output */
    int split_out = shortest_path(split_edges, source_src, source_dst, source_n + 1); // The number of vertices has increased by 1

    /* Verification */
    EXPECT_GE(split_out, source_out);
}

/**
 * @brief Metamorphic Relation 28: Introducing a new edge between two non-adjacent vertices on the shortest path should maintain or decrease the shortest path
 * length.
 *
 */
TEST_P(SpwikiParamTest, MR28) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    // The new edge to be introduced
    int u = ...; // Vertex on the shortest path
    int v = ...; // Another vertex on the shortest path
    int new_weight = ...; // Weight less than the current path between u and v on the shortest path
    vector<vector<int>> new_edge_edges = source_edges;
    new_edge_edges.push_back({u, v, new_weight});

    /* Get follow-up output */
    int new_edge_out = shortest_path(new_edge_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_LE(new_edge_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 29: Concatenating the existing graph with a copy of itself should double the shortest path between identical vertices in the two
 * graphs.
 *
 */
TEST_P(SpwikiParamTest, MR29) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> original_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int original_out = shortest_path(original_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> concatenated_edges = original_edges;
    int offset = source_n; // Offset vertices for the new graph

    // Add a copy of the original graph, with vertices offset by 'source_n'
    for (const auto &edge : original_edges) {
        concatenated_edges.push_back({edge[0] + offset, edge[1] + offset, edge[2]});
    }

    /* Get follow-up output */
    int concatenated_out = shortest_path(concatenated_edges, source_src, source_dst + offset, source_n * 2); // Number of vertices is now doubled

    /* Verification */
    EXPECT_EQ(concatenated_out, 2 * original_out);
}

/**
 * @brief Metamorphic Relation 30: Connecting all vertices to a new super vertex should not change the shortest path between any two original vertices.
 *
 */
TEST_P(SpwikiParamTest, MR30) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> original_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int original_out = shortest_path(original_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> updates_edges = original_edges;
    int super_vertex_id = source_n; // New super vertex ID

    // Connect every vertex to the super_vertex with high enough weight to not affect shortest path
    for (int i = 0; i < source_n; ++i) {
        updates_edges.push_back({i, super_vertex_id, INT_MAX / 2});
    }

    /* Get follow-up output */
    int updated_out = shortest_path(updates_edges, source_src, source_dst, source_n + 1); // Number of vertices increased by 1

    /* Verification */
    EXPECT_EQ(updated_out, original_out);
}

/**
 * @brief Metamorphic Relation 31: For each edge that does not lie on a shortest path from source to destination, increasing its weight should not change the
 * shortest path distance.
 *
 */
TEST_P(SpwikiParamTest, MR31) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> original_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int original_out = shortest_path(original_edges, source_src, source_dst, source_n);

    /* Determine shortest path edges (not provided) */
    vector<vector<int>> shortest_path_edges = find_shortest_path_edges(original_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> updated_edges;
    for (const auto& edge : original_edges) {
        if (!is_edge_on_shortest_path(shortest_path_edges, edge)) {
            updated_edges.push_back({edge[0], edge[1], edge[2] + 1000}); // Increase weight significantly
        } else {
            updated_edges.push_back(edge); // Leave shortest path edges unchanged
        }
    }

    /* Get follow-up output */
    int updated_out = shortest_path(updated_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(updated_out, original_out);
#endif
}

/**
 * @brief Metamorphic Relation 32: If each edge weight is reduced by subtracting a common decrement, the shortest path distance should be no greater than the
 * original shortest path distance.
 *
 */
TEST_P(SpwikiParamTest, MR32) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
    int decrement = 1; // Common decrement value, assuming there are no edges with weight less than 1

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> follow_edges = source_edges;
    for (auto &edge : follow_edges) {
        if (edge[2] > 1) { // Only decrement if the original weight is greater than 1
            edge[2] -= decrement;
        }
    }

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_LE(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 33: Inverting the weights of all edges (by applying a function f(x) = (C - x) where C is a constant greater than the maximum
 * weight) should not break the monotonicity of the path costs.
 *
 */
TEST_P(SpwikiParamTest, MR33) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
    int max_weight = find_maximum_weight(source_edges) + 1; // Find the maximum weight and add 1 to it to define the constant C

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input by inverting the weights */
    vector<vector<int>> inverted_edges = source_edges;
    for (auto& edge : inverted_edges) {
        if (edge[2] < max_weight) {
            edge[2] = max_weight - edge[2];
        }
    }

    /* Get follow-up output */
    int inverted_out = shortest_path(inverted_edges, source_src, source_dst, source_n);

    /* Verification will compare the path costs without assuming the actual distances because inversion changes the cost structure of the graph */
    // Assuming function to determine if the shortest path costs are monotonically increased or decreased
    EXPECT_TRUE(are_path_costs_monotonic(source_edges, inverted_edges, source_src, source_dst, source_n));
#endif
}

/**
 * @brief Metamorphic Relation 34: Shifting all vertices' identifiers by a fixed amount with appropriate re-labeling of edges should result in the same shortest
 * path distance.
 *
 */
TEST_P(SpwikiParamTest, MR34) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
    int shift = 10; // Shifting factor

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> shifted_edges;
    for (auto edge : source_edges) {
        edge[0] = (edge[0] + shift) % source_n;
        edge[1] = (edge[1] + shift) % source_n;
        shifted_edges.push_back(edge);
    }
    int shifted_src = (source_src + shift) % source_n;
    int shifted_dst = (source_dst + shift) % source_n;

    /* Get follow-up output */
    int follow_out = shortest_path(shifted_edges, shifted_src, shifted_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 35: Combining two disjoint graphs into one, keeping the original vertices and edges intact, should not affect the shortest paths
 * within each original graph.
 *
 */
TEST_P(SpwikiParamTest, MR35) {
#if 0
    // Assume we have two sets of inputs for two disjoint graphs, input1 and input2
    SpwikiInput input1 = GetParam();
    SpwikiInput input2 = GetAnotherParam(); // This is another set of parameters for a second disjoint graph
    vector<vector<int>> edges1 = input1.edges;
    vector<vector<int>> edges2 = input2.edges;
    int n1 = input1.n;
    int n2 = input2.n;
    // Assume both graphs are disjoint and n2 > n1 (the second graph has IDs greater than the first graph)

    // Get the shortest paths for both original graphs
    int source_out1 = shortest_path(edges1, input1.src, input1.dst, n1);
    int source_out2 = shortest_path(edges2, input2.src, input2.dst, n2);

    // Combine the two disjoint graphs
    vector<vector<int>> combined_edges = edges1;
    combined_edges.insert(combined_edges.end(), edges2.begin(), edges2.end());

    // Get the shortest paths in the combined graph for both original src-dst pairs
    int combined_out1 = shortest_path(combined_edges, input1.src, input1.dst, n1 + n2);
    int combined_out2 = shortest_path(combined_edges, input2.src, input2.dst, n1 + n2);

    /* Verification */
    EXPECT_EQ(source_out1, combined_out1);
    EXPECT_EQ(source_out2, combined_out2);
#endif
}

/**
 * @brief Metamorphic Relation 36: Deleting a subset of edges and vertices that are not part of any shortest path in the graph should not change the shortest
 * path between two vertices if it exists.
 *
 */
TEST_P(SpwikiParamTest, MR36) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    vector<int> source_vertices; // List of vertices involved in source_edges
    for (const auto &edge : source_edges) {
        source_vertices.push_back(edge[0]);
        source_vertices.push_back(edge[1]);
    }
    std::sort(source_vertices.begin(), source_vertices.end());
    source_vertices.erase(std::unique(source_vertices.begin(), source_vertices.end()), source_vertices.end());
    int source_src = input.src, source_dst = input.dst, source_n = source_vertices.size(); // Assuming vertices are 0 to n-1

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Identify which vertices and edges are not on any shortest path from source_src to any other vertex */
    vector<vector<int>> not_on_shortest_path_edges;
    vector<int> not_part_of_any_shortest_path_vertices;

    // Hypothetical functions needed:
    // find_all_shortest_paths_edges(source_edges, source_src, source_n) -> list of edges part of shortest paths
    // all_vertices_in_shortest_paths will be a set of vertices that are part of some shortest path starting from source_src

    /* Construct follow-up input */
    vector<vector<int>> follow_edges;
    for (const auto &edge : source_edges) {
        if (std::find(not_on_shortest_path_edges.begin(), not_on_shortest_path_edges.end(), edge) == not_on_shortest_path_edges.end()) {
            follow_edges.push_back(edge); // Keep only the edges that are part of some shortest path
        }
    }
    std::vector<int> follow_vertices = source_vertices;
    follow_vertices.erase(std::remove_if(follow_vertices.begin(), follow_vertices.end(),
                                         [&](int v) {
                                             return std::find(not_part_of_any_shortest_path_vertices.begin(), not_part_of_any_shortest_path_vertices.end(),
                                                              v) != not_part_of_any_shortest_path_vertices.end();
                                         }),
                          follow_vertices.end());
    int follow_n = follow_vertices.size();

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, follow_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 37: In a weighted undirected graph, converting all edge weights to their absolute values should not affect the shortest path
 * computation.
 *
 */
TEST_P(SpwikiParamTest, MR37) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> absolute_edges = source_edges;
    for (auto &edge : absolute_edges) {
        edge[2] = std::abs(edge[2]); // Apply absolute value on weights
    }

    /* Get follow-up output */
    int absolute_out = shortest_path(absolute_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(absolute_out, source_out);
}

/**
 * @brief Metamorphic Relation 38: Multiplying all edge weights by a common positive integer factor should not change the relative weights of the paths and thus
 * the selection of the shortest path.
 *
 */
TEST_P(SpwikiParamTest, MR38) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;
    int factor = 3; // Common positive integer factor for multiplication

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    vector<vector<int>> scaled_edges = source_edges;
    for (auto& edge : scaled_edges) {
        edge[2] *= factor; // Multiply weights by common factor
    }

    /* Get follow-up output */
    int scaled_out = shortest_path(scaled_edges, source_src, source_dst, source_n);

    /* Verification */
    std::set<std::vector<int>> original_shortest_paths = all_shortest_paths_set(source_edges, source_n, source_src);
    std::set<std::vector<int>> scaled_shortest_paths = all_shortest_paths_set(scaled_edges, source_n, source_src);
    EXPECT_EQ(original_shortest_paths, scaled_shortest_paths); // The sets of shortest paths should remain the same
#endif
}

/**
 * @brief Metamorphic Relation 39: If the destination vertex in the follow-up test case is a neighbor of the destination vertex in the source test case, and the
 * edge connecting them is the last edge in the shortest path, the difference in the shortest path distances should equal the weight of the connecting edge.
 *
 */
TEST_P(SpwikiParamTest, MR39) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src;
    int source_dst = input.dst; // Assume this is not a neighbor to the source vertex
    int source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    // Assume a new destination follow_dst that is a neighbor to source_dst.
    // The new destination is connected with an edge of weight = weight_connect.
    int follow_dst = source_dst + 1; // Neighbor vertex; ensure it is within bounds of [0, n).
    int weight_connect = 5;          // Edge weight from source_dst to follow_dst.
    // Add edge connecting source_dst to follow_dst
    source_edges.push_back({source_dst, follow_dst, weight_connect});

    /* Get follow-up output */
    int follow_out = shortest_path(source_edges, source_src, follow_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out + weight_connect);
}

/**
 * @brief Metamorphic Relation 40: Replacing all weights of a connected graph with a constant should result in the shortest path equivalent to the smallest
 * number of hops between source and destination.
 *
 */
TEST_P(SpwikiParamTest, MR40) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Construct follow-up input */
    const int constant_weight = 1; // Replace all weights with 1
    vector<vector<int>> constant_weight_edges = source_edges;
    for (auto &edge : constant_weight_edges) {
        edge[2] = constant_weight; // Set the constant weight
    }

    /* Get follow-up output, shortest path distance in the constant-weight graph */
    int constant_weight_out = shortest_path(constant_weight_edges, source_src, source_dst, source_n);

    /* Verification, using a helper function to count the hops in the original shortest path */
    int expected_hops = count_hops_in_shortest_path(source_edges, source_src, source_dst, source_n);
    int expected_constant_weight_distance = expected_hops * constant_weight; // In a constant-weight graph, distance is the number of hops multiplied by the constant
    EXPECT_EQ(constant_weight_out, expected_constant_weight_distance);
#endif
}

/**
 * @brief Metamorphic Relation 41: If an intermediate vertex exists on the shortest path, removing it along with its connecting edges and adding a direct edge
 * between its neighbors with the sum of the two weights should not change the shortest path length.
 *
 */
TEST_P(SpwikiParamTest, MR41) {
#if 0
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    // Let's hypothetically assume that there is an intermediate vertex 'v' in the shortest path from 'src' to 'dst'
    int intermediate_v = ...; // This would be identified through an auxiliary function
    int neighbor1 = ..., neighbor2 = ...; // The immediate neighbors of 'v' in the shortest path
    int weight_n1_to_v = ..., weight_v_to_n2 = ...; // The original weights in the shortest path

    /* Construct follow-up input */
    vector<vector<int>> follow_edges;
    // Remove 'v' and its edges
    for (const auto& edge : source_edges) {
        if (edge[0] != intermediate_v && edge[1] != intermediate_v) {
            follow_edges.push_back(edge);
        }
    }
    // Add a direct edge between two neighbors of 'v' in the shortest path
    follow_edges.push_back({neighbor1, neighbor2, weight_n1_to_v + weight_v_to_n2});

    /* Get follow-up output */
    int follow_out = shortest_path(follow_edges, source_src, source_dst, source_n);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
#endif
}

/**
 * @brief Metamorphic Relation 42: Symmetrical transformation of vertex identifiers (through a bijection) should give an identical shortest path distance.
 *
 */
TEST_P(SpwikiParamTest, MR42) {
    /* Get source input */
    SpwikiInput input = GetParam();
    vector<vector<int>> source_edges = input.edges;
    int source_src = input.src, source_dst = input.dst, source_n = input.n;

    /* Get source output */
    int source_out = shortest_path(source_edges, source_src, source_dst, source_n);

    /* Construct follow-up input */
    std::unordered_map<int, int> bijection_map; // Mapping from original to transformed vertex identifiers, bijection ensures one-to-one and onto
    // Populate bijection_map: here we perform a simple bijection where we map the vertex 'i' to '(i + n/2) % n'
    for (int i = 0; i < source_n; ++i) {
        bijection_map[i] = (i + source_n / 2) % source_n;
    }
    vector<vector<int>> transformed_edges;
    for (const auto &edge : source_edges) {
        transformed_edges.push_back({bijection_map[edge[0]], bijection_map[edge[1]], edge[2]});
    }
    int transformed_src = bijection_map[source_src];
    int transformed_dst = bijection_map[source_dst];

    /* Get follow-up output */
    int transformed_out = shortest_path(transformed_edges, transformed_src, transformed_dst, source_n);

    /* Verification */
    EXPECT_EQ(transformed_out, source_out);
}

INSTANTIATE_TEST_CASE_P(TrueReturn, SpwikiParamTest, testing::ValuesIn(gen_tcs_randomly()));
