import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test22(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 22: After adding a new edge with a negative weight to the graph, the 
        shortest path distance should decrease or remain the same."""
        # Get source output for the original graph
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Add a new edge with negative weight to the graph
        new_edge_src = src  # or any other node
        new_edge_dst = dst  # or any other node different from new_edge_src
        follow_graph = graph.copy()
        follow_graph[new_edge_src][new_edge_dst] = -5

        # Get follow-up output after adding the negative weight edge
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification: the shortest path distance should decrease or remain the same
        self.assertLessEqual(new_distance, original_distance)


if __name__ == "__main__":
    unittest.main()
