import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test23(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 23: Concatenating any number of shortest paths should not yield a path
        that is shorter than any direct shortest path between any two nodes."""
        graph = csr_matrix(graph)

        # Get original distance matrix
        original_dist_matrix = shortest_path(graph)

        # Combine shortest paths between different nodes to form indirect paths
        node_count = graph.shape[0]
        for start_node in range(node_count):
            for intermediate_node1 in range(node_count):
                for end_node in range(node_count):
                    if start_node != intermediate_node1 and intermediate_node1 != end_node:
                        # Create an indirect path via an intermediate node
                        indirect_path_dist = (original_dist_matrix[start_node][intermediate_node1] +
                                            original_dist_matrix[intermediate_node1][end_node])
                        # Check if the indirect path is longer than direct path
                        self.assertLessEqual(original_dist_matrix[start_node][end_node], indirect_path_dist)


if __name__ == "__main__":
    unittest.main()
