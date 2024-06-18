import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list,src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 29: Adding new nodes and edges that do not provide a shortcut path to
        existing nodes should not change the shortest paths in the original graph."""
        # Assume add_nodes is a list of nodes and their edges to add to the graph
        # Build an extended graph with the additional nodes and edges
        extended_graph = deepcopy(graph)
        add_cnt = 2
        for i in range(len(graph)):
            extended_graph[i] += [1e6 for _ in range(add_cnt)]
        extended_graph += [[1e6 for _ in range(len(graph) + add_cnt)] for _ in range(add_cnt)]

        # Get shortest paths of the original graph
        original_dist_matrix = shortest_path(graph, method=method)

        # Get shortest paths of the extended graph
        extended_dist_matrix = shortest_path(extended_graph, method=method)

        # Compare distances, which should remain the same for the original nodes
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertEqual(original_dist_matrix[i][j], extended_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
