import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test32(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 32: If we compute the shortest paths only for a subset of nodes, then
        the distances for those nodes should be the same as when computed for the full set of nodes."""
        node_subset = [0, 1]

        # Compute the full shortest path distances
        full_dists = shortest_path(graph)

        # Compute the shortest path distances for only the subset of nodes
        sub_dists = shortest_path(graph, indices=node_subset)

        # Verify that the distances for the node_subset are the same in both cases
        for i, node_i in enumerate(node_subset):
            for j, node_j in enumerate(node_subset):
                self.assertEqual(full_dists[node_i, node_j], sub_dists[i, j])


if __name__ == "__main__":
    unittest.main()
