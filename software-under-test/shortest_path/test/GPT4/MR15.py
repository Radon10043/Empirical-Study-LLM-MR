import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test15(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 15: Inverting the weights of all edges in a graph should not change
        the structure of the shortest paths, though the specific weights of the paths will change."""
        # Get source output for the original graph
        source_out, source_predecessors = shortest_path(graph, method=method, return_predecessors=True)

        # Invert weights of the graph for follow-up input
        inverted_graph = graph.copy()
        for i in range(len(inverted_graph)):
            for j in range(len(inverted_graph)):
                if inverted_graph[i][j] != 0:
                    inverted_graph[i][j] = 1 / inverted_graph[i][j]

        # Obtain a shortest path using inverted weights
        inverted_path_out, follow_predecessors = shortest_path(inverted_graph, method=method, return_predecessors=True)

        # Verification that the structure of the paths remains unchanged would require
        # more sophisticated analysis since we don't just compare path weights.
        # Assuming the existence of a function to extract shortest path sequences:
        source_path_sequence = get_shortest_path(source_predecessors, src, dst)
        inverted_path_sequence = get_shortest_path(follow_predecessors, src, dst)

        self.assertEqual(source_path_sequence, inverted_path_sequence)


if __name__ == "__main__":
    unittest.main()
