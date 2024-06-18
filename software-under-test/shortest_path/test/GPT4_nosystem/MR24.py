import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test24(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 24: The shortest path from a source to a destination, when the
        destination is added as a new source with zero-weight edges to all other nodes, should
        remain unchanged."""
        follow_graph = deepcopy(graph)
        for i in range(len(follow_graph)):
            follow_graph[i] = follow_graph[i] + [0]
        follow_graph.append([0 for _ in range(len(follow_graph) + 1)])

        num_v = len(graph)
        graph = csr_matrix(graph)
        follow_graph = csr_matrix(follow_graph)

        # Compute the original shortest path distances
        original_dist_matrix = shortest_path(graph)

        # Compute the shortest path distances with the new source node
        new_source_dist_matrix = shortest_path(follow_graph)

        # Compare the distances from the new source to the destination with original distances
        self.assertEqual(original_dist_matrix[src][dst], new_source_dist_matrix[src][dst])


if __name__ == "__main__":
    unittest.main()
