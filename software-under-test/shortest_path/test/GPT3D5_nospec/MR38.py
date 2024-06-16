import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test38(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 38: Given the same graph, source and destination vertices,
        if we add a constant to the weight of all edges in the graph and then subtract the same constant, 
        the shortest path remains the same as the original shortest path."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding and then subtracting a constant from the edge weights
        constant = 5
        follow_graph = [[x - constant for x in row] for row in [[x + constant for x in row] for row in graph]]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
