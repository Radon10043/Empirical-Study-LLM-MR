import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 33: Replacing all non-infinite weights with 1 should convert the graph to unweighted.
        The shortest path length from src to dst should then equal the fewest number of hops (edges) travelled."""
        # Convert graph to unweighted by replacing all non-infinite weights with 1
        unweighted_graph = [[1 if weight != float("inf") else float("inf") for weight in row] for row in graph]

        # Get the shortest path length from src to dst in the unweighted graph
        unweighted_path_length = shortest_path(unweighted_graph, src=src, dst=dst, method=method)[src][dst]

        # The path length should correspond to the number of edges (hops) in the shortest path,
        # Assuming get_path_hop_count is defined to count the number of edges in the shortest path
        hop_count = get_path_hop_count(graph, src=src, dst=dst, method=method)

        # Verification
        self.assertEqual(unweighted_path_length, hop_count)


if __name__ == "__main__":
    unittest.main()
