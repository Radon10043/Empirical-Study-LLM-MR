import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test18(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 18: Given the same graph with a loop on a vertex, the shortest path from that vertex to itself 
        should be 0, regardless of the method."""
        modified_graph = [row[:] for row in graph]
        modified_graph[src][src] = 0  # Adding a loop on the source vertex

        # Get source output
        source_out = shortest_path(graph, method=method)[src][src]

        # Verification
        self.assertEqual(source_out, 0)


if __name__ == "__main__":
    unittest.main()