import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test24(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 24: Replacing all positive weights with a uniform positive value should preserve the optimal path, 
        although the path cost will be directly proportional to the number of edges on the path."""
        directed = choice([True, False])

        uniform_weight = 10
        # Get the shortest path and path nodes for the original weighted graph
        original_matrix, predecessors = shortest_path(graph, method=method, directed=directed, return_predecessors=True)
        original_path_nodes = get_shortest_path(predecessors, src, dst)

        # Construct a graph with uniform positive weights
        uniform_weight_graph = self.create_uniform_weight_graph(graph, uniform_weight)

        # Get follow-up distances and path nodes for uniform weight graph
        uniform_matrix, uniform_predecessors = shortest_path(uniform_weight_graph, method=method, directed=directed, return_predecessors=True)
        uniform_path_nodes = get_shortest_path(uniform_predecessors, src, dst)
        uniform_distance = uniform_matrix[src][dst]

        # The shortest path nodes should be the same, even though the weight of the path is different
        self.assertEqual(original_path_nodes, uniform_path_nodes)
        # The weight of the path will now be the uniform weight times the number of edges in the original path
        self.assertEqual(uniform_distance, uniform_weight * (len(original_path_nodes) - 1))

    def create_uniform_weight_graph(self, graph, uniform_weight):
        """Replace all positive weights in the graph with a uniform value."""
        uniform_weight_graph = graph.copy()
        for i in range(len(uniform_weight_graph)):
            for j in range(i, len(uniform_weight_graph)):
                if uniform_weight_graph[i][j] > 0:
                    uniform_weight_graph[i][j] = uniform_weight
        return uniform_weight_graph

if __name__ == "__main__":
    unittest.main()
