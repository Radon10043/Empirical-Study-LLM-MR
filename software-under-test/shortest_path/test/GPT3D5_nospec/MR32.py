import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test32(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 32: Given the same graph, source and destination vertices,
        if we scale the weight of all edges in the graph by a positive constant, 
        the shortest path should also be scaled by the same constant."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by scaling the weight of all edges by a positive constant
        constant = 5
        follow_graph = [[x * constant for x in row] for row in graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(modified_shortest_path, constant * original_shortest_path)


if __name__ == "__main__":
    unittest.main()
