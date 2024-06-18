import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test25(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 25: If the source and destination are swapped, the path cost should be the same
        for an undirected graph."""
        # Get the current shortest path weight
        shortest_path_cost_src_to_dst = shortest_path(graph, method=method, directed=False)[src][dst]

        # Get the current shortest path weight for the swapped source and destination
        shortest_path_cost_dst_to_src = shortest_path(graph, method=method, directed=False)[dst][src]

        # Verify the path cost remains the same when source and destination are swapped
        self.assertEqual(shortest_path_cost_src_to_dst, shortest_path_cost_dst_to_src)


if __name__ == "__main__":
    unittest.main()
