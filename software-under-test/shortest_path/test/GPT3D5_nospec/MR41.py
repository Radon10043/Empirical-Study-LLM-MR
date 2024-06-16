import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test41(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 41: Given the same graph, source, and destination vertices,
        if we add a constant to the weight of a specific vertex, 
        the shortest path should reflect the addition of this constant to the specific vertex."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding a constant to the weight of a specific vertex
        constant = 5
        follow_graph = list(graph)
        follow_graph[dst][dst] += constant

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(modified_shortest_path, original_shortest_path + constant)


if __name__ == "__main__":
    unittest.main()
