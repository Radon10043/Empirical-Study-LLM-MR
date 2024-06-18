import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test37(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 37: A path that includes a loop (returns to a previously visited node)
        cannot be the shortest path and thus should be longer than the shortest path calculated."""
        # Calculate the shortest path length from src to dst
        shortest_path_length = shortest_path(graph, method=method)[src][dst]

        # Create a path that includes a loop by returning to src and then going to dst
        # Assumption: graph[src][src] is set to a valid edge weight (self-loop)
        loop_path_length = shortest_path(graph, method=method)[src][src] + shortest_path_length

        # Verify that the loop path is not shorter than the direct shortest path
        self.assertGreater(loop_path_length, shortest_path_length)


if __name__ == "__main__":
    unittest.main()
