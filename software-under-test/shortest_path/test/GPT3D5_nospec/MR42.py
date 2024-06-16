import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test42(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 42: Given the same graph, source, and destination vertices,
        if we remove a constant from the weight of a specific vertex, 
        the shortest path should reflect the removal of this constant from the specific vertex."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by removing a constant from the weight of a specific vertex
        constant = 3
        follow_graph = list(graph)
        follow_graph[src][src] -= constant

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(modified_shortest_path, original_shortest_path - constant)


if __name__ == "__main__":
    unittest.main()
