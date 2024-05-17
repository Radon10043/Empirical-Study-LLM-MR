import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 33: Converting a directed graph to an undirected graph by making the edge weights
        symmetric should not increase any shortest path."""
        csgraph = csr_matrix(graph)

        # Make the csgraph symmetric by setting the weight of edge (i, j) equal to (j, i)
        num_vertices = csgraph.shape[0]
        symmetric_csgraph = csgraph.copy()

        for i in range(num_vertices):
            for j in range(num_vertices):
                if symmetric_csgraph[i, j] != symmetric_csgraph[j, i]:
                    updated_weight = min(symmetric_csgraph[i, j], symmetric_csgraph[j, i])
                    symmetric_csgraph[i, j] = updated_weight
                    symmetric_csgraph[j, i] = updated_weight

        # Get the original shortest path distances and the distances after making the csgraph symmetric
        original_distances = shortest_path(csgraph, directed=True)
        symmetric_distances = shortest_path(symmetric_csgraph, directed=False)

        # Check that shortest paths are not increased
        n = original_distances.shape[0]
        for i in range(n):
            for j in range(n):
                self.assertLessEqual(symmetric_distances[i, j], original_distances[i, j])


if __name__ == "__main__":
    unittest.main()
