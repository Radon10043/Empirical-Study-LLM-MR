import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test10(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 10: If the directed graph is reversed (arrows flipped), the
        shortest path from a source to a destination should be the same as the shortest path from
        the destination to the source in the original directed graph."""
        # Get the distance matrix of the original graph
        original_dist_matrix = shortest_path(graph, method=method, directed=True)

        # Reverse the graph by transposing the matrix
        rev_graph = np.transpose(graph)
        rev_graph = np.ascontiguousarray(rev_graph)

        # Get the distance matrix of the reversed graph
        rev_dist_matrix = shortest_path(rev_graph, method=method, directed=True)

        # Verification that path(src, dst) in original equals path(dst, src) in reversed
        for src in range(len(graph)):
            for dst in range(len(graph)):
                self.assertEqual(original_dist_matrix[src][dst], rev_dist_matrix[dst][src])



if __name__ == "__main__":
    unittest.main()
