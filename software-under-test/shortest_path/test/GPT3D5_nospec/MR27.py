import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test27(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 27: Given the same graph, the same source and destination vertices, 
        if an edge with a very large weight is added, the shortest path should avoid that edge."""
        modified_graph = [row[:] for row in graph]
        modified_graph[src][dst] = 999999  # Adding a very large weight to an edge

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Get follow-up output
        follow_out = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(follow_out > source_out)


if __name__ == "__main__":
    unittest.main()
