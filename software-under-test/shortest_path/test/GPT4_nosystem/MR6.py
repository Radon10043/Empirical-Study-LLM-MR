import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test6(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 6: If return_predecessors is True, reconstructing the path from
        source to each node using predecessors should yield the same distances as the direct output."""
        # Get distances and predecessors
        dist_matrix, predecessors = shortest_path(graph, method=method, return_predecessors=True)

        # Verify the path reconstruction for each node from src
        for dst in range(len(graph)):
            if dst != src:
                path = [dst]
                while path[-1] != src:
                    pred = predecessors[src, path[-1]]
                    if pred == -9999:  # Invalid predecessor marker
                        break
                    path.append(pred)

                # Reversed path from src to destination
                path.reverse()
                if len(path) > 1:  # Valid path exists
                    reconstructed_distance = sum(graph[path[i]][path[i + 1]] for i in range(len(path) - 1))
                    self.assertEqual(dist_matrix[src][dst], reconstructed_distance)


if __name__ == "__main__":
    unittest.main()
