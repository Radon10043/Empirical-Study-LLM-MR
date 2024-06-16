import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 34: Given the same graph, source and destination vertices,
        if the weights of all edges are scaled by a positive constant and the entire graph is shifted, 
        the shortest path should be impacted accordingly."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by scaling the weight of all edges by a positive constant and shifting the entire graph
        constant = 2
        shifted_graph = [[x + constant for x in row] for row in graph]
        follow_graph = [[x * constant for x in row] for row in shifted_graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(modified_shortest_path, constant * original_shortest_path + constant)


if __name__ == "__main__":
    unittest.main()
