import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test38(self, efgraph: list, source: int, desst: int, method: str):  # Fixed
        """Metamorphic Relation 38: Given a weighted directed graph, reversing the direction of all edges
        should not change the set of achievable distances when considering all node pairs as src and dst."""
        # Get the set of shortest path distances for all pairs in original graph
        matrix = shortest_path(efgraph, method=method)
        original_distances = {(n1, n2): matrix[n1][n2] for n1 in range(len(efgraph)) for n2 in range(len(efgraph)) if n1 != n2}

        # Reverse the graph's edges to construct a new graph, assuming a utility function `reverse_edges` exists
        reversed_graph = np.transpose(efgraph)
        reversed_graph = np.ascontiguousarray(reversed_graph)

        # Get the set of shortest path distances for all pairs in the reversed graph
        matrix = shortest_path(reversed_graph, method=method)
        reversed_distances = {(n2, n1): matrix[n2][n1] for n1 in range(len(reversed_graph)) for n2 in range(len(reversed_graph)) if n1 != n2}

        # Verify that the set of distances is the same for the reversed graph
        self.assertEqual(set(original_distances.values()), set(reversed_distances.values()))


if __name__ == "__main__":
    unittest.main()
