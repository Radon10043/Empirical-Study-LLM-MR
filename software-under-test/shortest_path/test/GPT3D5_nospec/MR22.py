import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test22(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 22: Given the same graph, source, and destination vertices,
        if we add a constant to the weight of every edge along a specific path, 
        the shortest path should increase by the same constant."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding a constant to the weight of every edge along a specific path
        constant = 10
        follow_graph = [[x + 5 for x in row] for row in graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path + constant, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
