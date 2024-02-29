import unittest
import os, json
import scipy


import numpy as np

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

from utils import gen_tcs_randomly


def load_test_cases() -> list:
    """加载测试用例

    Returns
    -------
    list
        存储测试用例的列表

    Notes
    -----
    _description_
    """
    return gen_tcs_randomly()


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test1(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 1: Given the same graph, the same source and destination vertices,
        but with reversed direction (directed/undirected), the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test2(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 2: Given the same graph, the same source and destination vertices,
        but with the weights negated, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, unweighted=False)[src][dst]

        follow_graph = list()
        for row in graph:
            follow_graph.append([-x for x in row])

        # Get folllow-up output
        follow_out = shortest_path(follow_graph, method=method, unweighted=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test3(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 3: Given the same graph, the same source and destination vertices,
        but with a cut-off threshold for Dijkstra's algorithm, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, limit=None)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method, limit=10)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test4(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 4: Given the same graph, the same source and destination vertices,
        but representing a sub-graph (specific indices), the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, indices=None)[src][dst]

        # Construct follow-up input
        indices = [1, 3, 5]  # Example indices
        follow_out = shortest_path(graph, method=method, indices=indices)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)
    
    @parameterized.expand(load_test_cases)
    def test5(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 5: Given the same graph, the same source and destination vertices,
        but using the Bellman-Ford algorithm, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method='BF')[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test6(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 6: Given the same graph, the source and destination vertices swapped,
        the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test7(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 7: Given the same graph, the same source and destination vertices,
        but using unweighted input graph, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, unweighted=False)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method, unweighted=True)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    # fixed
    @parameterized.expand(load_test_cases)
    def test8(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 8: Given the same graph, the same source and destination vertices,
        but with different starting methods leading to the same method, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input
        follow_method = "auto" if method == "FW" else "FW"
        # Convert the list to a sparse matrix
        sparse_graph = scipy.sparse.csr_matrix(graph)
        follow_out = shortest_path(sparse_graph, method=follow_method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)
    
    @parameterized.expand(load_test_cases)
    def test9(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 9: Given the same graph with different edge weights, the output follows the triangle inequality."""
        # Get source outputs
        dist_a_b = shortest_path(graph, method=method)[src][dst]
        dist_a_c = shortest_path(graph, method=method)[src][1] # Example vertex
        dist_c_b = shortest_path(graph, method=method)[1][dst] # Example vertex

        # Verification - Triangle Inequality
        self.assertTrue(dist_a_b <= dist_a_c + dist_c_b)

    @parameterized.expand(load_test_cases)
    def test10(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 10: Given the same graph, the same source and destination vertices,
        but with different algorithms, the output should still satisfy the triangle inequality."""
        # Get source outputs
        source_out = shortest_path(graph, method=method)[src][dst]
        follow_out = shortest_path(graph, method='D')[src][dst]  # Using a different algorithm

        # Verification - Triangle Inequality
        self.assertTrue(source_out <= follow_out)
    
    @parameterized.expand(load_test_cases)
    def test11(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 11: Given the same graph, the same source and destination vertices,
        but with different algorithms, the output should have the property of monotonicity."""
        # Get source outputs
        source_out = shortest_path(graph, method=method)[src][dst]
        follow_out = shortest_path(graph, method='BF')[src][dst]  # Using a different algorithm

        # Verification - Monotonicity
        self.assertTrue(source_out >= follow_out)

    @parameterized.expand(load_test_cases)
    def test12(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 12: Given the same graph, the same source and destination vertices,
        but with a different scale for the edge weights, the output should have the property of monotonicity."""
        # Get source outputs
        source_out = shortest_path(graph, method=method)[src][dst]
        
        follow_graph = list()
        for row in graph:
            follow_graph.append([x * 2 for x in row])

        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification - Monotonicity
        self.assertTrue(source_out <= follow_out)

    @parameterized.expand(load_test_cases)
    def test13(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 13: Given the same graph, the same source and destination vertices,
        but with the weights multiplied by a positive constant, the shortest path remains the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        follow_graph = [[weight * 2 for weight in row] for row in graph]

        # Get folllow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test14(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 14: Given the same graph, the same source and destination vertices,
        but with the edge weights changed to their absolute values, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        follow_graph = [[abs(weight) for weight in row] for row in graph]

        # Get folllow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)
    
    @parameterized.expand(load_test_cases)
    def test15(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 15: Given the same graph, the same source and destination vertices,
        but with the weights changed with a constant offset, the shortest path remains the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        offset = 5
        follow_graph = [[weight + offset for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test16(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 16: Given the same input graph, the same source and destination vertices,
        but with the weights multiplied by -1 and the direction reversed, the distances should not change."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)[src][dst]

        follow_graph = [[-weight for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method, directed=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)
    
    @parameterized.expand(load_test_cases)
    def test17(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 17: Given the same graph, the same source and destination vertices,
        but with the graph representing an undirected graph, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)[src][dst]

        # Construct follow-up input: representing an undirected graph
        follow_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test18(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 18: Given the same graph, the same source and destination vertices,
        but with the graph having a limit for Dijkstra's algorithm, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, limit=None)[src][dst]

        # Construct follow-up input: applying a limit for Dijkstra's algorithm
        follow_out = shortest_path(graph, method=method, limit=5)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test19(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 19: Given the same graph, the same source and destination vertices,
        but with the nodes specified for the shortest paths, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, indices=None)[src][dst]

        # Construct follow-up input: specifying nodes for the shortest paths
        indices = [1, 2, 3]  # Example indices
        follow_out = shortest_path(graph, method=method, indices=indices)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test20(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 20: Given the same graph, the source and destination vertices swapped,
        the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input: swapping the source and destination vertices
        follow_out = shortest_path(graph, method=method)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test21(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 21: Given the same graph and vertices, the output should be the same irrespective of the path reconstruction option."""
        # Get source output
        source_out = shortest_path(graph, method=method, return_predecessors=True)[src][dst]

        # Construct follow-up input: without path reconstruction
        follow_out = shortest_path(graph, method=method, return_predecessors=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    # fixed
    @parameterized.expand(load_test_cases)
    def test22(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 22: Given the same graph, the same source and destination vertices,
        but with different algorithms, the output should follow the same sequence of vertices for the shortest path."""
        # Get source output
        source_out = shortest_path(graph, method=method, return_predecessors=True)[1]

        # Construct follow-up input: using a different algorithm
        follow_out = shortest_path(graph, method='D', return_predecessors=True)[1]

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))

    @parameterized.expand(load_test_cases)
    def test23(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 23: Given the same graph and vertices, the output should be the same irrespective of whether the input is unweighted or weighted."""
        # Get source output with weighted input graph
        source_weighted = shortest_path(graph, method=method, unweighted=False)[src][dst]
        
        # Get source output with unweighted input graph
        source_unweighted = shortest_path(graph, method=method, unweighted=True)[src][dst]

        # Verification
        self.assertEqual(source_weighted, source_unweighted)

    @parameterized.expand(load_test_cases)
    def test24(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 24: Given the same graph and vertices, but with the edge weights scaled by a constant factor, the output should also be scaled by the same factor."""
        scale_factor = 2
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input with scaled edge weights
        follow_graph = [[weight * scale_factor for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertAlmostEqual(source_out * scale_factor, follow_out)

    @parameterized.expand(load_test_cases)
    def test25(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 25: Given the same graph, the same source and destination vertices, and the same algorithm, 
        but with all weights increased by a constant value, the resulting shortest path should remain the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Increase all weights in the graph by a constant value
        follow_graph = [[weight + 5 for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test26(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 26: Given the same graph and vertices, the output of the shortest path should remain the same if
        the same graph is represented using different sparse matrix formats."""
        from scipy.sparse import csr_matrix, csc_matrix
        import numpy as np
        
        # Create a csr_matrix from the original graph
        csr_graph = csr_matrix(np.array(graph))

        # Get source output using csr_matrix
        source_out_csr = shortest_path(csr_graph, method=method)[src][dst]

        # Create a csc_matrix from the original graph
        csc_graph = csc_matrix(np.array(graph))

        # Get follow-up output using csc_matrix
        follow_out_csc = shortest_path(csc_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out_csr, follow_out_csc)

    @parameterized.expand(load_test_cases)
    def test27(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 27: Given the same graph with the same source and destination vertices, the output should remain the same 
        irrespective of the presence of negative edge weights."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Create a graph with negative edge weights
        negative_graph = [[-weight for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(negative_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test28(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 28: Given the same graph and vertices, the output of the shortest path should remain the same if
        the graph is represented using a different storage type (e.g., list of lists vs. NumPy array)."""
        import numpy as np

        # Get source output using list of lists
        source_out_list = shortest_path(graph, method=method)[src][dst]

        # Convert the graph to a NumPy array
        np_graph = np.array(graph)

        # Get follow-up output using NumPy array
        follow_out_np = shortest_path(np_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out_list, follow_out_np)

    @parameterized.expand(load_test_cases)
    def test29(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 29: Given the same graph, the same source and destination vertices, reversing the direction of all edges 
        should maintain the shortest path."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Reverse the direction of all edges
        reversed_graph = [row[::-1] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(reversed_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test30(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 30: Given the same graph and vertices, removing all edges incident on a particular vertex should not affect the shortest path for other vertices."""
        import copy

        # Get source output for destination vertex
        source_out_dst = shortest_path(graph, method=method)[src][dst]

        # Remove all edges incident on destination vertex
        modified_graph = copy.deepcopy(graph)
        for i in range(len(modified_graph)):
            modified_graph[i][dst] = 0

        # Get follow-up output for destination vertex
        follow_out_dst = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out_dst, follow_out_dst)

        # Get source output for a different vertex
        other_vertex = (dst + 1) % len(graph)  # Selecting a different vertex
        source_out_other = shortest_path(graph, method=method)[src][other_vertex]

        # Get follow-up output for the different vertex
        follow_out_other = shortest_path(modified_graph, method=method)[src][other_vertex]

        # Verification
        self.assertEqual(source_out_other, follow_out_other)

    @parameterized.expand(load_test_cases)
    def test31(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 31: Given the same graph, the same source and destination vertices,
        but with one edge weight incremented by a certain amount,
        the new shortest path length should be at least the original shortest path length."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Increase the weight of a single edge
        follow_graph = [row[:] for row in graph]
        follow_graph[0][1] += 1  # Increment the weight of edge (0, 1)

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(new_distance, original_distance)

    @parameterized.expand(load_test_cases)
    def test32(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 32: Given the same graph, the same source and destination vertices,
        but with edge weights multiplied by a constant factor,
        the new shortest path length should be multiplied by the same factor."""
        scale_factor = 2

        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Multiply all edge weights by the scale factor
        follow_graph = [[weight * scale_factor for weight in row] for row in graph]

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertAlmostEqual(new_distance, original_distance * scale_factor)

    @parameterized.expand(load_test_cases)
    def test33(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 33: Given the same graph, the same source and destination vertices, and the same algorithm,
        but with all weights decreased by a constant value, the resulting shortest path should remain the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Decrease all weights in the graph by a constant value
        follow_graph = [[weight - 3 for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

    # fixed
    @parameterized.expand(load_test_cases)
    def test34(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 34: Given the same graph and vertices, the output of the shortest path should remain the same if
        the same graph is represented using a different mutable data structure with the exact same elements."""
        from collections import defaultdict

        # Get source output using a list representation of the graph
        source_out_list = shortest_path(graph, method=method)[src][dst]

        # Ensure each row of the graph is represented as a dictionary
        graph_dict = [{idx: val for idx, val in enumerate(row)} for row in graph]

        # Convert the graph to a different mutable data structure (defaultdict)
        # dd_graph = [defaultdict(int, enumerate(row)) for row in graph]
        dd_graph = np.array([list(row.values()) for row in graph])

        # Get follow-up output using the converted data structure
        follow_out_dd = shortest_path(dd_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out_list, follow_out_dd)

    @parameterized.expand(load_test_cases)
    def test35(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 35: Given the same graph, the same source and destination vertices, but with a single edge removed, 
        the shortest path length should either remain the same or be greater."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Remove a single edge
        follow_graph = [row[:] for row in graph]
        follow_graph[0][1] = 0  # Remove the edge (0, 1)

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(new_distance, original_distance)

    @parameterized.expand(load_test_cases)
    def test36(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 36: Given the same graph, the same source and destination vertices, 
        but with an additional edge between two vertices, 
        the shortest path length should remain the same or decrease."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Add an additional edge with a lower weight
        follow_graph = [row[:] for row in graph]
        follow_graph[0][1] = 1  # Add an edge (0, 1) with weight 1

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(new_distance, original_distance)

    @parameterized.expand(load_test_cases)
    def test37(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 37: Given the same graph, the same source and destination vertices,
        but with all weights incremented by 1, the resulting shortest path length should remain the same."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Increment all weights in the graph by 1
        follow_graph = [[weight + 1 for weight in row] for row in graph]

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_distance, new_distance)

    @parameterized.expand(load_test_cases)
    def test38(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 38: Given the same graph, the same source and destination vertices,
        but with the graph represented as a completely disconnected graph, 
        the shortest path length should be infinity."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Create a disconnected graph
        follow_graph = [[float('inf') if weight!=0 else 0 for weight in row] for row in graph]

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(new_distance, float('inf'))

    @parameterized.expand(load_test_cases)
    def test39(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 39: Given the same graph, the same source and destination vertices, and the same algorithm,
        but with all weights set to the same value, the resulting shortest path should remain the same."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Set all weights in the graph to the same value
        follow_graph = [[5 for _ in row] for row in graph]

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_distance, new_distance)

    @parameterized.expand(load_test_cases)
    def test40(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 40: Given the same graph, the same source and destination vertices,
        but with one additional edge, the shortest path should remain the same or be shorter."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Add an additional edge
        follow_graph = [row[:] for row in graph]
        follow_graph[3][4] = 3  # Add an edge (3, 4) with weight 3

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(new_distance, original_distance)


if __name__ == "__main__":
    unittest.main()