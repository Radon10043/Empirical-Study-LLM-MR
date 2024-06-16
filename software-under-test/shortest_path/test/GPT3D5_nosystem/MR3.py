import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test3(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 3: Given the same graph with its predecessor matrix, the shortest path
        distances should be consistent with the predecessor matrix."""
        # Get source output with predecessors
        source_out, source_predecessors = shortest_path(graph, method=method, return_predecessors=True)

        # Get source output without predecessors
        source_out_without_predecessors = shortest_path(graph, method=method)

        # Verification
        for i in range(len(graph)):
            for j in range(len(graph)):
                if i != j:
                    # If there is a path from i to j
                    if source_out_without_predecessors[i][j] != np.inf:
                        path = get_shortest_path(source_predecessors, i, j)

                        # Calculate the distance using the reconstructed path
                        reconstructed_dist = 0
                        for k in range(len(path) - 1):
                            reconstructed_dist += graph[path[k]][path[k + 1]]

                        # Verify that the reconstructed distance matches the original distance
                        self.assertEqual(reconstructed_dist, source_out[i][j])


if __name__ == "__main__":
    unittest.main()
